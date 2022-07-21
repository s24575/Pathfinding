#pragma once

#include <stack>
#include "Pathfinding.h"

class DepthFirstSearch : public Pathfinding{
public:
    DepthFirstSearch(Graph* graph, std::vector<sf::RectangleShape>* TileMap, Node* start, Node* finish);

    bool runAlgorithm(int const& n) override;

private:
    std::stack<Node*> stack;
    
    void runBacktrack();
};