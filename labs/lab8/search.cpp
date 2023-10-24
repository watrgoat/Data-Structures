#include <iostream>

using namespace std;

/*
Now, write a simple recursive program (from scratch) that reads a starting location, (x, y)
and returns the total number of different paths back to the origin when the entire grid is “free”.
Two paths are different if there is at least one step on the path that is different even if most of the steps are the same.
As a hint, when x == 0 and y == 0 there is 1 path, when x == 2 and y == 1 there are 3 paths, and when x == 2 and y == 2 there are 6 paths.
When you’re confident your program is debugged try even bigger values. For what values does the program take a few seconds to complete on your computer?
If you increase these values by 1, how does it impact the running time? Is this what you expected from Big O Notation?
*/

int solve(int x, int y) {
    if (x == 0 && y == 0) {
        return 1;
    }
    int sum = 0;
    if (x > 0) {
        sum += solve(x-1, y);
    }
    if (y > 0) {
        sum += solve(x, y-1);
    }
    return sum;
}

int main() {
    int x, y;
    cin >> x >> y;

    // print the empty grid
    for (int i = 0; i < x+1; i++) {
        for (int j = 0; j < y+1; j++) {
            cout << " .";
        }
        cout << endl;
    }
    
    cout << "num paths: " << solve(x, y) << endl;
}