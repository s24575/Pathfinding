#include "Board.h"
#include <iostream>

Board::Board(sf::RenderWindow* window, int& width, int& height, int& tileSize, int& maze_width, int& maze_height, int& corridor_width)
    : window(window),
    xTiles(width),
    yTiles(height),
    tileSize(tileSize),
    maze_width(maze_width),
    maze_height(maze_height),
    corridor_width(corridor_width),
    graph(width, height)
{
    int startX, startY, finishX, finishY;

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

    start = &graph.getNode(startX, startY);
    finish = &graph.getNode(finishX, finishY);

    // squares
    for (int i = 0; i < xTiles * yTiles; ++i)
		tileMap.emplace_back(sf::Vector2f(tileSize, tileSize));
    
    for(int y = 0; y < yTiles; y++){
        for(int x = 0; x < xTiles; x++){
            tileMap[y * xTiles + x].setPosition(x * tileSize, y * tileSize);
            updateSquare(x, y);
        }
    }
}

void Board::createAlgorithm(int const& algorithm_type){
    if(algorithm_type == DFS) algorithm = std::make_unique<DepthFirstSearch>(&graph, &tileMap, start, finish);
    else if(algorithm_type == BFS) algorithm = std::make_unique<BreadthFirstSearch>(&graph, &tileMap, start, finish);
    else if(algorithm_type == DIJKSTRA) algorithm = std::make_unique<Dijkstra>(&graph, &tileMap, start, finish);
    else if(algorithm_type == ASTAR) algorithm = std::make_unique<AStar>(&graph, &tileMap, start, finish);

    current_algorithm_type = algorithm_type;
}

void Board::runAlgorithm(int const& n){
    if(algorithm && !algorithm->finished) algorithm->runAlgorithm(n);
}

void Board::editWall(sf::Vector2i const& pos){
    int x = pos.x / tileSize;
    int y = pos.y / tileSize;
    if(0 <= x && x < xTiles && 0 <= y && y < yTiles){
        if(placeWallState == 2){
            if(x != start->x || y != start->y){
                int startX = start->x;
                int startY = start->y;
                start = &graph.getNode(x, y);
                updateSquare(startX, startY);
                if(algorithm){
                    reset();
                    createAlgorithm(current_algorithm_type);
                    algorithm->runAlgorithm(xTiles * yTiles);
                }
            } 
        } else if(placeWallState == 3){
            if(x != finish->x || y != finish->y){
                int finishX = finish->x;
                int finishY = finish->y;
                finish = &graph.getNode(x, y);
                updateSquare(finishX, finishY);
                if(algorithm){
                    reset();
                    createAlgorithm(current_algorithm_type);
                    algorithm->runAlgorithm(xTiles * yTiles);
                }
            }
        } else {
            graph.getNode(x, y).obstacle = placeWallState;
        }
        
        updateSquare(x, y);
    }
}

void Board::checkWall(sf::Vector2i const& pos){
    int x = pos.x / tileSize;
    int y = pos.y / tileSize;
    if(0 <= x && x < xTiles && 0 <= y && y < yTiles){
        Node* node = &graph.getNode(x, y);
        if(node == start) placeWallState = 2;
        else if(node == finish) placeWallState = 3;
        else placeWallState = !node->obstacle;
    }
}

void Board::drawAllSquares() const{
    for (auto const& tile : tileMap){
        window->draw(tile);
    }
}

void Board::updateSquare(int const& x, int const& y){
    auto getColor = [&] (int const& x, int const& y){
        if(x == start->x && y == start->y) return Green;
        if(x == finish->x && y == finish->y) return Red;
        if(graph.getNode(x, y).obstacle) return Black;
        return Gray;
    };

    tileMap[y * xTiles + x].setFillColor(getColor(x, y));
}

void Board::reset(){
    for(auto& tile : tileMap){
        if(tile.getFillColor() != Black) tile.setFillColor(Gray);
    }
    tileMap[start->y * xTiles + start->x].setFillColor(Green);
    tileMap[finish->y * xTiles + finish->x].setFillColor(Red);
    graph.reset();
    algorithm.reset();
}

void Board::removeAllWalls(){
    for(int y = 0; y < yTiles; y++){
        for(int x = 0; x < xTiles; x++){
            graph.getNode(x, y).obstacle = false;
            updateSquare(x, y);
        }
    }
}

void Board::convertMazeToBoard(uint8_t* const maze){
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