#include <iostream>
#include <vector>

#include "enemy.h"

using namespace std;

const int gridRow = 20;
const int gridColumn = 20;

void viewMap(vector<vector<int>> map, Enemy enemy) {
    for (int i = 0; i < gridRow; ++i) {
        for (int j = 0; j < gridColumn; ++j) {
            if (i == enemy.row - 1 && j == enemy.col - 1) {
                cout << "e ";
            } else if (map[i][j] == 0) {
                cout << "- ";
            } else if (map[i][j] == 1) {
                cout << "# ";
            } else if (map[i][j] == 2) {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

extern const IntField gridMap;

int main() {
    Enemy fool(9, 20, 0, "");

    viewMap(gridMap, fool);
    for (int i = 0; i < 20; ++i) {
        std::cout << "\nAfter move " << i << ":\n";
        fool.move();
        viewMap(gridMap, fool);
    }

    fool.printFlowGrid();
    return 0;
}
