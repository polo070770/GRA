#ifndef CONJUNTMATERIALS_H
#define CONJUNTMATERIALS_H
#include <stdio.h>
#include <Common.h>
#include <material.h>

typedef enum{TERRA = 0, CARROSSERIA = 1, RODA = 2, OBSTACLE = 3} TMaterial;
class ConjuntMaterials
{
public:
    explicit ConjuntMaterials();
    void crearConjuntMaterials();
    Material* get(TMaterial tipus);
private:
    Material* conjunt[4];
};

#endif // CONJUNTMATERIALS_H
