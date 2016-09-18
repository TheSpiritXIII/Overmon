#include <SFML/Graphics.hpp>

#include "Npc.hpp"

namespace overmon
{

class DrawableNpc : public Npc
{
public:
	DrawableNpc(size_t gridX, size_t gridY, Direction direction);
	void draw(sf::RenderTarget &target, const sf::RenderStates &states = sf::RenderStates::Default);

private:
	sf::RectangleShape rectangleMain_;
	sf::RectangleShape rectangleDir_;
};

}
