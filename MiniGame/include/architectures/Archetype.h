#pragma once
#include <vector>
#include <memory>
#include "../entities/Entity.h"

class Archetype
{
public:
	Archetype() {}
	Archetype(const Bitmask& comps) {
		components.turnOnBits(comps.getMask());
	}
	~Archetype() {}

	const Bitmask& getComponents() const { return components; }
	std::vector<Entity*>& getEntities() { return entities; }

	void addEntity(Entity* entity) { entities.push_back(entity); }

private:
	Bitmask components;
	std::vector<Entity*> entities;
};