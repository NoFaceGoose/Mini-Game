#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

#define S_CAST_FIREBALL "Audios/442827.wav"
#define S_DRINK_POTION "Audios/574077.wav"
#define S_AXE_CHOP "Audios/205515.wav"
#define NUM_SOUNDS 3

enum class Audios {
	CAST_FIREBALL = 0,
	DRINK_POTION = 1,
	AXE_CHOP = 2
};

class Audio
{
public:
	virtual ~Audio() {}
	virtual void playSound(Audios soundID) = 0;
	virtual void registerSound(const char* path) = 0;
	virtual void loopSound(Audios soundID) = 0;
	virtual void stopSound(Audios soundID) = 0;
	virtual void stopAllSounds() = 0;
};

class NullAudio : public Audio
{
	virtual void playSound(Audios soundID) {}
	virtual void registerSound(const char* path) {}
	virtual void loopSound(Audios soundID) {}
	virtual void stopSound(Audios soundID) {}
	virtual void stopAllSounds() {}
};

class LoggedAudio : public Audio
{
public:
	LoggedAudio(std::shared_ptr<Audio> wrapped) :wrapped_(wrapped) {}

	virtual void playSound(Audios ID) override
	{
		wrapped_->playSound(ID);
	}

	virtual void loopSound(Audios ID) override
	{
		wrapped_->loopSound(ID);
	}

	virtual void registerSound(const char* path) override
	{
		wrapped_->registerSound(path);
	}

	virtual void stopAllSounds() override
	{
		wrapped_->stopAllSounds();
	}

	virtual void stopSound(Audios ID) override
	{
		wrapped_->stopSound(ID);
	}

private:
	std::shared_ptr<Audio> wrapped_;
};

class GameAudio : public Audio
{
public:
	GameAudio();
	virtual void playSound(Audios soundID) override;
	virtual void registerSound(const char* path) override;
	virtual void loopSound(Audios soundID) override;
	virtual void stopSound(Audios soundID) override;
	virtual void stopAllSounds() override;

private:
	std::vector<sf::Sound> sounds;
	std::vector<std::shared_ptr<sf::SoundBuffer>> buffers;
};