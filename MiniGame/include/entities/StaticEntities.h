#pragma once
#include "Entity.h"
#include "../components/GraphicsComponent.h"
#include "../components/ColliderComponent.h"
#include "../components/PositionComponent.h"

class Potion : public Entity
{
public:
	Potion() : Entity(EntityType::POTION) { addComponent(std::make_shared<ColliderComponent>()); }
	~Potion() {}

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override
	{
		Entity::init(textureFile, gc);
		dynamic_cast<ColliderComponent*>(getComponent(ComponentID::COLLIDER))->setBBoxSize(gc->getBBoxSize());
	}

	int getHealth() const { return potionHealth; }

protected:
	const int potionHealth{ 10 };
};


class Log : public Entity
{
public:
	Log() : Entity(EntityType::LOG) { addComponent(std::make_shared<ColliderComponent>()); }
	~Log() {}

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override
	{
		Entity::init(textureFile, gc);
		dynamic_cast<ColliderComponent*>(getComponent(ComponentID::COLLIDER))->setBBoxSize(gc->getBBoxSize());
	}

	int getWood() const { return woodAdded; }

protected:
	const int woodAdded{ 15 };
};