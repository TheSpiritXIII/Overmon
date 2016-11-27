#include <iostream>

#include <SFML/Graphics.hpp>

#include "Character/DrawablePlayer.hpp"
#include "Sprite/DynamicSpriteManager.hpp"

const size_t FPS = 60;

int main()
{
	sf::RenderWindow window(sf::VideoMode(256, 192), "Overmon");
	window.setSize(sf::Vector2u(512, 394));
	window.setFramerateLimit(FPS);

	sf::Event event;

	overmon::DrawablePlayer player;

	sf::Sprite sprite;
	sprite.setPosition(128, 128);

	DynamicSpriteManager spriteManager;
	spriteManager.setSpriteTexture(sprite, "Player");
	spriteManager.setSpriteRect(sprite, "Player", 0);

	size_t frame = 0;
	size_t counter = 0;

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
		window.draw(sprite);
		window.display();

		counter += 1;
		if (counter == 30)
		{
			counter = 0;
			frame += 1;
			if (frame == 12)
			{
				frame = 0;
			}

			spriteManager.setSpriteTexture(sprite, "Player");
			spriteManager.setSpriteRect(sprite, "Player", frame);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
		{
			spriteManager.reload();
		}
	}
	return EXIT_SUCCESS;
}
