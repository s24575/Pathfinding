#include "MazeGenerator.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <bitset>

MazeGenerator::MazeGenerator(int xTiles, int yTiles, int startX, int startY, int finishX, int finishY)
: xTiles(xTiles), yTiles(yTiles), startX(startX), startY(startY), finishX(finishX), finishY(finishY){
    maze = new uint8_t[xTiles * yTiles] {0};
}

MazeGenerator::MazeGenerator(int xTiles, int yTiles) : xTiles(xTiles), yTiles(yTiles) {
    maze = new uint8_t[xTiles * yTiles] {0};
}

uint8_t* MazeGenerator::generateMaze(){
    stack.push({startX, startY});
    maze[startY * xTiles + startX] = VISITED;
    int visited_count = 1;

    auto offset = [&](int x, int y){
        return (stack.top().second + y) * xTiles + (stack.top().first + x);
    };

    while(visited_count < xTiles * yTiles){
        std::vector<uint8_t> surrounding;

        if (stack.top().second > 0 && (maze[offset(0, -1)] & VISITED) == 0)
			surrounding.push_back(UP);
		if (stack.top().first < xTiles - 1 && (maze[offset(1, 0)] & VISITED) == 0)
			surrounding.push_back(RIGHT);
		if (stack.top().second < yTiles - 1 && (maze[offset(0, 1)] & VISITED) == 0)
			surrounding.push_back(DOWN);
		if (stack.top().first > 0 && (maze[offset(-1, 0)] & VISITED) == 0)
			surrounding.push_back(LEFT);

        if(surrounding.empty()) stack.pop();
        else {
            uint8_t next_cell_dir = surrounding[rand() % surrounding.size()];

            switch (next_cell_dir)
            {
            case UP:
                maze[offset(0, -1)] |= VISITED | DOWN;
                maze[offset(0, 0)] |= UP;
                stack.push({stack.top().first + 0, stack.top().second - 1});
                break;

            case RIGHT:
                maze[offset(+1, 0)] |= VISITED | LEFT;
                maze[offset(0, 0)] |= RIGHT;
                stack.push({stack.top().first + 1, stack.top().second + 0});
                break;

            case DOWN:
                maze[offset(0, +1)] |= VISITED | UP;
                maze[offset(0, 0)] |= DOWN;
                stack.push({stack.top().first + 0, stack.top().second + 1});
                break;

            case LEFT:
                maze[offset(-1, 0)] |= VISITED | RIGHT;
                maze[offset(0, 0)] |= LEFT;
                stack.push({stack.top().first - 1, stack.top().second + 0});
                break;
            }
            visited_count++;
        }
    }
    return maze;
}