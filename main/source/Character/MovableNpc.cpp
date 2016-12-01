#include "MovableNpc.hpp"

namespace overmon
{

MovableNpc::MovableNpc(GridType gridX, GridType gridY, Direction direction)
	: gridX_(gridX)
	, gridY_(gridY)
	, x_(gridX * 16)
	, y_(gridY * 16)
	, direction_(direction)
, moving_(0)

, counter_(0)
, moveCounter_(0)
{}

PositionType MovableNpc::x() const
{
	return x_;
}

PositionType MovableNpc::y() const
{
	return y_;
}

Direction MovableNpc::direction() const
{
	return direction_;
}

void MovableNpc::directionSet(Direction direction)
{
	direction_ = direction;
}

void MovableNpc::moveSpeed(uint8_t speed)
{
	moving_ = 1;
	speed_ = speed;
}

uint8_t MovableNpc::moveCounter() const
{
	return moveCounter_;
}

bool MovableNpc::moving() const
{
	return moving_;
}

void MovableNpc::update(DeltaTime delta)
{
	if (moving_ != 0)
	{
		uint8_t steps = 0;
		counter_ += speed_ * 60 * delta;
		while (counter_ >= 1)
		{
			steps += 1;
			counter_ -= 1;
		}

		moveCounter_ += steps;
		if (moveCounter_ >= 16)
		{
			counter_ += moveCounter_ - 16;
			moveCounter_ = 0;
			moving_ = false;

			switch (direction_)
			{
			case Direction::North:
				gridY_ -= 1;
				break;
			case Direction::South:
				gridY_ += 1;
				break;
			case Direction::East:
				gridX_ += 1;
				break;
			case Direction::West:
				gridX_ -= 1;
				break;
			}
		}

		switch (direction_)
		{
		case Direction::North:
			y_ -= steps;
			break;
		case Direction::South:
			y_ += steps;
			break;
		case Direction::East:
			x_ += steps;
			break;
		case Direction::West:
			x_ -= steps;
			break;
		}
	}
}

}
