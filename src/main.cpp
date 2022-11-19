#include "Screen.h"

int main()
{
    srand((unsigned int)time(0));

    const unsigned int screen_width = sf::VideoMode::getDesktopMode().width;
    const unsigned int screen_height = sf::VideoMode::getDesktopMode().height;

    constexpr int maze_width = 50;
    constexpr int maze_height = 50;
    constexpr int corridor_width = 3;

    constexpr int width = maze_width * (corridor_width + 1) + 1;
    constexpr int height = maze_height * (corridor_width + 1) + 1;
    const int tileSize = std::min(screen_width / width, screen_height / height);
    
    Screen screen(width, height, tileSize, maze_width, maze_height, corridor_width);
    screen.run();
}