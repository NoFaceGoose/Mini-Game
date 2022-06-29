#pragma once

class Game;

class Command
{
public:
	Command() {}
	virtual ~Command() {}

	virtual void execute(Game& game) = 0;
};

class PauseCommand : public Command
{
public:
	PauseCommand() {}
	~PauseCommand() {}

	virtual void execute(Game& game) override;
};

class MoveUpCommand : public Command
{
public:
	MoveUpCommand() {}
	~MoveUpCommand() {}

	virtual void execute(Game& game) override;
};

class MoveLeftCommand : public Command
{
public:
	MoveLeftCommand() {}
	~MoveLeftCommand() {}

	virtual void execute(Game& game) override;
};

class MoveDownCommand : public Command
{
public:
	MoveDownCommand() {}
	~MoveDownCommand() {}

	virtual void execute(Game& game) override;
};

class MoveRightCommand : public Command
{
public:
	MoveRightCommand() {}
	~MoveRightCommand() {}

	virtual void execute(Game& game) override;
};

class AttackCommand : public Command
{
public:
	AttackCommand() {}
	~AttackCommand() {}

	virtual void execute(Game& game) override;
};

class ShoutCommand : public Command
{
public:
	ShoutCommand() {}
	~ShoutCommand() {}

	virtual void execute(Game& game) override;
};

class ToggleMouseCommand : public Command
{
public:
	ToggleMouseCommand() {}
	~ToggleMouseCommand() {}

	virtual void execute(Game& game) override;
};

class MouseCommand : public Command
{
public:
	MouseCommand() {}
	~MouseCommand() {}

	virtual void execute(Game& game) override;
};