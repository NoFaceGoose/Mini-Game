#include "../../include/systems/Systems.h"
#include "../../include/entities/Player.h"
#include "../../include/entities/Fire.h"
#include "../../include/core/Game.h"
#include "../../include/components/LogicComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/services/Locator.h"
#include <iostream>

GameplaySystem::GameplaySystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::LOGIC));
	componentMask.turnOnBit(static_cast<int>(ComponentID::GRAPHICS));
	componentMask.turnOnBit(static_cast<int>(ComponentID::VELOCITY));
}

void GameplaySystem::update(Game* game, Entity* entity, float elapsed)
{
	auto logic{ dynamic_cast<LogicComponent*>(entity->getComponent(ComponentID::LOGIC)) };
	auto grapahics{ dynamic_cast<SpriteSheetGraphicsComponent*>(entity->getComponent(ComponentID::GRAPHICS)) };
	auto velocity{ dynamic_cast<VelocityComponent*>(entity->getComponent(ComponentID::VELOCITY)) };

	if (logic)
	{
		if (grapahics)
		{
			if (velocity)
			{
				auto& spriteSheet{ grapahics->getSpriteSheet() };

				// update player's animation
				auto player{ dynamic_cast<Player*>(entity) };

				if (player->isAttacking())
				{
					spriteSheet.setAnimation("Attack", true, false);
				}
				else if (player->isShouting())
				{
					spriteSheet.setAnimation("Shout", true, false);
				}
				else if (velocity->getVelocity() != Vector2f(0.f, 0.f))
				{
					spriteSheet.setAnimation("Walk", true, true);

					if (velocity->getVelocity().x > 0.f)
					{
						spriteSheet.setSpriteDirection(Direction::Right);
					}

					if (velocity->getVelocity().x < 0.f)
					{
						spriteSheet.setSpriteDirection(Direction::Left);
					}
				}
				else
				{
					spriteSheet.setAnimation("Idle", true, true);
				}

				if ((logic->getShootCooldown() > 0))
				{
					logic->reduceShootCooldown(elapsed);
				}

				if (logic->isShouting() && grapahics->isInAction() && logic->getWood() >= logic->getShootingCost() && logic->getShootCooldown() <= 0)
				{
					logic->setShootCooldown(logic->getShootCooldownTime());
					Fire* fire{ game->getFirePool()->activate(player) };

					Vector2f pos{ dynamic_cast<PositionComponent*>(player->getComponent(ComponentID::POSITION))->getPosition().x + player->getTextureSize().x * 0.5f,
						dynamic_cast<PositionComponent*>(player->getComponent(ComponentID::POSITION))->getPosition().y + player->getTextureSize().y * 0.5f };
					dynamic_cast<PositionComponent*>(fire->getComponent(ComponentID::POSITION))->setPosition(pos.x, pos.y);
					Vector2f vel{ fireSpeed, 0.f };
					if (dynamic_cast<GraphicsComponent*>(player->getComponent(ComponentID::GRAPHICS))->getSpriteDirection() == Direction::Left)
					{
						vel.x *= -1.f;
					}
					dynamic_cast<VelocityComponent*>(fire->getComponent(ComponentID::VELOCITY))->setVelocity(vel.x, vel.y);

					dynamic_cast<TTLComponent*>(fire->getComponent(ComponentID::TTL))->recoverTTL();

					Locator::getAuido()->playSound(Audios::CAST_FIREBALL);
					player->getAchievements().notify(Event::SHOUT);
					logic->addWood(-(logic->getShootingCost()));
				}

				if (logic->isAttacking() && !(grapahics->isPlaying()))
				{
					logic->setAttacking(false);
				}

				if (logic->isShouting() && !(grapahics->isPlaying()))
				{
					logic->setShouting(false);
				}
			}
			else
			{
				throw std::runtime_error("This entity does not have VelocityComponent");
			}
		}
		else
		{
			throw std::runtime_error("This entity does not have GraphicsComponent");
		}
	}
	else
	{
		throw std::runtime_error("This entity does not have LogicComponent");
	}
}