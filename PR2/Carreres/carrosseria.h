#ifndef CARROSSERIA_H
#define CARROSSERIA_H

#include <QGLShaderProgram>
#include <Common.h>
#include <objecte.h>
class Carrosseria : public Objecte

{
public:
    Carrosseria(GLfloat tamanio, GLfloat x0, GLfloat y0, GLfloat z0,
                            double girx, double giry, double girz,
                            float xdir, float ydir, float zdir);

private:

    static const int NumVerticesF = 100000;
    static const int NumCares = 300000;
};
#endif // CARROSSERIA_H
