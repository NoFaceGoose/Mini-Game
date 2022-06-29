#include "../../include/services/Locator.h"

static std::shared_ptr<Audio> service_;

void Locator::initialize()
{
	service_ = std::make_shared<NullAudio>();
}

std::shared_ptr<Audio> Locator::getAuido()
{
	return service_;
}

void Locator::provide(std::shared_ptr<Audio> service)
{
	if (service == nullptr)
	{
		service_ = std::make_shared<NullAudio>();
	}
	else
	{
		service_ = service;
	}
}

