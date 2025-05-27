#ifndef ENEMY__H
#define ENEMY__H

#include <vector>
#include <utility>
#include <string>

class Enemy{
    public: 
        int health;
        std::string name;
        int row;
        int col;
};

//implement the calculation
void calculateFlowGrid (std::vector<std::vector<std::pair<int, int>>> &flowGrid,std::vector<std::vector<int>> map){

}

void updateEnemyPos(Enemy &enemy, std::vector<std::vector<std::pair<int, int>>> &flowGrid){
    std::pair<int, int> direction = flowGrid[enemy.row-1][enemy.col-1];
    enemy.row += direction.first;
    enemy.col += direction.second;
}

#endif