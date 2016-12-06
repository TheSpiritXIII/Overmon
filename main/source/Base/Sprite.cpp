#include "Sprite.hpp"

namespace overmon
{

Sprite::Sprite(const SpriteManager &manager, SpriteId spriteId)
{
	setId(manager, spriteId, 0);
}

sf::Sprite Sprite::sprite() const
{
	return sprite_;
}

SpriteId Sprite::id() const
{
	return spriteId_;
}

void Sprite::setPosition(PositionType x, PositionType y)
{
	sprite_.setPosition(x, y);
}

void Sprite::setId(const SpriteManager &manager, SpriteId spriteId, uint8_t frame)
{
	spriteId_ = spriteId;
	manager.setTexture(sprite_, spriteId_);
	manager.setFrame(sprite_, spriteId_, frame);
}

void Sprite::setFrame(const SpriteManager &manager, uint8_t frame)
{
	manager.setFrame(sprite_, spriteId_, frame);
}

void Sprite::draw(sf::RenderTarget &target, const sf::RenderStates &states)
{
	target.draw(sprite_, states);
}

}
