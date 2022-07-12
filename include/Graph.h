#pragma once

#include <vector>
#include <cmath>

struct Node{
    Node(int x, int y) : x(x), y(y) {}

    int x, y;
    bool obstacle = false;
    bool visited = false;
    Node* previous = nullptr;
    double h_cost = INFINITY;
    double g_cost = INFINITY;
    std::vector<Node*> neighbors;
};

class Graph{
public:
    Graph(int x, int y);
    Node& getNode(int x, int y);
    void reset();
private:
    std::vector<Node> graph;
    int xTiles;
    int yTiles;
};