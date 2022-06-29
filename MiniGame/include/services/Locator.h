#pragma once
#include "Audio.h"

class Locator
{
public:
	static void initialize();
	static std::shared_ptr<Audio> getAuido();
	static void provide(std::shared_ptr<Audio> service);
};