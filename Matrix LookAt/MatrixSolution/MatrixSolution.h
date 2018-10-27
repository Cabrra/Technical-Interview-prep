#ifndef _MATRIX_SOLUTION_H_
#define _MATRIX_SOLUTION_H_

#include "../LookAt/float4x4.h"

class MatrixSolution
{
private:
	char dummy_bytes[8];
	bool FuzzyCheck(Float4x4& _a, Float4x4& _b, float _tolerance = 0.01f);

public:
	MatrixSolution(void);
	~MatrixSolution(void);

	void ValidateStep1(Float4x4& _dude, Float4x4& _rug, Float4x4& _door);
	void ValidateStep2(Float4x4& _dude, Float4x4& _rug, Float4x4& _door);
	void ValidateStep3(Float4x4& _dude, Float4x4& _rug, Float4x4& _door);
	void ValidateStep4(Float4x4& _dude, Float4x4& _rug, Float4x4& _door);

	void MatrixStep1Solution(Float4x4& _dude, Float4x4& _rug, Float4x4& _door, char* _invoker = nullptr);
	void MatrixStep2Solution(Float4x4& _dude, Float4x4& _rug, Float4x4& _door, char* _invoker = nullptr);
	void MatrixStep3Solution(Float4x4& _dude, Float4x4& _rug, Float4x4& _door, char* _invoker = nullptr, bool _flip = false);
	void MatrixStep4Solution(Float4x4& _dude, Float4x4& _rug, Float4x4& _door, char* _invoker = nullptr);

	int GetGrade();
};

#endif
