#ifndef _CARA_H_
#define _CARA_H_

#include <vector>
#include <Common.h>

using namespace std;

typedef vec4 Vertices;
// Face - representa una cara d'un objecte 3D
class Cara
{
public:
    Cara();

    // constructor a partir de 3 o 4 indexs a vertex
    Cara(int i1, int i2, int i3, int i4=-1);

    // // vector amb els indexs dels vertexs de la cara
    vector<int> idxVertices;

    // normal de la cara
    vec3 normal;

    // funcio que calcula la normal de la cara i l'assigna
    void calculaNormal(vector<Vertices> &);
};



#endif
