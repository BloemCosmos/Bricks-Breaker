#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>

using namespace std;
using namespace sf;

// Ladrillo de Vidrio
struct Ladrillo
{
    bool estado = true;
    RectangleShape ladrillo;
} ladrillos[8][10];
// Plataforma
struct Plataforma
{
    bool estado = false;
    RectangleShape plataforma;
} plataforma;
int auxPlataforma;
// Cantidad de Ladrillos Activos
int cantLadrillos = 56;
// Pelota
CircleShape pelota;
// Direccion y Velocidad Pelota
Vector2f velDirPelota(-3, -3);
// Paleta
RectangleShape paleta;
// Detectar Colision
bool enColision = false;
// Estado del Juego
bool activo = true;
// Fuente y Texto
Font fuente;
Text texto;
// Auxiliares para Colores
int idCV = 1, idCH = 1;
// Sonidos
SoundBuffer paredSB, paletaSB, ladrilloSB;
Sound paredS, paletaS, ladrilloS;
// Timer/Contador
int timer = 0;

int main()
{
    // Ventana
    RenderWindow ventana(VideoMode(650, 500), "Arcanoid");
    ventana.setFramerateLimit(60);
    
    // Pelota
    pelota = CircleShape(5.f);
    pelota.setOrigin(2.5f, 2.5f);
    pelota.setFillColor(Color::Yellow);
    pelota.setPosition(ventana.getSize().x / 2, ventana.getSize().y / 2);
    // Paleta
    paleta = RectangleShape(Vector2f(60, 10));
    paleta.setOrigin(paleta.getSize().x / 2, paleta.getSize().y / 2);
    paleta.setFillColor(Color::Blue);
    paleta.setPosition(ventana.getSize().x / 2, ventana.getSize().y - 20);
    
    // Fuente y Texto
    if (!fuente.loadFromFile("Fonts/Arial.ttf"))
    {
        cout << "Error al cargar la fuente." << endl;
    }
    texto.setFont(fuente);
    
    // Sonidos
    if (!paredSB.loadFromFile("Sounds/ReboteParedes.wav") || 
        !paletaSB.loadFromFile("Sounds/RebotePaleta.wav") || 
        !ladrilloSB.loadFromFile("Sounds/ReboteLadrillo.wav"))
    {
        cout << "Error al cargar los sonidos." << endl;
    }
    paredS.setBuffer(paredSB);
    paletaS.setBuffer(paletaSB);
    ladrilloS.setBuffer(ladrilloSB);
    
    // Inicializar Plataforma
    plataforma.plataforma = RectangleShape(Vector2f(30, 10));
    plataforma.plataforma.setFillColor(Color::Red);
    // Inicializacion de Ladrillos de Vidrio
    for (int i = 1; i < 8; i++)
    {
        idCV *= -1;
        for (int j = 1; j < 9; j++)
        {
            // Tamaño Ladrillos
            ladrillos[i][j].ladrillo = RectangleShape(Vector2f(65, 10));
            // Posicion Ladrillos
            ladrillos[i][j].ladrillo.setPosition(j * 66, (i + 1) * 11);
            // Colores Ladrillos
            if (idCV == 1)
            { // Cian Verde
                if (idCH == 1)
                {
                    ladrillos[i][j].ladrillo.setFillColor(Color::Cyan);
                }
                else
                {
                    ladrillos[i][j].ladrillo.setFillColor(Color::Green);
                }
            }
            else
            { // Amarillo y Magenta
                if (idCH == 1)
                {
                    ladrillos[i][j].ladrillo.setFillColor(Color::Yellow);
                }
                else
                {
                    ladrillos[i][j].ladrillo.setFillColor(Color::Magenta);
                }
            }
            idCH *= -1;
        }
    }

    // Cargar la textura de la imagen de fondo
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/fondo_brick.jpg")) {
        std::cerr << "Error al cargar la imagen de fondo" << std::endl;
        return -1;
    }

    // Crear un sprite para la imagen de fondo
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Crear un bloque grande de color blanco
    RectangleShape bloqueBlanco(Vector2f(650, 500));
    bloqueBlanco.setFillColor(Color::White);

    while (ventana.isOpen())
    {
        Event event;
        while (ventana.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                ventana.close();
            }
        }
        timer++;
        if (activo)
        { // Si esta activo el juego ejecutamos el codigo
            // Rebote Pelota
            if (pelota.getPosition().x >= ventana.getSize().x || pelota.getPosition().x <= 0)
            {
                // Cambiamos Direccion en X
                velDirPelota.x *= -1;
                paredS.play();
            }
            if (pelota.getPosition().y <= 0)
            {
                // Cambiamos Direccion en Y
                velDirPelota.y *= -1;
                paredS.play();
            }
            if (pelota.getPosition().y >= ventana.getSize().y)
            {
                // Perdio el juego
                activo = false;
                texto.setString("Perdiste");
                texto.setPosition(200, ventana.getSize().y / 2);
            }
            // Movimiento Paleta
            if (Keyboard::isKeyPressed(Keyboard::Right) && paleta.getPosition().x <= ventana.getSize().x)
            {
                paleta.move(3.5, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::Left) && paleta.getPosition().x >= 0)
            {
                paleta.move(-3.5, 0);
            }
            // Movimiento Pelota
            pelota.move(velDirPelota.x, velDirPelota.y);
            // Colision Plataforma
            if (plataforma.estado && paleta.getGlobalBounds().contains(plataforma.plataforma.getPosition().x, plataforma.plataforma.getPosition().y))
            {
                paleta.setScale(2, 1);
                plataforma.estado = false;
                timer = 0;
            }
            // Colisiones Pelota
            if (!enColision)
            {
                // Colision Pelota Paleta
                if (paleta.getGlobalBounds().contains(pelota.getPosition().x, pelota.getPosition().y))
                {
                    if (paleta.getPosition().x - pelota.getPosition().x >= 20)
                    { // Rebote Lado Izquierdo
                        velDirPelota.x = -3;
                    }
                    else if (paleta.getPosition().x - pelota.getPosition().x <= -20)
                    { // Rebote Lado Derecho
                        velDirPelota.x = 3;
                    }
                    else
                    { // Rebote en el Medio
                        if (velDirPelota.x > 0)
                        {
                            velDirPelota.x = 1.5;
                        }
                        else
                        {
                            velDirPelota.x = -1.5;
                        }
                    }
                    velDirPelota.y *= -1; // Cambiar Direccion Y
                    enColision = true;
                    paletaS.play();
                }
                // Colision Pelota Ladrillo Vidrio
                for (int i = 1; i < 8; i++)
                {
                    for (int j = 1; j < 9; j++)
                    {
                        if (ladrillos[i][j].estado && ladrillos[i][j].ladrillo.getGlobalBounds().contains(pelota.getPosition().x, pelota.getPosition().y))
                        {
                            velDirPelota.y *= -1;
                            ladrillos[i][j].estado = false;
                            enColision = true;
                            cantLadrillos--;
                            ladrilloS.play();
                            // Plataforma Aleatoria
                            srand(time(NULL));
                            auxPlataforma = 1 + rand() % 6; // Num Aleatorio 1-5
                            if (auxPlataforma == 1 && !plataforma.estado)
                            {
                                plataforma.estado = true;
                                plataforma.plataforma.setPosition(ladrillos[i][j].ladrillo.getPosition().x, ladrillos[i][j].ladrillo.getPosition().y);
                            }
                        }
                    }
                }
            }
            else
            {
                enColision = false;
                if (paleta.getGlobalBounds().contains(pelota.getPosition().x, pelota.getPosition().y))
                {
                    enColision = true;
                }
                for (int i = 1; i < 8; i++)
                {
                    for (int j = 1; j < 9; j++)
                    {
                        if (ladrillos[i][j].estado && ladrillos[i][j].ladrillo.getGlobalBounds().contains(pelota.getPosition().x, pelota.getPosition().y))
                        {
                            enColision = true;
                            break;
                        }
                    }
                    if (enColision)
                    {
                        break;
                    }
                }
            }
        }
        // Movimiento Plataforma
        if (plataforma.estado)
        {
            plataforma.plataforma.move(0, 2.5f);
        }
        // Comprobar Efecto Plataforma
        if (timer >= 600)
        {
            paleta.setScale(1, 1);
        }
        // Comprobar si quedan ladrillos
        if (cantLadrillos <= 0)
        {
            activo = false;
            texto.setString("Ganaste");
            texto.setPosition(200, ventana.getSize().y / 2);
        }
        // Limpiar Pantalla con un color de fondo específico
        ventana.clear(Color(135, 206, 250)); // Azul claro

        if (activo)
        {
            // Dibujar bloque blanco
            ventana.draw(bloqueBlanco);
            // Dibujar Pantalla
            ventana.draw(backgroundSprite);
            ventana.draw(pelota);
            // Dibujar Paleta
            ventana.draw(paleta);
            // Dibujar Vitral de Ladrillos
            for (int i = 1; i < 8; i++)
            {
                for (int j = 1; j < 9; j++)
                {
                    if (ladrillos[i][j].estado)
                    {
                        ventana.draw(ladrillos[i][j].ladrillo);
                    }
                }
            }
            // Dibujar Plataforma
            if (plataforma.estado)
            {
                ventana.draw(plataforma.plataforma);
            }
        }
        else
        {
            ventana.draw(texto);
        }
        // Mostrar Pantalla
        ventana.display();
    }
    return 0;
}
