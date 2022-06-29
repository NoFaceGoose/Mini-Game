#include "../../include/pool/EntityPools.h"
#include "../../include/entities/Player.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/services/Locator.h"

PotionPool::PotionPool()
{
	firstAvailable = &potions[0];
	for (int i{ 0 }; i < POTION_POOL_SIZE - 1; i++)
	{
		potions[i].setNext(&potions[i + 1]);
	}
	potions[POTION_POOL_SIZE - 1].setNext(nullptr);
}

Potion* PotionPool::create(const std::string& filename, int col, int row)
{
	assert(firstAvailable != nullptr);

	Potion* newPotion{ firstAvailable };
	firstAvailable = static_cast<Potion*>(newPotion->getNext());

	float x{ col * spriteWH * tileScale };
	float y{ row * spriteWH * tileScale };
	float cntrFactor{ (tileScale - itemScale) * spriteWH * 0.5f };

	dynamic_cast<PositionComponent*>(newPotion->getComponent(ComponentID::POSITION))->setPosition(x + cntrFactor, y + cntrFactor);
	newPotion->init(filename, std::make_shared<SpriteGraphicsComponent>(itemScale));

	return newPotion;
}

void PotionPool::update()
{
	for (int i{ 0 }; i < POTION_POOL_SIZE; i++)
	{
		if (!potions[i].isInUse())
		{
			potions[i].setNext(firstAvailable);
			firstAvailable = &potions[i];
		}
	}
}

Potion& PotionPool::getAt(int index)
{
	if (index >= 0 && index < POTION_POOL_SIZE)
		return potions[index];
	throw std::exception("Potion Index Out of Range!");
}

Potion* PotionPool::getPool()
{
	return potions;
}