#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/entities/Entity.h"
#include "../../include/graphics/Window.h"
#include "../../include/entities/Player.h"

// SpriteSheetGraphicsComponent functions
void SpriteSheetGraphicsComponent::init(const std::string& spriteSheetFile)
{
	spriteSheet.loadSheet(spriteSheetFile);
	spriteSheet.setAnimation("Idle", true, true);
	bBoxSize = { spriteSheet.getSpriteSize().x * spriteSheet.getSpriteScale().x,
		spriteSheet.getSpriteSize().y * spriteSheet.getSpriteScale().y };
}

void SpriteSheetGraphicsComponent::setPosition(Vector2f position)
{
	spriteSheet.getSprite().setPosition(position.x, position.y);
}

const sf::Vector2f& SpriteSheetGraphicsComponent::getSpriteScale() const
{
	return spriteSheet.getSpriteScale();
}

const sf::Vector2i& SpriteSheetGraphicsComponent::getTextureSize() const
{
	return spriteSheet.getSpriteSize();
}

bool SpriteSheetGraphicsComponent::isInAction() const
{
	return spriteSheet.getCurrentAnim()->isInAction();
}

bool SpriteSheetGraphicsComponent::isPlaying() const
{
	return spriteSheet.getCurrentAnim()->isPlaying();
}

const Direction& SpriteSheetGraphicsComponent::getSpriteDirection() const
{
	return spriteSheet.getSpriteDirection();
}

const std::string& SpriteSheetGraphicsComponent::getAnimName() const
{
	return spriteSheet.getCurrentAnim()->getName();
}


// SpriteGraphicsComponent functions
void SpriteGraphicsComponent::init(const std::string& textureFile)
{
	texture.loadFromFile(textureFile);
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
	isSpriteSheet = false;
	bBoxSize = { texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y };
	textureSize = { static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y) };
}

void SpriteGraphicsComponent::setPosition(Vector2f position)
{
	sprite.setPosition(position.x, position.y);
}

const sf::Vector2f& SpriteGraphicsComponent::getSpriteScale() const
{
	return sprite.getScale();
}