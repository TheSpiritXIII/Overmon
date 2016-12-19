#include "Turning.hpp"

namespace overmon
{

Turning::Turning(GridType gridX, GridType gridY, Direction direction, Sprite &sprite, DeltaTime off)
	: Timely(gridX, gridY, direction, sprite, off)
{
	sprite.setPosition(x(), y());
}

void Turning::update(const Global &global, DeltaTime delta)
{
	timerUpdate(delta);
	while (timerReset())
	{
		directionSet(static_cast<Direction>(rand() % 4));
		sprite.setFrame(global.spriteManager(), characterDirectionFrame());
	}
}


}
