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
#include <llum.h>
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
    Capsa3D addCapsaMinima(Capsa3D capsaBase, Capsa3D novaCapsa);
    float getYOrig();

    void accelera_cotxe(int num);
    void desaccelera_cotxe(int num);
    void gira_dreta_cotxe(int num);
    void gira_esquerra_cotxe(int num);
    void llibera_gir_cotxe(int num);
    void llibera_acceleracio_cotxe(int num);


    // Capsa contenedora de l'escena
    Capsa3D capsaMinima;
    Camera camera;
    //Camera cameraPanoramica;
    //Camera cameraTerceraPersona;

    Terra *terra;
    void temps();

    vector<Cotxe *> getCotxes();
    vector<Obstacle *> getObstacles();

    void setWidgetSize(float width, float height);

    // deprecated
    void setWidthGLWidget(float w);
    void setHeightGLWidget(float h);

    void camera_toGPU(QGLShaderProgram *program);
    void llum_toGPU(QGLShaderProgram *program);

    void mou_EixXCamera(int angle);
    void mou_EixYCamera(int angle);
    void mou_EixZCamera(int angle);

    void zoom_camera(double z);

    void panning_dx(double delta);
    void panning_dy(double delta);

    void resetCameraTop();
    void initLookAtCotxe();
    void initLookAtCockpit();
private:
    Llum *llum;
    bool terceraPersona;
    bool primeraPersona;
    float widthGLWidget;
    float heightGLWidget;

    Cotxe *cotxe_1;
    Cotxe *cotxe_2;
    CotxeContainer cotxes;
    ObstacleContainer obstacles;

};


#endif // ESCENA_H
