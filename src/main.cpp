#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.hpp"
#include "asteroid.hpp"
#include "bullet.hpp"
#include <cmath>
#include <optional>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <filesystem>

void shoot(sf::Vector2f playerPosition, sf::Angle playerRotation, sf::Texture& bulletTexture, std::vector<Bullet>& bullets)
{
	// Convert angle to direction
	float radians = (playerRotation - sf::degrees(90)).asRadians();
	float dx = std::cos(radians);
	float dy = std::sin(radians);

	float bulletSpeed = 500.f;

	Bullet newBullet(bulletTexture, playerPosition, bulletSpeed);
	newBullet.setVelocity(sf::Vector2f(dx * bulletSpeed, dy * bulletSpeed));
	newBullet.setRotation(playerRotation);

	bullets.push_back(newBullet);
}

int main()
{
	enum class GameState
	{
		MainMenu,
		Playing,
		GameOver
	};

	int score = 0;

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

	GameState currentState = GameState::MainMenu;

	//Shooter Sound Effect
	sf::SoundBuffer shootBuffer;
	if(!shootBuffer.loadFromFile(basePath + "sounds/shootersound.wav"))
	{
		std::cout << "Failed to load shootersound.wav\n";
	}

	sf::Sound shootSound(shootBuffer);

	// Player lives
	int lives = 3;

	// Invincibility timer
	float invincibilityTimer = 0.f;
	const float invincibilityDuration = 1.5f;

	// Font
	sf::Font font;
	if (!font.openFromFile(basePath + "fonts/Orbitron-VariableFont_wght.ttf"))
	{
		std::cout << "Failed to load " << basePath + "fonts/Orbitron-VariableFont_wght.ttf" << '\n';
		return 1;
	}

	// Main Menu UI
	sf::Text titleText(font);
	titleText.setString("MODERN ASTEROIDS");
	titleText.setCharacterSize(52);
	titleText.setPosition({110.f, 160.f});

	sf::Text playText(font);
	playText.setString("Play");
	playText.setCharacterSize(34);
	playText.setPosition({350.f, 340.f});

	sf::Text quitMenuText(font);
	quitMenuText.setString("Quit");
	quitMenuText.setCharacterSize(34);
	quitMenuText.setPosition({355.f, 430.f});

	sf::Text ScoreText(font);
	ScoreText.setCharacterSize(34);

	// Game Over UI
	sf::Text gameOverText(font);
	gameOverText.setString("GAME OVER");
	gameOverText.setCharacterSize(58);
	gameOverText.setPosition({180.f, 170.f});

	sf::Text playAgainText(font);
	playAgainText.setString("Play Again");
	playAgainText.setCharacterSize(34);
	playAgainText.setPosition({285.f, 340.f});

	sf::Text quitText(font);
	quitText.setString("Quit");
	quitText.setCharacterSize(34);
	quitText.setPosition({350.f, 430.f});

	// Heart Texture
	sf::Texture heartTexture;
	if (!heartTexture.loadFromFile(basePath + "sprites/Life_Heart.png"))
	{
		std::cout << "Failed to load " << basePath + "sprites/Life_Heart.png" << '\n';
		return 1;
	}

	sf::Sprite heart1(heartTexture);
	sf::Sprite heart2(heartTexture);
	sf::Sprite heart3(heartTexture);

	float heartScale = 0.25f;
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
	player.setPosition({400.f, 400.f});

	// Clock
	sf::Clock clock;

	std::srand(static_cast<unsigned>(std::time(nullptr)));

	// Background
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile(basePath + "sprites/Space_Background.png"))
	{
		std::cout << "Failed to load " << basePath + "sprites/Space_Background.png" << '\n';
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
		std::cout << "Failed to load " << basePath + "sprites/astroid67.png" << '\n';
	}
	else
	{
		asteroidTextures.push_back(std::move(extraTexture));
	}

	std::vector<Asteroid> asteroids;

	auto spawnAsteroids = [&asteroids, &asteroidTextures]()
	{
		asteroids.clear();

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
	};

	//Particles
	class Particle 
	{
	public:
		sf::CircleShape shape;
		sf::Vector2f speed;

		float lifetime = 0.5f;

	};

	std::vector<Particle> particles;

	// Bullets
	sf::Texture bulletTexture;
	if (!bulletTexture.loadFromFile(basePath + "sprites/Bullet_Texture.png"))
	{
		std::cout << "Failed to load " << basePath + "sprites/Bullet_Texture.png" << '\n';
		return 1;
	}

	std::vector<Bullet> bullets;

	auto resetGame = [&]()
	{
		lives = 3;
		score = 0;
		invincibilityTimer = 0.f;

		bullets.clear();
		player.setPosition({400.f, 400.f});
		spawnAsteroids();

		currentState = GameState::Playing;
	};

	// Game loop
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

			if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mousePressed->button == sf::Mouse::Button::Left)
				{
					sf::Vector2f mousePos = window.mapPixelToCoords(mousePressed->position);

					if (currentState == GameState::MainMenu)
					{
						if (playText.getGlobalBounds().contains(mousePos))
						{
							resetGame();
						}

						if (quitMenuText.getGlobalBounds().contains(mousePos))
						{
							window.close();
						}
					}
					else if (currentState == GameState::GameOver)
					{
						if (playAgainText.getGlobalBounds().contains(mousePos))
						{
							resetGame();
						}

						if (quitText.getGlobalBounds().contains(mousePos))
						{
							window.close();
						}
					}
				}
			}
		}

		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		float delta = clock.restart().asSeconds();

		if (currentState == GameState::Playing)
		{
			player.update(delta, mousePosition);

			static bool wasMousePressed = false;
			bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

			if (isMousePressed && !wasMousePressed)
			{
				shootSound.play();
				shoot(player.getPosition(), player.getAngle(), bulletTexture, bullets);
			}

			wasMousePressed = isMousePressed;

			for (auto& bullet : bullets)
			{
				bullet.update(delta, window);
			}

			for (Asteroid& asteroid : asteroids)
			{
				asteroid.update(delta, window);
			}

			for (auto& bullet : bullets)
			{
				if (!bullet.isActive())
				{
					continue;
				}

				for (auto& asteroid : asteroids)
				{
					if (!asteroid.isActive())
					{
						continue;
					}

					if (bullet.getBounds().findIntersection(asteroid.getBounds()))
					{
						bullet.deactivate();
						
						for (int i = 0; i < 35; i++)
						{
							Particle p;
							p.shape.setRadius(2.f);
							p.shape.setFillColor(sf::Color::Yellow);
							p.shape.setPosition(asteroid.getPosition());

							float angle = (rand() % 360) * 3.14159f / 180.f;
							p.speed.x = cos(angle) * 100.f;
							p.speed.y = sin(angle) * 100.f;

							particles.push_back(p);

						}
						asteroid.reset();
						score += 10;
						std::cout << "Score: " << score << '\n';
						std::cout << "Asteroid destroyed!\n";
						break;
					}
				}
			}

			for (auto& particle : particles)
			{
				particle.shape.move({ particle.speed.x * delta, particle.speed.y * delta });
				particle.lifetime -= delta;
			}
			
			for (int i = particles.size() - 1; i >= 0; i--)
			{
				if (particles[i].lifetime <= 0)
				{
					particles.erase(particles.begin() + i);
				}
			}
			if (invincibilityTimer > 0.f)
			{
				invincibilityTimer -= delta;
			}

			if (invincibilityTimer <= 0.f)
			{
				for (Asteroid& asteroid : asteroids)
				{
					if (player.getBounds().findIntersection(asteroid.getBounds()))
					{
						lives--;
						invincibilityTimer = invincibilityDuration;

						std::cout << "Hit! Lives: " << lives << "\n";

						if (lives <= 0)
						{
							lives = 0;
							currentState = GameState::GameOver;
							std::cout << "Game Over\n";
						}

						break;
					}
				}
			}

			for (int i = static_cast<int>(bullets.size()) - 1; i >= 0; i--)
			{
				if (!bullets[i].isActive())
				{
					bullets.erase(bullets.begin() + i);
				}
			}

			for (int i = static_cast<int>(asteroids.size()) - 1; i >= 0; i--)
			{
				if (!asteroids[i].isActive())
				{
					asteroids.erase(asteroids.begin() + i);
				}
			}
		}

		// Draw
		window.clear();
		window.draw(backgroundSprite);

		if (currentState == GameState::MainMenu)
		{
			window.draw(titleText);
			window.draw(playText);
			window.draw(quitMenuText);
		}
		else if (currentState == GameState::Playing)
		{
			for (const Asteroid& asteroid : asteroids)
			{
				asteroid.draw(window);
			}

			for (const Bullet& bullet : bullets)
			{
				bullet.draw(window);
			}

			for (const Particle& particle : particles)
			{
				window.draw(particle.shape);
			}

			ScoreText.setString("Score: " + std::to_string(score));
			ScoreText.setCharacterSize(48);
			ScoreText.setPosition({250.f, 0.f});
			window.draw(ScoreText);
			player.draw(window);


			if (lives >= 1) window.draw(heart1);
			if (lives >= 2) window.draw(heart2);
			if (lives >= 3) window.draw(heart3);
		}
		else if (currentState == GameState::GameOver)
		{
			
			ScoreText.setString("Score: " + std::to_string(score));
			ScoreText.setCharacterSize(58);
			ScoreText.setPosition({ 225.f, 250.f });
			window.draw(ScoreText);
			window.draw(gameOverText);
			window.draw(playAgainText);
			window.draw(quitText);
		}

		window.display();
	}

	return 0;
}