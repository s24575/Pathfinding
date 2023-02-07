#include "SquareMap.hpp"

SquareMap::SquareMap(int xTiles, int yTiles, int tileSize)
    : xTiles(xTiles)
{
    tiles.setPrimitiveType(sf::Quads);
    for (size_t y = 0; y < yTiles; y++)
    {
        for (size_t x = 0; x < xTiles; x++)
        {
            {
                sf::Vector2f position = sf::Vector2f(x * (float)tileSize, y * (float)tileSize);
                sf::Color color = defaultColor;
                tiles.append(sf::Vertex(position, color));
                tiles.append(sf::Vertex(position + sf::Vector2f((float)tileSize, 0.f), color));
                tiles.append(sf::Vertex(position + sf::Vector2f((float)tileSize, (float)tileSize), color));
                tiles.append(sf::Vertex(position + sf::Vector2f(0.f, (float)tileSize), color));
            }
        }
    };
}

void SquareMap::setSquareColor(const int& x, const int& y, const sf::Color& color)
{
    tiles[4 * (x + y * xTiles)].color = color;
    tiles[4 * (x + y * xTiles) + 1].color = color;
    tiles[4 * (x + y * xTiles) + 2].color = color;
    tiles[4 * (x + y * xTiles) + 3].color = color;
}