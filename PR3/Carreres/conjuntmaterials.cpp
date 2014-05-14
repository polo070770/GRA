#include "conjuntmaterials.h"

ConjuntMaterials::ConjuntMaterials(){
    this->crearConjuntMaterials();
}

void ConjuntMaterials::crearConjuntMaterials(){

    // Para los materiales, los números corresponden a las proporciones
    // de luz reflejada de esos colores. Así si R=1 y G=0.5 y B=0 para
    // un material, ese material refleja toda la luz roja, la mitad de
    // la verde, y ninguna de la luz azul.

    // Ambiente: Componente que refleja la luz independientemente de la dirección que venga
    // Difusa: Componente que refleja según la dirección de procedencia de la luz.
    // Especular: Componente que refleja la luz especular provoca el efecto brillo


    //creem la carrosseria
    Material *carrosseria = new Material("Carrosseria");
    carrosseria->coefEspecular = 0.4;
    carrosseria->intensitat.difusa = vec4(0.8, 0.0, 0.0 , 1.0);
    carrosseria->intensitat.ambient = vec4(0.2, 0.0, 0.0 , 1.0);
    carrosseria->intensitat.especular = vec4(0.9, 0.1, 0.1, 1.0);
    conjunt[CARROSSERIA] = carrosseria;

    //creem la roda
    Material *roda = new Material("Roda");
    roda->coefEspecular = 0.05;
    roda->intensitat.difusa = vec4(0.75, 0.75, 0.75 , 1.0);
    roda->intensitat.ambient = vec4(0.9, 0.9, 0.9, 1.0);
    roda->intensitat.especular = vec4(0.01, 0.01, 0.01 , 1.0);
    conjunt[RODA] = roda;

    Material *terra = new Material("Terra");
    terra->coefEspecular = 0.7;
    terra->intensitat.difusa = vec4(0.8, 0.0, 0.0, 1.0);
    terra->intensitat.ambient = vec4(0.2, 0.0, 0.0, 1.0);
    terra->intensitat.especular = vec4(0.9, 0.1, 0.1, 1.0);
    conjunt[TERRA] = terra;


}
Material* ConjuntMaterials::get(TMaterial tipus){
    return this->conjunt[tipus];
}
