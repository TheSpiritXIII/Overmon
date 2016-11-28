#pragma once

/// Precision type for delta timing.
typedef float DeltaTime;

/// A class that can be updated using delta timing.
template <class T> 
class Updatable
{
public:
	/// Updates the base class using the given delta time.
	void update(DeltaTime delta)
	{
		static_cast<T*>(this)->update(delta);
	}
};
