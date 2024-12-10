#ifndef PUNTUAJE_HPP
#define PUNTUAJE_HPP
#include <iostream>

#include <SFML/Graphics.hpp>

class Puntuaje {
private:
    int puntuacion;
    sf::Text textoPuntuacion;
    sf::Font fuente;

public:
    Puntuaje();
    void incrementarPuntuacion(int puntos);
    void reiniciarPuntuacion();
    void draw(sf::RenderWindow &window);
};


Puntuaje::Puntuaje() {
    puntuacion = 0;
    if (!fuente.loadFromFile("Fonts/ARCADE.TTF")) {
        std::cout << "Error al cargar la fuente." << std::endl;
    }
    textoPuntuacion.setFont(fuente);
    textoPuntuacion.setCharacterSize(20);
    textoPuntuacion.setFillColor(sf::Color::White);
    reiniciarPuntuacion();
}

void Puntuaje::incrementarPuntuacion(int puntos) {
    puntuacion += puntos;
    textoPuntuacion.setString("Puntuacion: " + std::to_string(puntuacion));
}

void Puntuaje::reiniciarPuntuacion() {
    puntuacion = 0;
    textoPuntuacion.setString("Puntuacion: " + std::to_string(puntuacion));
}

void Puntuaje::draw(sf::RenderWindow &window) {
    window.draw(textoPuntuacion);
}
#endif // PUNTUAJE_HPP