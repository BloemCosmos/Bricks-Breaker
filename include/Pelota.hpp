#ifndef PELOTA_HPP
#define PELOTA_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Ladrillo.hpp" // Asumiendo que Ladrillo.hpp define la estructura Ladrillo

class Pelota
{
private:
    sf::CircleShape PelotaShape;
    sf::Vector2f VelDirPelota;

public:
    Pelota(float radius, sf::Vector2f position, sf::Color color);
    void Move();
    void CheckBoundaryCollision(sf::RenderWindow &window, sf::Sound &paredSound);
    void CheckPaletaCollision(sf::RectangleShape &paleta, sf::Sound &paletaSound);
    void CheckLadrilloCollision(Ladrillo ladrillos[8][10], int &cantLadrillos, sf::Sound &ladrilloSound, sf::RectangleShape &plataforma);
    void Draw(sf::RenderWindow &window);
    sf::Vector2f GetPosition();
};

Pelota::Pelota(float radius, sf::Vector2f position, sf::Color color)
{
    PelotaShape = sf::CircleShape(radius);
    PelotaShape.setOrigin(radius, radius);
    PelotaShape.setFillColor(color);
    PelotaShape.setPosition(position);
    VelDirPelota = sf::Vector2f(-3, -3);
}

void Pelota::Move()
{
    PelotaShape.move(VelDirPelota);
}

void Pelota::CheckBoundaryCollision(sf::RenderWindow &window, sf::Sound &paredSound)
{
    if (PelotaShape.getPosition().x >= window.getSize().x || PelotaShape.getPosition().x <= 0)
    {
        VelDirPelota.x *= -1;
        paredSound.play();
    }
    if (PelotaShape.getPosition().y <= 0)
    {
        VelDirPelota.y *= -1;
        paredSound.play();
    }
}

void Pelota::CheckPaletaCollision(sf::RectangleShape &paleta, sf::Sound &paletaSound)
{
    if (paleta.getGlobalBounds().intersects(PelotaShape.getGlobalBounds()))
    {
        float paletaCenterX = paleta.getPosition().x;
        float pelotaCenterX = PelotaShape.getPosition().x;

        if (pelotaCenterX < paletaCenterX)
        {
            VelDirPelota.x = -3;
        }
        else if (pelotaCenterX > paletaCenterX)
        {
            VelDirPelota.x = 3;
        }
        else
        {
            VelDirPelota.x = 0;
        }

        VelDirPelota.y *= -1;
        paletaSound.play();
    }
}

void Pelota::CheckLadrilloCollision(Ladrillo ladrillos[8][10], int &cantLadrillos, sf::Sound &ladrilloSound, sf::RectangleShape &plataforma)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (ladrillos[i][j].estado && ladrillos[i][j].ladrillo.getGlobalBounds().intersects(PelotaShape.getGlobalBounds()))
            {
                VelDirPelota.y *= -1;
                ladrillos[i][j].estado = false;
                cantLadrillos--;
                ladrilloSound.play();

                // Check for plataforma activation
                srand(time(NULL));
                int random = 1 + rand() % 6;
                if (random == 1 && !plataforma.estado)
                {
                    plataforma.estado = true;
                    plataforma.plataforma.setPosition(ladrillos[i][j].ladrillo.getPosition());
                }
            }
        }
    }
}

void Pelota::Draw(sf::RenderWindow &window)
{
    window.draw(PelotaShape);
}

sf::Vector2f Pelota::GetPosition()
{
    return PelotaShape.getPosition();
}

#endif // PELOTA_HPP
