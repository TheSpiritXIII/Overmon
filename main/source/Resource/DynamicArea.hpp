#pragma once

#include <string>

#include "SFML/Graphics.hpp"

namespace overmon
{

class DynamicArea
{
public:
	void loadArea(const char *filename);
	size_t width() const;
	size_t height() const;
	void draw(bool background, sf::RenderTarget &target,
		const sf::RenderStates& states = sf::RenderStates::Default) const;
	void drawForeground(sf::RenderTarget &target,
		const sf::RenderStates& states = sf::RenderStates::Default) const;
	void drawBackground(sf::RenderTarget &target,
		const sf::RenderStates& states = sf::RenderStates::Default) const;

private:
	std::vector<sf::Sprite> tilesForeground_;
	std::vector<sf::Sprite> tilesBackground_;
	size_t width_;
	size_t height_;
};

}
