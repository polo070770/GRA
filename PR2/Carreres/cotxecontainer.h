#ifndef COTXECONTAINER_H
#define COTXECONTAINER_H

#include <stdio.h>


#include <Common.h>


#include <objecte.h>
#include <cotxe.h>
class CotxeContainer{
public:
    CotxeContainer();
    ~CotxeContainer();
    void add(Cotxe *cotxe);
    vector<Cotxe *> getListado();
    void aplicaTG(mat4 trans);
    void aplicaTGPoints(mat4 trans);
    void aplicaTGCentrat(mat4 trans);
    void draw();
    void reset(float yorig);
    void temps();
private:
    vector<Cotxe * > listado; // lo llamamos listado y no vector para evitar problemas de nombres
    vector<Cotxe *>::iterator iterador;
};

#endif // COTXECONTAINER_H
