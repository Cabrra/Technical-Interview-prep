#include <iostream>

#include "BitArray.h"
#include "../BitArraySolutions/BitArraySolutions.h"

using namespace std;

int main(void)
{
	const int NUM_TESTS = 5;
	const int num_bits[NUM_TESTS] = { 32, 64, 15, 55, 12345 };
	int result[NUM_TESTS];

	for (int i = 0; i < NUM_TESTS; i++)
	{
		cout << "\n--- Testing Bit Array with " << num_bits[i] << " bits --------\n";
		cout << "Testing Init function\n";
		BitArray bits1(num_bits[i]);
		BitArraySolutions::GetRef().VerifyInit(num_bits[i]);

		cout << "\nTesting Set function\n";
		BitArraySolutions::GetRef().VerifySet(num_bits[i]);

		cout << "\nTesting Population function\n";
		BitArraySolutions::GetRef().VerifyPopulation(num_bits[i]);

		cout << "\nTesting Clear function\n";
		BitArraySolutions::GetRef().VerifyClear(num_bits[i]);

		cout << "\nTesting Set All function\n";
		BitArraySolutions::GetRef().VerifySetAll(num_bits[i]);

		cout << "\nTesting Copy function\n";
		BitArraySolutions::GetRef().VerifyCopy(num_bits[i]);

		result[i] = BitArraySolutions::GetRef().GetGrade();
		BitArraySolutions::GetRef().ResetCheck();
	}

	cout << "\n\nTesting done, lets check the result.\n";

	for (int i = 0; i < NUM_TESTS; i++)
	{
		cout << "For test of " << num_bits[i] << " bits, the result looks like " << result[i] << "% \n";
	}

	cout << "\n\n";

	system("pause");
	return 0;
}
