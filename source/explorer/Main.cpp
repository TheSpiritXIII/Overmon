#include <thread>

#include <Overmon/Resource/RegionViewer.hpp>
#include <SFML/Graphics.hpp>

#include "Util/Navigator.hpp"
#include "Util/NavigatorDisplay.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Overmon Explorer");

	overmon::RegionViewer regionViewer;
	regionViewer.reload();

	overmon::Navigator navigator(window);
	overmon::NavigatorDisplay navigatorDisplay;

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			navigator.update(event);
			navigatorDisplay.update(navigator);
		}

		window.setView(navigator.view());
		window.clear();

		regionViewer.draw(window);
		navigatorDisplay.draw(window);
		window.display();

		std::this_thread::yield();
	}
	return EXIT_SUCCESS;
}
