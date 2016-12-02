#pragma once

#include <SFML/Graphics.hpp>

namespace overmon
{

template <class SpriteId>
class Sprite
{
public:
	Sprite(SpriteManager<SpriteId> &manager, SpriteId spriteId)
	{
		setId(manager, spriteId);
		setFrame(manager, 0);
	}

	sf::Sprite sprite() const
	{
		return sprite_;
	}

	SpriteId id() const
	{
		return spriteId_;
	}

	void setPosition(PositionType x, PositionType y)
	{
		sprite_.setPosition(x, y);
	}

	void setId(SpriteManager<SpriteId> &manager, SpriteId spriteId)
	{
		spriteId_ = spriteId;
		manager.setTexture(sprite_, spriteId_);
	}

	void setFrame(SpriteManager<SpriteId> &manager, uint8_t frame)
	{
		manager.setRect(sprite_, spriteId_, frame);
	}

	void draw(sf::RenderTarget &target, const sf::RenderStates &states = sf::RenderStates::Default)
	{
		target.draw(sprite_, states);
	}

private:
	sf::Sprite sprite_;
	SpriteId spriteId_;
};

}
