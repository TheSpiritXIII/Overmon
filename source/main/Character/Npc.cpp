#include "Npc.hpp"

namespace overmon
{

Npc::Npc(size_t gridX, size_t gridY, Direction direction)
	: gridX_(gridX)
	, gridY_(gridY)
	, x_(gridX * 16)
	, y_(gridY * 16)
	, direction_(direction)
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

void Npc::update()
{
	if (moving_ != 0)
	{
		switch (direction_)
		{
		case Direction::North:
			y_ -= 1;
			if (y_ % 16 == 0)
			{
				moving_ = false;
			}
			break;
		case Direction::South:
			y_ += 1;
			if (y_ % 16 == 0)
			{
				moving_ = false;
			}
			break;
		case Direction::East:
			x_ += 1;
			if (x_ % 16 == 0)
			{
				moving_ = false;
			}
			break;
		case Direction::West:
			x_ -= 1;
			if (x_ % 16 == 0)
			{
				moving_ = false;
			}
			break;
		}
	}
}

}
