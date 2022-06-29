#include "../../include/pool/EntityPools.h"
#include "../../include/entities/Player.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/services/Locator.h"

LogPool::LogPool()
{
	firstAvailable = &logs[0];
	for (int i{ 0 }; i < LOG_POOL_SIZE - 1; i++)
	{
		logs[i].setNext(&logs[i + 1]);
	}
	logs[LOG_POOL_SIZE - 1].setNext(nullptr);
}

Log* LogPool::create(const std::string& filename, int col, int row)
{
	assert(firstAvailable != nullptr);

	Log* newLog{ firstAvailable };
	firstAvailable = static_cast<Log*>(newLog->getNext());

	float x{ col * spriteWH * tileScale };
	float y{ row * spriteWH * tileScale };
	float cntrFactor{ (tileScale - itemScale) * spriteWH * 0.5f };

	dynamic_cast<PositionComponent*>(newLog->getComponent(ComponentID::POSITION))->setPosition(x + cntrFactor, y + cntrFactor);
	newLog->init(filename, std::make_shared<SpriteGraphicsComponent>(itemScale));

	return newLog;
}

void LogPool::update()
{
	for (int i{ 0 }; i < LOG_POOL_SIZE; i++)
	{
		if (!logs[i].isInUse())
		{
			logs[i].setNext(firstAvailable);
			firstAvailable = &logs[i];
		}
	}
}

Log& LogPool::getAt(int index)
{
	if (index >= 0 && index < LOG_POOL_SIZE)
		return logs[index];
	throw std::exception("Log Index Out of Range!");
}

Log* LogPool::getPool()
{
	return logs;
}