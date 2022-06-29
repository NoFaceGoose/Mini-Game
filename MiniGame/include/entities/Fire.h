#pragma once
#include "Entity.h"

class VelocityComponent;

class Fire : public Entity
{
public:
	const int startTimeToLive{ 150 }; //frames

	Fire();
	~Fire() {}

	int getTTL();
};