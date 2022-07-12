#include "Screen.h"

int main()
{
    srand(time(0));

    int constexpr screen_width = 1280;
    int constexpr screen_height = 720 - 60;

    int constexpr maze_width = 19;
    int constexpr maze_height = 10;
    int constexpr corridor_width = 3;

    int width = maze_width * (corridor_width + 1) + 1;
    int height = maze_height * (corridor_width + 1) + 1;
    int tileSize;

    if(screen_width / width > screen_height / height)
        tileSize = screen_height / height;
    else
        tileSize = screen_width / width;
    
    Screen screen(width, height, tileSize, maze_width, maze_height, corridor_width);
    screen.run();

    return 0;
}

// to do:
// Dijkstra
// BestFS
// A*
// add diagonal