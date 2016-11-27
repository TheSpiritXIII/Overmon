#include "DrawableNpc.hpp"

namespace overmon
{

class DrawablePlayer : public DrawableNpc
{
public:
	DrawablePlayer();
	void update();

private:
	size_t counterMove_;
};

}
