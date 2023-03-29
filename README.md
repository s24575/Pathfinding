# Pathfinding Visualizer

Interactive visualization of 4 most popular pathfinding algorithms:

- DepthFirstSearch
- BreadthFirstSearch
- Dijkstra's
- A\*

## Example

<p align="center">
	<img src="images/pathfinding_example.PNG" alt="Example image" width="768"/>
</p>

## How to compile

```
mkdir build
cd build
cmake ..
cmake --build .
./src/imgui-sfml-example # Linux
.\src\Debug\imgui-sfml-example.exe # Windows
```

## Dependencies

CMake >= 3.24

In case you're on Linux, you'll need to install dependencies for building SFML
specified [here](https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php#installing-dependencies).
