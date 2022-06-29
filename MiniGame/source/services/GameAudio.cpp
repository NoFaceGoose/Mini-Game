#include "../../include/services/Audio.h"

GameAudio::GameAudio()
{
	registerSound(S_CAST_FIREBALL);
	registerSound(S_DRINK_POTION);
	registerSound(S_AXE_CHOP);
}

void GameAudio::registerSound(const char* path)
{
	std::shared_ptr<sf::SoundBuffer> buffer{ std::make_shared<sf::SoundBuffer>() };
	buffer->loadFromFile(path);
	buffers.push_back(buffer);
	sf::Sound sound;
	sound.setBuffer(*buffer.get());
	sounds.push_back(sound);
}

void GameAudio::playSound(Audios soundID)
{
	sounds[static_cast<int>(soundID)].play();
}

void GameAudio::loopSound(Audios soundID)
{
	sounds[static_cast<int>(soundID)].play();
	sounds[static_cast<int>(soundID)].setLoop(true);
}

void GameAudio::stopAllSounds()
{
	auto soundIt{ sounds.begin() };
	while (soundIt != sounds.end())
	{
		soundIt->stop();
		soundIt++;
	}
}

void GameAudio::stopSound(Audios soundID)
{
	sounds[static_cast<int>(soundID)].stop();
}