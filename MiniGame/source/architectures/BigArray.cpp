#include "../../include/architectures/BigArray.h"
#include "../../include/systems/Systems.h"

void BigArray::update(Game* game, float elapsed, bool isLogicSystem)
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
		auto itEnt{ entities.begin() };

		while (itEnt != entities.end())
		{
			if ((*itEnt)->isInUse() && (*itSys)->validate(*itEnt))
			{
				(*itSys)->update(game, *itEnt, elapsed);
			}

			itEnt++;
		}

		itSys++;
	}
}