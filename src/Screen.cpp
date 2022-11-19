#include "imgui.h"
#include "imgui-SFML.h"

#include "Screen.h"

Screen::Screen(int width, int height, int tileSize, int maze_width, int maze_height, int corridor_width)
    : window(sf::VideoMode(width * tileSize, height * tileSize), "Pathfinding"),
      board(&window, width, height, tileSize, maze_width, maze_height, corridor_width)
{}

void Screen::run(){
    sf::Event event;
    sf::Clock clock;
    constexpr int framerate = 60;
    constexpr int solve_time = 5; // time it takes to finish maze

    bool isLeftPressed = false;
    int total_tiles = board.getTotalTiles();

    // ImGui setup
    IMGUI_CHECKVERSION();
    ImGui::SFML::Init(window);
    ImGuiIO& io = ImGui::GetIO();
    static const char* items[]{ "DFS", "BFS", "Dijkstra", "A*" };
    static int currentAlgorithm = NULL;
    constexpr ImVec2 algorithmButtonSize(75.f, 30.f);
    constexpr ImVec2 mazeButtonSize(125.f, 30.f);
    bool isStopped = false;
    static bool areDiagonalsEnabled = false;
    static int graphWeight = 1;
    static int distanceCalculation = 0;

    window.setFramerateLimit(framerate);
    while (window.isOpen()){
        while (window.pollEvent(event)){
            // INPUT
            ImGui::SFML::ProcessEvent(event);

            if (!io.WantCaptureMouse) {
                switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::R:
                        board.reset();
                        break;
                    case sf::Keyboard::Q:
                        board.removeAllWalls();
                        break;
                    case sf::Keyboard::D:
                        board.createAlgorithm(algorithm_type::DFS);
                        break;
                    case sf::Keyboard::B:
                        board.createAlgorithm(algorithm_type::BFS);
                        break;
                    case sf::Keyboard::I:
                        board.createAlgorithm(algorithm_type::DIJKSTRA);
                        break;
                    case sf::Keyboard::A:
                        board.createAlgorithm(algorithm_type::ASTAR);
                        break;
                    default:
                        break;
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        isLeftPressed = true;
                        board.checkWall(sf::Mouse::getPosition(window));
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        isLeftPressed = false;
                        board.checkWall(sf::Mouse::getPosition(window));
                    }
                    break;
                }

                if (isLeftPressed) board.editWall(sf::Mouse::getPosition(window));
            }
        }

        // UPDATE

        if (board.hasMoved) {
            board.hasMoved = false;
            board.reset();
            board.createAlgorithm(static_cast<algorithm_type>(currentAlgorithm));
            board.runAlgorithm(board.getTotalTiles());
        }
        // progress algorithm so it takes around {solve_time} seconds in total
        else if(!isStopped) board.runAlgorithm((int)(total_tiles * clock.getElapsedTime().asSeconds() / solve_time));

        // ImGui window
        ImGui::SFML::Update(window, clock.restart());
        ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
        ImGui::Begin("Menu", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

        if (ImGui::CollapsingHeader("Info")) {
            ImGui::Text("ABOUT THIS PROGRAM:");
            ImGui::BulletText("This is a simple program showcasing different pathfinding algorithms.");
            ImGui::BulletText("As of now, there are four different algorithms:");
            ImGui::Indent();
            ImGui::BulletText("DepthFirstSearch (DFS) - stack");
            ImGui::BulletText("BreadthFirstSearch (BFS) - queue");
            ImGui::BulletText("Dijkstra - priority queue, h cost");
            ImGui::BulletText("A* - priority queue, h cost, g cost");
            ImGui::Unindent();
            ImGui::Separator();
            ImGui::Text("SETTINGS:");
            ImGui::BulletText("All algorithms have the option to turn diagonal moves on/off.");
            ImGui::BulletText("Dijkstra and A* have two ways of measuring the distance between points:");
            ImGui::Indent();
            ImGui::BulletText("Euclidean - uses Pythagorean theorem, which requires\n"
                "a square root operation, making it computationally expensive");
            ImGui::BulletText("Manhattan - adds the absolute difference\n"
                "of their Cartesian coordinates, making it very fast");
            ImGui::Unindent();
        }

        if (ImGui::CollapsingHeader("Maze")) {
            if (ImGui::Button("REGENERATE MAZE", mazeButtonSize)) {
                board.generateMaze();
            }
            ImGui::SameLine();
            if (ImGui::Button("DELETE WALLS", mazeButtonSize)) {
                board.removeAllWalls();
            }
        }

        if (ImGui::CollapsingHeader("Algorithms")) {
            ImGui::Combo("algorithm type", &currentAlgorithm, items, IM_ARRAYSIZE(items));

            auto algorithm = static_cast<algorithm_type>(currentAlgorithm);
            if (algorithm == algorithm_type::DIJKSTRA || algorithm == algorithm_type::ASTAR) {
                ImGui::SliderInt("weight", &graphWeight, 1, 1000);

                ImGui::AlignTextToFramePadding();
                ImGui::Text("Distance:"); ImGui::SameLine();
                ImGui::RadioButton("Euclidean", &distanceCalculation, 0); ImGui::SameLine();
                ImGui::RadioButton("Manhattan", &distanceCalculation, 1);
            }

            ImGui::Checkbox("diagonals moves", &areDiagonalsEnabled);

            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.30f, 0.6f, 0.6f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.30f, 0.7f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.30f, 0.8f, 0.8f));
            if (ImGui::Button("START", algorithmButtonSize)) {
                isStopped = false;
                board.reset();
                board.updateSettings(areDiagonalsEnabled, graphWeight, distanceCalculation);
                board.createAlgorithm(static_cast<algorithm_type>(currentAlgorithm));
            }
            ImGui::PopStyleColor(3);

            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.02f, 0.6f, 0.6f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.02f, 0.8f, 0.8f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.02f, 0.7f, 0.7f));
            if (ImGui::Button("PAUSE", algorithmButtonSize)) {
                isStopped = !isStopped;
            }
            ImGui::PopStyleColor(3);

            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.60f, 0.6f, 0.6f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.60f, 0.8f, 0.8f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.60f, 0.7f, 0.7f));
            if (ImGui::Button("RESET", algorithmButtonSize)) {
                board.reset();
            }
            ImGui::PopStyleColor(3);
        }
        ImGui::End();

        // RENDER
        window.clear(sf::Color::Black);
        board.drawAllSquares();
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}