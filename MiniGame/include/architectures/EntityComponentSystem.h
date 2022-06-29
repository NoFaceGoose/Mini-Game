#pragma once
#include <vector>
#include <memory>
#include <stdexcept>

class System;
class Entity;
class Game;
class Archetype;
using EntityID = unsigned;

class EntityComponentSystem
{
public:
	EntityComponentSystem();
	EntityComponentSystem(bool enableDebug);
	virtual ~EntityComponentSystem() {}

	virtual void addEntity(Entity* entity) = 0;

	/*
	* update systems
	* @param game The pointer to the game
	* @param elapsed The time elapsed for this frame
	* @param if it is going to update the logic system
	*/
	virtual void update(Game* game, float elapsed, bool isLogicSystem = true) = 0;

protected:
	std::vector<std::shared_ptr<System>> logicSystems;
	std::vector<std::shared_ptr<System>> graphicsSystems;
};