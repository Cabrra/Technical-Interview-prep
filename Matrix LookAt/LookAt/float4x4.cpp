#include "Float4x4.h"
#include <algorithm>

Float4x4::Float4x4( float xx, float xy, float xz, float xw,
    float yx, float yy, float yz, float yw,
    float zx, float zy, float zz, float zw,
    float wx, float wy, float wz, float ww)
{
    Xx = xx; Xy = xy; Xz = xz; Xw = xw;
    Yx = yx; Yy = yy; Yz = yz; Yw = yw;
    Zx = zx; Zy = zy; Zz = zz; Zw = zw;
    Wx = wx; Wy = wy; Wz = wz; Ww = ww;
}

Float4x4 &Float4x4::makeZero()
{
    Xx = Xy = Xz = Xw = 
        Yx = Yy = Yz = Yw = 
        Zx = Zy = Zz = Zw = 
        Wx = Wy = Wz = Ww = 0;    
    return *this;
}

Float4x4 &Float4x4::makeIdentity()
{
    Xy = Xz = Xw = 
        Yx = Yz = Yw = 
        Zx = Zy = Zw = 
        Wx = Wy = Wz = 0;  

    Xx = Yy = Zz = Ww = 1;
    return *this;
}
Float4x4 &Float4x4::makeRotationX(float radians)
{
    float sinAngle = sin(radians);
    float cosAngle = cos(radians);

    Xx = 1;     Xy = 0;         Xz = 0;         Xw = 0;
    Yx = 0;     Yy = cosAngle;  Yz = sinAngle;  Yw = 0;
    Zx = 0;     Zy = -sinAngle; Zz = cosAngle;  Zw = 0;
    Wx = 0;     Wy = 0;         Wz = 0;         Ww = 1;

    return *this;
}

Float4x4 &Float4x4::makeRotationY(float radians)
{
    float sinAngle = sin(radians);
    float cosAngle = cos(radians);

    Xx = cosAngle;  Xy = 0; Xz = -sinAngle; Xw = 0;
    Yx = 0;         Yy = 1; Yz = 0;         Yw = 0;
    Zx = sinAngle;  Zy = 0; Zz = cosAngle;  Zw = 0;
    Wx = 0;         Wy = 0; Wz = 0;         Ww = 1;
    return *this;
}

Float4x4 &Float4x4::makeRotationZ(float radians)
{
    float sinAngle = sin(radians);
    float cosAngle = cos(radians);

    Xx = cosAngle;  Xy = sinAngle;  Xz = 0; Xw = 0;
    Yx = -sinAngle; Yy = cosAngle;  Yz = 0; Yw = 0;
    Zx = 0;         Zy = 0;         Zz = 1; Zw = 0;
    Wx = 0;         Wy = 0;         Wz = 0; Ww = 1;
    return *this;
}

Float4x4 &Float4x4::makeScale(float xScale, float yScale, float zScale)
{
    Xy = Xz = Xw = 
        Yx = Yz = Yw = 
        Zx = Zy = Zw = 
        Wx = Wy = Wz = 0;  

    Xx = xScale;
    Yy = yScale;
    Zz = zScale;
    Ww = 1;
    return *this;
}

Float4x4 &Float4x4::makePerspectiveLH(float fFov, float fAspect, 
    float fNear, float fFar)
{
	float yScale = 1.0f / tan(fFov/2);
	float xScale = yScale / fAspect;

    makeIdentity();
	m[0][0] = xScale;
	m[1][1] = yScale;
	m[2][2] = fFar/(fFar-fNear);
	m[3][2] = -fNear * fFar/(fFar-fNear);
	m[2][3] = 1;
	m[3][3] = 0;
    return *this;
}

void Multiply(Float4x4 &out, const Float4x4 &a, const Float4x4 &b)
{
    out.Xx = a.Xx * b.Xx + a.Xy * b.Yx + a.Xz * b.Zx + a.Xw * b.Wx;
    out.Xy = a.Xx * b.Xy + a.Xy * b.Yy + a.Xz * b.Zy + a.Xw * b.Wy;
    out.Xz = a.Xx * b.Xz + a.Xy * b.Yz + a.Xz * b.Zz + a.Xw * b.Wz;
    out.Xw = a.Xx * b.Xw + a.Xy * b.Yw + a.Xz * b.Zw + a.Xw * b.Ww;

    out.Yx = a.Yx * b.Xx + a.Yy * b.Yx + a.Yz * b.Zx + a.Yw * b.Wx;
    out.Yy = a.Yx * b.Xy + a.Yy * b.Yy + a.Yz * b.Zy + a.Yw * b.Wy;
    out.Yz = a.Yx * b.Xz + a.Yy * b.Yz + a.Yz * b.Zz + a.Yw * b.Wz;
    out.Yw = a.Yx * b.Xw + a.Yy * b.Yw + a.Yz * b.Zw + a.Yw * b.Ww;

    out.Zx = a.Zx * b.Xx + a.Zy * b.Yx + a.Zz * b.Zx + a.Zw * b.Wx;
    out.Zy = a.Zx * b.Xy + a.Zy * b.Yy + a.Zz * b.Zy + a.Zw * b.Wy;
    out.Zz = a.Zx * b.Xz + a.Zy * b.Yz + a.Zz * b.Zz + a.Zw * b.Wz;
    out.Zw = a.Zx * b.Xw + a.Zy * b.Yw + a.Zz * b.Zw + a.Zw * b.Ww;

    out.Wx = a.Wx * b.Xx + a.Wy * b.Yx + a.Wz * b.Zx + a.Ww * b.Wx;
    out.Wy = a.Wx * b.Xy + a.Wy * b.Yy + a.Wz * b.Zy + a.Ww * b.Wy;
    out.Wz = a.Wx * b.Xz + a.Wy * b.Yz + a.Wz * b.Zz + a.Ww * b.Wz;
    out.Ww = a.Wx * b.Xw + a.Wy * b.Yw + a.Wz * b.Zw + a.Ww * b.Ww;
}

