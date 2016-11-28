#pragma once

#include <cstddef>
#include <cstdint>

namespace overmon
{

enum class Direction
{
	North = 2,
	South = 0,
	East  = 1,
	West  = 3
};

class Npc
{
public:
	Npc(size_t gridX, size_t gridY, Direction direction);

	Direction direction() const;
	virtual void directionSet(Direction direction);

	void moveSpeed(uint8_t speed);
	void moveStop(bool stop);

	int16_t x() const;
	int16_t y() const;

	void update();

private:
	int16_t x_;
	int16_t y_;
	int8_t gridX_;
	int8_t gridY_;
	Direction direction_;
	uint8_t moving_;
	uint8_t speed_;
};

}
