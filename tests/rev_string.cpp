#include <iostream>
#include <string>

void reverse(std::string &str, int i, int j) {
    if (i >= j) {
        return;
    }
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    reverse(str, i+1, j-1);
}

void reverse(std::string &str) {
    // front and back index
    reverse(str, 0, str.size()-1);
}

int main() {
    std::string word = "WORD";
    reverse(word);
    std::cout << word << std::endl; 
}