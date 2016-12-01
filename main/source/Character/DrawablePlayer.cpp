#include "DrawablePlayer.hpp"

#include "../Sprite/DynamicSpriteManager.hpp"

#include <iostream>

namespace overmon
{

DrawablePlayer::DrawablePlayer()
	: MovableNpc(0, 0, Direction::South)
	, leg_(0)
	, wait_(0)
	, wasMoving_(false)
{}

void DrawablePlayer::update(DynamicSpriteManager &manager, DeltaTime delta)
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
			if (directionLast != direction() && !wasMoving_)
			{
				wait_ = 0.1;
			}
			if (wait_ == 0)
			{
				moveSpeed(1 + running);
				wasMoving_ = true;
			}
		}

		if (moving())
		{
			if (running)
			{
				manager.setTexture(sprite_, "PlayerRunning");
				runLeg_ = (runLeg_ + 1) % 4;
			}
			else
			{
				manager.setTexture(sprite_, "Player");
			}
			leg_ = !leg_;
		}
		else
		{
			manager.setTexture(sprite_, "Player");
			manager.setRect(sprite_, "Player", static_cast<size_t>(direction()) * 3);
			runLeg_ = 0;
		}
	}

	if (moving())
	{
		MovableNpc::update(delta);
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
			size_t counter = leg_;
			index = counter;
			std::cout << (runLeg_ == 3 ? "true" : "false") << std::endl;
			if (index == 1 && runLeg_ == 3)
			{
				index += 1;
			}
		}
		manager.setRect(sprite_, "Player", static_cast<size_t>(direction()) * 3 + index);
	}
	else if (wait_ > 0)
	{
		// Waiting for player to turn directions (when they have no momentum).
		wait_ = std::max<DeltaTime>(wait_ - delta, static_cast<DeltaTime>(0.0));
		manager.setRect(sprite_, "Player", static_cast<size_t>(direction()) * 3 + 1 + leg_);
	}
	else
	{
		wasMoving_ = false;
	}
}

void DrawablePlayer::draw(sf::RenderTarget &target, const sf::RenderStates &states)
{
	sprite_.setPosition(x(), y());
	target.draw(sprite_, states);
}

}
