#include "../../include/graphics/AnimDirectional.h"
#include "../../include/graphics/SpriteSheet.h"

void AnimDirectional::frameStep()
{
	//Advance to the next frame in the sheet.
	if (startFrame < endFrame)	curFrame++;
	else						curFrame--; //Backwards animations

	//We reached the end.
	if ((startFrame < endFrame && curFrame > endFrame) || (startFrame > endFrame && curFrame < endFrame))
	{
		if (loop)
		{
			//If looping, back to start.
			curFrame = startFrame;
			return;
		}

		//Get to the end of the animation and pause the play.
		curFrame = endFrame;
		pause();
	}
}

void AnimDirectional::cropSprite()
{
	const auto spriteSize{ spriteSheet->getSpriteSize() };
	int numAnimations{ spriteSheet->getNumAnimations() };
	int x{ spriteSize.x * curFrame };
	int y{ spriteSize.y * (frameRow + numAnimations * static_cast<short>(spriteSheet->getSpriteDirection())) };
	sf::IntRect rect(x, y, spriteSize.x, spriteSize.y);
	spriteSheet->cropSprite(rect);
}

void AnimDirectional::readIn(std::stringstream& st)
{
	st >> startFrame >> endFrame >> frameRow >> frameTime >> frameActionStart >> frameActionEnd;
}