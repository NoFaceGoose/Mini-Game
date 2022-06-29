#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/entities/Player.h"


void MoveUpCommand::execute(Game& game)
{
	auto v{ dynamic_cast<VelocityComponent*>(game.getPlayer()->getComponent(ComponentID::VELOCITY)) };
	v->setVelocity(v->getVelocity().x, -1.f);
}

void MoveLeftCommand::execute(Game& game)
{
	auto v{ dynamic_cast<VelocityComponent*>(game.getPlayer()->getComponent(ComponentID::VELOCITY)) };
	v->setVelocity(-1.f, v->getVelocity().y);
}

void MoveDownCommand::execute(Game& game)
{
	auto v{ dynamic_cast<VelocityComponent*>(game.getPlayer()->getComponent(ComponentID::VELOCITY)) };
	v->setVelocity(v->getVelocity().x, 1.f);
}

void MoveRightCommand::execute(Game& game)
{
	auto v{ dynamic_cast<VelocityComponent*>(game.getPlayer()->getComponent(ComponentID::VELOCITY)) };
	v->setVelocity(1.f, v->getVelocity().y);
}

void AttackCommand::execute(Game& game)
{
	game.getPlayer()->setAttacking(true);
}

void ShoutCommand::execute(Game& game)
{
	game.getPlayer()->setShouting(true);
}

void MouseCommand::execute(Game& game)
{
	sf::Vector2i globalPos{ sf::Mouse::getPosition() };
	sf::Vector2i winPos{ game.getWindow()->getPosition() };
	sf::Vector2i relativePos{ globalPos - winPos };
	Vector2f playerPos{ game.getPlayer()->getPosition() };
	sf::Vector2f dis{ sf::Vector2f(static_cast<float>(relativePos.x) - playerPos.x,
		static_cast<float>(relativePos.y) - playerPos.y) };
	auto v{ dynamic_cast<VelocityComponent*>(game.getPlayer()->getComponent(ComponentID::VELOCITY)) };
	v->setVelocity(
		dis.x > 0.f ? 1.f : -1.f,
		dis.y > 0.f ? 1.f : -1.f
	);
}