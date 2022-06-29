#pragma once
#include "Event.h"
#include "Achievement.h"

class Entity;

class Observer
{
public:
	virtual ~Observer() {}
	virtual bool onNotify(Event event) = 0;
	virtual void initAchievements(int tp) = 0;
};

class AchievementManager : public Observer
{
public:
	AchievementManager() : collectedPotions{ 0 }, shouts{ 0 }, totalPotions{ 0 }{}

	virtual bool onNotify(Event event) override
	{
		switch (event) {
		case Event::COLLECTPOTION:
		{
			collectedPotions++;
			if (collectedPotions == totalPotions)
			{
				unlockAchievement(Achievement(AchievementType::POTION));
			}
			return true;
		}
		case Event::SHOUT:
		{
			shouts++;
			if (shouts == 5)
			{
				unlockAchievement(Achievement(AchievementType::SHOUT));
			}
			return true;
		}
		default:
			return false;
		}
	}

	virtual void initAchievements(int tp) override
	{
		totalPotions = tp;
	}

private:
	int collectedPotions;
	int shouts;
	int totalPotions;

	void unlockAchievement(Achievement a) {
		a.unlock();
	}
};