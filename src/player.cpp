/*
This file contains the player movement and 
obtaining the png from the assests folder.
*/


#include "player.hpp"
#include<iostream>

Player::Player() : texture(), sprite(texture), speed(1.f)
{
    if (!texture.loadFromFile("../../../../assets/sprites/sprite.png"))
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
    sprite.setScale({1.f, 1.f});

    //Get the local bounds of the sprite and define the origin as the center of those bounds
    sf::FloatRect bounds = sprite.getLocalBounds();
    float centerX = bounds.getCenter().x;
    float centerY = bounds.getCenter().y;
    sprite.setOrigin({ centerX, centerY });
    
}

// Detect keystrokes and assign movement to said keys
void Player::update()
{
    //Get the current size of the window and sprite position
    sf::Vector2u windowSize = sf::VideoMode::getDesktopMode().size;
    sf::Vector2f spritePosition = sprite.getPosition();
    

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        if (spritePosition.y - speed > 0)
        {
            // Sprite moves upward
            std::cout << "W pressed\n"; // debugging cout statement
            sprite.move({ 0.f, -speed });
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        if (spritePosition.y + speed < 800)
        {
            // Sprite moves Downward
            sprite.move({ 0.f, speed });
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        if (spritePosition.x - speed > 0)
        {
            // Sprite moves leftward, actually it just moves left ;)
            sprite.move({ -speed, 0.f });
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        if (spritePosition.x + speed < 800)
        {
            // Sprite moves right
            sprite.move({ speed, 0.f });
        }
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        sprite.setRotation(sf::degrees(-90));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        sprite.setRotation(sf::degrees(0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        sprite.setRotation(sf::degrees(90));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        sprite.setRotation(sf::degrees(180));
    }

}

// Following code draws the player every frame
void Player::draw(sf::RenderWindow& window)
{
    //std::cout << "Drawing player\n"; // debugging cout statement
    window.draw(sprite);
}