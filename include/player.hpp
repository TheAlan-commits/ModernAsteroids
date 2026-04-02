/*
This file contains the Player definition 
and will be using in combination with the 
player.cpp file.
*/
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

// Creating the Player class
class Player 
{
    public:
        Player();
        void update(float deltaTime, const sf::Vector2i mousePosition);
        void draw(sf::RenderWindow& window);

    private:
        sf::Texture texture;
        sf::Sprite sprite;
        float speed;
};

#endif