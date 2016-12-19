#include <sstream>
#include <iomanip>

#include "Navigator.hpp"
#include "NavigatorDisplay.hpp"

namespace overmon
{

NavigatorDisplay::NavigatorDisplay()
{
	font_.loadFromFile("../resources/fonts/main.ttf");
	text_ = sf::Text("Zoom: 4", font_);
	text_.setPosition(4, 4);

	sf::Color rectColor = sf::Color::Black;
	rectColor.a = 128;
	rectShape_.setFillColor(rectColor);
	rectShape_.setPosition(4, 4);
	rectShape_.setSize(sf::Vector2f(64, 64));
}

void NavigatorDisplay::update(const Navigator &navigator)
{
	const size_t OFFSET = 4;

	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << (navigator.zoomPercentage() * 100);
	text_.setString(stream.str() + "%");

	sf::Vector2f size(text_.getGlobalBounds().width, text_.getGlobalBounds().height);
	rectShape_.setSize(sf::Vector2f(size.x + OFFSET * 2, size.y + OFFSET * 2));
	sf::Vector2f position;
	position.x = text_.getGlobalBounds().left - OFFSET;
	position.y = text_.getGlobalBounds().top - OFFSET;
	rectShape_.setPosition(position);
}

void NavigatorDisplay::draw(sf::RenderTarget &target, sf::RenderStates states)
{
	sf::Vector2f size(static_cast<float>(target.getSize().x),
		static_cast<float>(target.getSize().y));
	target.setView(sf::View(sf::FloatRect(sf::Vector2f(0, 0), size)));
	target.draw(rectShape_, states);
	target.draw(text_, states);
}

}
