#include "Screen.h"
#include <iostream>

Screen::Screen(int width, int height, int tileSize, int maze_width, int maze_height, int corridor_width)
    : window(sf::VideoMode(width * tileSize, height * tileSize), "Pathfinding"),
      board(&window, width, height, tileSize, maze_width, maze_height, corridor_width){}

void Screen::run(){
    // sf::Clock clock;
    window.setFramerateLimit(60);
    board.drawAllSquares();
    window.display();
    while (window.isOpen()){
        // float time = 1.0f / clock.restart().asSeconds();
        // std::cout << time << " fps\n";
        // input
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();

            else if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape) window.close();
                else if(event.key.code == sf::Keyboard::R) board.reset();
                else if(event.key.code == sf::Keyboard::D) board.createDepthFirstSearch();
                else if(event.key.code == sf::Keyboard::B) board.createBreadthFirstSearch();
            }
            
            else if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left) leftPressed = true;
                else if(event.mouseButton.button == sf::Mouse::Right) rightPressed = true;
            }
            
            else if(event.type == sf::Event::MouseButtonReleased){
                if(event.mouseButton.button == sf::Mouse::Left) leftPressed = false;
                else if(event.mouseButton.button == sf::Mouse::Right) rightPressed = false;
            }

            if(leftPressed) board.placeWall(sf::Mouse::getPosition(window));
            else if(rightPressed) board.removeWall(sf::Mouse::getPosition(window));
        }

        // update
        board.runAlgorithm(5);

        // render
        window.clear();
        board.drawAllSquares();
        window.display();
    }
}