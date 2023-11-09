#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

// Starting with any positive integer, replace the number by the sum of the squares of its digits.
// Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
// Those numbers for which this process ends in 1 are happy.
// how to determine if a number is going to infinitely loop?
// if a number is going to infinitely loop, then it will eventually repeat a number
#include <unordered_map>

class ListNode {
public:
    int value;
    ListNode *next;
    ListNode(int x) : value(x), next(nullptr) {}
};

class HashTable {
private:
    vector<ListNode*> table;  // table should store pointers to ListNode
    int hashFunction(int key) const {
        return key % table.size();
    }

public:
    HashTable(int size) : table(size, nullptr) {}  // Initialize table with nullptrs

    ~HashTable() {
        for (ListNode* head : table) {
            while (head != nullptr) {
                ListNode* temp = head;
                head = head->next;
                delete temp;
            }
        }
    }

    bool insert(int key) {
        // insert key into hash table
        int index = hashFunction(key);
        ListNode* &head = table[index];  // Reference to pointer

        ListNode* node = head;
        while (node != nullptr) {
            if (node->value == key) {
                return false;  // Key already exists
            }
            node = node->next;
        }

        ListNode* newNode = new ListNode(key);
        newNode->next = head;
        head = newNode;
        return true;
    }

    ListNode* search(int key) const {
        // search for key in hash table
        int index = hashFunction(key);
        ListNode* node = table[index];

        while (node != nullptr) {
            if (node->value == key) {
                return node;
            }
            node = node->next;
        }
        return nullptr;
    }
};

bool isHappy3(int n, HashTable& seen) {
    if (n == 1) {
        return true;
    }
    if (seen.search(n)) {
        return false;
    }
    seen.insert(n);

    int sum = 0;
    int digit;

    while (n > 0) {
        digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }

    return isHappy3(sum, seen);
}

bool isHappy3(int n) {
    HashTable seen(100); // 100 is arbitrary, ideally should be based on expected range of input
    return isHappy3(n, seen);
}

bool isHappy2(int n, std::unordered_map<int, bool> &seen) {
    if (n == 1) {
        return true;
    }
    if (seen.find(n) != seen.end()) {
        return false;
    }

    seen[n] = false;

    std::vector<int> digits;
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }

    int sum = 0;
    for (int digit : digits) {
        sum += digit * digit;
    }
    
    return isHappy2(sum, seen);
}

bool isHappy2(int n) {
    unordered_map<int, bool> seen;
    return isHappy2(n, seen);
}

bool isHappy1(int n, std::unordered_set<int> &seen) {
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

    return isHappy1(sum, seen);
}

bool isHappy1(int n) {
    unordered_set<int> seen;
    return isHappy1(n, seen);
}

int main() {
	// Test cases
	// 2, 4, 5, 6, 17, 18, 20 are not happy numbers.
	// 1, 7, 10, 13, 19, 23, 28, 68 are happy numbers.

    int testCases[] = {2,4,5,6,17,18,20,1,7,10,13,19,23,28,68};

    for (int n : testCases) {
        if (isHappy3(n)) {
            std::cout << n << " is a happy number." << std::endl;
        } else {
            std::cout << n << " is not a happy number." << std::endl;
        }
    }

    return 0;
}
