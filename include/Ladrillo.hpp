#ifndef LADRILLO_HPP
#define LADRILLO_HPP

#include <SFML/Graphics.hpp>

class Ladrillo {
private:
    sf::RectangleShape ladrillo;
    bool estado;

public:
    Ladrillo();
    void inicializar(float x, float y, bool estado, sf::Color color);
    bool colision(sf::FloatRect pelotaPos);
    void dibujar(sf::RenderWindow& ventana);
    sf::Vector2f getPosition();
};

#endif // LADRILLO_HPP

Ladrillo::Ladrillo() {
    estado = true;
}

void Ladrillo::inicializar(float x, float y, bool estado, sf::Color color) {
    ladrillo.setSize(sf::Vector2f(65, 10));
    ladrillo.setFillColor(color);
    ladrillo.setPosition(x, y);
    this->estado = estado;
}

bool Ladrillo::colision(sf::FloatRect pelotaPos) {
    if (estado && ladrillo.getGlobalBounds().intersects(pelotaPos)) {
        estado = false;
        return true;
    }
    return false;
}

void Ladrillo::dibujar(sf::RenderWindow& ventana) {
    if (estado) {
        ventana.draw(ladrillo);
    }
}

sf::Vector2f Ladrillo::getPosition() {
    return ladrillo.getPosition();
}

#endif // LADRILLO_HPP

