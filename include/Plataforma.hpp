#ifndef PLATAFORMA_HPP
#define PLATAFORMA_HPP

#include <SFML/Graphics.hpp>

class Plataforma {
private:
    sf::RectangleShape plataforma;
    bool estado;

public:
    Plataforma();
    void inicializar(float x, float y);
    void mover();
    void dibujar(sf::RenderWindow& ventana);
    bool colision(sf::FloatRect jugadorPos);
    bool getEstado();
    void desactivar();
};

Plataforma::Plataforma() {
    estado = false;
}

void Plataforma::inicializar(float x, float y) {
    plataforma.setSize(sf::Vector2f(30, 10));
    plataforma.setFillColor(sf::Color::White);
    plataforma.setPosition(x, y);
    estado = true;
}

void Plataforma::mover() {
    plataforma.move(0, 2.5f);
}

void Plataforma::dibujar(sf::RenderWindow& ventana) {
    if (estado) {
        ventana.draw(plataforma);
    }
}

bool Plataforma::colision(sf::FloatRect jugadorPos) {
    if (estado && plataforma.getGlobalBounds().intersects(jugadorPos)) {
        estado = false;
        return true;
    }
    return false;
}

bool Plataforma::getEstado() {
    return estado;
}

void Plataforma::desactivar() {
    estado = false;
}

#endif // PLATAFORMA_HPP

