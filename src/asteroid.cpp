#include "asteroid.hpp"

Asteroid::Asteroid(const sf::Texture& texture, sf::Vector2f position, sf::Vector2f vel, float rotSpeed)
    : sprite(texture), velocity(vel), rotationSpeed(rotSpeed)
{
    sf::Vector2u size = texture.getSize();
    sprite.setOrigin({
        static_cast<float>(size.x) / 2.f,
        static_cast<float>(size.y) / 2.f
    });

    sprite.setPosition(position);

    // Size of the Asteroids
     sprite.setScale({7.f, 7.f});
}

// Asteroid Hitbox
sf::FloatRect Asteroid::getBounds() const
{
    sf::Vector2f pos = sprite.getPosition();

    float hitboxWidth = 80.f;
    float hitboxHeight = 80.f;

    return sf::FloatRect(
        {pos.x - hitboxWidth / 2.f, pos.y - hitboxHeight / 2.f},
        {hitboxWidth, hitboxHeight}
    );
}

void Asteroid::update(float delta, const sf::RenderWindow& window)
{
    sprite.move(velocity * delta);
    sprite.rotate(sf::degrees(rotationSpeed * delta));

    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2u windowSize = window.getSize();

    if (pos.x < 0.f)
        pos.x = static_cast<float>(windowSize.x);
    else if (pos.x > static_cast<float>(windowSize.x))
        pos.x = 0.f;

    if (pos.y < 0.f)
        pos.y = static_cast<float>(windowSize.y);
    else if (pos.y > static_cast<float>(windowSize.y))
        pos.y = 0.f;

    sprite.setPosition(pos);
}

void Asteroid::draw(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

void Asteroid::deactivate()
{
    active = false;
}

sf::Vector2f Asteroid::getPosition() const
{
    return sprite.getPosition();
}

void Asteroid::reset()
{
    //sprite.setPosition({ static_cast<float>(std::rand() % 800), static_cast<float>(std::rand() % 800) });

    int respawnPoint = static_cast<float>(std::rand() % 4);
    /*
    0 - Up
    1 - Down
    2 - Left
    3 - Right
    */
    if (respawnPoint == 0)
    {
        sprite.setPosition({ static_cast<float>(std::rand() % 800), static_cast<float>(std::rand() % 25) });
    }
    else if (respawnPoint == 1)
    {
        sprite.setPosition({ static_cast<float>(std::rand() % 800), static_cast<float>(std::rand() % 25) + 775.f });
    }
    else if (respawnPoint == 2)
    {
        sprite.setPosition({ static_cast<float>(std::rand() % 25), static_cast<float>(std::rand() % 800) });
    }
    else
    {
        sprite.setPosition({ static_cast<float>(std::rand() % 25) + 775.f, static_cast<float>(std::rand() % 800) });
    }
    //int x_or_y = std::rand() % 2;
    //int b_or_f = std::rand() % 2;

    //if (b_or_f)
    //{
    //    float resetPosition = 0.f;
    //}
    //else
    //{
    //    float resetPostion = static_cast<float>(800)
    //}
    //if (x_or_y)
    //{
    //    sprite.setPosition({ sprite.getPosition().y });
    //}
}