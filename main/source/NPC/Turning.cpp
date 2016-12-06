#include "Turning.hpp"

namespace overmon
{

Turning::Turning(GridType gridX, GridType gridY, Direction direction, Sprite &sprite, DeltaTime off)
	: Movable(gridX, gridY, direction)
	, sprite(sprite)
	, timer_(-off)
{
	sprite.setPosition(x(), y());
}

void Turning::update(Global &global, DeltaTime delta)
{
	timerUpdate(delta);
	while (timerReset())
	{
		directionSet(static_cast<Direction>(rand() % 4));
		sprite.setFrame(global.spriteManager(), characterDirectionFrame());
	}
}

void Turning::timerUpdate(DeltaTime delta)
{
	timer_ -= delta;
}

bool Turning::timerReset()
{
	if (timer_ <= 0)
	{
		timer_ += 1;
		return true;
	}
	return false;
}

}
