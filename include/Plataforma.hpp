#ifndef PLATAFORMA_HPP
#define PLATAFORMA_HPP

#include <SFML/Graphics.hpp>

class Plataforma {
private:
    sf::RectangleShape PlataformaShape;
    bool Estado;

public:
    Plataforma();
    void Inicializar(float x, float y);
    void Mover();
    void Dibujar(sf::RenderWindow& ventana);
    bool Colision(sf::FloatRect jugadorPos);
    bool GetEstado();
    void Desactivar();
};

Plataforma::Plataforma() {
    Estado = false;
}

void Plataforma::Inicializar(float x, float y) {
    PlataformaShape.setSize(sf::Vector2f(30, 10));
    PlataformaShape.setFillColor(sf::Color::White);
    PlataformaShape.setPosition(x, y);
    Estado = true;
}

void Plataforma::Mover() {
    PlataformaShape.move(0, 2.5f);
}

void Plataforma::Dibujar(sf::RenderWindow& ventana) {
    if (Estado) {
        ventana.draw(PlataformaShape);
    }
}

bool Plataforma::Colision(sf::FloatRect jugadorPos) {
    if (Estado && PlataformaShape.getGlobalBounds().intersects(jugadorPos)) {
        Estado = false;
        return true;
    }
    return false;
}

bool Plataforma::GetEstado() {
    return Estado;
}

void Plataforma::Desactivar() {
    Estado = false;
}

#endif // PLATAFORMA_HPP
