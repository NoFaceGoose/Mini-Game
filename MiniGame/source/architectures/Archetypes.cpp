#include "../../include/architectures/Archetypes.h"
#include "../../include/architectures/Archetype.h"
#include "../../include/systems/Systems.h"
#include <iostream>

Archetypes::Archetypes() :EntityComponentSystem()
{
	init();
}

Archetypes::Archetypes(bool enableDebug) : EntityComponentSystem(enableDebug)
{
	init();
}

void Archetypes::init()
{
	Bitmask bStatic;
	bStatic.turnOnBit(static_cast<unsigned int>(ComponentID::POSITION));
	bStatic.turnOnBit(static_cast<unsigned int>(ComponentID::GRAPHICS));
	bStatic.turnOnBit(static_cast<unsigned int>(ComponentID::COLLIDER));
	archetypes.push_back(std::make_shared<Archetype>(bStatic));

	Bitmask Player;
	Player.turnOnBit(static_cast<unsigned int>(ComponentID::POSITION));
	Player.turnOnBit(static_cast<unsigned int>(ComponentID::GRAPHICS));
	Player.turnOnBit(static_cast<unsigned int>(ComponentID::HEALTH));
	Player.turnOnBit(static_cast<unsigned int>(ComponentID::INPUT));
	Player.turnOnBit(static_cast<unsigned int>(ComponentID::VELOCITY));
	Player.turnOnBit(static_cast<unsigned int>(ComponentID::COLLIDER));
	Player.turnOnBit(static_cast<unsigned int>(ComponentID::LOGIC));
	archetypes.push_back(std::make_shared<Archetype>(Player));

	Bitmask fire;
	fire.turnOnBit(static_cast<unsigned int>(ComponentID::POSITION));
	fire.turnOnBit(static_cast<unsigned int>(ComponentID::GRAPHICS));
	fire.turnOnBit(static_cast<unsigned int>(ComponentID::VELOCITY));
	fire.turnOnBit(static_cast<unsigned int>(ComponentID::TTL));
	archetypes.push_back(std::make_shared<Archetype>(fire));
}

void Archetypes::addEntity(Entity* entity)
{
	auto it{ archetypes.begin() };
	while (it != archetypes.end())
	{
		if ((*it)->getComponents().match(entity->getComponentSet()))
		{
			(*it)->addEntity(entity);
			break;
		}

		it++;
	}
}

void Archetypes::update(Game* game, float elapsed, bool isLogicSystem)
{
	std::vector<std::shared_ptr<System>>* sys;

	if (isLogicSystem)
	{
		sys = &logicSystems;
	}
	else
	{
		sys = &graphicsSystems;
	}

	auto itSys{ (*sys).begin() };

	while (itSys != (*sys).end())
	{
		auto itArch{ archetypes.begin() };

		while (itArch != archetypes.end())
		{
			if ((*itSys)->validate(itArch->get()))
			{
				auto& entities{ (*itArch)->getEntities() };

				auto itEnt{ entities.begin() };
				while (itEnt != entities.end())
				{
					if ((*itEnt)->isInUse())
					{
						(*itSys)->update(game, *itEnt, elapsed);
					}

					itEnt++;
				}
			}

			itArch++;
		}

		itSys++;
	}
}