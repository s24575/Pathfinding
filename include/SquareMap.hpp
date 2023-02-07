#ifndef SQUARE_MAP_H
#define SQUARE_MAP_H

#include <SFML/Graphics.hpp>

#include "Graph.hpp"

class SquareMap : public sf::Drawable
{
public:
    SquareMap(int xTiles, int yTiles, int tileSize);

    void setSquareColor(const int& x, const int& y, const sf::Color& color);

public:
    const sf::Color startColor{ sf::Color::Green };
    const sf::Color endColor{ sf::Color::Red };
    const sf::Color wallColor{ sf::Color::Black };
    const sf::Color emptyColor{ sf::Color{50, 50, 50} };
    const sf::Color searchedColor{ sf::Color::Yellow };
    const sf::Color visitedColor{ sf::Color::White };
    const sf::Color backtrackingColor{ sf::Color::Blue };
    const sf::Color defaultColor{ sf::Color::Magenta };

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(tiles, states);
    }

private:
    sf::VertexArray tiles;
    int xTiles;
};

#endif // SQUARE_MAP_H