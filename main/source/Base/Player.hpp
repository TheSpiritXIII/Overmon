#include <SFML/Graphics.hpp>

#include "Movable.hpp"

#include "Resource/SpriteManager.hpp"
#include "Base/Global.hpp"
#include "Base/Sprite.hpp"

namespace overmon
{

class DrawablePlayer : public Movable
{
public:
	DrawablePlayer(Sprite &sprite);
	void update(Global &global, DeltaTime delta);
	void draw(sf::RenderTarget &target, const sf::RenderStates &states = sf::RenderStates::Default);

private:
	size_t counterMove_;
	sf::Sprite sprite_;
	Sprite &realSprite_;
	uint8_t leg_;
	uint8_t runLeg_;
	DeltaTime wait_;
	uint8_t wasMoving_;
};

}
