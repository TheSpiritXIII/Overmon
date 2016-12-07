#include <SFML/Graphics.hpp>

#include "Base/Global.hpp"
#include "Base/Player.hpp"
#include "NPC/Turning.hpp"
#include "NPC/Walking.hpp"
#include "Resource/SpriteManager.hpp"
#include "Resource/AreaManager.hpp"

const size_t FPS = 60;
const size_t WINDOW_WIDTH = 256;
const size_t WINDOW_HEIGHT = 192;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH * 2, WINDOW_HEIGHT * 2), "Overmon");
	window.setFramerateLimit(FPS);

	sf::View view;
	view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	window.setView(view);

	sf::Event event;

	overmon::Global global;

	overmon::Sprite spritePool[3] =
	{
		overmon::Sprite(global.spriteManager(), 0),
		overmon::Sprite(global.spriteManager(), 0),
		overmon::Sprite(global.spriteManager(), 0)
	};

	overmon::Player player(spritePool[0]);
	overmon::Turning turningNpc(4, 4, overmon::Direction::East, spritePool[1], 0);
	overmon::Walking walkingNpc(4, 0, overmon::Direction::East, spritePool[2], 0);

	overmon::AreaManager areaManager;

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
		global.update(delta);
		player.update(global, delta);
		turningNpc.update(global, delta);
		walkingNpc.update(global, delta);

		view.setCenter(player.x() + 8, player.y() + 8);
		window.setView(view);

		window.clear(sf::Color(100, 149, 237));

		areaManager.drawBackground(window);

		std::vector<overmon::Sprite*> spriteDrawPool;
		for (size_t i = 0; i < 3; ++i)
		{
			spriteDrawPool.push_back(&spritePool[i]);
		}
		std::sort(spriteDrawPool.begin(), spriteDrawPool.end(), [](overmon::Sprite *left, overmon::Sprite *right)
		{
			return left->sprite().getPosition().y < right->sprite().getPosition().y;
		});

		for (auto && sprite : spriteDrawPool)
		{
			sprite->draw(window);
		}

		areaManager.drawForeground(window);
		window.display();

//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
//		{
//			global.spriteManager().reload();
//		}
	}
	return EXIT_SUCCESS;
}
