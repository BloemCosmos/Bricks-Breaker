#ifndef LADRILLO_HPP
#define LADRILLO_HPP

#include <SFML/Graphics.hpp>

class Brick
{
private:
    sf::RectangleShape brick;
    bool state;

public:
    Brick();
    void Initialize(float x, float y, bool state, sf::Color color);
    bool Collision(sf::FloatRect ballPos);
    void Draw(sf::RenderWindow &window);
    sf::Vector2f GetPosition();
};

#endif // LADRILLO_HPP

Brick::Brick()
{
    state = true;
}

void Brick::Initialize(float x, float y, bool state, sf::Color color)
{
    brick.setSize(sf::Vector2f(65, 10));
    brick.setFillColor(color);
    brick.setPosition(x, y);
    this->state = state;
}

bool Brick::Collision(sf::FloatRect ballPos)
{
    if (state && brick.getGlobalBounds().intersects(ballPos))
    {
        state = false;
        return true;
    }
    return false;
}

void Brick::Draw(sf::RenderWindow &window)
{
    if (state)
    {
        window.draw(brick);
    }
}

sf::Vector2f Brick::GetPosition()
{
    return brick.getPosition();
}

#endif // LADRILLO_HPP
