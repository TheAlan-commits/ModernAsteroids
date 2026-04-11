#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "asteroid.hpp"
#include <optional>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <filesystem>

int main()
{
	// Determine asset base path
	std::string basePath = "assets/";

	if (!std::filesystem::exists(basePath))
	{
		basePath = "../assets/";
	}

	// Get current desktop mode
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	// Create window
	sf::RenderWindow window(
		sf::VideoMode({800, 800}, desktop.bitsPerPixel),
		"Modern Asteroids",
		sf::Style::Default,
		sf::State::Windowed
	);

	// Player lives
	int lives = 3;
	bool gameOver = false;

	// Invincibility timer
	float invincibilityTimer = 0.f;
	const float invincibilityDuration = 1.5f;

	// Heart Texture (Fixed path)
	sf::Texture heartTexture;
	if (!heartTexture.loadFromFile(basePath + "sprites/Life_Heart.png"))
	{
		std::cout << "Failed to load " << basePath + "sprites/Life_Heart.png" << '\n';
		return 1;
	}

	sf::Sprite heart1(heartTexture);
	sf::Sprite heart2(heartTexture);
	sf::Sprite heart3(heartTexture);

	// Much smaller scale
	float heartScale = 0.25f;

	// Proper spacing
	float startX = 4.f;
	float startY = 4.f;
	float spacing = 45.f;

	heart1.setScale({heartScale, heartScale});
	heart2.setScale({heartScale, heartScale});
	heart3.setScale({heartScale, heartScale});

	heart1.setPosition({startX, startY});
	heart2.setPosition({startX + spacing, startY});
	heart3.setPosition({startX + spacing * 2.f, startY});

	Player player;

	// Clock
	sf::Clock clock;

	std::srand(static_cast<unsigned>(std::time(nullptr)));

	// Background
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile(basePath + "sprites/Purple_Nebula.png"))
	{
		std::cout << "Failed to load " << basePath + "sprites/Purple_Nebula.png" << '\n';
		return 1;
	}

	sf::Sprite backgroundSprite(backgroundTexture);

	sf::Vector2u textureSize = backgroundTexture.getSize();
	sf::Vector2u windowSize = window.getSize();

	backgroundSprite.setScale({
		static_cast<float>(windowSize.x) / textureSize.x,
		static_cast<float>(windowSize.y) / textureSize.y
	});

	// Asteroids
	std::vector<sf::Texture> asteroidTextures;

	for (int i = 1; i <= 9; i++)
	{
		sf::Texture texture;
		std::string path = basePath + "sprites/astroid" + std::to_string(i) + ".png";

		if (!texture.loadFromFile(path))
		{
			std::cout << "Failed to load " << path << '\n';
		}
		else
		{
			asteroidTextures.push_back(std::move(texture));
		}
	}

	sf::Texture extraTexture;
	if (!extraTexture.loadFromFile(basePath + "sprites/astroid67.png"))
	{
		std::cout << "Failed to load astroid67\n";
	}
	else
	{
		asteroidTextures.push_back(std::move(extraTexture));
	}

	std::vector<Asteroid> asteroids;

	for (int i = 0; i < 6; i++)
	{
		int textureIndex = std::rand() % asteroidTextures.size();

		float x = static_cast<float>(std::rand() % 800);
		float y = static_cast<float>(std::rand() % 800);

		float vx = static_cast<float>((std::rand() % 201) - 100);
		float vy = static_cast<float>((std::rand() % 201) - 100);

		if (vx == 0.f && vy == 0.f)
			vx = 50.f;

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
				window.close();
		}

		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		float delta = clock.restart().asSeconds();

		if (!gameOver)
		{
			player.update(delta, mousePosition);

			for (Asteroid& asteroid : asteroids)
				asteroid.update(delta, window);

			if (invincibilityTimer > 0.f)
				invincibilityTimer -= delta;

			if (invincibilityTimer <= 0.f)
			{
				for (Asteroid& asteroid : asteroids)
				{
					if (player.getBounds().findIntersection(asteroid.getBounds()))
					{
						std::cout << "Collision detected!\n";
        				std::cout << "Player: " 
                  		<< player.getBounds().position.x << ", "
                  		<< player.getBounds().position.y << " | "
                  		<< player.getBounds().size.x << " x "
                  		<< player.getBounds().size.y << '\n';

        				std::cout << "Asteroid: "
                  		<< asteroid.getBounds().position.x << ", "
                  		<< asteroid.getBounds().position.y << " | "
                  		<< asteroid.getBounds().size.x << " x "
                  		<< asteroid.getBounds().size.y << '\n';

						lives--;
						invincibilityTimer = invincibilityDuration;

						std::cout << "Hit! Lives: " << lives << "\n";

						if (lives <= 0)
						{
							lives = 0;
							gameOver = true;
							std::cout << "Game Over\n";
						}

						break;
					}
				}
			}
		}

		// DRAW
		window.clear();

		window.draw(backgroundSprite);

		for (const Asteroid& asteroid : asteroids)
			asteroid.draw(window);

		player.draw(window);

		// Draw hearts
		if (lives >= 1) window.draw(heart1);
		if (lives >= 2) window.draw(heart2);
		if (lives >= 3) window.draw(heart3);

		window.display();
	}

	return 0;
}