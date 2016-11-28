#include "DrawableNpc.hpp"

namespace overmon
{

class DrawablePlayer : public DrawableNpc
{
public:
	DrawablePlayer();
	void update(DeltaTime delta);

private:
	size_t counterMove_;
};

}
