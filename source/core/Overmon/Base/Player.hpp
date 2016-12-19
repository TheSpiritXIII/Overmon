#include <SFML/Graphics.hpp>

#include "Overmon/Base/Global.hpp"
#include "Overmon/Base/Sprite.hpp"
#include "Overmon/Base/Movable.hpp"
#include "Overmon/Resource/SpriteManager.hpp"

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
