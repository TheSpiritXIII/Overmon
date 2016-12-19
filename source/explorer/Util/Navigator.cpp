#include "Navigator.hpp"

namespace overmon
{

Navigator::Navigator(const sf::Window &window)
	: zoom_(4)
	, active_(false)
{
	view_.setSize(window.getSize().x, window.getSize().y);
	view_.setCenter(0, 0);
}

void Navigator::update(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		switch (event.key.code)
		{
		case sf::Keyboard::Add:
			zoomIn();
			break;
		case sf::Keyboard::Subtract:
			zoomOut();
			break;
		default:
			break;
		}
		break;
	case sf::Event::MouseButtonPressed:
		active_ = true;
		break;
	case sf::Event::MouseButtonReleased:
		active_ = false;
		break;
	case sf::Event::MouseMoved:
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition();
		if (active_)
		{
			sf::Vector2i delta(lastMousePosition_.x - mousePosition.x, lastMousePosition_.y - mousePosition.y);
			view_.move(delta.x / exp2(4 - zoom_), delta.y / exp2(4 - zoom_));
		}
		lastMousePosition_ = mousePosition;
		break;
	}
	case sf::Event::MouseWheelMoved:
		if (event.mouseWheel.delta > 0)
		{
			zoomIn();
		}
		else
		{
			zoomOut();
		}
		break;
	case sf::Event::Resized:
		view_.setSize(event.size.width, event.size.height);
		break;
	default:
		break;
	}
}

void Navigator::zoomIn()
{
	if (zoom_ > 1)
	{
		view_.zoom(0.5);
		zoom_ -= 1;
	}
}

void Navigator::zoomOut()
{
	if (zoom_ < 10)
	{
		view_.zoom(2);
		zoom_ += 1;
	}
}

sf::View Navigator::view() const
{
	return view_;
}

float Navigator::zoomPercentage() const
{
	return 2 / exp2(4 - zoom_);
}

}
