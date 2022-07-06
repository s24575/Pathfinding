#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include "Screen.h"
#include "Pathfinding.h"

int Screen::tile_counter = 0;

Screen::Screen(){
    tileSize = 64;
    board = Board {2, 2};
    xTiles = board.getxTiles();
    yTiles = board.getyTiles();

    window.create(sf::VideoMode(xTiles * tileSize + 1, yTiles * tileSize + 1), "Pathfinding algorithms");
    drawAllSquares();
}

Screen::~Screen(){}

sf::Color chooseColor(int state){
    switch(state){
        case pf::Empty:
            return sf::Color{50, 50, 50};
        case pf::Wall:
            return sf::Color::Black;
        case pf::Start:
            return sf::Color::Green;
        case pf::Finish:
            return sf::Color::Red;
        case pf::Visited:
            return sf::Color::Yellow;
        case pf::Processed:
            return sf::Color::White;
        case pf::Backtrack:
            return sf::Color::Blue;
        default:
            return sf::Color::Magenta;
    }
}

void Screen::drawAllSquares(){
    window.clear();
    // draw squares
    for(int i = 0; i < yTiles; i++){
        for(int j = 0; j < xTiles; j++){
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setPosition(j * tileSize, i * tileSize);
            tile.setFillColor(chooseColor(board.getBoard()[i][j]));
            window.draw(tile);
            Screen::tile_counter++;
        }
    }

    // draw vertical lines
    for(int i = 0; i < yTiles; i++){
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, i * tileSize + (i > 0)), sf::Color::Black),
            sf::Vertex(sf::Vector2f(xTiles * tileSize, i * tileSize + (i > 0)), sf::Color::Black)};
        window.draw(line, 2, sf::Lines);
    }
    // draw horizontal lines
    for(int i = 0; i < xTiles; i++){
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(i * tileSize + (i > 0), 0), sf::Color::Black),
            sf::Vertex(sf::Vector2f(i * tileSize + (i > 0), yTiles * tileSize), sf::Color::Black)};
        window.draw(line, 2, sf::Lines);
    }

    window.display();
}

void Screen::reset(){
    window.clear();
    for(int i = 0; i < yTiles; i++){
        for(int j = 0; j < xTiles; j++){
            if(board.getBoard()[i][j] != pf::Empty &&
                board.getBoard()[i][j] != pf::Wall &&
                board.getBoard()[i][j] != pf::Start &&
                board.getBoard()[i][j] != pf::Finish)
            {
                board.getBoard()[i][j] = pf::Empty;
            }
        }
    }
    drawAllSquares();
}

void Screen::updateSquare(int x, int y){
    sf::RectangleShape tile(sf::Vector2f(tileSize - 1, tileSize - 1));
    tile.setPosition(x * tileSize + 1, y * tileSize + 1);
    tile.setFillColor(chooseColor(board.getBoard()[y][x]));
    window.draw(tile);
    Screen::tile_counter++;
    window.display();
}

void Screen::placeWall(sf::Vector2i pos){
    int x = pos.x / tileSize;
    int y = pos.y / tileSize;
    if(x < 0 || xTiles <= x || y < 0 || yTiles <= y) return;
    if(board.getBoard()[y][x] == pf::Empty){
        board.getBoard()[y][x] = pf::Wall;
        updateSquare(x, y);
    }
}

void Screen::removeWall(sf::Vector2i pos){
    int x = pos.x / tileSize;
    int y = pos.y / tileSize;
    if(x < 0 || xTiles <= x || y < 0 || yTiles <= y) return;
    if (board.getBoard()[y][x] == pf::Wall){
        board.getBoard()[y][x] = pf::Empty;
        updateSquare(x, y);
    }
}

void Screen::displayDepthFirstSearch(){
    std::pair<int,int> start = board.getStart();
    std::pair<int,int> finish = board.getFinish();

    Pathfinding dfs {board.getBoard(), xTiles, yTiles, start, finish};
    std::vector<std::vector<int>> path (dfs.DepthFirstSearch());
    for(std::vector<int> cords : path){
        board.getBoard()[cords[1]][cords[0]] = cords[2];
        updateSquare(cords[0], cords[1]);
        std::chrono::milliseconds timespan(1);
        std::this_thread::sleep_for(timespan);
    }

    const auto map = dfs.getMap();

    if (map.count(finish)){
        std::pair<int,int> cords {map.at(finish)};

        while(cords != start){
            board.getBoard()[cords.second][cords.first] = pf::Backtrack;
            updateSquare(cords.first, cords.second);
            cords = map.at(cords);
            std::chrono::milliseconds timespan(10);
            std::this_thread::sleep_for(timespan);
        }
    }
}

void Screen::displayBreadthFirstSearch(){
    std::pair<int,int> start = board.getStart();
    std::pair<int,int> finish = board.getFinish();

    Pathfinding bfs {board.getBoard(), xTiles, yTiles, start, finish};
    std::vector<std::vector<int>> path (bfs.BreadthFirstSearch());
    for(std::vector<int> cords : path){
        board.getBoard()[cords[1]][cords[0]] = cords[2];
        updateSquare(cords[0], cords[1]);
        std::chrono::milliseconds timespan(1);
        std::this_thread::sleep_for(timespan);
    }

    const auto map = bfs.getMap();

    if (map.count(finish)){
        std::pair<int,int> cords {map.at(finish)};

        while(cords != start){
            board.getBoard()[cords.second][cords.first] = pf::Backtrack;
            updateSquare(cords.first, cords.second);
            cords = map.at(cords);
            std::chrono::milliseconds timespan(10);
            std::this_thread::sleep_for(timespan);
        }
    }
}

void Screen::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        if (window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::R:
                    reset();
                    break;
                case sf::Keyboard::D:
                    displayDepthFirstSearch();
                    break;
                case sf::Keyboard::B:
                    displayBreadthFirstSearch();
                    break;
                    
                default:
                    break;
                }
                break;
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left) {
                    isLeftPressed = true;
                    placeWall(sf::Mouse::getPosition(window));
                }
                else if(event.mouseButton.button == sf::Mouse::Right){
                    isRightPressed = true;
                    removeWall(sf::Mouse::getPosition(window));
                }
                break;
            case sf::Event::MouseButtonReleased:
                if(event.mouseButton.button == sf::Mouse::Left) isLeftPressed = false;
                if(event.mouseButton.button == sf::Mouse::Right) isRightPressed = false;
                break;
            case sf::Event::MouseMoved: {
                if(isLeftPressed) placeWall(sf::Mouse::getPosition(window));
                if(isRightPressed) removeWall(sf::Mouse::getPosition(window));
                break;
            }
            default:
                break;
            }
            // std::cout << Screen::tile_counter << '\n';
        }
    }
}