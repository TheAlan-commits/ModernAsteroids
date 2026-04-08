#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "asteroid.hpp"
#include <optional>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

int main()
{
	// Get current desktop mode
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	// Create window
	sf::RenderWindow window(
		sf::VideoMode({800, 800}, desktop.bitsPerPixel),
		"Modern Asteroids",
		sf::Style::Default,
		sf::State::Windowed
	);

	Player player;

	// Initialize clock for time-based calculations
	sf::Clock clock;

	// Seed random generator
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	// Load background texture
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("assets/sprites/Purple_Nebula.png"))
	{
		std::cout << "Failed to load assets/sprites/Purple_Nebula.png\n";
		return 1;
	}

	sf::Sprite backgroundSprite(backgroundTexture);

	// Scale background to fit the window
	sf::Vector2u textureSize = backgroundTexture.getSize();
	sf::Vector2u windowSize = window.getSize();

	backgroundSprite.setScale({
		static_cast<float>(windowSize.x) / textureSize.x,
		static_cast<float>(windowSize.y) / textureSize.y
	});

	// Load asteroid textures
	std::vector<sf::Texture> asteroidTextures;

	for (int i = 1; i <= 9; i++)
	{
		sf::Texture texture;
		std::string path = "assets/sprites/astroid" + std::to_string(i) + ".png";

		if (!texture.loadFromFile(path))
		{
			std::cout << "Failed to load " << path << '\n';
		}
		else
		{
			std::cout << "Loaded " << path << '\n';
			asteroidTextures.push_back(std::move(texture));
		}
	}

	sf::Texture extraTexture;
	if (!extraTexture.loadFromFile("assets/sprites/astroid67.png"))
	{
		std::cout << "Failed to load assets/sprites/astroid67.png\n";
	}
	else
	{
		std::cout << "Loaded assets/sprites/astroid67.png\n";
		asteroidTextures.push_back(std::move(extraTexture));
	}

	if (asteroidTextures.empty())
	{
		std::cout << "No asteroid textures were loaded. Exiting program.\n";
		return 1;
	}

	// Create asteroids
	std::vector<Asteroid> asteroids;

	for (int i = 0; i < 6; i++)
	{
		int textureIndex = std::rand() % asteroidTextures.size();

		float x = static_cast<float>(std::rand() % 800);
		float y = static_cast<float>(std::rand() % 800);

		float vx = static_cast<float>((std::rand() % 201) - 100);
		float vy = static_cast<float>((std::rand() % 201) - 100);

		// Prevent completely still asteroids
		if (vx == 0.f && vy == 0.f)
		{
			vx = 50.f;
		}

		float rotationSpeed = static_cast<float>((std::rand() % 181) - 90);

		asteroids.emplace_back(
			asteroidTextures[textureIndex],
			sf::Vector2f(x, y),
			sf::Vector2f(vx, vy),
			rotationSpeed
		);
	}

	// Game loop
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		// Get mouse position
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		// Time since last frame
		float delta = clock.restart().asSeconds();

		// Update player
		player.update(delta, mousePosition);

		// Update asteroids
		for (Asteroid& asteroid : asteroids)
		{
			asteroid.update(delta, window);
		}

		// Draw everything
		window.clear();

		// Draw background first
		window.draw(backgroundSprite);

		// Draw asteroids
		for (const Asteroid& asteroid : asteroids)
		{
			asteroid.draw(window);
		}

		// Draw player
		player.draw(window);

		window.display();
	}
}