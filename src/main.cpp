#include <SFML/Graphics.hpp>
#include "player.hpp"
#include <optional>
#include<iostream>

int main()
{	
	//Get current desktop mode
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	// Getting the window size 
	sf::RenderWindow window( sf::VideoMode({800, 800}, desktop.bitsPerPixel), "Modern Asteroids", sf::Style::Default, sf::State::Windowed);
	Player player;

	//Intialize clock for time based calulations, mainly the framerate control
	sf::Clock clock;

	// This is just a test object Alan put into the game to test rendering and drawing of SFML and CMAKE
	//sf::RectangleShape test({100.f, 100.f});
	//test.setFillColor(sf::Color::Yellow);
	//test.setPosition({50.f, 50.f});
	


	// Game loop, sets the window color and makes sure the window says open until the user closes it.
	while (window.isOpen())
	{


		while (const std::optional event = window.pollEvent())
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		//Gets mouse position
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		
		//Returns time elapsed since last frame
		float delta = clock.restart().asSeconds();

		//Update player object with elapsed time since last frame and mouse position
		player.update(delta, mousePosition);

		window.clear(sf::Color::Black);
		//window.draw(test);
		player.draw(window);
		window.display();
	}

	return 0;
}
