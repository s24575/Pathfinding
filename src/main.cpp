#include "Screen.h"

int main()
{
    srand(time(0));

    unsigned int const screen_width = sf::VideoMode::getDesktopMode().width;
    unsigned int const screen_height = sf::VideoMode::getDesktopMode().height;

    int constexpr maze_width = 19;
    int constexpr maze_height = 10;
    int constexpr corridor_width = 3;

    int constexpr width = maze_width * (corridor_width + 1) + 1;
    int constexpr height = maze_height * (corridor_width + 1) + 1;
    int const tileSize = std::min(screen_width / width, screen_height / height);
    
    Screen screen(width, height, tileSize, maze_width, maze_height, corridor_width);
    screen.run();
}