#pragma once
#include "../utils/Vector2.h"
#include "Components.h"

class Entity;

class VelocityComponent : public Component
{
public:
	VelocityComponent(float speedValue = 1.f) :speed{ speedValue } {}

	const Vector2f& getVelocity() const { return velocity; }
	float getSpeed() const { return speed; }
	virtual const ComponentID getID() const { return ComponentID::VELOCITY; }

	void setVelocity(float x, float y) { velocity.x = x; velocity.y = y; }

private:
	Vector2f velocity;
	float speed;
};