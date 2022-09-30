#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
//#include <cmath>
//#define INFINITY ((float)(1e+300 * 1e+300))

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
    
    int xTiles;
    int yTiles;
private:
    std::vector<Node> graph;
};

#endif // GRAPH_H