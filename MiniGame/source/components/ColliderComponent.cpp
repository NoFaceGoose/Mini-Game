#include "../../include/components/ColliderComponent.h"
#include "../../include/graphics/Window.h"

bool ColliderComponent::interesects(ColliderComponent* colliderComp)
{
	return boundingBox.intersects(colliderComp->getBoundingBox());
}