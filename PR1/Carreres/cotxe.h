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
    void make();
    void aplicaTG(mat4 trans);
    void draw();
    void toGPU(QGLShaderProgram *program);
    void aplicaTGPoints(mat4 mtrans);
    void aplicaTGCentrat(mat4 mtrans);
    void forward();
    void backward();
    void turnleft();
    void turnright();
    Capsa3D calculCapsa3D();
    point4 direction;


private:

    vector<Objecte * > vector_fills;
    vector<Objecte *>::iterator fill_iter;
    Carrosseria *carroseria;
    Roda *roda_dreta_davantera;
    Roda *roda_esquerra_davantera;
    Roda *roda_dreta_posterior;
    Roda *roda_esquerra_posterior;

    static const int NumVerticesF = 100000;
    static const int NumCares = 300000;

    void escalar(float factor);


};

#endif // COTXE_H
