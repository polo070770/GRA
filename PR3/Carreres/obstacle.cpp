#include "obstacle.h"

Obstacle::Obstacle(QString n, GLfloat mida, GLfloat x0, GLfloat y0, GLfloat z0,
                   double girx, double giry, double girz):
    Objecte(NumVerticesF){

    nom = n;
    Index = 0;
    tam = mida;

    xorig = x0;
    yorig = y0;
    zorig = z0;

    xRot = girx;
    yRot = giry;
    zRot = girz;
    readObj(n);

    make();

}

void Obstacle::make(){

    //cridem al make del pare
    Objecte::make();

    escalarFrom1(this->tam); // escalem l'obstacle a mida

    //centre del cotxe
    point4 centre = calculCentre();

    // apliquem la transformacio al centre, no cal que sigui centrada
    this->aplicaTG(Translate(-centre));

    //movem l'objecte al desti
    //invertimos la direccion
    // tambe serviria l'altura
    this->calculCapsa3D();
    float y_desti = yorig + (-capsa.pmin.y);
    point4 desti = point4(xorig * 1, y_desti,zorig * 1 ,0); // vector destino
    this->aplicaTG(Translate(desti));

}
