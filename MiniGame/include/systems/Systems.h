#pragma once
#include "../utils/Bitmask.h"
#include "../entities/Entity.h"
#include "../architectures/Archetype.h"

class Game;

class System
{
public:
	virtual void update(Game* game, Entity* entity, float elapsed) = 0;

	bool validate(Entity* entity) const { return entity->hasComponent(componentMask); }
	bool validate(Archetype* archetype) const { return archetype->getComponents().contains(componentMask); }

protected:
	Bitmask componentMask;
};

class TTLSystem : public System
{
public:
	TTLSystem();
	virtual void update(Game* game, Entity* entity, float elapsed) override;
};

class InputSystem : public System
{
public:
	InputSystem();
	virtual void update(Game* game, Entity* entity, float elapsed) override;
};

class MovementSystem : public System
{
public:
	MovementSystem();
	virtual void update(Game* game, Entity* entity, float elapsed) override;
};

class GraphicsSystem : public System
{
public:
	GraphicsSystem();
	virtual void update(Game* game, Entity* entity, float elapsed) override;
};

class ColliderSystem : public System
{
public:
	ColliderSystem();
	virtual void update(Game* game, Entity* entity, float elapsed) override;
};

class GameplaySystem : public System
{
public:
	GameplaySystem();
	virtual void update(Game* game, Entity* entity, float elapsed) override;
};

class PrintDebugSystem : public System
{
public:
	PrintDebugSystem();
	virtual void update(Game* game, Entity* entity, float elapsed) override;
};