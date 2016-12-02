#include <iostream>

#include <SFML/Graphics.hpp>

#include "Character/DrawablePlayer.hpp"
#include "Sprite/DynamicSpriteManager.hpp"
#include "Util/Counter.hpp"
#include "Character/WalkingNpc.hpp"

const size_t FPS = 30;

int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 394), "Overmon");
//	window.setSize(sf::Vector2u(, ));
	window.setFramerateLimit(FPS);

	sf::View view;
	view.setSize(256, 192);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	window.setView(view);

	sf::Event event;

	overmon::DrawablePlayer player;

	sf::Sprite sprite;
	sprite.setPosition(64, 64);

	DynamicSpriteManager spriteManager;
	spriteManager.setTexture(sprite, "Player");
	spriteManager.setRect(sprite, "Player", 0);

	size_t frame = 0;
	size_t counter = 0;

	Counter<4, 1, 4> animationCounter;

	overmon::Sprite<const char*> npcSprite(spriteManager, "Player");

	overmon::Walking<const char*> walkingNpc(4, 4, overmon::Direction::East, npcSprite);

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

		walkingNpc.update(spriteManager, delta);
		npcSprite.draw(window);
		window.draw(sprite);


		//view.setCenter(player.x() + 8, player.y() + 8);
		window.setView(view);

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
