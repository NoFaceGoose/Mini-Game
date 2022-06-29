#pragma once
#include "EntityComponentSystem.h"
#include "../entities/Entity.h"
#include <windows.h>

using EntityID = unsigned;

const int MAX_ENTITIES{ 64 * 1024 };
const int INDEX_MASK{ 0xffff };
const int NEW_ENTITY_ID_ADD{ 0x10000 };

class PackedArrays : public EntityComponentSystem
{
protected:
	struct Index {
		EntityID id;
		unsigned short index;
		unsigned short next;
	};

public:
	PackedArrays(bool enableDebug = false);
	~PackedArrays() {}

	void addEntity(Entity* entity) override;

	virtual void update(Game* game, float elapsed, bool isLogicSystem = true) override;

private:
	bool has(EntityID id);
	Entity& lookup(EntityID id);
	EntityID add();
	void remove(EntityID id);

	unsigned _num_entities;
	Entity* _entities[MAX_ENTITIES];
	Index _indices[MAX_ENTITIES];
	unsigned short _freelist_enqueue;
	unsigned short _freelist_dequeue;
};