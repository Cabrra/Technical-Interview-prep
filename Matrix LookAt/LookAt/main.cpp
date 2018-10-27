#include <iostream>

#include "float3.h"
#include "float4x4.h"

#include "../MatrixSolution/MatrixSolution.h"

using namespace std;

void main(void)
{
	MatrixSolution solution;
	Float4x4 the_dude, fancy_rug, front_door;

	// setup the entities for the scene
	cout << "Init\n";
	//solution.MatrixStep1Solution(the_dude, fancy_rug, front_door);
	the_dude.makeIdentity();
	the_dude.WAxis = Float3(-5.0f, 0.0f, 5.5f);

	fancy_rug.makeIdentity();
	fancy_rug.WAxis = Float3(3.0f, -1.0f, 2.5f);

	front_door.makeIdentity();
	front_door.WAxis = Float3(9.5f, 3.5f, -2.0f);

	solution.ValidateStep1(the_dude, fancy_rug, front_door);

	// look at how the rug ties the room together
	cout << "\nLook At\n";
	//solution.MatrixStep2Solution(the_dude, fancy_rug, front_door);

	Float3 zVector = fancy_rug.WAxis - the_dude.WAxis;
	zVector.normalize();

	Float3 xVector;
	CrossProduct(xVector, Float3(0.0f, 1.0f, 0.0f), zVector);
	xVector.normalize();

	Float3 yVector;
	CrossProduct(yVector, xVector, zVector);
	yVector.negate();

	the_dude.XAxis = xVector;
	the_dude.YAxis = yVector;
	the_dude.ZAxis = zVector;

	solution.ValidateStep2(the_dude, fancy_rug, front_door);

	// nihilists are knocking at the door, turn towards the door
	cout << "\nTurn To\n";
	//solution.MatrixStep3Solution(the_dude, fancy_rug, front_door);

	Float3 toTarget = front_door.WAxis - the_dude.WAxis;
	//toTarget.normalize();

	float dotX = DotProduct(toTarget, the_dude.XAxis);
	float dotY = DotProduct(toTarget, the_dude.YAxis);
	float spaceX = 1.0f;
	float spaceY = 1.0f;

	if (dotX < 0)
		spaceX = -spaceX;

	if (dotY > 0)
		spaceY = -spaceY;

	//Xrotate
	the_dude.rotateLocalX(spaceY);
	the_dude.ZAxis.normalize();

	//Yrotate
	the_dude.rotateLocalY(spaceX);
	the_dude.ZAxis.normalize();

	CrossProduct(xVector, Float3(0.0f, 1.0f, 0.0f), the_dude.ZAxis);
	xVector.normalize();

	CrossProduct(yVector, the_dude.ZAxis, xVector);
	yVector.normalize();

	the_dude.XAxis = xVector;
	the_dude.YAxis = yVector;
	
	solution.ValidateStep3(the_dude, fancy_rug, front_door);
	
	// move the dude to the door
	cout << "\nTranslate\n";
	//solution.MatrixStep4Solution(the_dude, fancy_rug, front_door);

	the_dude.WAxis += the_dude.ZAxis * 1.5f;

	solution.ValidateStep4(the_dude, fancy_rug, front_door);

	// grade
	cout << "\nLooks like your grade should be " << solution.GetGrade() << "\n\n";

	system("pause");
}
