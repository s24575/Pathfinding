#include "Board.hpp"

Board::Board(sf::RenderWindow* _window)
    : _window(_window),
    graph(X_TILES, Y_TILES),
    squareMap(X_TILES, Y_TILES, TILE_SIZE)
{
    generateMaze();
}

void Board::generateMaze()
{
    int startX, startY, finishX, finishY;

    startX = (rand() % maze_width);
    startY = (rand() % maze_height);
    do {
        finishX = (rand() % maze_width);
        finishY = (rand() % maze_height);
    } while (finishX == startX && finishY == startY);

    graph.fullReset();
    MazeGenerator maze(maze_width, maze_height, startX, startY, finishX, finishY);
    convertMazeToBoard(maze.generateMaze());

    startX = startX * (corridor_width + 1) + 2;
    startY = startY * (corridor_width + 1) + 2;
    finishX = finishX * (corridor_width + 1) + 2;
    finishY = finishY * (corridor_width + 1) + 2;

    start = &graph.getNode(startX, startY);
    finish = &graph.getNode(finishX, finishY);

    for (int y = 0; y < yTiles; y++)
    {
        for (int x = 0; x < xTiles; x++)
        {
            updateSquareColor(x, y);
        }
    }
}

void Board::updateSettings(bool getAreDiagonalsEnabled, int graphWeight, distance_function distanceCalculation) {
    bool updateNeighbors = false;
    if (graph.getDiagonalEnabled() != getAreDiagonalsEnabled)
    {
        graph.setDiagonalEnabled(getAreDiagonalsEnabled);
        updateNeighbors = true;
    }
    if (graph.getWeight() != graphWeight)
    {
        graph.setWeight(graphWeight);
        updateNeighbors = true;
    }

    if (updateNeighbors)
    {
        graph.addNeighbors();
    }

    distanceFunction = distanceCalculation;
}

void Board::createAlgorithm(algorithm_type type){
    switch (type) {
    case algorithm_type::DFS:
        algorithm = std::make_unique<DepthFirstSearch>(&graph, &squareMap, start, finish, distanceFunction);
        break;
    case algorithm_type::BFS:
        algorithm = std::make_unique<BreadthFirstSearch>(&graph, &squareMap, start, finish, distanceFunction);
        break;
    case algorithm_type::DIJKSTRA:
        algorithm = std::make_unique<Dijkstra>(&graph, &squareMap, start, finish, distanceFunction);
        break;
    case algorithm_type::ASTAR:
        algorithm = std::make_unique<AStar>(&graph, &squareMap, start, finish, distanceFunction);
        break;
    }

    current_algorithm_type = type;
}

void Board::runAlgorithm(int n){
    if(algorithm && !algorithm->hasFinished())
        algorithm->runAlgorithm(n);
}

void Board::editWall(sf::Vector2i const& pos){
    int x = pos.x / tileSize;
    int y = pos.y / tileSize;
    if(0 <= x && x < xTiles && 0 <= y && y < yTiles){
        switch (placeWallType) {
        case WallType::START:
            if (x != start->x || y != start->y) {
                hasChanged = true;
                const int startX = start->x;
                const int startY = start->y;
                start = &graph.getNode(x, y);
                updateSquareColor(startX, startY);
            }
            break;
        case WallType::FINISH:
            if (x != finish->x || y != finish->y) {
                hasChanged = true;
                const int finishX = finish->x;
                const int finishY = finish->y;
                finish = &graph.getNode(x, y);
                updateSquareColor(finishX, finishY);
            }
            break;
        case WallType::EMPTY:
        case WallType::WALL:
            hasChanged = true;
            graph.getNode(x, y).obstacle = (bool)placeWallType;
            break;
        }
        
        updateSquareColor(x, y);
    }
}

void Board::checkWall(sf::Vector2i const& pos){
    int x = pos.x / tileSize;
    int y = pos.y / tileSize;
    if(0 <= x && x < xTiles && 0 <= y && y < yTiles){
        Node* node = &graph.getNode(x, y);
        if(node == start) placeWallType = WallType::START;
        else if(node == finish) placeWallType = WallType::FINISH;
        else placeWallType = static_cast<WallType>(!node->obstacle);
    }
}

void Board::drawAllSquares()
{
    _window->draw(squareMap);
}

sf::Color Board::getSquareColor(const int& x, const int& y)
{
    if (x == start->x && y == start->y) return squareMap.startColor;
    if (x == finish->x && y == finish->y) return squareMap.endColor;
    if (graph.getNode(x, y).obstacle) return squareMap.wallColor;
    return squareMap.emptyColor;
}

void Board::updateSquareColor(const int& x, const int& y)
{
    const sf::Color& color = getSquareColor(x, y);
    squareMap.setSquareColor(x, y, color);
}

void Board::reset(){
    for (int y = 0; y < yTiles; y++)
    {
        for (int x = 0; x < xTiles; x++)
        {
            updateSquareColor(x, y);
        }
    }
    graph.reset();
    algorithm.reset();
}

void Board::removeAllWalls(){
    for(int y = 0; y < yTiles; y++){
        for(int x = 0; x < xTiles; x++){
            graph.getNode(x, y).obstacle = false;
            updateSquareColor(x, y);
        }
    }
    graph.reset();
    algorithm.reset();
}

void Board::convertMazeToBoard(uint8_t* const maze){
    for(int i = 0; i < xTiles; i++)
        graph.getNode(i, 0).obstacle = true;
    for(int i = 1; i < yTiles; i++)
        graph.getNode(0, i).obstacle = true;
    
    for(int i = 0; i < maze_height; i++){
        for(int j = 0; j < maze_width; j++){
            graph.getNode((corridor_width + 1) * (j + 1), (corridor_width + 1) * (i + 1)).obstacle = true;

            if((maze[i * maze_width + j] & 2) == 0)
                for(int k = 0; k < corridor_width; k++)
                    graph.getNode((corridor_width + 1) * (j + 1), (corridor_width + 1) * i + 1 + k).obstacle = true;
            
            if((maze[i * maze_width + j] & 4) == 0)
                for(int k = 0; k < corridor_width; k++)
                    graph.getNode((corridor_width + 1) * j + 1 + k, (corridor_width + 1) * (i + 1)).obstacle = true;
        }
    }
}