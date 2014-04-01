#ifndef TRAJECTORIA_H
#define TRAJECTORIA_H

#include <Common.h>
class trajectoria
{
public:
    trajectoria(vec4 plano, int sampling);

    virtual vec4 calculaSeguentPunt() = 0;
protected:
    vec4  plane; // pla base sobre el que es defineix la trajectoria
    int sampling; // núnero de muestras por vuelta
    int iactual;
};

#endif // TRAJECTORIA_H
