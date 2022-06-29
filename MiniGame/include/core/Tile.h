#pragma once
#include "../graphics/Window.h"

enum class TileType
{
	CORRIDOR,
	WALL
};

class TileTexture
{
private:
	sf::Texture texture;

public:
	sf::Texture& getTexture() { return texture; }
};

class Vector2;
class Window;

class Tile
{
private:
	// extrinsic data
	TileType type;
	sf::Vector2i position; // Position in the grid (not in screen pixels, for that sprite.getPosition())
	sf::Sprite sprite;

	void place(int x, int y, float sc, TileTexture* tileTexture);

public:
	Tile(TileType tt) : type{ tt }, position{ 0, 0 } {}

	void loadTile(int x, int yy, float sc, TileTexture* tileTexture);

	inline int x() const { return position.x; }
	inline int y() const { return position.y; }

	inline const sf::Vector2f& getScale() const { return sprite.getScale(); }
	inline const TileType& getType() const { return type; }
	inline float getSpriteXpos() const { return sprite.getPosition().x; }
	inline float getSpriteYpos() const { return sprite.getPosition().y; }

	void draw(Window* window);
};