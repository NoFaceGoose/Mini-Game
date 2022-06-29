#include "../../include/utils/Rectangle.h"

bool Rectangle::inside(float x, float y) const
{
	if (x >= std::min(topLeft.x, bottomRight.x)
		&& x <= std::max(topLeft.x, bottomRight.x)
		&& y >= std::min(topLeft.y, bottomRight.y)
		&& y <= std::max(topLeft.y, bottomRight.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Rectangle::intersects(const Rectangle& rect) const
{
	if (inside(rect.topLeft) || inside(rect.bottomRight)
		|| inside(rect.topLeft.x, rect.bottomRight.y) || inside(rect.bottomRight.x, rect.topLeft.y)
		|| rect.inside(topLeft) || rect.inside(bottomRight)
		|| rect.inside(topLeft.x, bottomRight.y) || rect.inside(bottomRight.x, topLeft.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}