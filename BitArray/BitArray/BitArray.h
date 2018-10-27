#ifndef _BIT_ARRAY_H_
#define _BIT_ARRAY_H_

#define BITS_PER_INT		32
#define BYTES_PER_INT		4
#define BITS_PER_BYTE		8

class BitArray
{
private:

	// array pointer
	int* bit_array;
	
	// how many integers are in the array
	unsigned short int size;

public:

	friend class BitArraySolutions;

	BitArray(unsigned int _num_bits);
	~BitArray();

	// Accessor
	inline unsigned int GetSize() const		{ return size; }
	inline unsigned int GetBytes() const	{ return size * BYTES_PER_INT; }
	inline unsigned int GetBits() const		{ return size * BYTES_PER_INT * BITS_PER_BYTE; }

	// creates an array large enough to hold _num_bits bits
	void Init(unsigned int _num_bits);

	// find the number of bits that are on (hamming weight)
	unsigned int Population();

	// turns a specified bit on or off
	void Set(unsigned int _bit, bool _value);

	// set all to 0
	void ClearAll();

	// set all to 1
	void SetAll();

	// copy the right hand side
	BitArray& operator=(const BitArray& _rhs);
};

#endif
