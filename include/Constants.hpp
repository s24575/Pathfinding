#pragma once

// Maze
constexpr int MAZE_WIDTH = 50;
constexpr int MAZE_HEIGHT = 50;
constexpr int MAZE_CORRIDOR_WIDTH = 3;
constexpr int X_TILES = MAZE_WIDTH * (MAZE_CORRIDOR_WIDTH + 1) + 1;
constexpr int Y_TILES = MAZE_HEIGHT * (MAZE_CORRIDOR_WIDTH + 1) + 1;
constexpr int TOTAL_TILES = X_TILES * Y_TILES;

constexpr int SOLVE_TIME = 5;

// Screen
constexpr unsigned FRAMERATE = 60;
constexpr char WINDOW_NAME[] = "Pathfinding";
constexpr int TILE_SIZE = 5;
constexpr int SCREEN_WIDTH = X_TILES * TILE_SIZE;
constexpr int SCREEN_HEIGHT = Y_TILES * TILE_SIZE;