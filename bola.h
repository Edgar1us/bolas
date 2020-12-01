#ifndef _BOLA_H
#define _BOLA_H

#include <QPainter>
#include <QColor>


class Bola {

public:
    Bola(float posicionX, float posicionY, float velX, float velY);
    Bola();

    float posicionX;
    float posicionY;
    float velX;
    float velY;
    int vida;
    static int vidaInicial;
    QColor color = QColor(random()%256, random()%256, random()%256);
     
    static const int diametro = 50;

    void moverBola(int ancho, int alto); //anchura y altura del area de juego
    void pintar(QPainter &pintor);
    bool choca(Bola * otra);

};

#endif