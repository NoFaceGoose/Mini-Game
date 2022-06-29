#pragma once
#include <memory>
#include "Observer.h"

class Subject
{
public:
	Subject() :observer{ std::make_shared<AchievementManager>() } {}
	void notify(Event event)
	{
		observer->onNotify(event);
	}
	void initAchievements(int totalPotions)
	{
		observer->initAchievements(totalPotions);
	}

private:
	std::shared_ptr<Observer> observer;
};