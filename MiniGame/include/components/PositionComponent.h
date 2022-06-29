#pragma once

#include "../utils/Vector2.h"
#include "Components.h"

class PositionComponent : public Component
{
public:
	virtual const ComponentID getID() const { return ComponentID::POSITION; }
	const Vector2f& getPosition() const { return position; }
	void setPosition(float x, float y) { position.x = x; position.y = y; }

private:
	Vector2f position;
};