#include <escena.h>

using namespace std;

escena::escena()

{
    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes
    capsaMinima.pmin[0] = 0; capsaMinima.pmin[1] = 0; capsaMinima.pmin[2]=0;
    capsaMinima.a = 1; capsaMinima.h = 1; capsaMinima.p = 1;

    cotxe = NULL;
}


escena::~escena()
{
    printf("DESTRUCTOR!");

}

void escena::addObjecte(Objecte *obj) {
    if (dynamic_cast<Cotxe*>(obj))
        this->cotxe = (Cotxe*)obj;
}


void escena::CapsaMinCont3DEscena()
{
    // Metode a implementar
}

void escena::aplicaTG(mat4 m) {

    // Metode a modificar

    if (cotxe!=NULL)
        cotxe->aplicaTG(m);

}

void escena::aplicaTGCentrat(mat4 m) {

    // Metode a modificar

    if (cotxe!=NULL)
        cotxe->aplicaTGCentrat(m);

}

void escena::draw() {

    // Metode a modificar

    if (cotxe!=NULL)
        cotxe->draw();

}

void escena::reset() {

    // Metode a modificar

    if (cotxe!=NULL)
        cotxe->make();

}

