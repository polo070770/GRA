#include "obstacle.h"

Obstacle::Obstacle(QString n, GLfloat mida, GLfloat x0, GLfloat y0, GLfloat z0,
                   double girx, double giry, double girz):
    Objecte(NumVerticesF, n,  mida,  x0,  y0,  z0, girx,  giry,  girz){
std::cout<< "Estic en el constructor parametritzat de l'obstacle";
double escalaX = 1.0 / 4.6;
mat4 trans = Translate(-1.93*escalaX, (+0.26)*escalaX, -2.16*escalaX)*Scale(escalaX, escalaX, escalaX)*Translate(+1.93, -0.26, 2.16);


aplicaTG(trans);
}
