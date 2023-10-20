#include <iostream>
#include <vector>

using namespace std;

// finds all the factors of a number and returns their sum
int solve(int n) {
	int sum = 0;
	for (int i = 1; i <= (n/2)+1; i++) {
		if (n % i == 0) {
			cout << "factor: " << i << endl;	
			sum += i;
		}
	}
	return sum;
}

vector<int> removeDuplicates(vector<int> v) {
	vector<int> newV;
	for (int i = 0; i < v.size(); i++) {
		bool found = false;
		for (int j = 0; j < newV.size(); j++) {
			if (v[i] == newV[j]) {
				found = true;
			}
		}
		if (!found) {
			newV.push_back(v[i]);
		}
	}
	return newV;
}

// find the maximum sum of a continuis subsequence of a vector
vector<int> maxSumSeq(vector<int> v) {
	
	int maxSum = 0;
	int subseqBeg, subseqEnd;
	int sum = 0;
	// using only 1 loop
	for (int i = 0; i < v.size(); i++) {
		sum += v[i];
		if (sum > maxSum) {
			maxSum = sum;
			subseqEnd = i;
		}
		if (sum < 0) {
			sum = 0;
			subseqBeg = i+1;
		}
	}
	vector<int> newV;
	for (int i = subseqBeg; i <= subseqEnd; i++) {
		newV.push_back(v[i]);
	}
	return newV;
}

int main() {
	std::vector<int> v;
	int x;
	while (std::cin >> x) {
		if (x == 0) {
			break;
		}
		v.push_back(x);
	}

	int sum = 0;
	vector<int> newV = maxSumSeq(v);
	for (int i = 0; i < newV.size(); i++) {
		cout << newV[i] << " ";
		sum += newV[i];
	}
	cout << "Max sum: " << sum << endl;
}