#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>

using namespace std;
using namespace sf;

struct Bloque
{
    bool estado = true;
    RectangleShape bloque;
} bloques[8][10];

struct Pastilla
{
    bool estado = false;
    RectangleShape pastilla;
} pastilla;
int auxPastilla;
int cantBloques = 56;
CircleShape bola;
Vector2f velDirBola(-3, -3);
RectangleShape paleta;

bool enColision = false;
bool activo = true;

Font fuente;
Text texto;

int idCV = 1, idCH = 1;
SoundBuffer paredSB, paletaSB, bloqueSB;
Sound paredS, paletaS, bloqueS;

int timer = 0;

int main()
{
    RenderWindow ventana(VideoMode(650, 500), "Arcanoid");
    ventana.setFramerateLimit(60);
    bola = CircleShape(5.f);
    bola.setOrigin(2.5f, 2.5f);
    bola.setFillColor(Color::Yellow);
    bola.setPosition(ventana.getSize().x / 2, ventana.getSize().y / 2);
    
    paleta = RectangleShape(Vector2f(60, 10));
    paleta.setOrigin(paleta.getSize().x / 2, paleta.getSize().y / 2);
    paleta.setFillColor(Color::Blue);
    paleta.setPosition(ventana.getSize().x / 2, ventana.getSize().y - 20);

    if (!fuente.loadFromFile("Fonts/ARCADE.TTF"))
    {
        cout << "Error al cargar la fuente." << endl;
    }
    texto.setFont(fuente);

    if (!paredSB.loadFromFile("Sounds/ReboteParedes.wav") || !paletaSB.loadFromFile("Sounds/RebotePaleta.wav") || !bloqueSB.loadFromFile("Sounds/ReboteLadrillo.wav"))
    {
        cout << "Error al cargar los sonidos." << endl;
    }
    paredS.setBuffer(paredSB);
    paletaS.setBuffer(paletaSB);
    bloqueS.setBuffer(bloqueSB);

    pastilla.pastilla = RectangleShape(Vector2f(30, 10));
    pastilla.pastilla.setFillColor(Color::Red);

    for (int i = 1; i < 8; i++)
    {
        idCV *= -1;
        for (int j = 1; j < 9; j++)
        {
            bloques[i][j].bloque = RectangleShape(Vector2f(65, 10));
            bloques[i][j].bloque.setPosition(j * 66, (i + 1) * 11);
            if (idCV == 1)
            { 
                if (idCH == 1)
                {
                    bloques[i][j].bloque.setFillColor(Color::Cyan);
                }
                else
                {
                    bloques[i][j].bloque.setFillColor(Color::Green);
                }
            }
            else
            { 
                if (idCH == 1)
                {
                    bloques[i][j].bloque.setFillColor(Color::Yellow);
                }
                else
                {
                    bloques[i][j].bloque.setFillColor(Color::Magenta);
                }
            }
            idCH *= -1;
        }
    }

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
        { 
            if (bola.getPosition().x >= ventana.getSize().x || bola.getPosition().x <= 0)
            {
                velDirBola.x *= -1;
                paredS.play();
            }
            if (bola.getPosition().y <= 0)
            {
                velDirBola.y *= -1;
                paredS.play();
            }
            if (bola.getPosition().y >= ventana.getSize().y)
            {
                activo = false;
                texto.setString("Perdiste");
                texto.setPosition(200, ventana.getSize().y / 2);
            }
            if (Keyboard::isKeyPressed(Keyboard::Right) && paleta.getPosition().x <= ventana.getSize().x)
            {
                paleta.move(3.5, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::Left) && paleta.getPosition().x >= 0)
            {
                paleta.move(-3.5, 0);
            }
            bola.move(velDirBola.x, velDirBola.y);
            if (pastilla.estado && paleta.getGlobalBounds().contains(pastilla.pastilla.getPosition().x, pastilla.pastilla.getPosition().y))
            {
                paleta.setScale(2, 1);
                pastilla.estado = false;
                timer = 0;
            }
            if (!enColision)
            {
                if (paleta.getGlobalBounds().contains(bola.getPosition().x, bola.getPosition().y))
                {
                    if (paleta.getPosition().x - bola.getPosition().x >= 20)
                    {
                        velDirBola.x = -3;
                    }
                    else if (paleta.getPosition().x - bola.getPosition().x <= -20)
                    { 
                        velDirBola.x = 3;
                    }
                    else
                    { 
                        if (velDirBola.x > 0)
                        {
                            velDirBola.x = 1.5;
                        }
                        else
                        {
                            velDirBola.x = -1.5;
                        }
                    }
                    velDirBola.y *= -1; 
                    enColision = true;
                    paletaS.play();
                }
                for (int i = 1; i < 8; i++)
                {
                    for (int j = 1; j < 9; j++)
                    {
                        if (bloques[i][j].estado && bloques[i][j].bloque.getGlobalBounds().contains(bola.getPosition().x, bola.getPosition().y))
                        {
                            velDirBola.y *= -1;
                            bloques[i][j].estado = false;
                            enColision = true;
                            cantBloques--;
                            bloqueS.play();
                            srand(time(NULL));
                            auxPastilla = 1 + rand() % 6; 
                            if (auxPastilla == 1 && !pastilla.estado)
                            {
                                pastilla.estado = true;
                                pastilla.pastilla.setPosition(bloques[i][j].bloque.getPosition().x, bloques[i][j].bloque.getPosition().y);
                            }
                        }
                    }
                }
            }
            else
            {
                enColision = false;
                if (paleta.getGlobalBounds().contains(bola.getPosition().x, bola.getPosition().y))
                {
                    enColision = true;
                }
                for (int i = 1; i < 8; i++)
                {
                    for (int j = 1; j < 9; j++)
                    {
                        if (bloques[i][j].estado && bloques[i][j].bloque.getGlobalBounds().contains(bola.getPosition().x, bola.getPosition().y))
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
        if (pastilla.estado)
        {
            pastilla.pastilla.move(0, 2.5f);
        }
        if (timer >= 600)
        {
            paleta.setScale(1, 1);
        }
        if (cantBloques <= 0)
        {
            activo = false;
            texto.setString("Ganaste");
            texto.setPosition(200, ventana.getSize().y / 2);
        }
        ventana.clear();
        if (activo)
        {
            ventana.draw(bola);
            ventana.draw(paleta);
            for (int i = 1; i < 8; i++)
            {
                for (int j = 1; j < 9; j++)
                {
                    if (bloques[i][j].estado)
                    {
                        ventana.draw(bloques[i][j].bloque);
                    }
                }
            }
            if (pastilla.estado)
            {
                ventana.draw(pastilla.pastilla);
            }
        }
        else
        {
            ventana.draw(texto);
        }
        ventana.display();
    }
    return 0;
}