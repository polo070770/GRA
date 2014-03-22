#ifndef TERRA_H
#define TERRA_H

#include <QGLShaderProgram>
#include <Common.h>
#include <objecte.h>

class Terra : public Objecte
{
public:
    Terra(float amplaria, float profunditat, float y);

    point4 direction;

    void make();


private:
    int a; // amplada
    int y; // y
    int p; // profunditat

    static const int NumVerticesF = 12; // (2 faces)(2triangles/face)(3vertices/triangle)

    point4 vertices[4];
    color4 vertex_colors[4];

    void quad( int a, int b, int c, int d );



};

#endif // TERRA_H
