#pragma once

#include "Updatable.hpp"

// Manages a counter that look at the given rate and loops at LIMIT.
template<uint8_t RATE_NUMERATOR, uint8_t RATE_DENOMINATOR, uint8_t LIMIT>
class Counter : public Updatable<Counter<RATE_NUMERATOR, RATE_DENOMINATOR, LIMIT>>
{
public:
	/// Zero initializes a counter.
	Counter()
		: counter_(0)
		, counterIndex_(0)
	{}

	/// The current counter value.
	DeltaTime counter() const
	{
		return counter_;
	}

	/// The current counter truncated as an integer.
	uint8_t counterIndex() const
	{
		return counterIndex_;
	}

	/// Updates the counter using the given delta time.
	void update(DeltaTime delta)
	{
		counter_ += RATE * delta;
		while (counter_ >= LIMIT)
		{
			counter_ -= LIMIT;
		}
		counterIndex_ = static_cast<uint8_t>(counter_);
	}

private:
	static constexpr DeltaTime RATE = static_cast<DeltaTime>(RATE_NUMERATOR) / RATE_DENOMINATOR;
	DeltaTime counter_;
	uint8_t counterIndex_;
};
