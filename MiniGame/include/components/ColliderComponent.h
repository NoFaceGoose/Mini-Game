#pragma once
#include "../utils/Rectangle.h"
#include "Components.h"

class Window;

class ColliderComponent : public Component
{
public:
	virtual const ComponentID getID() const { return ComponentID::COLLIDER; }
	Rectangle& getBoundingBox() { return boundingBox; }
	const Vector2f& getBBoxSize() const { return bboxSize; }

	void setBBoxSize(Vector2f size) { bboxSize = size; }

	bool interesects(ColliderComponent* colliderComp);

private:
	Rectangle boundingBox;
	Vector2f bboxSize;
};