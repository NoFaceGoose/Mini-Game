#include "../../include/pool/EntityPools.h"
#include "../../include/entities/Player.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/TTLComponent.h"

FirePool::FirePool()
{
	firstAvailable = &fires[0];
	for (int i{ 0 }; i < FIRE_POOL_SIZE - 1; i++)
	{
		fires[i].setNext(&fires[i + 1]);
	}
	fires[FIRE_POOL_SIZE - 1].setNext(nullptr);
}

Fire* FirePool::createFire(const std::string& filename)
{
	assert(firstAvailable != nullptr);

	Fire* newFire{ firstAvailable };
	firstAvailable = static_cast<Fire*>(newFire->getNext());

	newFire->init(filename, std::make_shared<SpriteGraphicsComponent>(1.f));
	return newFire;
}

Fire* FirePool::activate(Player* player)
{
	assert(firstAvailable != nullptr);

	firstAvailable->toggleUse();

	Fire* fire{ firstAvailable };

	firstAvailable = static_cast<Fire*>(firstAvailable->getNext());

	return fire;
}

void FirePool::update()
{
	for (int i{ 0 }; i < FIRE_POOL_SIZE; i++)
	{
		if (!fires[i].isInUse())
		{
			fires[i].setNext(firstAvailable);
			firstAvailable = &fires[i];
		}
	}
}