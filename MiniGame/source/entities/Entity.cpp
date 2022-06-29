#include "../../include/entities/Entity.h"
#include "../../include/graphics/Window.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include <iostream>

Entity::Entity() :
	id{ 0 },
	type{ EntityType::UNDEFINED },
	inUse{ true }
{
	auto position{ std::make_shared<PositionComponent>() };
	position->setPosition(0.f, 0.f);
	addComponent(position);
}

Entity::Entity(EntityType et) :
	id{ 0 },
	type{ et },
	inUse{ true }
{
	auto position{ std::make_shared<PositionComponent>() };
	position->setPosition(0.f, 0.f);
	addComponent(position);
}

void Entity::init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc)
{
	gc->init(textureFile);
	gc->setPosition(dynamic_cast<PositionComponent*>(getComponent(ComponentID::POSITION))->getPosition());
	addComponent(gc);
}

const sf::Vector2f& Entity::getSpriteScale()
{
	return dynamic_cast<GraphicsComponent*>(getComponent(ComponentID::GRAPHICS))->getSpriteScale();
}

const sf::Vector2i& Entity::getTextureSize()
{
	return dynamic_cast<GraphicsComponent*>(getComponent(ComponentID::GRAPHICS))->getTextureSize();
}

bool Entity::isSpriteSheetEntity()
{
	return dynamic_cast<GraphicsComponent*>(getComponent(ComponentID::GRAPHICS))->isSpriteSheetEntity();
}

const std::string& Entity::getAnimName()
{
	return dynamic_cast<GraphicsComponent*>(getComponent(ComponentID::GRAPHICS))->getAnimName();
}

void Entity::addComponent(std::shared_ptr<Component> comp)
{
	map[comp->getID()] = comp;
	componentSet.turnOnBit(static_cast<unsigned int>(comp->getID()));
}

bool Entity::hasComponent(Bitmask mask) const
{
	return componentSet.contains(mask);
}

Component* Entity::getComponent(ComponentID id)
{
	return map.find(id)->second.get();
}