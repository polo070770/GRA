#ifndef OBSTACLECONTAINER_H
#define OBSTACLECONTAINER_H
#include <stdio.h>


#include <Common.h>


#include <objecte.h>
#include <obstacle.h>
class ObstacleContainer
{
public:
    ObstacleContainer();
    ~ObstacleContainer();
    void add(Obstacle *obstacle);
    vector<Obstacle * > getListado();
    void aplicaTG(mat4 trans);
    void aplicaTGCentrat(mat4 trans);
    void draw();
    void reset(float yorig);
    Capsa3D getCapsa3D();
private:
    void calculCapsa3D();
    void addCapsaMinima(Capsa3D novaCapsa);
    Capsa3D capsaMin;
    vector<Obstacle * > listado; // lo llamamos listado y no vector para evitar problemas de nombres
    vector<Obstacle *>::iterator iterador;
};

#endif // OBSTACLECONTAINER_H