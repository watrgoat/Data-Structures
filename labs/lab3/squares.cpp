#include <iostream>
#include <math.h>

bool computeSquares(unsigned int *inArray, unsigned int *outArray, unsigned int n) {
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
	unsigned int arr1[len] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	unsigned int arr2[len];

	computeSquares(arr1, arr2, len);

	unsigned int *p;
	p = arr2;
	for (int i=0;i<len;i++) {
		std::cout << *(p+i) << std::endl;
	}
}