#include "roda.h"

Roda::Roda(GLfloat mida, GLfloat x0, GLfloat y0, GLfloat z0,
            double girx, double giry, double girz,
            float xdir, float ydir, float zdir):
    Objecte(NumVerticesF){

tam = mida;
std::cout<< "Estic en el constructor parametritzat de la roda" << endl;
xorig = x0;
yorig = y0;
zorig = z0;

xRot = xdir;
yRot = ydir;
zRot = zdir;
}
