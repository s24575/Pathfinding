#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Graph.h"
#include <utility>
#include <vector>

class Pathfinding{
public:
    Pathfinding(Graph* graph, std::vector<sf::RectangleShape>* TileMap, Node* start, Node* finish)
        : graph(graph), TileMap(TileMap), start(start), finish(finish) {}

    virtual ~Pathfinding() {}

    virtual bool runAlgorithm(int const& n) = 0;
        
    bool finished;
protected:
    Graph* graph;
    std::vector<sf::RectangleShape>* TileMap;

    Node* current;
    Node* start;
    Node* finish;

};