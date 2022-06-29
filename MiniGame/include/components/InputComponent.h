#pragma once

#include<memory>
#include "Components.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Game.h"

class InputComponent : public Component
{
public:
	virtual ~InputComponent() {}
	virtual void update(Game& game) {}
	virtual const ComponentID getID() const { return ComponentID::INPUT; }

	virtual const std::shared_ptr<PlayerInputHandler> getPlayerInputHandler() const { return nullptr; }
};

class PlayerInputComponent : public InputComponent
{
public:
	PlayerInputComponent() :playerInputHandler{ std::make_unique<PlayerInputHandler>() } {}
	~PlayerInputComponent() {}
	virtual const std::shared_ptr<PlayerInputHandler> getPlayerInputHandler() const override { return playerInputHandler; }

private:
	std::shared_ptr<PlayerInputHandler> playerInputHandler;
};