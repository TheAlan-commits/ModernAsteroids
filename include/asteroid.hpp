#pragma once
#include<SFML/Graphics.hpp>

class Asteroid
{
private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    float rotationSpeed;

public:
    Asteroid(const sf::Texture& texture, sf::Vector2f position, sf::Vector2f vel, float rotSpeed);

    void update(float delta, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
};