#pragma once

#include "Resource/SpriteManager.hpp"
#include "Util/Updatable.hpp"

namespace overmon
{

/// Globally passed data.
class Global : Updatable<Global>
{
public:
	/// Zero initializes the counter.
	Global();

	/// The current animation counter value.
	DeltaTime animationCounter() const;

	/// The current animation counter truncated as an integer.
	uint8_t animationCounterIndex() const;

	/// The sprite manager.
	SpriteManager &spriteManager();

	/// Updates the animation counter.
	void update(DeltaTime delta);

private:
	DeltaTime counter_;
	uint8_t counterIndex_;
	SpriteManager spriteManager_;
};

}
