#include "DrawablePlayer.hpp"

namespace overmon
{

DrawablePlayer::DrawablePlayer()
	: DrawableNpc(0, 0, Direction::South)
{}

void DrawablePlayer::update()
{
	bool ready = false;
	counterMove_ = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		directionSet(Direction::West);
		moveSpeed(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		directionSet(Direction::East);
		moveSpeed(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		directionSet(Direction::North);
		moveSpeed(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		directionSet(Direction::South);
		moveSpeed(1);
	}

	DrawableNpc::update();
}

}
