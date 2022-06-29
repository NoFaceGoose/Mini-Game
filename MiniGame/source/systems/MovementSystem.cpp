#include "../../include/systems/Systems.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/VelocityComponent.h"

MovementSystem::MovementSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
	componentMask.turnOnBit(static_cast<int>(ComponentID::VELOCITY));
}

void MovementSystem::update(Game* game, Entity* entity, float elapsed)
{
	auto position{ dynamic_cast<PositionComponent*>(entity->getComponent(ComponentID::POSITION)) };
	auto velocity{ dynamic_cast<VelocityComponent*>(entity->getComponent(ComponentID::VELOCITY)) };

	if (position)
	{
		if (velocity)
		{
			auto newPos{ position->getPosition() + velocity->getVelocity() * velocity->getSpeed() * elapsed };
			position->setPosition(newPos.x, newPos.y);
		}
		else
		{
			throw std::runtime_error("This entity does not have VelocityComponent");
		}
	}
	else
	{
		throw std::runtime_error("This entity does not have PositionComponent");
	}
}