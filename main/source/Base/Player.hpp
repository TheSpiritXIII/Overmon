#include <SFML/Graphics.hpp>

#include "Movable.hpp"

#include "Resource/SpriteManager.hpp"
#include "Base/Global.hpp"
#include "Base/Sprite.hpp"

namespace overmon
{

class Player final : public Movable
{
public:
	Player(Sprite &sprite);
	void update(const Global &global, DeltaTime delta);

private:
	size_t counterMove_;
	Sprite &sprite_;
	uint8_t leg_;
	uint8_t runLeg_;
	DeltaTime wait_;
	uint8_t wasMoving_;
};

}
