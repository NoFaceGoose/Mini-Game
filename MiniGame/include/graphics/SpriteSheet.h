#pragma once
//Adapted from SFML Game Development By Example (Raimondas Pupius)

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "AnimBase.h"

class AnimBase;

using Animations = std::unordered_map<std::string, AnimBase*>;
enum class Direction
{
	Right = 0,
	Left
};

class SpriteSheet
{
public:
	SpriteSheet();
	~SpriteSheet();

	void releaseSheet();

	void setSpriteSize(const sf::Vector2i& size);
	void setSpriteScale(const sf::Vector2f& scale);
	void setSpritePosition(const sf::Vector2f& pos);
	void setSpriteDirection(const Direction& dir);
	bool setAnimation(const std::string& name, bool play = false, bool loop = false);

	const sf::Vector2i& getSpriteSize() const { return spriteSize; }
	const sf::Vector2f& getSpriteScale() const { return spriteScale; }
	const Direction& getSpriteDirection() const { return direction; }
	const sf::Vector2f& getSpritePosition() const { return sprite.getPosition(); }
	const std::string& getAnimType() const { return animType; }
	int getNumAnimations() const { return animations.size(); }
	sf::Sprite& getSprite() { return sprite; }
	AnimBase* getCurrentAnim() const;

	void cropSprite(const sf::IntRect& rect);
	bool loadSheet(const std::string& file);

	void draw(sf::RenderWindow* window);

	void update(float elapsedTime);

private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i spriteSize;
	sf::Vector2f spriteScale;
	Direction direction;
	std::string animType;
	Animations animations;
	AnimBase* curAnimation;
};