#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef std::vector<std::string> DonutBox;

void findBoxes(const DonutBox& box, DonutBox& current_box, std::vector<DonutBox>& boxes) {
    if (current_box.size() == box.size()) {
        boxes.push_back(current_box);
        return;
    }
    for (const std::string &donut : box) {
        if (std::find(current_box.begin(), current_box.end(), donut) == current_box.end()) {
            current_box.push_back(donut);
            findBoxes(box, current_box, boxes);
            current_box.pop_back();
        }
    }
}

// solution (trash)
/*
void findBoxes(const DonutBox& box, DonutBox& current_box, std::vector<DonutBox>& boxes){
    if(box.empty()){
        boxes.push_back(current_box);
        return;
    }
    for(unsigned int i=0; i<box.size(); i++){
        DonutBox tmp_box = box;
        current_box.push_back(box[i]);
        tmp_box.erase(tmp_box.begin()+i);
        findBoxes(tmp_box, current_box, boxes);
        current_box.pop_back();
    }
}
*/

void findBoxes(const DonutBox& box, std::vector<DonutBox>& boxes) {
    DonutBox tmp;
    findBoxes(box, tmp, boxes);
}

void printDonutBox(const DonutBox& box) {
    for (const std::string &donut : box) {
        std::cout << donut << " ";
    }
    std::cout << std::endl;
}

void printDonutBoxes(const std::vector<DonutBox>& boxes) {
    for (const DonutBox &box : boxes) {
        printDonutBox(box);
        std::cout << std::endl;
    }
}

int main() {
    DonutBox donuts;
    std::vector<DonutBox> boxes;
    donuts.push_back("strawberry"); donuts.push_back("chocolate"); donuts.push_back("maple");

    findBoxes(donuts, boxes);

    printDonutBoxes(boxes);
}
