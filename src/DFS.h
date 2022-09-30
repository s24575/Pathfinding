#ifndef DFS_H
#define DFS_H

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

#endif // DFS_H