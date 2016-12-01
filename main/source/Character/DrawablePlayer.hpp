#include <SFML/Graphics.hpp>

#include "MovableNpc.hpp"

class DynamicSpriteManager;

namespace overmon
{

class DrawablePlayer : public MovableNpc
{
public:
	DrawablePlayer();
	void update(DynamicSpriteManager &manager, DeltaTime delta);
	void draw(sf::RenderTarget &target, const sf::RenderStates &states = sf::RenderStates::Default);

private:
	size_t counterMove_;
	sf::Sprite sprite_;
	uint8_t leg_;
	uint8_t runLeg_;
	DeltaTime wait_;
	bool wasMoving_;
};

}
