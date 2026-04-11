/*
This file contains the player movement and 
obtaining the png from the assests folder.
*/

#include "player.hpp"
#include <iostream>
#include <filesystem>

Player::Player() : texture(), sprite(texture), speed(350.f)
{
    if (!texture.loadFromFile("assets/sprites/sprite.png"))
    {
        std::cout << "Failed to load player texture\n";
    }
    else
    {
        std::cout << "Player texture loaded\n";
    }

    auto size = texture.getSize();
    std::cout << "Texture size: " << size.x << " x " << size.y << "\n";

    sprite.setTexture(texture, true);
    sprite.setPosition({400.f, 400.f});
    sprite.setScale({.35f, .35f});

    sf::FloatRect bounds = sprite.getLocalBounds();
    float centerX = bounds.getCenter().x;
    float centerY = bounds.getCenter().y;
    sprite.setOrigin({centerX, centerY});
}

// Detect keystrokes and assign movement to said keys
void Player::update(float deltaTime, const sf::Vector2i mousePosition)
{
    sf::Vector2f spritePosition = sprite.getPosition();

    float dx = mousePosition.x - spritePosition.x;
    float dy = mousePosition.y - spritePosition.y;
    sf::Angle angle = sf::degrees(atan2(dy, dx) * 180.0f / 3.14159f);

    sprite.setRotation(angle + sf::degrees(90));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        if (spritePosition.y - speed * deltaTime > 0)
        {
            sprite.move({0.f, -speed * deltaTime});
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        if (spritePosition.y + speed * deltaTime < 800)
        {
            sprite.move({0.f, speed * deltaTime});
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        if (spritePosition.x - speed * deltaTime > 0)
        {
            sprite.move({-speed * deltaTime, 0.f});
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        if (spritePosition.x + speed * deltaTime < 800)
        {
            sprite.move({speed * deltaTime, 0.f});
        }
    }
}

// Following code draws the player every frame
void Player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::FloatRect Player::getBounds() const
{
    sf::Vector2f pos = sprite.getPosition();

    float hitboxWidth = 50.f;
    float hitboxHeight = 50.f;

    return sf::FloatRect(
        {pos.x - hitboxWidth / 2.f, pos.y - hitboxHeight / 2.f},
        {hitboxWidth, hitboxHeight}
    );
}