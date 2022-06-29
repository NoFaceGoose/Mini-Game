#pragma once
#include "../graphics/SpriteSheet.h"
#include "../utils/Rectangle.h"
#include "../utils/Bitmask.h"
#include "../components/Components.h"

using EntityID = unsigned int;
enum class EntityType
{
	UNDEFINED = -1,
	PLAYER = 0,
	POTION = 1,
	LOG = 2,
	FIRE = 3
};

class Game; //forward declaration
class Window;
class PositionComponent;
class GraphicsComponent;
class ColliderComponent;
class Component;
class TTLComponent;
class InputComponent;
class VelocityComponent;
class LogicComponent;

class Entity
{
public:

	//Constructors and Desctrutors
	Entity();
	Entity(EntityType et);
	~Entity() {}

	//Init function
	virtual void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc);

	//Getters and Setters
	void setID(EntityID entId) { id = entId; }
	void setNext(Entity* nextEnt) { next = nextEnt; }
	Entity* getNext() const { return next; }
	const EntityID& getID() const { return id; }
	const sf::Vector2f& getSpriteScale();
	const sf::Vector2i& getTextureSize();
	const EntityType& getEntityType() const { return type; }
	const std::string& getAnimName();
	const Bitmask& getComponentSet() const { return componentSet; }

	bool isSpriteSheetEntity();
	bool isInUse() const { return inUse; }

	void toggleUse() { inUse = !inUse; }

	void addComponent(std::shared_ptr<Component> comp);
	bool hasComponent(Bitmask mask) const;
	Component* getComponent(ComponentID id);

protected:
	EntityType type;
	EntityID id;

	Entity* next;

	bool inUse;

	Bitmask componentSet;
	std::map<ComponentID, std::shared_ptr<Component>> map;
};