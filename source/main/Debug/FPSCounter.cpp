/*
 * FPSCounter.cpp
 *
 *  Created on: Oct 12, 2016
 *      Author: Michal
 */
//FPS Calc vars (like fonts), should turn global, so you can remove this later.
//Also, I got this idea from http://en.sfml-dev.org/forums/index.php?topic=7018.0
#include "FPSCounter.hpp"

namespace overmon
{

FPSCounter::FPSCounter()
{
	fpsInt = 0;
	if(!fpsFont.loadFromFile("./Resource/xy.ttf"))
	{
		std::cout << "ERROR: FPS Counter Font could not be found!";
	}
	//Define Text Properties
	fps.setFont(fpsFont);
	fps.setCharacterSize(32);

	//Clock for  counting time, necessary for FPS calc
	sf::Clock clock;
	sf::Clock clocktwo;

}

void FPSCounter::draw(sf::RenderWindow &target)
{
	calc();
	target.draw(fps);
}

void FPSCounter::calc()
{
	float currentTime = clock.restart().asSeconds();
	float frames = 1.f / currentTime;
	if(clockTwo.getElapsedTime().asSeconds() >= 1)
	{
		fps.setString(std::to_string((int)(round(frames))));
		fpsInt = ((int)(round(frames)));
		clockTwo.restart();
	}
}

}


