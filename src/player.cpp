/*
This file contains the player movement and 
obtaining the png from the assests folder.
*/


#include "player.hpp"
#include<iostream>
#include<filesystem>

Player::Player() : texture(), sprite(texture), speed(350.f)
{
    if (!texture.loadFromFile("assets/sprites/sprite.png"))
    {
        std::cout << "Failed to load player texture\n"; // troubleshooting cout, has no actual importance to code
    }
    else
    {
        std::cout << "Player texture loaded\n"; // another troubleshooting cout, also no importance, only if the code breaks, fingers crossed it doesn't
    }
    // Fixes the size of the sprite
    auto size = texture.getSize();
    std::cout << "Texture size: " << size.x << " x " << size.y << "\n";

    // Set the png to always be connected to the sprite and position it in the window
    sprite.setTexture(texture, true);
    sprite.setPosition({100.f, 100.f});
    sprite.setScale({.35f, .35f});

    //Get the local bounds of the sprite and define the origin as the center of those bounds
    sf::FloatRect bounds = sprite.getLocalBounds();
    float centerX = bounds.getCenter().x;
    float centerY = bounds.getCenter().y;
    sprite.setOrigin({ centerX, centerY });   
}

// Detect keystrokes and assign movement to said keys
void Player::update(float deltaTime, const sf::Vector2i mousePosition)
{
    //Get the current sprite position
    sf::Vector2f spritePosition = sprite.getPosition();

    //Use mouse and sprite postition to calculate and set angle between sprite and mouse
    float dx = mousePosition.x - spritePosition.x;
    float dy = mousePosition.y - spritePosition.y;
    sf::Angle angle = sf::degrees(atan2(dy, dx) * 180.0f / 3.14159f);

    sprite.setRotation(angle + sf::degrees(90));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        if (spritePosition.y - speed * deltaTime > 0)
        {
            // Sprite moves upward
            // std::cout << "W pressed\n"; // debugging cout statement
            sprite.move({ 0.f, -speed * deltaTime});
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        if (spritePosition.y + speed * deltaTime < 800)
        {
            // Sprite moves Downward
            sprite.move({ 0.f, speed * deltaTime });
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        if (spritePosition.x - speed * deltaTime > 0)
        {
            // Sprite moves leftward, actually it just moves left ;)
            sprite.move({ -speed * deltaTime, 0.f });
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        if (spritePosition.x + speed * deltaTime < 800)
        {
            // Sprite moves right
            sprite.move({speed * deltaTime, 0.f });
        }
    }
}

// Following code draws the player every frame
void Player::draw(sf::RenderWindow& window)
{
    //std::cout << "Drawing player\n"; // debugging cout statement
    window.draw(sprite);
}