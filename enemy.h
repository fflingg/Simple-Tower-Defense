#ifndef ENEMY__H
#define ENEMY__H

#include <string>
#include <vector>

using VecField = std::vector<std::vector<std::pair<int, int>>>;

class Enemy {
   private:
    static VecField flowGrid;

   public:
    int health;
    std::string name;
    int row;
    int col;
};

// return a flow grid based on given map
// pair indicates the direction of enemy should move on path
// (0, 0) for off path
VecField calculateFlowGrid(std::vector<std::vector<int>> map);

void updateEnemyPos(Enemy &enemy, VecField &flowGrid);

// print the flow grid
// < left
// > right
// ^ up
// v down
// . off path
void printFlowGrid(const VecField &flowGrid);

#endif  // ENEMY__H
