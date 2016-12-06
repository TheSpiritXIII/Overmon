//#include "Updatable.hpp"

//// Manages a counter that look at the given rate and loops at LIMIT.
//class Counter : public Updatable<Counter<RATE_NUMERATOR, RATE_DENOMINATOR, LIMIT>>
//{
//public:
//	/// Zero initializes a counter.
//	Counter()
//		: counter_(0)
//		, counterIndex_(0)
//	{}

//	/// The current counter value.
//	DeltaTime counter() const
//	{
//		return counter_;
//	}

//	/// The current counter truncated as an integer.
//	uint8_t counterIndex() const
//	{
//		return counterIndex_;
//	}

//	/// Updates the counter using the given delta time.
//	void update(DeltaTime delta)
//	{
//		counter_ += 4 * delta;
//		while (counter_ >= 4)
//		{
//			counter_ -= 4;
//		}
//		counterIndex_ = static_cast<uint8_t>(counter_);
//	}

//private:
//	DeltaTime counter_;
//	uint8_t counterIndex_;
//};
