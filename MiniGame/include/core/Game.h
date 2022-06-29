#pragma once
#include "../core/Board.h"
#include "../graphics/Window.h"
#include "../entities/Player.h"
#include "../core/InputHandler.h"
#include "../architectures/EntityComponentSystem.h"
#include "../pool/EntityPools.h"
#include "../services/Audio.h"
#include <functional>

using OnCollisionCallback = std::function<void(Pool&)>;

enum class ECSArchitecture
{
	UNDEFINED = -1,
	BIGARRAY = 0,
	ARCHETYPES = 1,
	PACKEDARRAYS = 2
};

class System;

class Game
{
public:
	const int spriteWH{ 50 };
	const float tileScale{ 2.f };
	const float itemScale{ 1.f };

	Game(ECSArchitecture arch, bool enableDebug);
	~Game() {}

	void init(std::vector<std::string> lines);
	void addEntity(Entity* newEntity);

	void buildBoard(int width, int height);
	void initWindow(int width, int height);

	void handleInput();
	void update(float elapsed);
	void render(float elapsed);

	void setFPS(int FPS);

	void togglePause() { paused = !paused; }

	bool isPaused() const { return paused; }

	bool isMouseEnable() const { return mouseEnable; }
	void toggleMouseInput() { mouseEnable = !mouseEnable; }

	const EntityID& getIDCounter() const;
	const std::shared_ptr<Player>& getPlayer() const { return player; }
	std::unique_ptr<FirePool>& getFirePool() { return firePool; }

	Window* getWindow() { return &window; }
	sf::Time getElapsed() const;
private:
	void registerCallback(EntityID id, OnCollisionCallback func)
	{
		collisionCallbacks.emplace(id, func);
	}
private:
	Window window;
	bool paused;
	sf::Clock gameClock;
	sf::Time elapsed;

	std::unique_ptr<Board> board;
	int potions;

	EntityID entityCounter;

	std::shared_ptr<Player> player;

	std::unique_ptr<InputHandler> inputHandler;

	std::unique_ptr<EntityComponentSystem> ecs;
	ECSArchitecture ecsType;

	std::unique_ptr<PotionPool> potionPool;
	std::unique_ptr<LogPool> logPool;
	std::unique_ptr<FirePool> firePool;

	std::shared_ptr<Audio> audio;

	/*
	* Toggle Mouse Input
	*
	*/
	bool mouseEnable{ false };

	/*
	* Collision system
	* to store callback functions
	*/
	std::map<unsigned, OnCollisionCallback> collisionCallbacks;
};