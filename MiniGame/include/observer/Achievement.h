#pragma once
#include <iostream>

enum class AchievementType
{
	UNDEFINED = -1,
	POTION = 0,
	SHOUT = 1
};

class Achievement
{
public:
	Achievement(AchievementType achievementTypetype) :type{ achievementTypetype } {}

	/*
	* unlock this achievement
	* @note the achievement type is fixed once the class is instantiated
	*/
	void unlock()
	{
		switch (type)
		{
		case AchievementType::POTION:
		{
			std::cout << "I want them all! Achievement unclocked: You have collected all potions." << std::endl;
			break;
		}
		case AchievementType::SHOUT:
		{
			std::cout << "Feel my wrath! Achievement unclocked: You have shouted 5 times." << std::endl;
			break;
		}
		case AchievementType::UNDEFINED:
		{
			std::cout << "Undefined Achievement" << std::endl;
			break;
		}
		default:
			break;
		}
	}

private:
	AchievementType type;
};