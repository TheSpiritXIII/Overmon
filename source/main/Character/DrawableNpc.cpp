#include "DrawableNpc.hpp"

namespace overmon
{

DrawableNpc::DrawableNpc(size_t gridX, size_t gridY, Direction direction)
	: Npc(gridX, gridX, direction)
	, rectangleMain_(sf::Vector2f(16, 16))
	, rectangleDir_(sf::Vector2f(8, 8))
{
	rectangleMain_.setFillColor(sf::Color(255, 0, 0));
	rectangleDir_.setFillColor(sf::Color(0, 255, 0));
}

void DrawableNpc::draw(sf::RenderTarget &target, const sf::RenderStates &states)
{
	sf::Vector2f position(x(), y());
	rectangleMain_.setPosition(position);

	switch (direction())
	{
	case Direction::North:
	default:
		rectangleDir_.setPosition(position + sf::Vector2f(4, 0));
		break;
	case Direction::South:
		rectangleDir_.setPosition(position + sf::Vector2f(4, 8));
		break;
	case Direction::East:
		rectangleDir_.setPosition(position + sf::Vector2f(8, 4));
		break;
	case Direction::West:
		rectangleDir_.setPosition(position + sf::Vector2f(0, 4));
		break;
	}
	target.draw(rectangleMain_, states);
	target.draw(rectangleDir_, states);
}

}
