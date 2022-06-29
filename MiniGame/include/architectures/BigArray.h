#pragma once
#include "EntityComponentSystem.h"

class BigArray : public EntityComponentSystem
{
public:
	BigArray() : EntityComponentSystem() {}
	BigArray(bool enableDebug) : EntityComponentSystem(enableDebug) {}
	~BigArray() {}

	virtual void addEntity(Entity* entity) override { entities.push_back(entity); }

	virtual void update(Game* game, float elapsed, bool isLogicSystem = true) override;

private:
	std::vector<Entity*> entities;
};