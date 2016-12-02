#pragma once

#include "Util/Updatable.hpp"
#include "../Util/Direction.hpp"

namespace overmon
{

typedef int8_t GridType;
typedef int16_t PositionType;

/// NPC instance that be moved on a tiled basis.
class MovableNpc : public Updatable<MovableNpc>
{
public:
	/// Creates an NPC with the given grid position and direction.
	MovableNpc(GridType gridX, GridType gridY, Direction direction);

	/// The x coordinate of the NPC.
	PositionType x() const;

	/// The y coordinate of the NPC.
	PositionType y() const;

	/// Returns the current direction.
	Direction direction() const;

	/// Turns the NPC to face the given direction.
	virtual void directionSet(Direction direction);

	/// Moves the NPC a single tile forward with the given speed.
	void moveSpeed(uint8_t speed);

	/// Returns the distance traveled in the current step.
	uint8_t moveCounter() const;

	/// Returns true if the NPC is moving with a non-zero speed.
	bool moving() const;

	/// Returns the current character frame based on the current distance traveled.
	uint8_t characterFrame(bool leg) const;

	/// Moves the NPC position using the last given speed and direction.
	void update(DeltaTime delta);

	/// Calculates the character frame index for a 3-frame character sheet.
	/// @param direction The direction the character is facing.
	/// @param counter The total distance traveled.
	/// @param leg The leg that the character is walking with. This should alternate.
	static uint8_t characterFrame(Direction direction, uint8_t counter, bool leg);

protected:
	GridType gridX_;
	GridType gridY_;
private:
	PositionType x_;
	PositionType y_;
	Direction direction_;
	uint8_t speed_;
	DeltaTime counter_;
	bool moving_;
	uint8_t moveCounter_;
};

}
