#include "Walking.hpp"

namespace overmon
{

Walking::Walking(GridType gridX, GridType gridY, Direction direction, Sprite &sprite, DeltaTime off)
	: Timely(gridX, gridY, direction, sprite, off)
	, leg_(false)
	, xOriginal_(xGrid())
	, yOriginal_(yGrid())
{}

template <typename UnsignedType>
UnsignedType difference(UnsignedType num1, UnsignedType num2)
{
	return std::max(num1, num2) - std::min(num1, num2);
}

void Walking::update(const Global &global, DeltaTime delta)
{
	if (moving())
	{
		Movable::update(delta);
		sprite.setPosition(x(), y());
		sprite.setFrame(global.spriteManager(), characterFrame(leg_));
	}
	else
	{
		timerUpdate(delta);
		while (timerReset())
		{
			updateAction();
			leg_ = !leg_;
		}
	}

	uint8_t index = (global.animationCounterIndex() % 2) + (global.animationCounterIndex() == 1);
	sprite.setFrame(global.spriteManager(), characterDirectionFrame() + index);
}

void Walking::updateAction()
{
	// There are 8 possible actions. Two types of actions per direction (4 directions).
	// An NPC can either stay idle or not. If less than 4 idle otherwise move.
	const uint8_t action = rand() % 8;
	const Direction direction = static_cast<Direction>(action % 4);

	directionSet(direction);

	if (action > 4)
	{
		GridType xProposed = x() / 16;
		GridType yProposed = y() / 16;

		switch (direction)
		{
		case Direction::North:
			yProposed -= 1;
			break;
		case Direction::South:
			yProposed += 1;
			break;
		case Direction::East:
			xProposed += 1;
			break;
		case Direction::West:
			xProposed -= 1;
			break;
		}

		moveSpeed(difference(xProposed, xOriginal_) <= 2 && difference(yProposed, yOriginal_) <= 2);
	}
}

}
