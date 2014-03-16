#ifndef ESCENA_H
#define ESCENA_H

#include <cmath>
#include <iostream>
#include <stdlib.h>

#include <list>
#include <vector>
#include <string>
#include <stdio.h>


#include <Common.h>


#include <objecte.h>
#include <cotxe.h>
#include <obstacle.h>
#include <terra.h>
#include <cotxecontainer.h>
#include <obstaclecontainer.h>

using namespace std;

class escena
{
public:
    escena();
    ~escena();

    void addObjecte(Objecte *cotxe);
    void aplicaTG(mat4 m);

    void aplicaTGCentrat(mat4 m);
    void reset();

    void draw();
    void CapsaMinCont3DEscena();

    // Capsa contenedora de l'escena
    Capsa3D capsaMinima;


    Terra *terra;

private:
    CotxeContainer cotxes;
    ObstacleContainer obstacles;

};


#endif // ESCENA_H
