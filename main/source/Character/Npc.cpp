#include "Npc.hpp"

namespace overmon
{

Npc::Npc(size_t gridX, size_t gridY, Direction direction)
	: gridX_(gridX)
	, gridY_(gridY)
	, x_(gridX * 16)
	, y_(gridY * 16)
	, direction_(direction)
, moving_(0)

, counter_(0)
, moveCounter_(0)
{}

Direction Npc::direction() const
{
	return direction_;
}

void Npc::directionSet(Direction direction)
{
	direction_ = direction;
}

void Npc::moveSpeed(uint8_t speed)
{
	moving_ = 1;
	speed_ = speed;
}

int16_t Npc::x() const
{
	return x_;
}

int16_t Npc::y() const
{
	return y_;
}

void Npc::update(DeltaTime delta)
{
	if (moving_ != 0)
	{
		size_t steps = 0;
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

}
