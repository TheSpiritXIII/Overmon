#pragma once

#include "MovableNpc.hpp"
#include "Sprite.hpp"
#include "Sprite/SpriteManager.hpp"

#include <iostream>

namespace overmon
{

template <typename SpriteId>
class Walking : public MovableNpc
{
public:
	Walking(GridType gridX, GridType gridY, Direction direction, Sprite<SpriteId> &sprite,
		DeltaTime offset = 0)
			: MovableNpc(gridX, gridY, direction)
			, sprite_(sprite)
			, timer_(offset)
			, leg_(false)
	{}

	virtual void update(SpriteManager<SpriteId> &manager, DeltaTime delta)
	{
		if (moving())
		{
			MovableNpc::update(delta);
			sprite_.setPosition(x(), y());
			sprite_.setFrame(manager, characterFrame(0));
		}
		else
		{
			updateTimer(manager, delta);
			sprite_.setFrame(manager, static_cast<size_t>(direction()) * 3);
		}
	}

protected:

	/// Turns or moves the NPC and updates its sprite.
	void updateTimer(SpriteManager<SpriteId> &manager, DeltaTime delta)
	{
		timer_ -= delta;
		if (timer_ <= 0)
		{
			timer_ = 1;

			directionSet(changed());
			sprite_.setFrame(manager, static_cast<size_t>(direction()) * 3);
		}
	}

	/// Triggered when the NPC decides to update itself.
	virtual Direction changed()
	{
		// There are 8 possible actions. Two types of actions per direction (4 directions).
		// An NPC can either stay idle or not. If less than 4 idle otherwise move.
		uint8_t action = rand() % 8;
		moveSpeed(action > 4);
		leg_ = !leg_;

		return static_cast<Direction>(action % 4);
	}

private:
	Sprite<SpriteId> &sprite_;
	DeltaTime timer_;
	bool leg_;
};

}
