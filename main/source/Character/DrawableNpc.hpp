#include <SFML/Graphics.hpp>

#include "Npc.hpp"

class DynamicSpriteManager;

namespace overmon
{

class DrawableNpc : public Npc
{
public:
	DrawableNpc(size_t gridX, size_t gridY, Direction direction);
	void draw(DynamicSpriteManager &manager, sf::RenderTarget &target, const sf::RenderStates &states = sf::RenderStates::Default);

private:
	sf::RectangleShape rectangleMain_;
	sf::RectangleShape rectangleDir_;
	sf::Sprite sprite_;
	bool leg;
	bool ready;
};

}
