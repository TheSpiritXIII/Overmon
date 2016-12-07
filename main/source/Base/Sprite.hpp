#pragma once

#include "Base/Movable.hpp"
#include "Resource/SpriteManager.hpp"

namespace overmon
{

class Sprite
{
public:
	/// Initializes a new sprite at the first frame.
	Sprite(const SpriteManager &manager, SpriteId spriteId);

	/// Returns the sprite instance.
	sf::Sprite sprite() const;

	/// Returns the current displayed sprite identifier.
	SpriteId id() const;

	/// Sets the sprite's display position.
	void setPosition(PositionType x, PositionType y);

	/// Changes the sprite texture and sets its new frame.
	void setId(const SpriteManager &manager, SpriteId spriteId, uint8_t frame);

	/// Changes the sprite's frame.
	void setFrame(const SpriteManager &manager, uint8_t frame);

	/// Draws the sprite.
	void draw(sf::RenderTarget &target,
		const sf::RenderStates &states = sf::RenderStates::Default) const;

private:
	sf::Sprite sprite_;
	SpriteId spriteId_;
};

}
