#include <iostream>
#include <math.h>

bool computeSquares(const unsigned int (&inArray)[], unsigned int (&outArray)[], unsigned int n) {
	unsigned int *inp;
	unsigned int *outp;
	inp=inArray;
	outp=outArray;
	unsigned int i;
	for (i=0;i<n;i++) {
		*(outp+i) = pow(*(inp+i), 2);
	}
	return true;
}

int main() {
	// test cases: n = 10
	unsigned int len = 10;
	unsigned int arr1[len];
	unsigned int arr2[len];
	for (int i=0;i<len;i++) {
		std::cout << i << std::endl;
			}
	computeSquares(arr1, arr2, len);
	for (int i=0;i<len;i++) {
		std::cout << arr2[i] << std::endl;
	}
}