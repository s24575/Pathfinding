#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <stack>
#include <vector>
#include <cstdint>

class MazeGenerator{
private:
    enum{
        UP =        0b00000001,
        RIGHT =     0b00000010,
        DOWN =      0b00000100,
        LEFT =      0b00001000,
        VISITED =   0b00010000
    };
    
    uint8_t* maze;

    const int xTiles = 0;
    const int yTiles = 0;

    const int startX = 0;
    const int startY = 0;
    const int finishX = 0;
    const int finishY = 0;

    std::stack<std::pair<int,int>> stack;
public:
    uint8_t* generateMaze();

    MazeGenerator(int xTiles, int yTiles, int startX, int startY, int finishX, int finishY);
    MazeGenerator(int xTiles, int yTiles);
};

#endif // MAZEGENERATOR_H