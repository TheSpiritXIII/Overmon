#pragma once

#include "SFML/Graphics.hpp"

namespace overmon
{

/// The variable type signifying unique sprites.
typedef uint8_t SpriteId;

/// Loads and stores sprite metadata.
template<typename T>
class BaseSpriteManager
{
public:

	/// Sets the texture and origin for the given sprite.
	void setTexture(sf::Sprite &sprite, SpriteId id) const
	{
		static_cast<T*>(this)->setTexture(sprite, id);
	}

	/// Sets the frame rect of the indicated frame index to the given sprite.
	void setFrame(sf::Sprite &sprite, SpriteId id, uint8_t frame) const
	{
		static_cast<T*>(this)->setFrame(sprite, id, frame);
	}
 
};

}
