#include "Board.h"
#include <iostream>

Board::Board(){}

Board::Board(int x, int y) : maze_xTiles(x), maze_yTiles(y){
    maze_width = 3;

    xTiles = maze_xTiles * (maze_width + 1) + 1;
    yTiles = maze_yTiles * (maze_width + 1) + 1;

    board = new int * [yTiles];
    for(int i = 0; i < yTiles; i++){
        board[i] = new int[xTiles];
        for(int j = 0; j < xTiles; j++){
            board[i][j] = pf::Tile::Empty;
        }
    }

    srand(time(NULL));
    startX = (rand() % maze_xTiles);
    startY = (rand() % maze_yTiles);
    do {
        finishX = (rand() % maze_xTiles);
        finishY = (rand() % maze_yTiles);
    } while (finishX == startX && finishY == startY);

    MazeGenerator maze {maze_xTiles, maze_yTiles, startX, startY, finishX, finishY};
    convertMazeToBoard(maze.generateMaze());

    startX = startX * (maze_width + 1) + 2;
    startY = startY * (maze_width + 1) + 2;
    finishX = finishX * (maze_width + 1) + 2;
    finishY = finishY * (maze_width + 1) + 2;

    board[startY][startX] = pf::Tile::Start;
    board[finishY][finishX] = pf::Tile::Finish;
}

// Board::Board(const Board& other){}

// Board::~Board(){
//     for(int i = 0; i < yTiles; i++){
//         delete board[i];
//     }
//     delete board;
// }

void Board::convertMazeToBoard(uint8_t* maze){
    for(int i = 0; i < xTiles; i++)
        board[0][i] = pf::Wall;
    for(int i = 0; i < yTiles; i++)
        board[i][0] = pf::Wall;
    
    for(int i = 0; i < maze_yTiles; i++){
        for(int j = 0; j < maze_xTiles; j++){
            board[(maze_width + 1) * (i + 1)][(maze_width + 1) * (j + 1)] = pf::Wall;

            if((maze[i * maze_xTiles + j] & 2) == 0)
                for(int i2 = 0; i2 < maze_width; i2++)
                    board[(maze_width + 1) * i + 1 + i2][(maze_width + 1) * (j + 1)] = pf::Wall;
            
            if((maze[i * maze_xTiles + j] & 4) == 0)
                for(int i2 = 0; i2 < maze_width; i2++)
                    board[(maze_width + 1) * (i + 1)][(maze_width + 1) * j + 1 + i2] = pf::Wall;
        }
    }
}