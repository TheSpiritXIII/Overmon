#pragma once

#include "Base/Global.hpp"
#include "Base/Movable.hpp"
#include "Base/Sprite.hpp"

namespace overmon
{

/// An NPC that turns when its timer runs out.
class Turning : public Movable
{
public:
	/// Initializes an NPC with the indicated offset as the initial action timer.
	Turning(GridType gridX, GridType gridY, Direction direction, Sprite &sprite, DeltaTime off = 0);

	/// Updates the timer and turns if the timer has to be reset.
	void update(Global &global, DeltaTime delta);

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
