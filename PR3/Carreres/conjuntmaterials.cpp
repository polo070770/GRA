#include "conjuntmaterials.h"

ConjuntMaterials::ConjuntMaterials(){
    this->crearConjuntMaterials();
}

void ConjuntMaterials::crearConjuntMaterials(){
    //creem la carrosseria
    Material *carrosseria = new Material("Carrosseria");
    carrosseria->coefEspecular = 0.5;
    carrosseria->intensitat.difusa = vec4(0.8, 0.0, 0.0 , 1.0);
    carrosseria->intensitat.ambient = vec4(0.2, 0.0, 0.0 , 1.0);
    carrosseria->intensitat.especular = vec4(0.9, 0.1, 0.1, 1.0);
    conjunt[CARROSSERIA] = carrosseria;

    //creem la roda
    Material *roda = new Material("Roda");
    roda->coefEspecular = 96.0;
    roda->intensitat.difusa = vec4(0.05, 0.05, 0.05 , 1.0);
    roda->intensitat.ambient = vec4(0.05, 0.05, 0.05 , 1.0);
    roda->intensitat.especular = vec4(0.05, 0.05, 0.05 , 1.0);
    conjunt[RODA] = roda;


}
Material* ConjuntMaterials::get(TMaterial tipus){
    return this->conjunt[tipus];
}