#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

const size_t FPS = 60;

enum class Direction
{
	Left,
	Right,
	Up,
	Down
};

class Player
{
public:
	Player()
		: moving_(false)
		, direction_(Direction::Left)
		, rectangleMain_(sf::Vector2f(16, 16))
		, rectangleDir_(sf::Vector2f(8, 8))
	{
		rectangleMain_.setFillColor(sf::Color(255, 0, 0));
		rectangleDir_.setFillColor(sf::Color(0, 255, 0));
	}
	void step()
	{
		if (moving_)
		{
			switch (direction_)
			{
			case Direction::Left:
				rectangleMain_.setPosition(rectangleMain_.getPosition() + sf::Vector2f(-1, 0));
				break;
			case Direction::Right:
				rectangleMain_.setPosition(rectangleMain_.getPosition() + sf::Vector2f(1, 0));
				break;
			case Direction::Up:
				rectangleMain_.setPosition(rectangleMain_.getPosition() + sf::Vector2f(0, -1));
				break;
			case Direction::Down:
				rectangleMain_.setPosition(rectangleMain_.getPosition() + sf::Vector2f(0, 1));
				break;
			}
			sf::Vector2f position = rectangleMain_.getPosition();
			if (static_cast<int32_t>(position.x) % 16 == 0 && static_cast<int32_t>(position.y) % 16 == 0)
			{
				moving_ = false;
			}
		}
		if (!moving_)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				direction_ = Direction::Left;
				moving_ = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				direction_ = Direction::Right;
				moving_ = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				direction_ = Direction::Up;
				moving_ = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				direction_ = Direction::Down;
				moving_ = true;
			}
		}
		switch (direction_)
		{
		case Direction::Left:
			rectangleDir_.setPosition(rectangleMain_.getPosition() + sf::Vector2f(0, 4));
			break;
		case Direction::Right:
			rectangleDir_.setPosition(rectangleMain_.getPosition() + sf::Vector2f(8, 4));
			break;
		case Direction::Up:
			rectangleDir_.setPosition(rectangleMain_.getPosition() + sf::Vector2f(4, 0));
			break;
		case Direction::Down:
			rectangleDir_.setPosition(rectangleMain_.getPosition() + sf::Vector2f(4, 8));
			break;
		}
	}
	void draw(sf::RenderWindow &window)
	{
		window.draw(rectangleMain_);
		window.draw(rectangleDir_);
	}
private:
	bool moving_;
	Direction direction_;
	sf::RectangleShape rectangleMain_;
	sf::RectangleShape rectangleDir_;
};

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(256, 192), "Overmon");
	window.setSize(sf::Vector2u(512, 394));
	window.setFramerateLimit(FPS);

	sf::Event event;

	Player player;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear(sf::Color(100, 149, 237));
		player.step();
		player.draw(window);
		window.display();
	}
	return EXIT_SUCCESS;
}
