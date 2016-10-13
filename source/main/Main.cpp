//#define DEBUG 1
#include <SFML/Graphics.hpp>

#include "Character/DrawablePlayer.hpp"

#if defined(DEBUG) && DEBUG
#include "Debug/FPSCounter.hpp"
#endif

const size_t FPS = 60;


int main()
{
	sf::RenderWindow window(sf::VideoMode(256, 192), "Overmon");
	window.setSize(sf::Vector2u(512, 394));
	window.setFramerateLimit(FPS);

	sf::Event event;

	overmon::DrawablePlayer player;

	//Initialize Debug Vars Here.
	#if defined(DEBUG) && DEBUG
	overmon::FPSCounter fps;
	#endif

	while (window.isOpen())
	{

		//Event Handler
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		//Clears Window for Redraw
		window.clear(sf::Color(100, 149, 237));

		//Debug Stuff Here
		#if defined(DEBUG) && DEBUG
		fps.draw(window);
		#endif

		//Updates Player
		player.update();
		player.draw(window);

		//Disp Window
		window.display();
	}
	return EXIT_SUCCESS;
}
