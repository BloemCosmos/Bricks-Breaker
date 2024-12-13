#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <SFML/Graphics/Image.hpp>
using namespace std;
using namespace sf;

// Ladrillo de Vidrio
struct Ladrillo
{
    bool Estado = true;
    RectangleShape LadrilloShape;
} Ladrillos[8][10];
// Plataforma
struct Plataforma
{
    bool Estado = false;
    RectangleShape PlataformaShape;
} Plataforma;
int AuxPlataforma;
// Cantidad de Ladrillos Activos
int CantLadrillos = 80;
// Pelota
CircleShape Pelota;
// Direccion y Velocidad Pelota
Vector2f VelDirPelota(-3, -3);
// Paleta
RectangleShape Paleta;
// Detectar Colision
bool EnColision = false;
// Estado del Juego
bool Activo = true;
// Fuente y Texto
Font Fuente;
Text Texto;
// Auxiliares para Colores
int IdCV = 1, IdCH = 1;
// Sonidos
SoundBuffer ParedSB, PaletaSB, LadrilloSB;
Sound ParedS, PaletaS, LadrilloS;
// Timer/Contador
int Timer = 0;

int main()
{
    // Ventana
    RenderWindow Ventana(VideoMode(850, 700), "Arcanoid");
    Ventana.setFramerateLimit(60);

    // Pelota
    Pelota = CircleShape(5.f);
    Pelota.setOrigin(2.5f, 2.5f);
    Pelota.setFillColor(Color::Red);
    Pelota.setPosition(Ventana.getSize().x / 2, Ventana.getSize().y / 2);
    // Paleta
    Paleta = RectangleShape(Vector2f(60, 10));
    Paleta.setOrigin(Paleta.getSize().x / 2, Paleta.getSize().y / 2);
    Paleta.setFillColor(Color::White);
    Paleta.setPosition(Ventana.getSize().x / 2, Ventana.getSize().y - 20);

    // Fuente y Texto
    if (!Fuente.loadFromFile("fonts/Arial.ttf"))
    {
        cout << "Error al cargar la fuente." << endl;
    }
    Texto.setFont(Fuente);
    if (!Fuente.loadFromFile("Fonts/Arial.TTF"))
    {
        cout << "Error al cargar la fuente." << endl;
    }
    Texto.setFont(Fuente);

    // Sonidos
    if (!ParedSB.loadFromFile("Sounds/ReboteParedes.wav") ||
        !PaletaSB.loadFromFile("Sounds/RebotePaleta.wav") ||
        !LadrilloSB.loadFromFile("Sounds/ReboteLadrillo.wav"))
    {
        cout << "Error al cargar los sonidos." << endl;
    }
    ParedS.setBuffer(ParedSB);
    PaletaS.setBuffer(PaletaSB);
    LadrilloS.setBuffer(LadrilloSB);

    // Inicializar Plataforma
    Plataforma.PlataformaShape = RectangleShape(Vector2f(30, 10));
    Plataforma.PlataformaShape.setFillColor(Color::Red);
    // Inicializacion de Ladrillos de Vidrio
    for (int i = 1; i < 8; i++)
    {
        IdCV *= -1;
        for (int j = 1; j < 9; j++)
        {
            // Tamaño Ladrillos
            Ladrillos[i][j].LadrilloShape = RectangleShape(Vector2f(65, 10));
            // Posicion Ladrillos
            Ladrillos[i][j].LadrilloShape.setPosition(j * 66, (i + 1) * 11);
            // Colores Ladrillos
            if (IdCV == 1)
            { // Cian Verde
                if (IdCH == 1)
                {
                    Ladrillos[i][j].LadrilloShape.setFillColor(Color::Cyan);
                }
                else
                {
                    Ladrillos[i][j].LadrilloShape.setFillColor(Color::Green);
                }
            }
            else
            { // Amarillo y Magenta
                if (IdCH == 1)
                {
                    Ladrillos[i][j].LadrilloShape.setFillColor(Color::Blue);
                }
                else
                {
                    Ladrillos[i][j].LadrilloShape.setFillColor(Color::brown);
                }
            }
            IdCH *= -1;
        }
    }

    // Cargar la textura de la imagen de fondo
    sf::Texture BackgroundTexture;
    if (!BackgroundTexture.loadFromFile("images/fondo_brick.jpg"))
    {
        std::cerr << "Error al cargar la imagen de fondo" << std::endl;
        return -1;
    }

    // Crear un sprite para la imagen de fondo
    sf::Sprite BackgroundSprite;
    BackgroundSprite.setTexture(BackgroundTexture);

    // Crear un bloque grande de color blanco
    RectangleShape BloqueBlanco(Vector2f(650, 500));
    BloqueBlanco.setFillColor(Color::White);

    while (Ventana.isOpen())
    {
        Event Event;
        while (Ventana.pollEvent(Event))
        {
            if (Event.type == Event::Closed)
            {
                Ventana.close();
            }
        }
        Timer++;
        if (Activo)
        { // Si esta activo el juego ejecutamos el codigo
            // Rebote Pelota
            if (Pelota.getPosition().x >= Ventana.getSize().x || Pelota.getPosition().x <= 0)
            {
                // Cambiamos Direccion en X
                VelDirPelota.x *= -1;
                ParedS.play();
            }
            if (Pelota.getPosition().y <= 0)
            {
                // Cambiamos Direccion en Y
                VelDirPelota.y *= -1;
                ParedS.play();
            }
            if (Pelota.getPosition().y >= Ventana.getSize().y)
            {
                // Perdio el juego
                Activo = false;
                Texto.setString("Perdiste");
                Texto.setPosition(200, Ventana.getSize().y / 2);
            }
            // Movimiento Paleta
            if (Keyboard::isKeyPressed(Keyboard::Right) && Paleta.getPosition().x <= Ventana.getSize().x)
            {
                Paleta.move(3.5, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::Left) && Paleta.getPosition().x >= 0)
            {
                Paleta.move(-3.5, 0);
            }
            // Movimiento Pelota
            Pelota.move(VelDirPelota.x, VelDirPelota.y);
            // Colision Plataforma
            if (Plataforma.Estado && Paleta.getGlobalBounds().contains(Plataforma.PlataformaShape.getPosition().x, Plataforma.PlataformaShape.getPosition().y))
            {
                Paleta.setScale(2, 1);
                Plataforma.Estado = false;
                Timer = 0;
            }
            // Colisiones Pelota
            if (!EnColision)
            {
                // Colision Pelota Paleta
                if (Paleta.getGlobalBounds().contains(Pelota.getPosition().x, Pelota.getPosition().y))
                {
                    if (Paleta.getPosition().x - Pelota.getPosition().x >= 20)
                    { // Rebote Lado Izquierdo
                        VelDirPelota.x = -3;
                    }
                    else if (Paleta.getPosition().x - Pelota.getPosition().x <= -20)
                    { // Rebote Lado Derecho
                        VelDirPelota.x = 3;
                    }
                    else
                    { // Rebote en el Medio
                        if (VelDirPelota.x > 0)
                        {
                            VelDirPelota.x = 1.5;
                        }
                        else
                        {
                            VelDirPelota.x = -1.5;
                        }
                    }
                    VelDirPelota.y *= -1; // Cambiar Direccion Y
                    EnColision = true;
                    PaletaS.play();
                }
                // Colision Pelota Ladrillo Vidrio
                for (int i = 1; i < 8; i++)
                {
                    for (int j = 1; j < 9; j++)
                    {
                        if (Ladrillos[i][j].Estado && Ladrillos[i][j].LadrilloShape.getGlobalBounds().contains(Pelota.getPosition().x, Pelota.getPosition().y))
                        {
                            VelDirPelota.y *= -1;
                            Ladrillos[i][j].Estado = false;
                            EnColision = true;
                            CantLadrillos--;
                            LadrilloS.play();
                            // Plataforma Aleatoria
                            srand(time(NULL));
                            AuxPlataforma = 1 + rand() % 6; // Num Aleatorio 1-5
                            if (AuxPlataforma == 1 && !Plataforma.Estado)
                            {
                                Plataforma.Estado = true;
                                Plataforma.PlataformaShape.setPosition(Ladrillos[i][j].LadrilloShape.getPosition().x, Ladrillos[i][j].LadrilloShape.getPosition().y);
                            }
                        }
                    }
                }
            }
            else
            {
                EnColision = false;
                if (Paleta.getGlobalBounds().contains(Pelota.getPosition().x, Pelota.getPosition().y))
                {
                    EnColision = true;
                }
                for (int i = 1; i < 8; i++)
                {
                    for (int j = 1; j < 9; j++)
                    {
                        if (Ladrillos[i][j].Estado && Ladrillos[i][j].LadrilloShape.getGlobalBounds().contains(Pelota.getPosition().x, Pelota.getPosition().y))
                        {
                            EnColision = true;
                            break;
                        }
                    }
                    if (EnColision)
                    {
                        break;
                    }
                }
            }
        }
        // Movimiento Plataforma
        if (Plataforma.Estado)
        {
            Plataforma.PlataformaShape.move(0, 2.5f);
        }
        // Comprobar Efecto Plataforma
        if (Timer >= 600)
        {
            Paleta.setScale(1, 1);
        }
        // Comprobar si quedan ladrillos
        if (CantLadrillos <= 0)
        {
            Activo = false;
            Texto.setString("Ganaste");
            Texto.setPosition(200, Ventana.getSize().y / 2);
        }
        // Limpiar Pantalla con un color de fondo específico
        Ventana.clear(Color(135, 206, 250)); // Azul claro

        if (Activo)
        {
            // Dibujar bloque blanco
            Ventana.draw(BloqueBlanco);
            // Dibujar Pantalla
            Ventana.draw(BackgroundSprite);
            Ventana.draw(Pelota);
            // Dibujar Paleta
            Ventana.draw(Paleta);
            // Dibujar Vitral de Ladrillos
            for (int i = 1; i < 8; i++)
            {
                for (int j = 1; j < 9; j++)
                {
                    if (Ladrillos[i][j].Estado)
                    {
                        Ventana.draw(Ladrillos[i][j].LadrilloShape);
                    }
                }
            }
            // Dibujar Plataforma
            if (Plataforma.Estado)
            {
                Ventana.draw(Plataforma.PlataformaShape);
            }
        }
        else
        {
            Ventana.draw(Texto);
        }
        // Mostrar Pantalla
        Ventana.display();
    }
    return 0;
}
