#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace overmon
{

/// Allows users to move and zoom on a view with their mouse.
class Navigator
{
public:
	/// Creates a new navigator filling the entire window.
	Navigator(const sf::Window &window);

	/// Updates the navigation view.
	void update(sf::Event event);

	/// Zooms in, showing less in the navigation view.
	void zoomIn();

	/// Zooms out, showing more in the navigation view.
	void zoomOut();

	/// Returns the current navigated view.
	sf::View view() const;

	/// Returns the current navigated view zoom value.
	float zoomPercentage() const;

private:
	sf::View view_;
	sf::Vector2i lastMousePosition_;
	bool active_;
	float zoom_;
};

}
