#include "../../include/core/Tile.h"
#include "../../include/utils/Vector2.h"
#include <sstream>

void Tile::loadTile(int x, int y, float sc, TileTexture* tileTexture)
{
	sprite.setTexture(tileTexture->getTexture());

	//Place tile on the screen.
	place(x, y, sc, tileTexture);
}

void Tile::place(int x, int y, float sc, TileTexture* tileTexture)
{
	//Position in grid:
	position.x = x;
	position.y = y;

	//scale for texture:
	sprite.setScale(sc, sc);

	//Position on screen:
	auto textSize{ tileTexture->getTexture().getSize() };
	float pixels_x{ static_cast<float>(x * (textSize.x * sc)) };
	float pixels_y{ static_cast<float>(y * (textSize.y * sc)) };
	sprite.setPosition(pixels_x, pixels_y);
}

void Tile::draw(Window* window)
{
	window->draw(sprite);
}