#include "../../include/systems/Systems.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Game.h"

InputSystem::InputSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::INPUT));
	componentMask.turnOnBit(static_cast<int>(ComponentID::VELOCITY));
}

void InputSystem::update(Game* game, Entity* entity, float elapsed)
{
	auto input{ dynamic_cast<InputComponent*>(entity->getComponent(ComponentID::INPUT)) };
	auto velocity{ dynamic_cast<VelocityComponent*>(entity->getComponent(ComponentID::VELOCITY)) };

	if (input)
	{
		if (velocity)
		{
			velocity->setVelocity(0.f, 0.f);

			auto handler{ input->getPlayerInputHandler() };
			if (handler)
			{
				
				auto& commands{ handler->handlePlayerInput(game->isMouseEnable()) };
				for (auto command : commands)
				{
					command->execute(*game);
				}
			}
			else
			{
				throw std::runtime_error("Input System can not retrieve PlayerInputHandler in function update()");
			}
		}
		else
		{
			throw std::runtime_error("This entity does not have VelocityComponent");
		}
	}
	else
	{
		throw std::runtime_error("This entity does not have InputComponent");
	}
}