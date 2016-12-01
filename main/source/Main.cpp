#include <iostream>

#include <SFML/Graphics.hpp>

#include "Character/DrawablePlayer.hpp"
#include "Sprite/DynamicSpriteManager.hpp"
#include "Util/Counter.hpp"

const size_t FPS = 120;

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
	spriteManager.setTexture(sprite, "Player");
	spriteManager.setRect(sprite, "Player", 0);

	size_t frame = 0;
	size_t counter = 0;

	Counter<4, 1, 4> animationCounter;

	const float delta = 1.0 / FPS;

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
		player.update(spriteManager, delta);
		player.draw(window);
		window.draw(sprite);
		window.display();

		animationCounter.update(delta);
		uint8_t index = (animationCounter.counterIndex() % 2) + (animationCounter.counterIndex() == 1);
		spriteManager.setRect(sprite, "Player", index);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
		{
			spriteManager.reload();
		}
	}
	return EXIT_SUCCESS;
}
