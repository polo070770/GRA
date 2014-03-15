#ifndef RODA_H
#define RODA_H


#include <QGLShaderProgram>
#include <Common.h>
#include <objecte.h>
class Roda : public Objecte
{
public:
    Roda(QString n);
    Roda(QString n, GLfloat tamanio, GLfloat x0, GLfloat y0, GLfloat z0,
          double girx, double giry, double girz,
          float xdir, float ydir, float zdir);

    point4 direction;

private:

    static const int NumVerticesF = 100000;
    static const int NumCares = 300000;
};

#endif // RODA_H
