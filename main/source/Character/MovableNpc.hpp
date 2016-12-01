#pragma once

#include "../Util/Updatable.hpp"
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
	virtual void directionSet(Direction direction); // TODO: Behavior when not moving.

	/// Moves the NPC a single tile forward with the given speed.
	void moveSpeed(uint8_t speed);

	/// Returns the distance traveled in the current step.
	uint8_t moveCounter() const; // TODO: Implement this.

	/// Returns true if the NPC is moving with a non-zero speed.
	bool moving() const; // TODO: Implement this.

	/// Moves the NPC position using the last given speed and direction.
	void update(DeltaTime delta);

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
