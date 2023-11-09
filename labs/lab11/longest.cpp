#include <iostream>
#include <vector>

using namespace std;

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

int longestConsecutive(std::vector<int>& nums) {
    int size = nums.size();
    // If the vector is empty, return 0
    if(size == 0){
        return 0;
    }
    
    HashTable table(size);

    // Insert all the elements into the hash table
    for(int i=0; i<size; i++){
        table.insert(nums[i]);
    }

    int max = 1;
    // Search for the longest consecutive sequence
    for(int i=0; i<size; i++){
        int count = 1;
        int num = nums[i];

        // Search for the next consecutive number
        ListNode* node = table.search(num);

        // If the next consecutive number exists, increment the count
        while(node != nullptr){
            num++;
            node = table.search(num);
            if(node != nullptr){
                count++;
            }
        }
        // If the count is greater than the max, update the max
        if(count > max){
            max = count;
        }
    }
    return max;
}

int main() {
	//std::vector<int> nums = {100, 4, 200, 1, 3, 2};
	//std::vector<int> nums = {100, 4, 200, 1, 3, 2, 2, 2, 2, 3};
	//std::vector<int> nums = {100, 4, 200, 1, 3, 2, 5, 6};
	//std::vector<int> nums = {0,3,7,2,5,8,4,6,0,1};
	//std::vector<int> nums = {100, 4, 200, 201, 202, 203, 205, 204, 1, 3, 2};
	std::vector<int> nums = {-3,0,1,2,3,-2,-1,-5};
	int size = nums.size();
	std::cout<< "for vector {";
	for(int i=0;i<size-1;i++){
		std::cout<< nums[i] << ",";
	}
	std::cout<< nums[size-1] << "}" <<std::endl;
	int length = longestConsecutive(nums);
	std::cout << "The length of the longest consecutive sequence is: " << length << std::endl;
	return 0;
}