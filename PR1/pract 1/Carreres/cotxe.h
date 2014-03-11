#ifndef COTXE_H
#define COTXE_H

#include <Common.h>
#include <objecte.h>

#include <iostream>

using namespace std;

class Cotxe: public Objecte
{
public:
    Cotxe(QString n);
    Cotxe(QString n, GLfloat tamanio, GLfloat x0, GLfloat y0, GLfloat z0,
          double girx, double giry, double girz,
          float xdir, float ydir, float zdir);

    void forward();
    void backward();
    void turnleft();
    void turnright();
    point4 direction;

private:

    static const int NumVerticesF = 100000;
    static const int NumCares = 300000;


};

#endif // COTXE_H
