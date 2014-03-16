#ifndef COTXE_H
#define COTXE_H

#include <Common.h>
#include <objecte.h>
#include <roda.h>
#include <carrosseria.h>
#include <iostream>

using namespace std;

class Cotxe: public Objecte
{
public:
    Cotxe(QString n);
    Cotxe(QString n, GLfloat tamanio, GLfloat x0, GLfloat y0, GLfloat z0,
          double girx, double giry, double girz,
          float xdir, float ydir, float zdir);

    void readObj(QString filename);
    void forward();
    void backward();
    void turnleft();
    void turnright();
    point4 direction;
    void make();
    void aplicaTG(mat4 trans);
private:
    vector<Objecte * > vector_fills;
    Carrosseria *carroseria;
    Roda *roda_dreta_davantera;
    Roda *roda_esquerra_davantera;
    Roda *roda_dreta_posterior;
    Roda *roda_esquerra_posterior;

    static const int NumVerticesF = 100000;
    static const int NumCares = 300000;


};

#endif // COTXE_H
