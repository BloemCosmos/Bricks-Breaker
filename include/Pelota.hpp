#ifndef PELOTA_HPP
#define PELOTA_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Ladrillo.hpp" // Asumiendo que Ladrillo.hpp define la estructura Ladrillo

class Pelota {
private:
    sf::CircleShape pelota;
    sf::Vector2f velDirPelota;

public:
    Pelota(float radius, sf::Vector2f position, sf::Color color);
    void move();
    void checkBoundaryCollision(sf::RenderWindow &window, sf::Sound &paredSound);
    void checkPaletaCollision(sf::RectangleShape &paleta, sf::Sound &paletaSound);
    void checkLadrilloCollision(Ladrillo ladrillos[8][10], int &cantLadrillos, sf::Sound &ladrilloSound, sf::RectangleShape &plataforma);
    void draw(sf::RenderWindow &window);
    sf::Vector2f getPosition();
};

Pelota::Pelota(float radius, sf::Vector2f position, sf::Color color) {
    pelota = sf::CircleShape(radius);
    pelota.setOrigin(radius, radius);
    pelota.setFillColor(color);
    pelota.setPosition(position);
    velDirPelota = sf::Vector2f(-3, -3);
}

void Pelota::move() {
    pelota.move(velDirPelota);
}

void Pelota::checkBoundaryCollision(sf::RenderWindow &window, sf::Sound &paredSound) {
    if (pelota.getPosition().x >= window.getSize().x || pelota.getPosition().x <= 0) {
        velDirPelota.x *= -1;
        paredSound.play();
    }
    if (pelota.getPosition().y <= 0) {
        velDirPelota.y *= -1;
        paredSound.play();
    }
}

void Pelota::checkPaletaCollision(sf::RectangleShape &paleta, sf::Sound &paletaSound) {
    if (paleta.getGlobalBounds().intersects(pelota.getGlobalBounds())) {
        float paletaCenterX = paleta.getPosition().x;
        float pelotaCenterX = pelota.getPosition().x;
        
        if (pelotaCenterX < paletaCenterX) {
            velDirPelota.x = -3;
        } else if (pelotaCenterX > paletaCenterX) {
            velDirPelota.x = 3;
        } else {
            velDirPelota.x = 0;
        }
        
        velDirPelota.y *= -1;
        paletaSound.play();
    }
}

void Pelota::checkLadrilloCollision(Ladrillo ladrillos[8][10], int &cantLadrillos, sf::Sound &ladrilloSound, sf::RectangleShape &plataforma) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            if (ladrillos[i][j].estado && ladrillos[i][j].ladrillo.getGlobalBounds().intersects(pelota.getGlobalBounds())) {
                velDirPelota.y *= -1;
                ladrillos[i][j].estado = false;
                cantLadrillos--;
                ladrilloSound.play();
                
                // Check for plataforma activation
                srand(time(NULL));
                int random = 1 + rand() % 6;
                if (random == 1 && !plataforma.estado) {
                    plataforma.estado = true;
                    plataforma.plataforma.setPosition(ladrillos[i][j].ladrillo.getPosition());
                }
            }
        }
    }
}

void Pelota::draw(sf::RenderWindow &window) {
    window.draw(pelota);
}

sf::Vector2f Pelota::getPosition() {
    return pelota.getPosition();
}

#endif // PELOTA_HPP

