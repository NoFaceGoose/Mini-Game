#pragma once
#include "Command.h"
#include <memory>
#include <vector>

class InputHandler
{
public:
	InputHandler() :pauseCommand{ std::make_shared<PauseCommand>() }, toggleMouseCommand{ std::make_shared<ToggleMouseCommand>() }{}
	~InputHandler() {}

	std::shared_ptr<Command> handle();

private:
	std::shared_ptr<Command> pauseCommand;
	std::shared_ptr<Command> toggleMouseCommand;
};

class PlayerInputHandler
{
public:
	PlayerInputHandler() :moveUpCommand{ std::make_shared<MoveUpCommand>() },
		moveLeftCommand{ std::make_shared<MoveLeftCommand>() },
		moveDownCommand{ std::make_shared<MoveDownCommand>() },
		moveRightCommand{ std::make_shared<MoveRightCommand>() },
		attackCommand{ std::make_shared<AttackCommand>() },
		shoutCommand{ std::make_shared<ShoutCommand>() },
		mouseCommand{ std::make_shared<MouseCommand>() }
	{}

	~PlayerInputHandler() {}

	/*
	* handle all inputs of players
	* @note this function can determine the input methd
	* @param mouseInput get the mouse input status
	* @return command queue
	*/
	std::vector<std::shared_ptr<Command>>& handlePlayerInput(bool mouseInput);

private:
	std::vector<std::shared_ptr<Command>> playerCommands;
	std::shared_ptr<Command> moveUpCommand;
	std::shared_ptr<Command> moveLeftCommand;
	std::shared_ptr<Command> moveDownCommand;
	std::shared_ptr<Command> moveRightCommand;
	std::shared_ptr<Command> attackCommand;
	std::shared_ptr<Command> shoutCommand;
	std::shared_ptr<Command> mouseCommand;
};