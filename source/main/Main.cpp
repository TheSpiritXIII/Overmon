#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character/DrawablePlayer.hpp"
#include <math.h>


const size_t FPS = 60;



int main()
{
	sf::RenderWindow window(sf::VideoMode(256, 192), "Overmon");
	window.setSize(sf::Vector2u(512, 394));
	window.setFramerateLimit(FPS);

	sf::Event event;

	overmon::DrawablePlayer player;

	//FPS Calc vars (like fonts), should turn global, so you can remove this later.
	//Also, I got this idea from http://en.sfml-dev.org/forums/index.php?topic=7018.0
	#if defined(DRAW_FPS) && DRAW_FPS
		//Load Font
		sf::Font fpsFont;
		if(!fpsFont.loadFromFile("./Resource/pkmndp.ttf")){
			std::cout << "ERROR: FPS Counter Fontd could not be found!";
		}

		//Define Text Properties
		sf::Text fps;
		fps.setFont(fpsFont);
		fps.setCharacterSize(16);

		//Clock for  counting time, necessary for FPS calc
		sf::Clock clock;
		sf::Clock clocktwo;



	#endif

	while (window.isOpen())
	{
		//FPS Calc, only displays if macro DRAW_FPS is defined and true
		#if defined(DRAW_FPS) && DRAW_FPS
			float currentTime = clock.restart().asSeconds();
			float frames = 1.f / currentTime;
			if(clocktwo.getElapsedTime().asSeconds() >= 1){
		    	fps.setString(std::to_string((int)(round(frames))));
		    	clocktwo.restart();
			}
		#endif


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

		//Updates Player
		player.update();
		player.draw(window);

		//Draw FPS
		#if defined(DRAW_FPS) && DRAW_FPS
		window.draw(fps);
		#endif

		window.display();
	}
	return EXIT_SUCCESS;
}
