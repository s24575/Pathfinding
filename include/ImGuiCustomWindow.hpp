#ifndef IMGUIWINDOW_H
#define IMGUIWINDOW_H

#include "imgui.h"
#include "imgui-SFML.h"

#include "Board.hpp"

class ImGuiCustomWindow {
public:
	ImGuiCustomWindow(sf::RenderWindow* window, Board* board);
	~ImGuiCustomWindow();
	void processInput(const sf::Event& event);
	void loadWindow(sf::Time deltaTime);
	void render();

	bool wantCaptureMouse() const { return io->WantCaptureMouse; }
	algorithm_type getCurrentAlgorithm() const { return static_cast<algorithm_type>(currentAlgorithm); }
	bool getAreDiagonalsEnabled() const { return areDiagonalsEnabled; }
	int getGraphWeight() const { return graphWeight; }
	distance_function getDistanceFunction() const { return static_cast<distance_function>(distanceCalculation); }
	bool getIsStopped() const { return isStopped; }
private:
	sf::RenderWindow* window;
	Board* board;
	ImGuiIO* io = nullptr;

	int currentAlgorithm = 0;
	bool isStopped = false;
	bool areDiagonalsEnabled = false;
	int graphWeight = 1;
	int distanceCalculation = 0;
};

#endif // IMGUIWINDOW_H