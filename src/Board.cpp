#include "Board.h"
#include <iostream>

Board::Board(sf::RenderWindow* window, int width, int height, int tileSize, int maze_width, int maze_height, int corridor_width)
    : window(window),
    xTiles(width),
    yTiles(height),
    tileSize(tileSize),
    maze_width(maze_width),
    maze_height(maze_height),
    corridor_width(corridor_width),
    graph(width, height)
{
    startX = (rand() % maze_width);
    startY = (rand() % maze_height);
    do {
        finishX = (rand() % maze_width);
        finishY = (rand() % maze_height);
    } while (finishX == startX && finishY == startY);

    MazeGenerator maze {maze_width, maze_height, startX, startY, finishX, finishY};
    convertMazeToBoard(maze.generateMaze());

    startX = startX * (corridor_width + 1) + 2;
    startY = startY * (corridor_width + 1) + 2;
    finishX = finishX * (corridor_width + 1) + 2;
    finishY = finishY * (corridor_width + 1) + 2;

    // squares
    for (int i = 0; i < xTiles * yTiles; ++i)
		tileMap.emplace_back(sf::Vector2f(tileSize, tileSize));
    
    for(int y = 0; y < yTiles; y++){
        for(int x = 0; x < xTiles; x++){
            tileMap[y * xTiles + x].setPosition(x * tileSize, y * tileSize);
            tileMap[y * xTiles + x].setFillColor(getColor(x, y));
        }
    }
}

void Board::createDepthFirstSearch(){
     algorithm = std::make_unique<DepthFirstSearch>(&graph, &tileMap, xTiles, yTiles, std::pair<int,int> {startX, startY}, std::pair<int,int> {finishX, finishY});
}

void Board::createBreadthFirstSearch(){
    algorithm = std::make_unique<BreadthFirstSearch>(&graph, &tileMap, xTiles, yTiles, std::pair<int,int> {startX, startY}, std::pair<int,int> {finishX, finishY});
}

void Board::runAlgorithm(int n){
    if(algorithm && algorithm->runAlgorithm(n)) algorithm.reset();
}

void Board::placeWall(sf::Vector2i pos){
    int x = pos.x / tileSize;
    int y = pos.y / tileSize;
    if(0 <= x || x < xTiles || 0 <= y || y < yTiles){
        if(!graph.getNode(x, y).obstacle){
            graph.getNode(x, y).obstacle = true;
            updateSquare(x, y);
        }
    }
}

void Board::removeWall(sf::Vector2i pos){
    int x = pos.x / tileSize;
    int y = pos.y / tileSize;
    if(0 <= x || x < xTiles || 0 <= y || y < yTiles){
        if(graph.getNode(x, y).obstacle){
            graph.getNode(x, y).obstacle = false;
            updateSquare(x, y);
        }
    }
}

sf::Color& Board::getColor(int x, int y){
    if(x == startX && y == startY) return Green;
    if(x == finishX && y == finishY) return Red;
    if(graph.getNode(x, y).obstacle) return Black;
    return Gray;
}

void Board::drawAllSquares(){
    for (const sf::RectangleShape& tile : tileMap){
        window->draw(tile);
    }
}

void Board::updateSquare(int x, int y){
    tileMap[y * xTiles + x].setFillColor(getColor(x, y));
}

void Board::reset(){
    for(sf::RectangleShape& tile : tileMap){
        if(tile.getFillColor() != Black) tile.setFillColor(Gray);
    }
    tileMap[startY * xTiles + startX].setFillColor(Green);
    tileMap[finishY * xTiles + finishX].setFillColor(Red);
    graph.reset();
    algorithm.reset();
}

void Board::convertMazeToBoard(uint8_t* maze){
    for(int i = 0; i < xTiles; i++)
        graph.getNode(i, 0).obstacle = true;
    for(int i = 0; i < yTiles; i++)
        graph.getNode(0, i).obstacle = true;
    
    for(int i = 0; i < maze_height; i++){
        for(int j = 0; j < maze_width; j++){
            graph.getNode((corridor_width + 1) * (j + 1), (corridor_width + 1) * (i + 1)).obstacle = true;

            if((maze[i * maze_width + j] & 2) == 0)
                for(int i2 = 0; i2 < corridor_width; i2++)
                    graph.getNode((corridor_width + 1) * (j + 1), (corridor_width + 1) * i + 1 + i2).obstacle = true;
            
            if((maze[i * maze_width + j] & 4) == 0)
                for(int i2 = 0; i2 < corridor_width; i2++)
                    graph.getNode((corridor_width + 1) * j + 1 + i2, (corridor_width + 1) * (i + 1)).obstacle = true;
        }
    }
}