#include "../../include/components/LogicComponent.h"
#include "../../include/core/Game.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/entities/Fire.h"

PlayerStateComponent::PlayerStateComponent(int maxWood, int shootingCost, float shootCooldownTime) :
	wood{ 0 },
	maxWood{ maxWood },
	attacking{ false },
	shouting{ false },
	shootingCost{ shootingCost },
	shootCooldown{ 0.f },
	shootCooldownTime{ shootCooldownTime }
{}

void PlayerStateComponent::addWood(int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
	if (wood < 0) wood = 0;
}