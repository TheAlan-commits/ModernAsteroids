#include<bullet.hpp>

Bullet::Bullet(const sf::Texture& texture, sf::Vector2f position, float speed)
	: sprite(texture)
{
    sf::Vector2u size = texture.getSize();
    sprite.setOrigin({
        static_cast<float>(size.x) / 2.f,
        static_cast<float>(size.y) / 2.f
        });

    sprite.setPosition(position);

    // Size of the bullets
    sprite.setScale({ 2.f, 2.f });
}

// Bullet Hitbox
sf::FloatRect Bullet::getBounds() const
{
    sf::Vector2f pos = sprite.getPosition();

    float hitboxWidth = 10.f;
    float hitboxHeight = 10.f;

    return sf::FloatRect(
        { pos.x - hitboxWidth / 2.f, pos.y - hitboxHeight / 2.f },
        { hitboxWidth, hitboxHeight }
    );
}

void Bullet::update(float delta, const sf::RenderWindow& window)
{
    if (!active) { return; }
    sprite.move(velocity * delta);

    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2u windowSize = window.getSize();

    //if (pos.x < 0.f)
    //    pos.x = static_cast<float>(windowSize.x);
    //else if (pos.x > static_cast<float>(windowSize.x))
    //    pos.x = 0.f;

    //if (pos.y < 0.f)
    //    pos.y = static_cast<float>(windowSize.y);
    //else if (pos.y > static_cast<float>(windowSize.y))
    //    pos.y = 0.f;

    sprite.setPosition(pos);
}

void Bullet::deactivate()
{
    active = false; 
}

void Bullet::draw(sf::RenderWindow& window) const
{
    if (active){
        window.draw(sprite);
    }
}

sf::Vector2f Bullet::getPosition() const
{
    return sprite.getPosition();
}

void Bullet::setRotation(sf::Angle angle)
{
    sprite.setRotation(angle);
}