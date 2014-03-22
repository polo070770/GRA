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
    void temps();
    void llibera_acceleracio();
    void llibera_gir();

private:

    vector<Objecte * > vector_fills;
    vector<Objecte *>::iterator fill_iter;
    Carrosseria *carroseria;
    Roda *roda_dreta_davantera;
    Roda *roda_esquerra_davantera;
    Roda *roda_dreta_posterior;
    Roda *roda_esquerra_posterior;
    void moviment();
    void avansar_rodes();
    void girar_rodes_davanteres();
    static const int NumVerticesF = 100000;
    static const int NumCares = 300000;
    static const int MAX_VELOCITAT = 330;
    static const int MIN_VELOCITAT = -50;
    static const float FACTOR_ROSAMENT = 2.9;
    static const float FACTOR_VELOCITAT = 0.002;
    static const float MAX_ANGLE = 40.0;
    static const float MIN_ANGLE = -40.0;
    static const float FACTOR_MOTLLA_DIRECCIO = 2.5;
    static const float FACTOR_ANGLE_GIR = 4;
    virtual void escalarFrom1(float factor);
    float velocitat;
    float angle_gir;
    int girant;
    int reset_rodes;
    int accelerant;

};

#endif // COTXE_H
