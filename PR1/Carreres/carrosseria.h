#ifndef CARROSSERIA_H
#define CARROSSERIA_H

#include <QGLShaderProgram>
#include <Common.h>
#include <objecte.h>
class Carrosseria : public Objecte

{
public:
    Carrosseria(QString n);


    point4 direction;

private:

    static const int NumVerticesF = 100000;
    static const int NumCares = 300000;
};
#endif // CARROSSERIA_H
