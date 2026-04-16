#include<SFML/Graphics.hpp>

class Bullet
{
private:
	sf::Sprite sprite;
	sf::Vector2f velocity = { 0.f, 0.f };
    bool active = true;

public:
    Bullet(const sf::Texture& texture, sf::Vector2f position, float speed = 200.f);

    void update(float delta, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;
    void setRotation(sf::Angle angle);
    void deactivate();
    void setVelocity(sf::Vector2f newVelocity) 
    {
        velocity = newVelocity;
    }

    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    bool isActive() 
    {
        return active;
    }
};