#include "../../include/entities/Player.h"
#include "../../include/graphics/AnimBase.h"
#include "../../include/entities/Fire.h"
#include "../../include/core/Game.h"
#include "../../include/core/Command.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/pool/EntityPools.h"
#include "../../include/services/Locator.h"

Player::Player() :
	Entity{ EntityType::PLAYER }
{
	addComponent(std::make_shared<HealthComponent>(startingHealth, maxHealth));
	addComponent(std::make_shared<PlayerInputComponent>());
	addComponent(std::make_shared<VelocityComponent>(playerSpeed));
	addComponent(std::make_shared<ColliderComponent>());
	addComponent(std::make_shared<PlayerStateComponent>(maxWood, shootingCost, shootCooldownTime));
}

void Player::init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc)
{
	Entity::init(textureFile, gc);
	dynamic_cast<ColliderComponent*>(getComponent(ComponentID::COLLIDER))->setBBoxSize(gc->getBBoxSize());
}

bool Player::isAttacking()
{
	return dynamic_cast<LogicComponent*>(getComponent(ComponentID::LOGIC))->isAttacking();
}

void Player::setAttacking(bool at)
{
	dynamic_cast<LogicComponent*>(getComponent(ComponentID::LOGIC))->setAttacking(at);
}

bool Player::isShouting()
{
	return dynamic_cast<LogicComponent*>(getComponent(ComponentID::LOGIC))->isShouting();
}

void Player::setShouting(bool sh)
{
	dynamic_cast<LogicComponent*>(getComponent(ComponentID::LOGIC))->setShouting(sh);
}

void Player::positionSprite(int row, int col, int spriteWH, float tileScale)
{
	auto scaleV2f{ getSpriteScale() };
	auto textureSize{ getTextureSize() };

	float x{ col * spriteWH * tileScale };
	float y{ (row)*spriteWH * tileScale };
	float spriteSizeY{ scaleV2f.y * textureSize.y };
	float cntrFactorY{ ((spriteWH * tileScale) - spriteSizeY) };	// to align to lower side of the tile.
	float cntrFactorX{ cntrFactorY * 0.5f };						//to center horizontally

	dynamic_cast<PositionComponent*>(getComponent(ComponentID::POSITION))->setPosition(x + cntrFactorX, y + cntrFactorY);
	dynamic_cast<VelocityComponent*>(getComponent(ComponentID::VELOCITY))->setVelocity(0.f, 0.f);
}

/*
* @param other object to be checked
* whether it is collided with player
* @return boolean test result
*/
bool Player::collidesWith(Entity& other)
{
	return dynamic_cast<ColliderComponent*>(getComponent(ComponentID::COLLIDER))
		->interesects(dynamic_cast<ColliderComponent*>(other.getComponent(ComponentID::COLLIDER)));
}

int Player::getWood()
{
	return dynamic_cast<LogicComponent*>(getComponent(ComponentID::LOGIC))->getWood();
}

void Player::addWood(int w)
{
	dynamic_cast<LogicComponent*>(getComponent(ComponentID::LOGIC))->addWood(w);
}

void Player::onCollisionPotion(Pool& p)
{
	PotionPool& pool{ dynamic_cast<PotionPool&>(p) };
	for (int i{ 0 }; i < pool.getPoolSize(); ++i)
	{
		if (pool.getAt(i).isInUse() && collidesWith(pool.getAt(i)))
		{
			dynamic_cast<HealthComponent*>(getComponent(ComponentID::HEALTH))->changeHealth(pool.getAt(i).getHealth());
			pool.getAt(i).toggleUse();
			std::cout << "Player restore health: " << pool.getAt(i).getHealth() << std::endl;
			std::cout << "Player current health: " << dynamic_cast<HealthComponent*>(getComponent(ComponentID::HEALTH))->getHealth() << std::endl;
			Locator::getAuido()->playSound(Audios::DRINK_POTION);
			getAchievements().notify(Event::COLLECTPOTION);
		}
	}
}

void Player::onCollisionLog(Pool& p)
{
	LogPool& pool{ dynamic_cast<LogPool&>(p) };
	for (int i{ 0 }; i < pool.getPoolSize(); ++i)
	{
		if (pool.getAt(i).isInUse() && collidesWith(pool.getAt(i)) && isAttacking() && dynamic_cast<GraphicsComponent*>(getComponent(ComponentID::GRAPHICS))->isInAction())
		{
			addWood(pool.getAt(i).getWood());
			Locator::getAuido()->playSound(Audios::AXE_CHOP);
			pool.getAt(i).toggleUse();
			std::cout << "Player collect wood: " << pool.getAt(i).getWood() << std::endl;
			std::cout << "Player current wood: " << getWood() << std::endl;
		}
	}
}