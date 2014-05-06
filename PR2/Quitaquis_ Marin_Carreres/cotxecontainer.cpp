#include "cotxecontainer.h"

using namespace std;
CotxeContainer::CotxeContainer()
{
}
CotxeContainer::~CotxeContainer(){
    printf("DESTRUCTOR cotxe container!");
}
void CotxeContainer::add(Cotxe *cotxe){
    this->listado.push_back((Cotxe*)cotxe);
}

void CotxeContainer::aplicaTG(mat4 trans){
    for (iterador = this->listado.begin(); iterador < this->listado.end(); ++iterador) {
        if(*iterador!=NULL)(*iterador)->aplicaTG(trans);
    }
}

void CotxeContainer::aplicaTGCentrat(mat4 trans){
    for (iterador = this->listado.begin(); iterador < this->listado.end(); ++iterador) {
        if(*iterador!=NULL)(*iterador)->aplicaTGCentrat(trans);
    }
}

void CotxeContainer::aplicaTGPoints(mat4 trans){
    for (iterador = this->listado.begin(); iterador < this->listado.end(); ++iterador) {
        if(*iterador!=NULL)(*iterador)->aplicaTGPoints(trans);
    }
}

void CotxeContainer::draw(){
    for (iterador = this->listado.begin(); iterador < this->listado.end(); ++iterador) {
        if(*iterador!=NULL)(*iterador)->draw();
    }
}

void CotxeContainer::reset(float yorig){
    for (iterador = this->listado.begin(); iterador < this->listado.end(); ++iterador) {
        if(*iterador!=NULL) {
        (*iterador)->setYorig(yorig);
        (*iterador)->make();
     }
    }
}

void CotxeContainer::temps(){
    for (iterador = this->listado.begin(); iterador < this->listado.end(); ++iterador) {
        if(*iterador!=NULL)(*iterador)->temps();
    }
}

vector<Cotxe *> CotxeContainer::getListado(){
    return this->listado;
}
