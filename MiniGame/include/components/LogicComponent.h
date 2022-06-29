#pragma once

#include "Components.h"

class Entity;
class Game;

class LogicComponent : public Component
{
public:
	virtual const ComponentID getID() const { return ComponentID::LOGIC; }

	virtual bool isAttacking() const = 0;
	virtual void setAttacking(bool at) = 0;

	virtual bool isShouting() const = 0;
	virtual void setShouting(bool sh) = 0;

	virtual int getWood() const = 0;
	virtual void addWood(int w) = 0;

	virtual float getShootCooldown() const = 0;
	virtual void setShootCooldown(float s) = 0;
	virtual void reduceShootCooldown(float s) = 0;

	virtual float getShootCooldownTime() const = 0;

	virtual int getShootingCost() const = 0;
};

class PlayerStateComponent : public LogicComponent
{
public:
	PlayerStateComponent(int maxWood, int shootingCost, float shootCooldownTime);
	~PlayerStateComponent() {}

	virtual bool isAttacking() const override { return attacking; }
	virtual void setAttacking(bool at) override { attacking = at; }

	virtual bool isShouting() const override { return shouting; }
	virtual void setShouting(bool sh) override { shouting = sh; }

	virtual int getWood() const { return wood; }
	virtual void addWood(int w);

	virtual float getShootCooldown() const { return shootCooldown; }
	virtual void setShootCooldown(float s) { shootCooldown = s; }
	virtual void reduceShootCooldown(float s) { shootCooldown -= s; }

	virtual float getShootCooldownTime() const { return shootCooldownTime; }

	virtual int getShootingCost() const { return shootingCost; }

private:
	int wood;
	int maxWood;

	bool attacking;

	bool shouting;
	int shootingCost;
	float shootCooldown;
	float shootCooldownTime;
};