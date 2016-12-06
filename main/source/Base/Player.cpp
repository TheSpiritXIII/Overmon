#include "Player.hpp"

#include "Resource/SpriteManager.hpp"

#include <iostream>

namespace overmon
{

DrawablePlayer::DrawablePlayer(Sprite &sprite)
	: Movable(0, 0, Direction::South)
	, leg_(0)
	, wait_(0)
	, wasMoving_(false)
	, realSprite_(sprite)
{}

void DrawablePlayer::update(Global &global, DeltaTime delta)
{
	if (!moving())
	{
		bool running = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
		bool pressed = false;
		Direction directionLast = direction();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			directionSet(Direction::West);
			pressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			directionSet(Direction::East);
			pressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			directionSet(Direction::North);
			pressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			directionSet(Direction::South);
			pressed = true;
		}

		if (pressed)
		{
			if (!wasMoving_)
			{
				if (directionLast != direction())
				{
					wait_ = 0.1;
				}
				runLeg_ = ((leg_) % 2) * 2;
			}
			if (wait_ == 0)
			{
				moveSpeed(1 + running);
				wasMoving_ = 1 + running;
			}
		}

		if (moving())
		{
			if (running)
			{
				realSprite_.setId(global.spriteManager(), 1, 0);
				runLeg_ = (runLeg_ + 1) % 4;
			}
			else
			{
				realSprite_.setId(global.spriteManager(), 0, 0);
			}
			leg_ = !leg_;
		}
		else
		{
			realSprite_.setId(global.spriteManager(), 0, characterDirectionFrame());
		}
	}

	if (moving())
	{
		Movable::update(delta);
		bool running = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);

		uint8_t index;
		if (!running)
		{
			size_t counter = moveCounter() / 8;
			index = counter % 2;
			if (index == 1 && leg_)
			{
				index += 1;
			}
		}
		else
		{
			index = runLeg_ % 2;
			if (index == 1 && runLeg_ == 3)
			{
				index += 1;
			}
		}
		realSprite_.setFrame(global.spriteManager(), static_cast<size_t>(direction()) * 3 + index);
		realSprite_.setPosition(x(), y());
	}
	else if (wait_ > 0)
	{
		// Waiting for player to turn directions (when they have no momentum).
		wait_ = std::max<DeltaTime>(wait_ - delta, static_cast<DeltaTime>(0.0));
		realSprite_.setFrame(global.spriteManager(), static_cast<size_t>(direction()) * 3 + 1 + leg_);
	}
	else
	{
		wasMoving_ = false;
	}
}

}
