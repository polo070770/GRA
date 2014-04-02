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
#include <camera.h>

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

    float getYOrig();

    void accelera_cotxe1();
    void desaccelera_cotxe1();
    void gira_dreta_cotxe1();
    void gira_esquerra_cotxe1();
    void llibera_gir_cotxe1();
    void llibera_acceleracio_cotxe1();

    // Capsa contenedora de l'escena
    Capsa3D capsaMinima;
    Camera *cameraPanoramica;
    Camera *cameraTerceraPersona;

    Terra *terra;
    void temps();

    vector<Cotxe *> getCotxes();
    vector<Obstacle *> getObstacles();

    void setWidthGLWidget(float w);
    void setHeightGLWidget(float h);


private:

    float widthGLWidget;
    float heightGLWidget;

    Cotxe *cotxe_1;
    Cotxe *cotxe_2;
    CotxeContainer cotxes;
    ObstacleContainer obstacles;

};


#endif // ESCENA_H
