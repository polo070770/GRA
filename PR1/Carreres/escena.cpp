#include <escena.h>

using namespace std;

escena::escena()

{
    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes
    capsaMinima.pmin[0] = -25;
    capsaMinima.pmin[1] = -25;
    capsaMinima.pmin[2] = -25;
    capsaMinima.a = 50;
    capsaMinima.h = 50;
    capsaMinima.p = 50;

    terra = NULL;
    cotxe_1 = NULL;
    cotxe_2 = NULL;
}


escena::~escena()
{
    printf("DESTRUCTOR!");

}

void escena::addObjecte(Objecte *obj) {
    if (dynamic_cast<Cotxe*>(obj)){
        //inserim el cotxe a la llista de cotxes
        if (cotxe_1 == NULL) cotxe_1 = (Cotxe*) obj;
        else if(cotxe_2 == NULL) cotxe_2 = (Cotxe*) obj;

        cotxes.add((Cotxe*) obj);
    }

    if (dynamic_cast<Obstacle*>(obj)){
        //inserim el cotxe a la llista de cotxes
        obstacles.add((Obstacle*) obj);
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
    obstacles.aplicaTG(m);
    if(terra!=NULL)
        terra->aplicaTG(m);

}

void escena::aplicaTGCentrat(mat4 m) {

    // Metode a modificar
    //apliquem a la llista de cotxes
    cotxes.aplicaTGCentrat(m);
    obstacles.aplicaTGCentrat(m);
    if(terra!=NULL)
        terra->aplicaTGCentrat(m);

}

void escena::draw() {

    // Metode a modificar

    cotxes.draw();
    obstacles.draw();
    if (terra!=NULL)
        terra->draw();
}

void escena::reset() {

    // posem tots els element al origin
    float yorig = terra!=NULL ? terra->getYOrig() : 0;
    // Metode a modificar
    cotxes.reset(yorig);
    obstacles.reset(yorig);
    if (terra!=NULL)
        terra->make();

}

void escena::accelera_cotxe1(){
    if(cotxe_1!=NULL){
        cotxe_1->forward();
    }
}
void escena::desaccelera_cotxe1(){
    if(cotxe_1!=NULL){
        cotxe_1->backward();
    }
}

void escena::gira_dreta_cotxe1(){
    if(cotxe_1!=NULL){
        cotxe_1->turnright();
    }
}

void escena::gira_esquerra_cotxe1(){
    if(cotxe_1!=NULL){
        cotxe_1->turnleft();
    }
}
void escena::llibera_gir_cotxe1(){
    if(cotxe_1!=NULL){
        cotxe_1->llibera_gir();
    }
}

void escena::llibera_acceleracio_cotxe1(){
    if(cotxe_1!=NULL){
        cotxe_1->llibera_acceleracio();
    }
}
/**
 * Retorna el punt y origen de l'escena
 * @brief escena::getYOrig
 * @return
 */
float escena::getYOrig(){
    if (terra!=NULL)
        return terra->getYOrig();
    else
        return 0;

}


void escena::temps(){
    cotxes.temps();
}

vector<Cotxe *> escena::getCotxes(){
    return cotxes.getListado();
}

vector<Obstacle *> escena::getObstacles(){
    return obstacles.getListado();
}
