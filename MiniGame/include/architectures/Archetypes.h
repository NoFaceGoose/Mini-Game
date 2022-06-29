#pragma once
#include "EntityComponentSystem.h"

class Archetypes : public EntityComponentSystem
{
public:
	Archetypes();
	Archetypes(bool enableDebug);
	~Archetypes() {}

	/*
	* initialize the Archetypes architecture
	* @note this function initialize all the archetypes which are involved in the game
	*/
	void init();

	/*
	* add entity to the vector in the specific archetype it belongs to
	* @param entity The pointer to the entity variable in the object pool
	*/
	virtual void addEntity(Entity* entity) override;

	virtual void update(Game* game, float elapsed, bool isLogicSystem = true) override;

private:
	std::vector<std::shared_ptr<Archetype>> archetypes;
};