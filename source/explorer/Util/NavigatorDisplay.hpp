#include <SFML/Graphics.hpp>

namespace overmon
{

class Navigator;

/// Helper class that displays the current zoom value of a navigator.
class NavigatorDisplay
{
public:
	/// Loads all requried font resources.
	NavigatorDisplay();

	/// Updates the zoom percentage text.
	void update(const Navigator &navigator);

	/// Draws the navigation zoom percentage text with a black border.
	void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates());

private:
	sf::Font font_;
	sf::Text text_;
	sf::RectangleShape rectShape_;
};

}
