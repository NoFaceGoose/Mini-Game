#pragma once
#include "../entities/StaticEntities.h"
#include "../entities/Fire.h"
#include <cassert>

const int spriteWH{ 50 };
const float tileScale{ 2.f };
const float itemScale{ 1.f };

// template <typename entityName>
class Pool
{
public:
	virtual Entity* create(const std::string& filename, int col, int row) = 0;
	virtual int getPoolSize() const = 0;
	virtual Entity& getAt(int index) = 0;
	virtual Entity* getPool() = 0;
	virtual void update() = 0;
};

const int POTION_POOL_SIZE{ 6 };
class PotionPool : public Pool
{
public:
	PotionPool();
	Potion* create(const std::string& filename, int col, int row) override;
	void update() override;

	int getPoolSize() const override { return POTION_POOL_SIZE; }
	Potion& getAt(int index) override;
	Potion* getPool() override;

private:
	Potion potions[POTION_POOL_SIZE];
	Potion* firstAvailable;
};

const int LOG_POOL_SIZE{ 10 };
class LogPool : public Pool
{
public:
	LogPool();
	Log* create(const std::string& filename, int col, int row) override;
	void update() override;

	int getPoolSize() const  override { return LOG_POOL_SIZE; }
	Log& getAt(int index)override;
	Log* getPool() override;

private:
	Log logs[LOG_POOL_SIZE];
	Log* firstAvailable;
};

const float fireSpeed{ 200.f };
const int FIRE_POOL_SIZE{ 2 };
class FirePool
{
public:
	FirePool();
	Fire* createFire(const std::string& filename);

	/*
	* activate the fire
	* @note call this function only when the player launchs a fire ball
	* @param player The pointer to the player entity
	*/
	Fire* activate(Player* player);
	void update();

private:
	Fire fires[FIRE_POOL_SIZE];
	Fire* firstAvailable;
};