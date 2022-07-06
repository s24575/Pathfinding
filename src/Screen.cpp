#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Pathfinding.h"
#include "MazeGenerator.h"

#include <iostream>
#include <chrono>
#include <thread>

int tile_counter = 0;

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

Screen::Screen(){
    maze_xTiles = 20;
    maze_yTiles = 20;
    maze_width = 3;

    xTiles = maze_xTiles * (maze_width + 1) + 1;
    yTiles = maze_yTiles * (maze_width + 1) + 1;
    tileSize = 8;

    window.create(sf::VideoMode(xTiles * tileSize + 1, yTiles * tileSize + 1), "Pathfinding algorithms");

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
    convertMazeToScreen(maze.generateMaze());

    startX = startX * (maze_width + 1) + 2;
    startY = startY * (maze_width + 1) + 2;
    finishX = finishX * (maze_width + 1) + 2;
    finishY = finishY * (maze_width + 1) + 2;
    
    board[startY][startX] = pf::Tile::Start;
    board[finishY][finishX] = pf::Tile::Finish;

    drawAllSquares();
}

Screen::~Screen(){}

void Screen::printAllSquares(){
    for(int i = 0; i < yTiles; i++){
        for(int j = 0; j < xTiles; j++){
            std::cout << '[' << board[i][j] << ']';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

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

    for(int i = 0; i < yTiles; i++){
        for(int j = 0; j < xTiles; j++){
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setPosition(j * tileSize, i * tileSize);
            tile.setFillColor(chooseColor(board[i][j]));
            window.draw(tile);
            tile_counter++;
        }
    }

    // lines
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(0, yTiles * tileSize + 1), sf::Color::Black),
        sf::Vertex(sf::Vector2f(xTiles * tileSize, yTiles * tileSize + 1), sf::Color::Black)};
    window.draw(line, 2, sf::Lines);
    for(int i = 0; i < yTiles; i++){
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, i * tileSize + 1), sf::Color::Black),
            sf::Vertex(sf::Vector2f(xTiles * tileSize, i * tileSize + 1), sf::Color::Black)};
        window.draw(line, 2, sf::Lines);
    }

    sf::Vertex line2[] = {
        sf::Vertex(sf::Vector2f(xTiles * tileSize + 1, 0), sf::Color::Black),
        sf::Vertex(sf::Vector2f(xTiles * tileSize + 1, yTiles * tileSize), sf::Color::Black)};
    window.draw(line2, 2, sf::Lines);
    for(int j = -1; j < xTiles; j++){
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(j * tileSize + 1, 0), sf::Color::Black),
            sf::Vertex(sf::Vector2f(j * tileSize + 1, yTiles * tileSize), sf::Color::Black)};
        window.draw(line, 2, sf::Lines);
    }

    window.display();
}

void Screen::reset(){
    for(int i = 0; i < yTiles; i++){
        for(int j = 0; j < xTiles; j++){
            if(board[i][j] != pf::Empty &&
                board[i][j] != pf::Wall &&
                board[i][j] != pf::Start &&
                board[i][j] != pf::Finish)
            {
                board[i][j] = pf::Empty;
            }
        }
    }
    drawAllSquares();
}

void Screen::updateSquare(int x, int y)
{
    sf::RectangleShape tile(sf::Vector2f(tileSize - 1, tileSize - 1));
    tile.setPosition(x * tileSize + 1, y * tileSize + 1);
    tile.setFillColor(chooseColor(board[y][x]));
    window.draw(tile);
    tile_counter++;
    window.display();
}

void Screen::placeWall(sf::Vector2i pos){
    int x = pos.x / tileSize;
    int y = pos.y / tileSize;
    if(x < 0 || xTiles <= x || y < 0 || yTiles <= y) return;
    if(board[y][x] == pf::Empty){
        board[y][x] = pf::Wall;
        updateSquare(x, y);
    }
}

void Screen::removeWall(sf::Vector2i pos){
    int x = pos.x / tileSize;
    int y = pos.y / tileSize;
    if(x < 0 || xTiles <= x || y < 0 || yTiles <= y) return;
    if (board[y][x] == pf::Wall){
        board[y][x] = pf::Empty;
        updateSquare(x, y);
    }
}

void Screen::convertMazeToScreen(uint8_t* maze){
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

void Screen::displayDepthFirstSearch(){
    Pathfinding dfs {board, xTiles, yTiles, {startX, startY}, {finishX, finishY}};
    std::vector<std::vector<int>> path (dfs.DepthFirstSearch());
    for(std::vector<int> cords : path){
        board[cords[1]][cords[0]] = cords[2];
        updateSquare(cords[0], cords[1]);
        std::chrono::milliseconds timespan(1);
        std::this_thread::sleep_for(timespan);
    }

    const auto map = dfs.getMap();

    std::pair<int,int> start {startX, startY};
    std::pair<int,int> finish {finishX, finishY};

    if (map.count(finish)){
        std::pair<int,int> cords {map.at(finish)};

        while(cords != start){
            board[cords.second][cords.first] = pf::Backtrack;
            updateSquare(cords.first, cords.second);
            cords = map.at(cords);
            std::chrono::milliseconds timespan(10);
            std::this_thread::sleep_for(timespan);
        }
    }
}

void Screen::displayBreadthFirstSearch(){
    Pathfinding bfs {board, xTiles, yTiles, {startX, startY}, {finishX, finishY}};
    std::vector<std::vector<int>> path (bfs.BreadthFirstSearch());
    for(std::vector<int> cords : path){
        board[cords[1]][cords[0]] = cords[2];
        updateSquare(cords[0], cords[1]);
        std::chrono::milliseconds timespan(1);
        std::this_thread::sleep_for(timespan);
    }

    const auto map = bfs.getMap();

    std::pair<int,int> start {startX, startY};
    std::pair<int,int> finish {finishX, finishY};

    if (map.count(finish)){
        std::pair<int,int> cords {map.at(finish)};

        while(cords != start){
            board[cords.second][cords.first] = pf::Backtrack;
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
            // std::cout << tile_counter << '\n';
        }
    }
}