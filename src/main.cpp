#include <SFML/Graphics.hpp>
#include "player.hpp"
#include <optional>

int main()
{
	// Getting the window size 
	sf::RenderWindow window( sf::VideoMode( { 800, 600 } ), "Modern Asteroids");
	Player player;

	// This is just a test object Alan put into the game to test rendering and drawing of SFML and CMAKE
	sf::RectangleShape test({100.f, 100.f});
	test.setFillColor(sf::Color::Yellow);
	test.setPosition({50.f, 50.f});
	

	// Game loop, sets the window color and makes sure the window says open until the user closes it.
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}
		player.update();

		window.clear(sf::Color::Black);
		window.draw(test);
		player.draw(window);
		window.display();
	}

	return 0;
}
