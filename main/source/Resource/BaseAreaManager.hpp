#pragma once

#include <SFML/Graphics.hpp>

namespace overmon
{

/// The variable type signifying unique sprites.
typedef uint8_t SpriteId;

/// Loads and stores area metadata.
template<typename T>
class BaseAreaManager
{
public:
	/// Sets and loads the indicated area.
	void areaSet(AreaId id)
	{
		static_cast<T*>(this)->areaSet(id);
	}

	/// Draws the current area.
	void draw(sf::RenderTarget &target, const RenderStates& states = RenderStates::Default)
	{
		static_cast<T*>(this)->draw(target, states);
	}
};

}
