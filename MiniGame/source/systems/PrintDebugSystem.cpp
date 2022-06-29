#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/ColliderComponent.h"

PrintDebugSystem::PrintDebugSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::COLLIDER));
}

void PrintDebugSystem::update(Game* game, Entity* entity, float elapsed)
{
	auto collider{ dynamic_cast<ColliderComponent*>(entity->getComponent(ComponentID::COLLIDER)) };

	if (collider)
	{
		game->getWindow()->draw(collider->getBoundingBox().getDrawableRect());
	}
	else
	{
		throw std::runtime_error("This entity does not have ColliderComponent");
	}
}