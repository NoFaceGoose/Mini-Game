#include "../../include/core/Game.h"
#include "../../include/entities/Fire.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/core/Command.h"
#include "../../include/architectures/BigArray.h"
#include "../../include/architectures/Archetype.h"
#include "../../include/architectures/Archetypes.h"
#include "../../include/architectures/PackedArrays.h"
#include "../../include/services/Locator.h"

Game::Game(ECSArchitecture arch, bool enableDebug) :
	paused{ false },
	potions{ 0 },
	entityCounter{ 0 },
	inputHandler{ std::make_unique<InputHandler>() },
	ecsType{ arch },
	potionPool{ std::make_unique<PotionPool>() },
	logPool{ std::make_unique<LogPool>() },
	firePool{ std::make_unique<FirePool>() }
{
	/*Locator*/
	audio = std::make_shared<GameAudio>();
	Locator::initialize();
	Locator::provide(audio);
	/*Locator*/

	if (enableDebug)
	{
		std::shared_ptr<Audio> service{ std::make_shared<LoggedAudio>(Locator::getAuido()) };
		Locator::provide(service);
	}

	/****************************************/
	switch (ecsType)
	{
	case ECSArchitecture::BIGARRAY:
		ecs = std::make_unique<BigArray>(enableDebug);
		break;

	case ECSArchitecture::ARCHETYPES:
		ecs = std::make_unique<Archetypes>(enableDebug);
		break;

	case ECSArchitecture::PACKEDARRAYS:
		ecs = std::make_unique<PackedArrays>(enableDebug);
		break;

	default:
		break;
	}
}

void Game::buildBoard(int width, int height)
{
	board = std::make_unique<Board>(width, height);
}

void Game::initWindow(int width, int height)
{
	int wdt{ static_cast<int>(width * spriteWH * tileScale) };
	int hgt{ static_cast<int>(height * spriteWH * tileScale) };
	window.setSize(sf::Vector2u(wdt, hgt));
	window.redraw();
}

void Game::init(std::vector<std::string> lines)
{
	int h(lines.size() - 1);
	if (h < 0)
		throw std::exception("No data in level file");
	int w{ -1 };

	window.loadFont("font/AmaticSC-Regular.ttf");
	window.setTitle("Mini-Game");

	auto it{ lines.cbegin() };
	int row{ 0 };
	while (it != lines.cend())
	{
		int col{ 0 };

		if (w == -1)
		{
			w = it->size();
			buildBoard(w, h);
			initWindow(w, h);
		}

		auto is{ it->cbegin() };
		while (is != it->cend())
		{
			switch (*is)
			{
			case '.':
			{
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}

			case 'w':
			{
				board->addTile(col, row, tileScale, TileType::WALL);
				break;
			}

			case 'x':
			{
				addEntity(logPool->create("img/log.png", col, row));
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}

			case 'p':
			{
				addEntity(potionPool->create("img/potion.png", col, row));
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				potions++;
				break;
			}

			case '*':
			{
				player = std::make_shared<Player>();
				player->init("img/DwarfSpriteSheet_data.txt", std::make_shared<SpriteSheetGraphicsComponent>());
				player->positionSprite(row, col, spriteWH, tileScale);
				addEntity(player.get());

				/*
				* Bind callback functions
				*/
				std::function<void(Pool&)> func1{ std::bind(&Player::onCollisionLog, player, std::placeholders::_1) };
				registerCallback(static_cast<int>(EntityType::LOG), func1);
				std::function<void(Pool&)> func2{ std::bind(&Player::onCollisionPotion, player, std::placeholders::_1) };
				registerCallback(static_cast<int>(EntityType::POTION), func2);

				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			}
			col++; is++;
		}
		row++; it++;
	}

	// initialize total potions
	player->initAchievements(potions);

	// Technically, how many fire objects should be created at the beginning how many at most they can appear on the screen at the same time, 
	// which involves the cooldown time and the value of target frame (ttl decrease by 1 for each frame)
	// Here two fire objects should be enough for current settings
	addEntity(firePool->createFire("img/fire.png"));
	addEntity(firePool->createFire("img/fire.png"));
}

void Game::addEntity(Entity* newEntity)
{
	entityCounter++;
	newEntity->setID(entityCounter);
	ecs->addEntity(newEntity);
}

void Game::handleInput()
{
	auto command{ inputHandler->handle() };

	if (command)
	{
		command->execute(*this);
	}
}

void Game::update(float elapsed)
{
	if (paused == false)
	{
		ecs->update(this, elapsed);

		if (collisionCallbacks.find(static_cast<EntityID>(EntityType::LOG)) != collisionCallbacks.end())
			collisionCallbacks.at(static_cast<EntityID>(EntityType::LOG))(*logPool.get());
		if (collisionCallbacks.find(static_cast<EntityID>(EntityType::POTION)) != collisionCallbacks.end())
			collisionCallbacks.at(static_cast<EntityID>(EntityType::POTION))(*potionPool.get());

		// update the state of use (inUse) of each entity
		potionPool->update();
		logPool->update();
		firePool->update();
	}

	// Update the window for refreshing the graphics
	window.update();
}

void Game::render(float elapsed)
{
	// Empty the screen
	window.beginDraw();

	board->draw(&window);

	ecs->update(this, elapsed, false);

	// Draw FPS
	window.drawGUI(*this);

	// Close up for this frame.
	window.endDraw();
}

sf::Time Game::getElapsed() const
{
	return gameClock.getElapsedTime();
}

void Game::setFPS(int FPS)
{
	auto text("FPS: " + std::to_string(FPS));
	window.getFPSText().setString(text);
}

const EntityID& Game::getIDCounter() const
{
	return entityCounter;
}