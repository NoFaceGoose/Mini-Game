#include "../../include/entities/Fire.h"
#include "../components/VelocityComponent.h"
#include "../components/TTLComponent.h"

Fire::Fire() :
	Entity{ EntityType::FIRE }
{
	inUse = false;
	addComponent(std::make_shared<TTLComponent>(startTimeToLive));
	addComponent(std::make_shared<VelocityComponent>());
}

int Fire::getTTL()
{
	return dynamic_cast<TTLComponent*>(getComponent(ComponentID::TTL))->getTTL();
}