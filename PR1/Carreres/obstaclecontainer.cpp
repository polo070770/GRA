#include "obstaclecontainer.h"

using namespace std;
ObstacleContainer::ObstacleContainer()
{
}
ObstacleContainer::~ObstacleContainer(){
    printf("DESTRUCTOR cotxe container!");
}
void ObstacleContainer::add(Obstacle *obstacle){
    this->listado.push_back((Obstacle*)obstacle);
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

vector<Obstacle * > ObstacleContainer::getListado(){
    return this->listado;
}
