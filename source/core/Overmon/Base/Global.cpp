#include "Global.hpp"

namespace overmon
{

Global::Global()
	: counter_(0)
	, counterIndex_(0)
{}

DeltaTime Global::animationCounter() const
{
	return counter_;
}

uint8_t Global::animationCounterIndex() const
{
	return counterIndex_;
}

const SpriteManager &Global::spriteManager() const
{
	return spriteManager_;
}

void Global::update(DeltaTime delta)
{
	counter_ += 4 * delta;
	while (counter_ >= 4)
	{
		counter_ -= 4;
	}
	counterIndex_ = static_cast<uint8_t>(counter_);
}

}
