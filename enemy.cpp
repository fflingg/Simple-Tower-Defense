#include "enemy.h"

#include <algorithm>
#include <iostream>

static std::vector<std::pair<int, int>> probe(int length, int width, int row,
                                              int col) {
    std::vector<std::pair<int, int>> directions;
    if (row > 0) {
        directions.push_back({-1, 0});  // Up
    }
    if (row < length - 1) {
        directions.push_back({1, 0});  // Down
    }
    if (col > 0) {
        directions.push_back({0, -1});  // Left
    }
    if (col < width - 1) {
        directions.push_back({0, 1});  // Right
    }
    return directions;
}

static int calDist(std::vector<std::vector<int>> map, int row, int col) {
    if (map[row][col] == 1) {
        return 0;  // already reached target
    } else if (map[row][col] == 0) {
        return map.size() * map[row].size();  // not on path
    }
    map[row][col] = 0;  // Mark the current cell as empty
    std::vector<std::pair<int, int>> directions =
        probe(map.size(), map[row].size(), row, col);
    int dist = map.size() * map[row].size();  // max distance possible
    for (auto dir : directions) {
        int next = map[row + dir.first][col + dir.second];  // next step
        if (next == 0) {
            continue;  // not on path
        } else if (next == 1) {
            return 1;  // one step away from target
        } else {       // still on path
            int nextDist = calDist(map, row + dir.first, col + dir.second);
            dist = nextDist < dist ? nextDist : dist;
        }
    }
    return dist + 1;
}

static std::pair<int, int> calFlow(std::vector<std::vector<int>> map, int row,
                                   int col) {
    std::vector<std::pair<int, int>> directions =
        probe(map.size(), map[row].size(), row, col);
    std::vector<int> distances;
    bool hasWayOut = false;
    for (auto dir : directions) {
        int dist = calDist(map, row + dir.first, col + dir.second);
        if (dist != map.size() * map[row].size()) {
            hasWayOut = true;
        }
        distances.push_back(dist);
    }
    if (!hasWayOut) {
        return {0, 0};  // No way out
    } else {
        return directions[std::min_element(distances.begin(), distances.end()) -
                          distances.begin()];
    }
}

std::vector<std::vector<std::pair<int, int>>> calculateFlowGrid(
    std::vector<std::vector<int>> map) {
    std::vector<std::vector<std::pair<int, int>>> flowGrid(
        map.size(), std::vector<std::pair<int, int>>(map[0].size(), {0, 0}));
    for (int r = 0; r < map.size(); r++) {
        for (int c = 0; c < map[r].size(); c++) {
            if (map[r][c] == 2) {
                flowGrid[r][c] = calFlow(map, r, c);
            }
        }
    }
    return flowGrid;
}

void updateEnemyPos(Enemy &enemy,
                    std::vector<std::vector<std::pair<int, int>>> &flowGrid) {
    std::pair<int, int> direction = flowGrid[enemy.row - 1][enemy.col - 1];
    enemy.row += direction.first;
    enemy.col += direction.second;
}

void printFlowGrid(
    const std::vector<std::vector<std::pair<int, int>>> &flowGrid) {
    std::cout << "Flow Grid:\n";
    for (int i = 0; i < flowGrid.size(); i++) {
        for (int j = 0; j < flowGrid[0].size(); j++) {
            std::pair<int, int> flow = flowGrid[i][j];
            if (flow == std::make_pair(0, -1)) {
                std::cout << "<";
            } else if (flow == std::make_pair(0, 1)) {
                std::cout << ">";
            } else if (flow == std::make_pair(-1, 0)) {
                std::cout << "^";
            } else if (flow == std::make_pair(1, 0)) {
                std::cout << "v";
            } else {
                std::cout << ".";
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}
