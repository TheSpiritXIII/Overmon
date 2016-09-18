#include <SFML/Graphics.hpp>

#include "Character/DrawablePlayer.hpp"

const size_t FPS = 60;

int main()
{
	sf::RenderWindow window(sf::VideoMode(256, 192), "Overmon");
	window.setSize(sf::Vector2u(512, 394));
	window.setFramerateLimit(FPS);

	sf::Event event;

	overmon::DrawablePlayer player;

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
		player.update();
		player.draw(window);
		window.display();
	}
	return EXIT_SUCCESS;
}
