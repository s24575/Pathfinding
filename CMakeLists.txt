cmake_minimum_required (VERSION 3.16)

project(Pathfinding)

include(FetchContent)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED True)

# Move libraries to same folder as .exe
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Dependencies
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.x
)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.87
)

FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml.git
    GIT_TAG        master
)

# SFML
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_DOC OFF)
option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)
FetchContent_MakeAvailable(sfml)

# ImGui
FetchContent_MakeAvailable(imgui)

# ImGui-SFML
set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" OFF)
FetchContent_MakeAvailable(imgui-sfml)

# Pathfinding code
include_directories(include/)

set(SOURCE
    "src/AStar.cpp"
    "src/BFS.cpp"
    "src/Board.cpp"
    "src/DFS.cpp"
    "src/Dijkstra.cpp"
    "src/Graph.cpp"
    "src/ImGuiCustomWindow.cpp"
    "src/main.cpp"
    "src/MazeGenerator.cpp"
    "src/Screen.cpp"
    "src/SquareMap.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    ImGui-SFML::ImGui-SFML
)