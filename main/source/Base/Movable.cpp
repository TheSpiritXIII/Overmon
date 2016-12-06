#include "Movable.hpp"
#include "Util/Debug.hpp"

namespace overmon
{

Movable::Movable(GridType gridX, GridType gridY, Direction direction)
	: xGrid_(gridX)
	, yGrid_(gridY)
	, x_(gridX * 16)
	, y_(gridY * 16)
	, direction_(direction)
	, speed_(0)
	, counter_(0)
	, moving_(false)
	, moveCounter_(0)
{}

PositionType Movable::x() const
{
	return x_;
}

PositionType Movable::y() const
{
	return y_;
}

PositionType Movable::xGrid() const
{
	return xGrid_;
}

PositionType Movable::yGrid() const
{
	return yGrid_;
}

Direction Movable::direction() const
{
	return direction_;
}

void Movable::directionSet(Direction direction)
{
	direction_ = direction;
}

void Movable::moveSpeed(uint8_t speed)
{
	speed_ = speed;
	moving_ = speed_ != 0;

	switch (direction_)
	{
	case Direction::North:
		yGrid_ -= moving_;
		break;
	case Direction::South:
		yGrid_ += moving_;
		break;
	case Direction::East:
		xGrid_ += moving_;
		break;
	case Direction::West:
		xGrid_ -= moving_;
		break;
	}
}

uint8_t Movable::moveCounter() const
{
	return moveCounter_;
}

bool Movable::moving() const
{
	return moving_;
}

uint8_t Movable::characterDirectionFrame() const
{
	return characterDirectionFrame(direction());
}

uint8_t Movable::characterFrame(bool leg) const
{
	return characterFrame(direction(), moveCounter(), leg);
}

void Movable::update(DeltaTime delta)
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

uint8_t Movable::characterDirectionFrame(Direction direction)
{
	return static_cast<uint8_t>(direction) * 3;
}

uint8_t Movable::characterFrame(Direction direction, uint8_t counter, bool leg)
{
	uint8_t index = characterDirectionFrame(direction) + (counter / 8);
	if (index == 1 && leg)
	{
		index = 2;
	}
	return index;
}

}
