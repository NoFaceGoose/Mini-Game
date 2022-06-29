#pragma once

#include "Components.h"

class HealthComponent : public Component
{
public:
	HealthComponent(int playerStartingHealth, int playerMaxHealth)
		: health{ playerStartingHealth },
		maxHealth{ playerMaxHealth }
	{}

	virtual const ComponentID getID() const { return ComponentID::HEALTH; }
	int getHealth() const { return health; }

	void changeHealth(int valueChange)
	{
		health += valueChange;

		if (health > maxHealth)
		{
			health = maxHealth;
		}
		else if (health < 0)
		{
			health = 0;
		}
	}

protected:
	int health;
	int maxHealth;
};