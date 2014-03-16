#include <escena.h>

using namespace std;

escena::escena()

{
    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes
    capsaMinima.pmin[0] = 0;
    capsaMinima.pmin[1] = 0;
    capsaMinima.pmin[2]=0;
    capsaMinima.a = 1;
    capsaMinima.h = 1;
    capsaMinima.p = 1;

    terra = NULL;
}


escena::~escena()
{
    printf("DESTRUCTOR!");

}

void escena::addObjecte(Objecte *obj) {
    if (dynamic_cast<Cotxe*>(obj)){
        //inserim el cotxe a la llista de cotxes
        cotxes.add((Cotxe*) obj);
    }
    if (dynamic_cast<Terra*>(obj))
        this->terra = (Terra*)obj;
}


void escena::CapsaMinCont3DEscena()
{
    // Metode a implementar
    //TODO
}

void escena::aplicaTG(mat4 m) {

    // Metode a modificar
    //apliquem a la llista de cotxes
    cotxes.aplicaTG(m);
    if(terra!=NULL)
        terra->aplicaTG(m);

}

void escena::aplicaTGCentrat(mat4 m) {

    // Metode a modificar
    //apliquem a la llista de cotxes
    cotxes.aplicaTGCentrat(m);

    if(terra!=NULL)
        terra->aplicaTGCentrat(m);

}

void escena::draw() {

    // Metode a modificar

    cotxes.draw();

    if (terra!=NULL)
        terra->draw();
}

void escena::reset() {

    // Metode a modificar
    cotxes.reset();

    if (terra!=NULL)
        terra->make();

}

