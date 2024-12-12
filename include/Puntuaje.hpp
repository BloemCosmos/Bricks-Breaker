#ifndef PUNTUAJE_HPP
#define PUNTUAJE_HPP
#include <iostream>
#include <SFML/Graphics.hpp>

class Puntuaje {
private:
    int Puntuacion;
    sf::Text TextoPuntuacion;
    sf::Font Fuente;

public:
    Puntuaje();
    void IncrementarPuntuacion(int Puntos);
    void ReiniciarPuntuacion();
    void Draw(sf::RenderWindow &Window);
};

Puntuaje::Puntuaje() {
    Puntuacion = 0;
    if (!Fuente.loadFromFile("Fonts/ARCADE.TTF")) {
        std::cout << "Error al cargar la fuente." << std::endl;
    }
    TextoPuntuacion.setFont(Fuente);
    TextoPuntuacion.setCharacterSize(20);
    TextoPuntuacion.setFillColor(sf::Color::White);
    ReiniciarPuntuacion();
}

void Puntuaje::IncrementarPuntuacion(int Puntos) {
    Puntuacion += Puntos;
    TextoPuntuacion.setString("Puntuacion: " + std::to_string(Puntuacion));
}

void Puntuaje::ReiniciarPuntuacion() {
    Puntuacion = 0;
    TextoPuntuacion.setString("Puntuacion: " + std::to_string(Puntuacion));
}

void Puntuaje::Draw(sf::RenderWindow &Window) {
    Window.draw(TextoPuntuacion);
}
#endif // PUNTUAJE_HPP
