#pragma once

#include "Base/Global.hpp"
#include "NPC/Timely.hpp"

namespace overmon
{

/// An NPC that turns when its timer runs out.
class Turning final : public Timely
{
public:
	/// Initializes an NPC with the indicated offset as the initial action timer.
	Turning(GridType gridX, GridType gridY, Direction direction, Sprite &sprite, DeltaTime off = 0);

	/// Updates the timer and turns if the timer has to be reset.
	void update(const Global &global, DeltaTime delta);
};

}
