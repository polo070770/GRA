#include "obstaclecontainer.h"

using namespace std;
ObstacleContainer::ObstacleContainer()
{
    this->capsaMin.a =0;
    this->capsaMin.h =0;
    this->capsaMin.p =0;
    this->capsaMin.pmin.x = 0;
    this->capsaMin.pmin.y = 0;
    this->capsaMin.pmin.z = 0;
}
ObstacleContainer::~ObstacleContainer(){
    printf("DESTRUCTOR cotxe container!");
}
void ObstacleContainer::add(Obstacle *obstacle){
    this->listado.push_back((Obstacle*)obstacle);
    this->addCapsaMinima(obstacle->calculCapsa3D());
}

void ObstacleContainer::aplicaTG(mat4 trans){
    for (iterador = this->listado.begin(); iterador < this->listado.end(); ++iterador) {
        if(*iterador!=NULL)(*iterador)->aplicaTG(trans);
    }
}

void ObstacleContainer::aplicaTGCentrat(mat4 trans){
    for (iterador = this->listado.begin(); iterador < this->listado.end(); ++iterador) {
        if(*iterador!=NULL)(*iterador)->aplicaTGCentrat(trans);
    }
}

void ObstacleContainer::draw(){
    for (iterador = this->listado.begin(); iterador < this->listado.end(); ++iterador) {
        if(*iterador!=NULL)(*iterador)->draw();
    }
}

void ObstacleContainer::reset(float yorig){
    for (iterador = this->listado.begin(); iterador < this->listado.end(); ++iterador) {
        if(*iterador!=NULL){
            (*iterador)->setYorig(yorig);
            (*iterador)->make();
        }
    }
}
void ObstacleContainer::calculCapsa3D(){


}

/*
 *funcion que añade una capsa minima a otra y la devuelve
 */
void ObstacleContainer::addCapsaMinima(Capsa3D novaCapsa){

    vec3  pmax;

    Capsa3D capsaBase = capsaMin;

    pmax.x = capsaBase.pmin.x + capsaBase.a;
    pmax.y = capsaBase.pmin.y + capsaBase.h;
    pmax.z = capsaBase.pmin.z + capsaBase.p;

    if(novaCapsa.pmin.x < capsaBase.pmin.x) capsaBase.pmin.x = novaCapsa.pmin.x;
    if(novaCapsa.pmin.y < capsaBase.pmin.y) capsaBase.pmin.y = novaCapsa.pmin.y;
    if(novaCapsa.pmin.z < capsaBase.pmin.z) capsaBase.pmin.z = novaCapsa.pmin.z;

    if(novaCapsa.pmin.x + novaCapsa.a > pmax.x) pmax.x = novaCapsa.pmin.x + novaCapsa.a;
    if(novaCapsa.pmin.y + novaCapsa.h > pmax.y) pmax.y = novaCapsa.pmin.y + novaCapsa.h;
    if(novaCapsa.pmin.z + novaCapsa.p > pmax.z) pmax.z = novaCapsa.pmin.z + novaCapsa.p;

    capsaBase.a = pmax.x - capsaBase.pmin.x;
    capsaBase.h = pmax.y - capsaBase.pmin.y;
    capsaBase.p = pmax.z - capsaBase.pmin.z;
    this->capsaMin =  capsaBase;

}

Capsa3D ObstacleContainer::getCapsa3D(){
    Capsa3D capsa = this->capsaMin;
    return capsa;
}
vector<Obstacle * > ObstacleContainer::getListado(){
    return this->listado;
}