Float4x4 &Float4x4::rotateLocalX(float radians)
{
    Float4x4 temp = *this;
    Multiply(*this, Float4x4().makeRotationX(radians), temp);
    return *this;
}

Float4x4 &Float4x4::rotateLocalY(float radians)
{
    Float4x4 temp = *this;
    Multiply(*this, Float4x4().makeRotationY(radians), temp);
    return *this;
}

Float4x4 &Float4x4::rotateLocalZ(float radians)
{
    Float4x4 temp = *this;
    Multiply(*this, Float4x4().makeRotationZ(radians), temp);
    return *this;
}

Float4x4 &Float4x4::rotateGlobalX(float radians)
{
    Float4x4 temp = *this;
    Multiply(*this, temp, Float4x4().makeRotationX(radians));
    return *this;
}

Float4x4 &Float4x4::rotateGlobalY(float radians)
{
    Float4x4 temp = *this;
    Multiply(*this, temp, Float4x4().makeRotationY(radians));
    return *this;
}

Float4x4 &Float4x4::rotateGlobalZ(float radians)
{
    Float4x4 temp = *this;
    Multiply(*this, temp, Float4x4().makeRotationZ(radians));
    return *this;
}

Float4x4 &Float4x4::translateGlobal(float x, float y, float z)
{
    WAxis.x += x;
    WAxis.y += y;
    WAxis.z += z;
    return *this;
}

Float4x4 &Float4x4::scale(const Float3 &scaleVec)
{
    return scale(scaleVec.x, scaleVec.y, scaleVec.z);
}

Float4x4 &Float4x4::scale(float x, float y, float z)
{
    XAxis *= x;
    YAxis *= y;
    ZAxis *= z;
    return *this;
}

Float4x4 &Float4x4::scale(float scalar)
{
    XAxis *= scalar;
    YAxis *= scalar;
    ZAxis *= scalar;
    return *this;
}

Float4x4 &Float4x4::transpose(void)
{
    std::swap(Xy, Yx);
    std::swap(Xz, Zx);
    std::swap(Yz, Zy);

    std::swap(Wx, Xw);
    std::swap(Wy, Yw);
    std::swap(Wz, Zw);
    return *this;
}

Float4x4 &Float4x4::transpose3x3(void)
{
    std::swap(Xy, Yx);
    std::swap(Xz, Zx);
    std::swap(Yz, Zy);
    return *this;
}

void TransformVector(Float3 &out, const Float3 &inVec,
    const Float4x4 &inMat)
{
	Float3 vectorIn = inVec;

    out.x = inMat.Xx * vectorIn.x + inMat.Yx * vectorIn.y + 
        inMat.Zx * vectorIn.z;
    out.y = inMat.Xy * vectorIn.x + inMat.Yy * vectorIn.y + 
        inMat.Zy * vectorIn.z;
    out.z = inMat.Xz * vectorIn.x + inMat.Yz * vectorIn.y + 
        inMat.Zz * vectorIn.z;
}

void TransformPoint(Float3 &out, const Float3 &inVec,
    const Float4x4 &inMat)
{
	Float3 vectorIn = inVec;

	out.x = inMat.Xx * vectorIn.x + inMat.Yx * vectorIn.y + 
        inMat.Zx * vectorIn.z + inMat.Wx;
    out.y = inMat.Xy * vectorIn.x + inMat.Yy * vectorIn.y + 
        inMat.Zy * vectorIn.z + inMat.Wy;
    out.z = inMat.Xz * vectorIn.x + inMat.Yz * vectorIn.y + 
        inMat.Zz * vectorIn.z + inMat.Wz;
}

void InvTransformVector(Float3 &out, const Float3 &inVec,
    const Float4x4 &inMat)
{
	out = Float3(	DotProduct( inVec, inMat.XAxis ),
				DotProduct( inVec, inMat.YAxis ),
				DotProduct( inVec, inMat.ZAxis ) );
}

void InvTransformPoint(Float3 &out, const Float3 &inVec,
    const Float4x4 &inMat)
{
	InvTransformVector( out, inVec - inMat.WAxis, inMat );
}

Float3 Float4x4::getScale(void) const
{
    return Float3(XAxis.magnitude(), YAxis.magnitude(), ZAxis.magnitude());
}

void Float4x4::TransformVector(Float3 &vector)
{
	Float3 vectorIn = vector;
	vector.x = Xx * vectorIn.x + Yx * vectorIn.y + 
		Zx * vectorIn.z;
	vector.y = Xy * vectorIn.x + Yy * vectorIn.y + 
		Zy * vectorIn.z;
	vector.z = Xz * vectorIn.x + Yz * vectorIn.y + 
		Zz * vectorIn.z;
}

void Float4x4::TransformPoint(Float3 &vector)
{
	Float3 vectorIn = vector;
	vector.x = Xx * vectorIn.x + Yx * vectorIn.y + 
		Zx * vectorIn.z + Wx;
	vector.y = Xy * vectorIn.x + Yy * vectorIn.y + 
		Zy * vectorIn.z + Wy;
	vector.z = Xz * vectorIn.x + Yz * vectorIn.y + 
		Zz * vectorIn.z + Wz;
}

void Float4x4::InvTransformVector(Float3 &vector)
{
	vector = Float3( DotProduct( vector, XAxis ),
				DotProduct( vector, YAxis ),
				DotProduct( vector, ZAxis ) );
}

void Float4x4::InvTransformPoint(Float3 &vector)
{
	vector -= WAxis;
	InvTransformVector( vector );
}