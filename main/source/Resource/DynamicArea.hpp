#include <string>

#include "SFML/Graphics.hpp"

namespace overmon
{

class DynamicArea
{
public:
	void loadArea(const char *filename);
	void drawForeground(sf::RenderTarget &target,
		const sf::RenderStates& states = sf::RenderStates::Default) const;
	void drawBackground(sf::RenderTarget &target,
		const sf::RenderStates& states = sf::RenderStates::Default) const;

private:
	std::vector<sf::Sprite> tilesForeground_;
	std::vector<sf::Sprite> tilesBackground_;
};

}
