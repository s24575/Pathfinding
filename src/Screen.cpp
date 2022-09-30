#include "imgui.h"
#include "imgui-SFML.h"

#include "Screen.h"
//#include <stdio.h>

Screen::Screen(int width, int height, int tileSize, int maze_width, int maze_height, int corridor_width)
    : window(sf::VideoMode(width * tileSize, height * tileSize), "Pathfinding"),
      board(&window, width, height, tileSize, maze_width, maze_height, corridor_width),
      tiles_total(width * height)
{}

void Screen::run(){
    sf::Event event;
    sf::Clock clock;
    float deltaTime;
    constexpr int framerate = 60;
    constexpr int solve_time = 5;

    ImGui::SFML::Init(window);

    window.setFramerateLimit(framerate);
    while (window.isOpen()){
        while (window.pollEvent(event)){
            // input
            ImGui::SFML::ProcessEvent(event);

            if (!ImGui::GetIO().WantCaptureMouse) {
                if (event.type == sf::Event::Closed) window.close();
                else if (event.type == sf::Event::Resized) {
                    window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                }
                else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) window.close();
                    else if (event.key.code == sf::Keyboard::R) board.reset();
                    else if (event.key.code == sf::Keyboard::Q) board.removeAllWalls();
                    else if (event.key.code == sf::Keyboard::D) board.createAlgorithm(algorithm_type::DFS);
                    else if (event.key.code == sf::Keyboard::B) board.createAlgorithm(algorithm_type::BFS);
                    else if (event.key.code == sf::Keyboard::I) board.createAlgorithm(algorithm_type::DIJKSTRA);
                    else if (event.key.code == sf::Keyboard::A) board.createAlgorithm(algorithm_type::ASTAR);
                }

                else if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        left_pressed = !left_pressed;
                        board.checkWall(sf::Mouse::getPosition(window));
                    }
                }

                if (left_pressed) board.editWall(sf::Mouse::getPosition(window));
            }
        }

        // update
        deltaTime = 1000.0f / clock.getElapsedTime().asMilliseconds();
        board.runAlgorithm(tiles_total / (deltaTime * solve_time));
        ImGui::SFML::Update(window, clock.restart());

        ImGui::Begin("Testing!");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        // render
        window.clear(sf::Color::Black);
        board.drawAllSquares();
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}