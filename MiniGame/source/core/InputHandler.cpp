#include "../../include/core/InputHandler.h"
#include <SFML/Graphics.hpp>

std::shared_ptr<Command> InputHandler::handle()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		return pauseCommand;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		return toggleMouseCommand;
	}

	return nullptr;
}

std::vector<std::shared_ptr<Command>>& PlayerInputHandler::handlePlayerInput(bool mouseInput)
{
	playerCommands.clear();
	if (!mouseInput)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			playerCommands.push_back(moveUpCommand);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			playerCommands.push_back(moveLeftCommand);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			playerCommands.push_back(moveDownCommand);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			playerCommands.push_back(moveRightCommand);
		}
	}
	else
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			playerCommands.push_back(mouseCommand);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		playerCommands.push_back(attackCommand);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		playerCommands.push_back(shoutCommand);
	}
	return playerCommands;
}