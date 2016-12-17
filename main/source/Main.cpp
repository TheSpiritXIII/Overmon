#include <SFML/Graphics.hpp>

#include "Base/Global.hpp"
#include "Base/Player.hpp"
#include "NPC/Turning.hpp"
#include "NPC/Walking.hpp"
#include "Resource/AreaManager.hpp"
#include "Resource/SpriteManager.hpp"
#include "Resource/RegionViewer.hpp"
//#include "Util/Navigator.hpp"
//#include "Util/NavigatorDisplay.hpp"

const size_t FPS = 60;
const size_t VIEW_WIDTH = 256;
const size_t VIEW_HEIGHT = 192;
const size_t WINDOW_WIDTH = VIEW_WIDTH * 2;
const size_t WINDOW_HEIGHT = VIEW_HEIGHT * 2;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Overmon");
	window.setFramerateLimit(FPS);

	sf::View view;
	view.setSize(VIEW_WIDTH, VIEW_HEIGHT);
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
//	overmon::RegionViewer regionViewer;
//	regionViewer.reload();

//	overmon::Navigator navigator(window);
//	overmon::NavigatorDisplay navigatorDisplay;

	const float delta = 1.0 / FPS;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
//			navigator.update(event);
//			navigatorDisplay.update(navigator);
		}
		global.update(delta);
		player.update(global, delta);
		turningNpc.update(global, delta);
		walkingNpc.update(global, delta);

		view.setCenter(player.x() + 8, player.y() + 8);
		window.setView(view);
//		window.setView(navigator.view());

		window.clear();

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

//		regionViewer.draw(window);
//		navigatorDisplay.draw(window);

		areaManager.drawForeground(window);
		window.display();

//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
//		{
//			global.spriteManager().reload();
//		}
	}
	return EXIT_SUCCESS;
}
