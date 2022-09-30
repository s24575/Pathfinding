#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

// #include <utility>
#include <stack>
#include <vector>

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

    int xTiles = -1;
    int yTiles = -1;

    int startX = -1;
    int startY = -1;
    int finishX = -1;
    int finishY = -1;

    std::stack<std::pair<int,int>> stack;
public:
    uint8_t* generateMaze();

    MazeGenerator(int xTiles, int yTiles, int startX, int startY, int finishX, int finishY);
    MazeGenerator(int xTiles, int yTiles);
};

#endif // MAZEGENERATOR_H