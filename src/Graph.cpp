#include "Graph.h"

Graph::Graph(int xTiles, int yTiles) : xTiles(xTiles), yTiles(yTiles){
    graph.reserve(xTiles * yTiles);
    for(int y = 0; y < yTiles; y++){
        for(int x = 0; x < xTiles; x++){
            graph.emplace_back(x, y);
        }
    }

    addNeighbors();
}

void Graph::addNeighbors() {
    for (int y = 0; y < yTiles; y++) {
        for (int x = 0; x < xTiles; x++) {
            auto& neighbors = getNode(x, y).neighbors;
            neighbors.clear();

            // add neighbors (top -> right -> bottom -> left)
            if (0 < y) neighbors.emplace_back(&getNode(x, y - 1));
            if (x < xTiles - 1) neighbors.emplace_back(&getNode(x + 1, y));
            if (y < yTiles - 1) neighbors.emplace_back(&getNode(x, y + 1));
            if (0 < x) neighbors.emplace_back(&getNode(x - 1, y));

            // add neighbors (TL -> TR -> BR -> BL)
            if (diagonalEnabled) {
                if (0 < x && 0 < y) neighbors.emplace_back(&getNode(x - 1, y - 1));
                if (x < xTiles - 1 && 0 < y) neighbors.emplace_back(&getNode(x + 1, y - 1));
                if (x < xTiles - 1 && y < yTiles - 1) neighbors.emplace_back(&getNode(x + 1, y + 1));
                if (0 < x && y < yTiles - 1) neighbors.emplace_back(&getNode(x - 1, y + 1));
            }
        }
    }
}

Node& Graph::getNode(int x, int y){
    return graph[y * xTiles + x];
}

void Graph::reset(){
    for(Node& node : graph){
        node.visited = false;
        node.previous = nullptr;
        node.h_cost = INFINITY;
        node.g_cost = INFINITY;
    }
}

void Graph::fullReset() {
    for (Node& node : graph) {
        node.obstacle = false;
        node.visited = false;
        node.previous = nullptr;
        node.h_cost = INFINITY;
        node.g_cost = INFINITY;
    }
}