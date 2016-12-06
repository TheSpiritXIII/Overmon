#pragma once

#include "Turning.hpp"
#include "Base/Global.hpp"

namespace overmon
{

/// NPC that walks and turns when its timer runs out.
class Walking : public Turning
{
public:
	/// Initializes an NPC with the indicated offset as the initial action timer.
	///
	/// The initial position is remembered as the origin and the NPC cannot move far from it.
	///
	Walking(GridType gridX, GridType gridY, Direction direction, Sprite &sprite, DeltaTime off);

	/// Moves the NPC or waits for the next action.
	///
	/// This NPC always ensures that it does not travel more than 2 grid positions away from its
	/// origin.
	///
	void update(Global &global, DeltaTime delta);

private:
	const GridType xOriginal_;
	const GridType yOriginal_;
	bool leg_;
};

}
