#include "carrosseria.h"

Carrosseria::Carrosseria(QString n) : Objecte(NumVerticesF){
    nom = n;
    Index = 0;
    tam = 1;

    xorig = 0;
    yorig = 0;
    zorig = 0;

    xRot = 0;
    yRot = 0;
    zRot = 0;

    this->direction[0] = -1;
    this->direction[1] = 0;
    this->direction[2] = 0;
    this->direction[3] = 0;
    readObj(n);

    make();
}
