#include "Graph.h"
#include "MazeGenerator.h"

Graph::Graph(int xTiles, int yTiles) : xTiles(xTiles), yTiles(yTiles){
    for(int y = 0; y < yTiles; y++){
        for(int x = 0; x < xTiles; x++){
            graph.emplace_back(x, y);

            // // add neighbors (top -> right -> bottom -> left)
            if(1 < y) graph[y * xTiles + x].neighbors.emplace_back(&graph[(y - 1) * xTiles + x]);
            if(x < xTiles - 1) graph[y * xTiles + x].neighbors.emplace_back(&graph[y * xTiles + x + 1]);
            if(y < yTiles - 1) graph[y * xTiles + x].neighbors.emplace_back(&graph[(y + 1) * xTiles + x]);
            if(1 < x) graph[y * xTiles + x].neighbors.emplace_back(&graph[y * xTiles + x - 1]);
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