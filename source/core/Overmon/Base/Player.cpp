#include <iostream>

#include "Overmon/Base/Player.hpp"
#include "Overmon/Resource/SpriteManager.hpp"

namespace overmon
{

Player::Player(Sprite &sprite)
	: Movable(0, 0, Direction::South)
	, sprite_(sprite)
	, leg_(0)
	, wait_(0)
	, wasMoving_(false)
{}

void Player::update(const Global &global, DeltaTime delta)
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
					wait_ = 0.1f;
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
				sprite_.setId(global.spriteManager(), 1, 0);
				runLeg_ = (runLeg_ + 1) % 4;
			}
			else
			{
				sprite_.setId(global.spriteManager(), 0, 0);
			}
			leg_ = !leg_;
		}
		else
		{
			sprite_.setId(global.spriteManager(), 0, characterDirectionFrame());
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
		sprite_.setFrame(global.spriteManager(), static_cast<size_t>(direction()) * 3 + index);
		sprite_.setPosition(x(), y());
	}
	else if (wait_ > 0)
	{
		// Waiting for player to turn directions (when they have no momentum).
		wait_ = std::max<DeltaTime>(wait_ - delta, static_cast<DeltaTime>(0.0));
		sprite_.setFrame(global.spriteManager(), static_cast<size_t>(direction()) * 3 + 1 + leg_);
	}
	else
	{
		wasMoving_ = false;
	}
}

}
