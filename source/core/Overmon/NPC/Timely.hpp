#pragma once

#include "Overmon/Base/Movable.hpp"
#include "Overmon/Base/Sprite.hpp"

namespace overmon
{

/// Base class for NPCs that perform actions on a constant interval.
class Timely : public Movable
{
public:
	/// Initializes an NPC with the indicated offset as the initial action timer.
	Timely(GridType gridX, GridType gridY, Direction direction, Sprite &sprite, DeltaTime off = 0);

protected:
	/// Updates the timer value.
	void timerUpdate(DeltaTime delta);

	/// Attempts to reset the timer and returns true if it does.
	bool timerReset();

	/// The sprite managed by this NPC.
	Sprite &sprite;

private:
	DeltaTime timer_;
};

}
