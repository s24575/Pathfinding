#include "Screen.hpp"
#include "ImGuiCustomWindow.hpp"

Screen::Screen()
    : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_NAME),
    board(&window)
{}

void Screen::run(){
    sf::Event event;
    sf::Clock clock;
    bool isLeftPressed = false;
    float tilesToProcess = 0.0f;

    // ImGui setup
    ImGuiCustomWindow imguiWindow(&window, &board);

    window.setFramerateLimit(FRAMERATE);
    while (window.isOpen()){

        // INPUT
        while (window.pollEvent(event)){
            imguiWindow.processInput(event);

            if (!imguiWindow.wantCaptureMouse()) {
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
        if (board.hasChanged)
        {
            board.hasChanged = false;
            board.updateSettings(imguiWindow.getAreDiagonalsEnabled(), imguiWindow.getGraphWeight(), imguiWindow.getDistanceFunction());
            board.reset();
            board.createAlgorithm(imguiWindow.getCurrentAlgorithm());
            board.runAlgorithm(board.getTotalTiles());
        }
        else if (!imguiWindow.getIsStopped())
        {
            // progress algorithm so it takes around {SOLVE_TIME} seconds in total
            tilesToProcess += TOTAL_TILES * clock.getElapsedTime().asSeconds() / SOLVE_TIME;
            if (tilesToProcess >= 1.0f)
            {
                int x = floor(tilesToProcess);
                board.runAlgorithm((int)tilesToProcess);
                tilesToProcess -= floor(tilesToProcess);
            }
        }

        imguiWindow.loadWindow(clock.restart());

        // RENDER
        window.clear(sf::Color::Black);
        board.drawAllSquares();
        imguiWindow.render();
        window.display();
    }
}