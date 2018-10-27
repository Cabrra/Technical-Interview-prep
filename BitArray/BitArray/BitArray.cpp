#include "BitArray.h"
#include "../BitArraySolutions/BitArraySolutions.h"

#define NUM_OF_BITS 32
// Assignment operator
BitArray& BitArray::operator=(const BitArray& _rhs)
{
	for (int i = 0; i < _rhs.size; i++)
	{
		for (int j = 0; j < NUM_OF_BITS; j++)
		{
			this->bit_array[i] = _rhs.bit_array[i];
		}
	}

	return *this;
}

// find the number of bits on in the bit vector (hamming weight)
unsigned int BitArray::Population()
{
	int pop = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < NUM_OF_BITS; j++)
		{
			if (bit_array[i] & (1 << j))
				pop++;
		}
	}

	return pop;
}

// turns a specified bit on or off
void BitArray::Set(unsigned int _bit, bool _value)
{
	if ((unsigned int)size * NUM_OF_BITS > _bit)
	{
		int index = _bit / NUM_OF_BITS;
		if (_value == true)
			bit_array[index] |= (1 << _bit);
		else
			bit_array[index] &= ~(1 << _bit);
	}
}

// creates an array large enough to hold _Size bits
void BitArray::Init(unsigned int _num_bits)
{
	size = _num_bits / NUM_OF_BITS;
	if (size == 0)
		size = 1;
	//check if is bigger
	if ((unsigned int)size * NUM_OF_BITS < _num_bits)
		size++;

	bit_array = new int[size];

}

// all to 0
void BitArray::ClearAll()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < NUM_OF_BITS; j++)
		{
			bit_array[i] &= ~(1 << j);
		}
	}
}

// all to 1
void BitArray::SetAll()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < NUM_OF_BITS; j++)
		{
			bit_array[i] |= (1 << j);
		}
	}
}
