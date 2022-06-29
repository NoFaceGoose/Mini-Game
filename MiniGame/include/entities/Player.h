#pragma once
#include "Entity.h"
#include "../components/HealthComponent.h"
#include "../components/ColliderComponent.h"
#include "../components/LogicComponent.h"
#include "../observer/Subject.h"
#include "../components/PositionComponent.h"

class Fire;
class VelocityComponent;
class Pool;

class Player : public Entity
{
public:
	const float playerSpeed{ 100.f };
	const int startingHealth{ 60 };
	const int maxHealth{ 100 };
	const int maxWood{ 100 };
	const int shootingCost{ 20 };
	const float shootCooldownTime{ 3.f }; //in seconds

	Player();
	~Player() {}

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override;

	bool isAttacking();
	void setAttacking(bool at);

	bool isShouting();
	void setShouting(bool sh);

	int getWood();
	void addWood(int w);

	Subject& getAchievements() { return achievements; }

	const Vector2f getPosition() { return dynamic_cast<PositionComponent*>(getComponent(ComponentID::POSITION))->getPosition(); }

	void positionSprite(int row, int col, int spriteWH, float tileScale);

	bool collidesWith(Entity& other);

	/*
	* Callback functions for collsion system
	*/
	void onCollisionPotion(Pool& p);
	void onCollisionLog(Pool& p);

	void initAchievements(int totalPotions) { achievements.initAchievements(totalPotions); }

private:
	Subject achievements;
};