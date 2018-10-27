#ifndef _BITARRAY_SOLUTIONS_H_
#define _BITARRAY_SOLUTIONS_H_

class BitArray;

class BitArraySolutions
{
private:

	int grade;
	char dummy_bytes[10];

	bool BitArrayCheck(BitArray* _a, BitArray* _b);

	BitArraySolutions(void);
	~BitArraySolutions(void);

public:

	static BitArraySolutions& GetRef();

	unsigned int PopulationSolution(BitArray* _bits);
	void VerifyPopulation(int _num_bits);

	void InitSolution(BitArray* _bits, int _num_bits);
	void VerifyInit(int _num_bits);

	void ClearSolution(BitArray* _bits);
	void VerifyClear(int _num_bits);

	void SetAllSolution(BitArray* _bits);
	void VerifySetAll(int _num_bits);

	void SetSolution(BitArray* _bits, int _which_bit, bool _val);
	void VerifySet(int _num_bits);

	void CopySolution(BitArray* _bits, const BitArray& _rhs);
	void VerifyCopy(int _num_bits);

	void UsingSolution(char* _func);

	int GetGrade();
	void ResetCheck();
};

#endif
