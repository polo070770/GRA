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

    widthGLWidget = 50.0;
    heightGLWidget = 50.0;
    terceraPersona = false;
    primeraPersona = false;
    crearLlumsEscena();



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

    reset();
}


void escena::CapsaMinCont3DEscena()
{
    // Metode a implementar
    //de momento
    if(cotxe_1 != NULL){
        this->capsaMinima = cotxe_1->calculCapsa3D();
    }

    if(cotxe_2 != NULL){
        this->capsaMinima = addCapsaMinima(this->capsaMinima, cotxe_2->calculCapsa3D());
    }
    if(terra != NULL){
        this->capsaMinima = addCapsaMinima(this->capsaMinima, terra->calculCapsa3D());
    }
    this->capsaMinima = addCapsaMinima(this->capsaMinima, obstacles.getCapsa3D());
    /*
    float factor;
    if(this->heightGLWidget > this->widthGLWidget){
        factor = this->heightGLWidget / this->widthGLWidget;
        this->capsaMinima.h *= factor;

    }else if(this->widthGLWidget > this->heightGLWidget){
        factor = this->widthGLWidget / this->heightGLWidget;
        this->capsaMinima.a *= factor;
    }else{
        factor = 1;

    }
    */

}

/*
 *funcion que añade una capsa minima a otra y la devuelve
 */
Capsa3D escena::addCapsaMinima(Capsa3D capsaBase, Capsa3D novaCapsa){

    vec3  pmax;

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
    return capsaBase;

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

    //calculo la capsa minima
    this->CapsaMinCont3DEscena();

    //inicio la camera
    resetCameraTop();

}

void escena::camera_toGPU(QGLShaderProgram *program){
    camera.toGPU(program);
}
void escena::llum_toGPU(QGLShaderProgram *program){
    llums.setAmbientToGPU(program);
    llums.toGPU(program);
}
void escena::accelera_cotxe(int num){
     Cotxe * cotxe;
     if(num == 0)
         cotxe = cotxe_1;
     else if(num == 1)
         cotxe = cotxe_2;

     if(cotxe != NULL)
        cotxe->forward();
}

void escena::desaccelera_cotxe(int num){
    Cotxe * cotxe;
    if(num == 0)
        cotxe = cotxe_1;
    else if(num == 1)
        cotxe = cotxe_2;


    if(cotxe != NULL)
        cotxe->backward();

}

void escena::gira_dreta_cotxe(int num){
    Cotxe * cotxe;
    if(num == 0)
        cotxe = cotxe_1;
    else if(num == 1)
        cotxe = cotxe_2;


    if(cotxe != NULL)
        cotxe->turnright();

}

void escena::gira_esquerra_cotxe(int num){
    Cotxe * cotxe;
    if(num == 0)
        cotxe = cotxe_1;
    else if(num == 1)
        cotxe = cotxe_2;


    if(cotxe != NULL)
        cotxe->turnleft();

}

void escena::llibera_gir_cotxe(int num){
    Cotxe * cotxe;
    if(num == 0)
        cotxe = cotxe_1;
    else if(num == 1)
        cotxe = cotxe_2;

    if(cotxe != NULL)
        cotxe->llibera_gir();

}

void escena::llibera_acceleracio_cotxe(int num){
    Cotxe * cotxe;
    if(num == 0)
        cotxe = cotxe_1;
    else if(num == 1)
        cotxe = cotxe_2;


    if(cotxe != NULL)
        cotxe->llibera_acceleracio();

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

void escena::setWidthGLWidget(float w){
    this->widthGLWidget = w;
}

void escena::setHeightGLWidget(float h){
    this->heightGLWidget = h;
}

void escena::setWidgetSize(float width, float height){
    this->widthGLWidget = width;
    this->heightGLWidget = height;

    camera.setViewport(0,0,width, height);
}

void escena::mou_EixXCamera(int angle){
    camera.setAngX_Vup(angle);

}
void escena::mou_EixYCamera(int angle){
    camera.setAngY_Vup(angle);

}
void escena::mou_EixZCamera(int angle){
    camera.setAngZ_Vup(angle);

}

void escena::zoom_camera(double dy){
    camera.zoom(dy);
}

void escena::panning_dx(double delta){
    camera.panning_2D_X(delta);
}

void escena::panning_dy(double delta){
    camera.panning_2D_Y(delta);
}

void escena::temps(){
    cotxes.temps();
    if(terceraPersona){
        camera.actualitzaCameraThirdPerson(cotxe_1->calculCapsa3D());
    }else if(primeraPersona){
        camera.actualitzaCameraCockpit(cotxe_1->calculCapsa3D());
    }
}

void escena::resetCameraTop(){
    terceraPersona = false;
    primeraPersona = false;
    camera.ini(this->widthGLWidget, this->heightGLWidget,
                         this->capsaMinima, this->terceraPersona);
    camera.resetTopView();

}
void escena::initLookAtCotxe(){
    if(cotxe_1 != NULL){
        terceraPersona = true;
        primeraPersona = false;
        camera.ini(this->widthGLWidget, this->heightGLWidget,
                             this->cotxe_1->calculCapsa3D(), this->terceraPersona);
        camera.resetLookCotxe(this->cotxe_1->calculCapsa3D());
    }
}

void escena::initLookAtCockpit(){
    if(cotxe_1 != NULL){
        terceraPersona = false;
        primeraPersona = true;
        camera.ini(this->widthGLWidget, this->heightGLWidget,
                             this->cotxe_1->calculCapsa3D(), this->primeraPersona);
        camera.resetLookCockpit(this->cotxe_1->calculCapsa3D());
    }
}

vector<Cotxe *> escena::getCotxes(){
    return cotxes.getListado();
}

vector<Obstacle *> escena::getObstacles(){
    return obstacles.getListado();
}

void escena::crearLlumsEscena(){
    //creamos la intensidad Global
    llums.ambientGlobal = 0.05;
    //creamos una luz blanca
    Llum* llum = new Llum();
    llum->ini(vec3(0.0,-1.0,.0));
    //llum->ini(vec4(0.0,10.0,0.0));
    llum->intensitat.difusa = vec4(0.9, 0.9, 0.9, 1.0);
    llum->intensitat.especular = vec4(0.5, 0.5, 0.5, 1.0);
    llum->intensitat.ambient = vec4(0.1, 0.1, 0.1, 1.0);
    llum->atenuacio.constant = 0.5;
    llum->atenuacio.lineal = 0.5;
    llum->atenuacio.cuadratica = 0.5;
    llums.add(llum);
    //llum->ini(vec4(0.0,10.0,0.0), vec3(0.0,-1.0,.0),30.0);

    //llum->ini(vec4(0.0,10.0,0.0));
}
