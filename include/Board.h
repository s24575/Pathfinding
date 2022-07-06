#pragma once

#include "MazeGenerator.h"

namespace pf{
    enum Tile {
        Empty,
        Wall,
        Start,
        Finish,
        Processed,
        Visited,
        Backtrack
    };
}

class Board{
private:
    int** board;

    int xTiles;
    int yTiles;

    int maze_xTiles;
    int maze_yTiles;
    int maze_width;

    int startX;
    int startY;
    int finishX;
    int finishY;

    void placeWall(int x, int y);
    void removeWall(int x, int y);
    void convertMazeToBoard(uint8_t* maze);
public:
    Board();
    Board(int x, int y);
    // Board(const Board& other);
    // ~Board();
    void run();

    inline int** getBoard(){ return board; };
    inline int getxTiles(){ return xTiles; };
    inline int getyTiles(){ return yTiles; };
    inline std::pair<int,int> getStart(){ return {startX, startY}; };
    inline std::pair<int,int> getFinish(){ return {finishX, finishY}; };
};