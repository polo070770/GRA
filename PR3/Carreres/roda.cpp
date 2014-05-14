#include "roda.h"

Roda::Roda(GLfloat mida, GLfloat x0, GLfloat y0, GLfloat z0,
            double girx, double giry, double girz,
            float xdir, float ydir, float zdir):
    Objecte(NumVerticesF){

    tam = mida;

    xorig = x0;
    yorig = y0;
    zorig = z0;

    xRot = xdir;
    yRot = ydir;
    zRot = zdir;
    angle_gir = 0.0;
    angle_cotxe = 0;

    this->material = materials.get(CARROSSERIA);
}

void Roda::aplicaTGCentrat(mat4 m){
    // calculamos el centro
    calculCapsa3D();
    point4 centre = calculCentre();

    // tenim en conte que es posible que les rodes estiguin rotades respecte les y
    mat4 transform_centrada = ( Translate(centre) * RotateY(angle_gir + angle_cotxe) * m * RotateY(-angle_gir - angle_cotxe) * Translate(-centre) );

    // aplicmos las transformaciones
    aplicaTG(transform_centrada);
    aplicaTGNormals(m);

}

void Roda::reset_angle(){
    angle_gir = 0.0;
}

void Roda::fer_gir(float angle){
    angle_gir = angle;
    mat4 gir = RotateY(angle_gir);
    this->aplicaTGCentrat(gir);
    aplicaTGNormals(gir);
}

void Roda::actualitzaAngleCotxe(int angle){
    this->angle_cotxe = angle;
}
