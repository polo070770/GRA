#include <escena.h>

using namespace std;

escena::escena()

{

    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes
    capsaMinima.pmin[0] = -25;
    capsaMinima.pmin[1] = -25;
    capsaMinima.pmin[2] = -25;
    capsaMinima.a = 25;
    capsaMinima.h = 25;
    capsaMinima.p = 25;

    terra = NULL;
    cotxe_1 = NULL;
    cotxe_2 = NULL;

    widthGLWidget = 50.0;
    heightGLWidget = 50.0;

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
    //de momento
    if(cotxe_1 != NULL){
        this->capsaMinima = cotxe_1->calculCapsa3D();
    }


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

void escena::reset(QGLShaderProgram *program) {

    // posem tots els element al origin
    float yorig = terra!=NULL ? terra->getYOrig() : 0;

    // Metode a modificar
    cotxes.reset(yorig);

    obstacles.reset(yorig);

    if (terra!=NULL)
        terra->make();

    //calculo la capsa minima
    //this->CapsaMinCont3DEscena();

    //inicio la camera

    //cameraPanoramica.ini(this->widthGLWidget, this->heightGLWidget, this->capsaMinima);
    //cameraPanoramica.toGPU(program);

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
