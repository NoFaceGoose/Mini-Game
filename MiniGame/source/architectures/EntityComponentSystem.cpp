#include "../../include/architectures/EntityComponentSystem.h"
#include "../../include/systems/Systems.h"

EntityComponentSystem::EntityComponentSystem()
{
	logicSystems.push_back(std::make_shared<TTLSystem>());
	logicSystems.push_back(std::make_shared<InputSystem>());
	logicSystems.push_back(std::make_shared<MovementSystem>());
	logicSystems.push_back(std::make_shared<ColliderSystem>());
	logicSystems.push_back(std::make_shared<GameplaySystem>());

	graphicsSystems.push_back(std::make_shared<GraphicsSystem>());
	graphicsSystems.push_back(std::make_shared<PrintDebugSystem>());
}

EntityComponentSystem::EntityComponentSystem(bool enableDebug)
{
	logicSystems.push_back(std::make_shared<TTLSystem>());
	logicSystems.push_back(std::make_shared<InputSystem>());
	logicSystems.push_back(std::make_shared<MovementSystem>());
	logicSystems.push_back(std::make_shared<ColliderSystem>());
	logicSystems.push_back(std::make_shared<GameplaySystem>());

	graphicsSystems.push_back(std::make_shared<GraphicsSystem>());
	if (enableDebug)
	{
		graphicsSystems.push_back(std::make_shared<PrintDebugSystem>());
	}
}