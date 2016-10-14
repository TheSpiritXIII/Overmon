/*
 * FPSCounter.hpp
 *
 *  Created on: Oct 12, 2016
 *      Author: Michal
 */
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

//TODO: Document this a bit better

namespace overmon
{

class FPSCounter
{

public:
	FPSCounter();
	void draw(sf::RenderWindow &target);
	int getFPS();

private:
	int fpsInt;
	sf::Text fps;
	sf::Clock clock;
	sf::Clock clockTwo;
	sf::Font fpsFont;
	void calc();
};

}

