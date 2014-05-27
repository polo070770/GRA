/***************************************************/
/*           Definicio de la llum                */
/***************************************************/
#ifndef LLUM_H
#define LLUM_H
#include <stdio.h>
#include <Common.h>
#include <QGLShaderProgram>

typedef enum {PUNTUAL = 0, DIRECCIONAL= 1, SPOT = 2} TipusLlum;
typedef Common::vec4  color4;

typedef struct{
    color4 ambient;
    color4 difusa;
    color4 especular;
} Intensitat;

typedef struct{
    float constant;
    float lineal;
    float cuadratica;
} Atenuacio;

using namespace std;

class Llum
{
public:
    Llum();
    void ini(vec3 direccio, char * light); //inicia una llum direccional
    void ini(vec4 posicio, char * light);  //inicia una llum puntual
    void ini(vec4 posicio, vec3 direccio, float obertura, char * light); //inicia un focus (spotlight)
    void toGPU(QGLShaderProgram *program);


private:
    Intensitat intensitat;
    Atenuacio atenuacio;
    TipusLlum tipus;
    vec4 posicio;
    vec3 direccio;
    float obertura;
    char * light;

};

#endif // LLUM_H
