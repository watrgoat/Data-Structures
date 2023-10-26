#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    int arr[11] = {19, 83, -12, 83, 65, 19, 45, -12, 45, 19, 45};
    map<int, int> m;

    // using map find and insert instead of map[]
    for (int i = 0; i < 11; i++) {
        map<int, int>::iterator it = m.find(arr[i]);
        if (it == m.end()) {
            m.insert(pair<int, int>(arr[i], 1));
        } else {
            it->second++;
        }
    }

    // get max modes
    int max = 0;
    vector<int> vals;
    for (auto it = m.begin(); it != m.end(); it++) {
        if (it->second > max) {
            max = it->second;
            vals.clear();
            vals.push_back(it->first);
        } else if (it->second == max) {
            vals.push_back(it->first);
        }
    }

    // print max modes
    for (int i = 0; i < vals.size(); i++) {
        cout << vals[i] << " ";
    }
    cout << endl;
}