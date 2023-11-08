#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>



using namespace std;

// Starting with any positive integer, replace the number by the sum of the squares of its digits.
// Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
// Those numbers for which this process ends in 1 are happy.
// how to determine if a number is going to infinitely loop?
// if a number is going to infinitely loop, then it will eventually repeat a number
#include <unordered_map>
#include <vector>
#include <string>

bool isHappy2(int n, std::unordered_map<int, bool> &seen) {
    if (n == 1) {
        return true;
    }
    if (seen.find(n) != seen.end()) {
        return seen[n];
    }

    std::vector<int> digits;
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }

    int sum = 0;
    for (int digit : digits) {
        sum += digit * digit;
    }

    seen[n] = isHappy2(sum, seen);  // Store the result of the sum
    return seen[n];
}

bool isHappy2(int n) {
    unordered_map<int, bool> seen;
    return isHappy2(n, seen);
}

bool isHappy(int n, std::unordered_set<int> &seen) {
    if (n == 1) {
        return true;
    }
    if (seen.find(n) != seen.end()) {
        return false;
    }

    seen.insert(n);

    std::vector<int> digits;
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }

    // sum the squares
    int sum = 0;
    for (int digit : digits) {
        sum += digit * digit;
    }

    return isHappy(sum, seen);
}

bool isHappy(int n) {
    unordered_set<int> seen;
    return isHappy(n, seen);
}

int main() {
	// Test cases
	// 2, 4, 5, 6, 17, 18, 20 are not happy numbers.
	// 1, 7, 10, 13, 19, 23, 28, 68 are happy numbers.

    int testCases[] = {2,4,5,6,17,18,20,1,7,10,13,19,23,28,68};

    for (int n : testCases) {
        if (isHappy(n)) {
            std::cout << n << " is a happy number." << std::endl;
        } else {
            std::cout << n << " is not a happy number." << std::endl;
        }
    }

    return 0;
}
