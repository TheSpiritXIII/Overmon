#include "Timely.hpp"

namespace overmon
{

Timely::Timely(GridType gridX, GridType gridY, Direction direction, Sprite &sprite, DeltaTime off)
	: Movable(gridX, gridY, direction)
	, sprite(sprite)
	, timer_(-off)
{
	sprite.setPosition(x(), y());
}

void Timely::timerUpdate(DeltaTime delta)
{
	timer_ -= delta;
}

bool Timely::timerReset()
{
	if (timer_ <= 0)
	{
		timer_ += 1;
		return true;
	}
	return false;
}

}
