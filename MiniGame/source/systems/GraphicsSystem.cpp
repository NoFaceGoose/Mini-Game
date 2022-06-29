#include "../../include/systems/Systems.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/entities/Player.h"
#include "../../include/core/Game.h"

GraphicsSystem::GraphicsSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
	componentMask.turnOnBit(static_cast<int>(ComponentID::GRAPHICS));
}

void GraphicsSystem::update(Game* game, Entity* entity, float elapsed)
{
	auto position{ dynamic_cast<PositionComponent*>(entity->getComponent(ComponentID::POSITION)) };
	auto graphics{ dynamic_cast<GraphicsComponent*>(entity->getComponent(ComponentID::GRAPHICS)) };

	if (position)
	{
		if (graphics)
		{
			if (graphics->isSpriteSheetEntity())
			{
				auto spriteSheetGraphics{ dynamic_cast<SpriteSheetGraphicsComponent*>(graphics) };

				// update the sprite position
				auto& spriteSheet{ spriteSheetGraphics->getSpriteSheet() };
				spriteSheet.setSpritePosition(sf::Vector2f(position->getPosition().x, position->getPosition().y));
				spriteSheet.update(elapsed);

				game->getWindow()->draw(spriteSheet.getSprite());
				
			}

			else
			{
				auto spriteGraphics{ dynamic_cast<SpriteGraphicsComponent*>(graphics) };
				spriteGraphics->getSprite().setPosition(position->getPosition().x, position->getPosition().y);

				game->getWindow()->draw(spriteGraphics->getSprite());
			}
		}
		else
		{
			throw std::runtime_error("This entity does not have GraphicsComponent");
		}
	}
	else
	{
		throw std::runtime_error("This entity does not have PositionComponent");
	}
}