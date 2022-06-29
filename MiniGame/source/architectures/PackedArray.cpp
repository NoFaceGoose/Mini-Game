#include "../../include/architectures/PackedArrays.h"
#include "../../include/systems/Systems.h"

PackedArrays::PackedArrays(bool enableDebug) :EntityComponentSystem(enableDebug)
{
	_num_entities = 0;
	for (unsigned i{ 0 }; i < MAX_ENTITIES; ++i) {
		_indices[i].id = i;
		_indices[i].next = i + 1;
	}
	_freelist_dequeue = 0;
	_freelist_enqueue = MAX_ENTITIES - 1;
}

bool PackedArrays::has(EntityID id)
{
	Index& in{ _indices[id & INDEX_MASK] };
	return in.id == id && in.index != USHRT_MAX;
}

Entity& PackedArrays::lookup(EntityID id)
{
	return *_entities[_indices[id & INDEX_MASK].index];
}

EntityID PackedArrays::add()
{
	Index& in{ _indices[_freelist_dequeue] };
	_freelist_dequeue = in.next;
	in.id += NEW_ENTITY_ID_ADD;
	in.index = _num_entities++;
	Entity& e{ *_entities[in.index] };
	e.setID(in.id);
	return e.getID();
}

void PackedArrays::remove(EntityID id)
{
	Index& in{ _indices[id & INDEX_MASK] };

	Entity& e{ *_entities[in.index] };
	e = *_entities[--_num_entities];
	_indices[e.getID() & INDEX_MASK].index = in.index;

	in.index = USHRT_MAX;
	_indices[_freelist_enqueue].next = id & INDEX_MASK;
	_freelist_enqueue = id & INDEX_MASK;
}

void PackedArrays::addEntity(Entity* entity)
{
	Index& in{ _indices[_freelist_dequeue] };
	_freelist_dequeue = in.next;
	in.id += NEW_ENTITY_ID_ADD;
	in.index = _num_entities++;
	_entities[in.index] = entity;
	entity->setID(in.id);
}

void PackedArrays::update(Game* game, float elapsed, bool isLogicSystem)
{
	std::vector<std::shared_ptr<System>>* sys;

	if (isLogicSystem)
	{
		sys = &logicSystems;
	}
	else
	{
		sys = &graphicsSystems;
	}

	auto itSys{ (*sys).begin() };

	while (itSys != (*sys).end())
	{
		for (unsigned i{ 0 }; i < _num_entities; ++i)
		{
			if (_entities[i]->isInUse() && itSys->get()->validate(_entities[i]))
			{
				(*itSys)->update(game, _entities[i], elapsed);
			}
		}
		itSys++;
	}
}