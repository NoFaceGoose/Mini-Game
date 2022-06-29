#pragma once
#include "Components.h"

class TTLComponent : public Component
{
public:
	TTLComponent(int ttlValue) :ttl{ ttlValue }, maxTTL{ ttlValue } {}
	void decrease() { ttl = ttl > 0 ? ttl - 1 : ttl; }
	int getTTL() const { return ttl; }
	void recoverTTL() { ttl = maxTTL; };
	virtual const ComponentID getID() const { return ComponentID::TTL; }

private:
	int ttl;
	int maxTTL;
};