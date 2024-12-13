#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include <SFML/Graphics.hpp>

class Jugador
{
private:
    sf::RectangleShape Paleta;

public:
    Jugador(sf::Vector2f Size, sf::Vector2f Position, sf::Color Color);
    void MoveLeft(float DeltaTime);
    void MoveRight(float DeltaTime);
    void Draw(sf::RenderWindow &Window);
    sf::Vector2f GetPosition();
    sf::FloatRect GetGlobalBounds();
};

Jugador::Jugador(sf::Vector2f Size, sf::Vector2f Position, sf::Color Color)
{
    Paleta.setSize(Size);
    Paleta.setOrigin(Size.x / 2, Size.y / 2);
    Paleta.setFillColor(Color);
    Paleta.setPosition(Position);
}

void Jugador::MoveLeft(float DeltaTime)
{
    Paleta.move(-3.5f * DeltaTime, 0);
}

void Jugador::MoveRight(float DeltaTime)
{
    Paleta.move(3.5f * DeltaTime, 0);
}

void Jugador::Draw(sf::RenderWindow &Window)
{
    Window.draw(Paleta);
}

sf::Vector2f Jugador::GetPosition()
{
    return Paleta.getPosition();
}

sf::FloatRect Jugador::GetGlobalBounds()
{
    return Paleta.getGlobalBounds();
}

#endif // JUGADOR_HPP
