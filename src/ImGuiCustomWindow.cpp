#include "ImGuiCustomWindow.hpp"

ImGuiCustomWindow::ImGuiCustomWindow(sf::RenderWindow* window, Board* board)
    : window(window), board(board)
{
    IMGUI_CHECKVERSION();
    ImGui::SFML::Init(*window);
    io = &ImGui::GetIO();
}

ImGuiCustomWindow::~ImGuiCustomWindow() {
    ImGui::SFML::Shutdown();
}

void ImGuiCustomWindow::processInput(const sf::Event& event) {
    ImGui::SFML::ProcessEvent(event);
}

void ImGuiCustomWindow::loadWindow(sf::Time deltaTime) {
    const ImVec2 algorithmButtonSize(75.f, 30.f);
    const ImVec2 mazeButtonSize(125.f, 30.f);

    ImGui::SFML::Update(*window, deltaTime);
    ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
    ImGui::Begin("Menu", NULL, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);

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
            board->generateMaze();
        }
        ImGui::SameLine();
        if (ImGui::Button("DELETE WALLS", mazeButtonSize)) {
            board->removeAllWalls();
        }
    }

    if (ImGui::CollapsingHeader("Algorithms")) {
        static const char* items[] = { "DFS", "BFS", "Dijkstra", "A*" };
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
            board->reset();
            board->updateSettings(areDiagonalsEnabled, graphWeight, distanceCalculation);
            board->createAlgorithm(static_cast<algorithm_type>(currentAlgorithm));
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
            board->reset();
        }
        ImGui::PopStyleColor(3);
    }
    ImGui::End();
}

void ImGuiCustomWindow::render() {
    ImGui::SFML::Render(*window);
}