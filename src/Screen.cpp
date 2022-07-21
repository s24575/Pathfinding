#include "Screen.h"
#include <stdio.h>

Screen::Screen(int width, int height, int tileSize, int maze_width, int maze_height, int corridor_width)
    : window(sf::VideoMode(width * tileSize, height * tileSize), "Pathfinding"),
      board(&window, width, height, tileSize, maze_width, maze_height, corridor_width){}

void Screen::run(){
    sf::Clock clock;
    float deltaTime;
    int const framerate {60};
    window.setFramerateLimit(framerate);
    while (window.isOpen()){
        deltaTime = 1.0f / clock.restart().asSeconds();
        if(deltaTime < framerate - 1)
            printf("%.2f\n", deltaTime);
        
        // input
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();

            else if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape) window.close();
                else if(event.key.code == sf::Keyboard::R) board.reset();
                else if(event.key.code == sf::Keyboard::Q) board.removeAllWalls();
                else if(event.key.code == sf::Keyboard::D) board.createAlgorithm(DFS);
                else if(event.key.code == sf::Keyboard::B) board.createAlgorithm(BFS);
                else if(event.key.code == sf::Keyboard::I) board.createAlgorithm(DIJKSTRA);
                else if(event.key.code == sf::Keyboard::A) board.createAlgorithm(ASTAR);
            }
            
            else if(event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased){
                if(event.mouseButton.button == sf::Mouse::Left){
                    leftPressed = !leftPressed;
                    board.checkWall(sf::Mouse::getPosition(window));
                }
            }

            if(leftPressed) board.editWall(sf::Mouse::getPosition(window));
        }

        // update
        board.runAlgorithm(5);

        // render
        window.clear();
        board.drawAllSquares();
        window.display();
    }
}