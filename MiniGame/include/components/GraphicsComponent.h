#pragma once
#include "../graphics/SpriteSheet.h"
#include "../utils/Rectangle.h"
#include "Components.h"

class Entity;
class Window;
class Player;

class GraphicsComponent : public Component
{
public:
	GraphicsComponent() : isSpriteSheet{ false } {}
	virtual ~GraphicsComponent() {}

	virtual void init(const std::string& File) = 0;

	virtual const ComponentID getID() const { return ComponentID::GRAPHICS; }
	virtual const sf::Vector2f& getSpriteScale() const = 0;
	virtual const sf::Vector2i& getTextureSize() const = 0;
	virtual const Direction& getSpriteDirection() const = 0;
	virtual const std::string& getAnimName() const = 0;
	const Vector2f& getBBoxSize() const { return bBoxSize; }

	virtual void setPosition(Vector2f position) = 0;

	virtual bool isInAction() const = 0;
	virtual bool isPlaying() const = 0;
	bool isSpriteSheetEntity() const { return isSpriteSheet; }

protected:
	bool isSpriteSheet;
	Vector2f bBoxSize;
};

class SpriteSheetGraphicsComponent : public GraphicsComponent
{
public:
	SpriteSheetGraphicsComponent() { isSpriteSheet = true; }
	~SpriteSheetGraphicsComponent() {}

	virtual void init(const std::string& spriteSheetFile) override;

	virtual const sf::Vector2f& getSpriteScale() const override;
	virtual const sf::Vector2i& getTextureSize() const override;
	virtual const Direction& getSpriteDirection() const override;
	virtual const std::string& getAnimName() const override;
	SpriteSheet& getSpriteSheet() { return spriteSheet; }

	virtual void setPosition(Vector2f position) override;

	virtual bool isInAction() const override;
	virtual bool isPlaying() const override;

private:
	SpriteSheet spriteSheet;
};

class SpriteGraphicsComponent : public GraphicsComponent
{
public:
	SpriteGraphicsComponent(float scaleValue) : scale{ scaleValue } {}
	~SpriteGraphicsComponent() {}

	virtual void init(const std::string& textureFile) override;

	virtual void setPosition(Vector2f position) override;

	sf::Sprite& getSprite() { return sprite; }
	virtual const sf::Vector2f& getSpriteScale() const override;
	virtual const sf::Vector2i& getTextureSize() const override { return textureSize; }
	virtual const Direction& getSpriteDirection() const override { throw std::runtime_error("Invalid function: The entity is sprite"); }
	virtual const std::string& getAnimName() const override { throw std::runtime_error("Invalid function: The entity is sprite"); }

	virtual bool isInAction() const override { throw std::runtime_error("Invalid function: The entity is sprite"); }
	virtual bool isPlaying() const override { throw std::runtime_error("Invalid function: The entity is sprite"); }

private:
	sf::Texture texture;
	sf::Sprite sprite;
	float scale;
	sf::Vector2i textureSize;
};