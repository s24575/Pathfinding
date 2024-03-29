#ifndef GRAPH_H
#define GRAPH_H

#include <cmath>
#include <vector>

enum class WallType {
    EMPTY,
    WALL,
    START,
    FINISH
};

struct Node{
    Node(int x, int y) : x(x), y(y) {}

    int x, y;
    // WallType type = WallType::EMPTY;
    bool obstacle = false;
    bool visited = false;
    Node* previous = nullptr;
    float h_cost = INFINITY;
    float g_cost = INFINITY;
    std::vector<Node*> neighbors;
};

class Graph{
public:
    Graph(int x, int y);
    void addNeighbors();
    Node& getNode(int x, int y);
    void reset();
    void fullReset();

    bool getDiagonalEnabled() const { return diagonalEnabled; }
    void setDiagonalEnabled(bool diagonal) { diagonalEnabled = diagonal; }
    int getWeight() const { return weight; }
    void setWeight(int new_weight) { weight = new_weight; }
    
    int xTiles;
    int yTiles;
private:
    std::vector<Node> graph;
    bool diagonalEnabled = false;
    int weight = 1;
};

#endif // GRAPH_H