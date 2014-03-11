#include "cotxe.h"

Cotxe::Cotxe(QString n) : Objecte(NumVerticesF)
{
    nom = n;
    Index = 0;
    tam = 1;

    xorig = 0;
    yorig = 0;
    zorig = 0;

    xRot = 0;
    yRot = 0;
    zRot = 0;

    this->direction[0] = -1;
    this->direction[1] = 0;
    this->direction[2] = 0;
    this->direction[3] = 0;
    readObj(n);

    make();
}

Cotxe::Cotxe(QString n, GLfloat tamanio, GLfloat x0, GLfloat y0, GLfloat z0,
             double girx, double giry, double girz,
             float xdir, float ydir, float zdir):Objecte(NumVerticesF, n, tamanio, x0, y0, z0, girx, giry, girz)
{
    // El seguent codi escala el cotxe entre 0 i 1 i el situa el seu centre  0,0,0. aixo fa que es vegi en la primera visualització
    //
    // Cal modificar el codi seguent

    double escalaX = 1.0 / 4.6;
    mat4 m= Translate(-1.93*escalaX, (+0.26)*escalaX, -2.16*escalaX)*Scale(escalaX, escalaX, escalaX)*Translate(+1.93, -0.26, 2.16);

    aplicaTG(m);

}

void Cotxe::forward(){
    // Metode a implementar per fer el moviment del cotxe
}

void Cotxe::backward(){
    // Metode a implementar per fer el moviment del cotxe

}

void Cotxe::turnleft(){
    // Metode a implementar per fer el moviment del cotxe

}

void Cotxe::turnright(){
    // Metode a implementar per fer el moviment del cotxe

}
