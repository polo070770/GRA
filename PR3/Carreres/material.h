#ifndef MATERIAL_H
#define MATERIAL_H
#include <stdio.h>
#include <Common.h>
#include <QGLShaderProgram>
typedef struct{
    vec4 ambient;
    vec4 difusa;
    vec4 especular;
} MIntensitat;

class Material
{
public:
    Material(QString nom);
    QString nom;
    MIntensitat intensitat;
    float coefEspecular;
    void toGPU(QGLShaderProgram *program);
};

#endif // MATERIAL_H
