#ifndef RODA_H
#define RODA_H


#include <QGLShaderProgram>
#include <Common.h>
#include <objecte.h>
class Roda : public Objecte
{
public:
    Roda(GLfloat tamanio, GLfloat x0, GLfloat y0, GLfloat z0,
          double girx, double giry, double girz,
          float xdir, float ydir, float zdir);
    void reset_angle();
    void fer_gir(float angle);
    void aplicaTGCentrat(mat4 m);
private:

static const int NumVerticesF = 100000;
static const int NumCares = 300000;
float angle_gir;
};

#endif // RODA_H
