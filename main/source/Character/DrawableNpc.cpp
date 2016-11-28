#include "DrawableNpc.hpp"

#include "../Sprite/DynamicSpriteManager.hpp"

namespace overmon
{

DrawableNpc::DrawableNpc(size_t gridX, size_t gridY, Direction direction)
	: Npc(gridX, gridX, direction)
	, rectangleMain_(sf::Vector2f(16, 16))
	, rectangleDir_(sf::Vector2f(8, 8))
, leg(false)
, ready(false)
{
	rectangleMain_.setFillColor(sf::Color(255, 0, 0));
	rectangleDir_.setFillColor(sf::Color(0, 255, 0));
}

void DrawableNpc::draw(DynamicSpriteManager &manager, sf::RenderTarget &target, const sf::RenderStates &states)
{
	manager.setTexture(sprite_, "Player");
	size_t counter = moveCounter_ / 8;
	uint8_t index = counter % 2;
	if (index == 1 && leg)
	{
	index += 1;
}
	manager.setRect(sprite_, "Player", static_cast<size_t>(direction()) * 3 + index);
	sprite_.setPosition(x(), y());

	target.draw(sprite_, states);

	bool aligned = x() % 16 == 0 && y() % 16 == 0;
	if (aligned)
	{
		if (ready)
		{
			leg = !leg;
			ready = false;
		}
	}
	else
	{
		ready = true;
	}
}

}
