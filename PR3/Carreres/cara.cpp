#include "cara.h"
#include <cmath>

Cara::Cara() 
{
    normal.x=0.0;
    normal.y=0.0;
    normal.z=0.0;
}

Cara::Cara(int i1, int i2, int i3, int i4)
{
    idxVertices.push_back(i1);
    idxVertices.push_back(i2);
    idxVertices.push_back(i3);
    if (i4!=-1) idxVertices.push_back(i4);
    normal.x=0.0;
    normal.y=0.0;
    normal.z=0.0;
}


void Cara::calculaNormal(vector<Vertices> &v)
{
    //int j;
    //int n = idxVertices.size();

//    normal.x=0.0;
//    normal.y=0.0;
//    normal.z=0.0;

    vec3 u = vec3(v[idxVertices[1]].x - v[idxVertices[0]].x,
            v[idxVertices[1]].y - v[idxVertices[0]].y,
            v[idxVertices[1]].z - v[idxVertices[0]].z);

    vec3 t = vec3(v[idxVertices[2]].x - v[idxVertices[0]].x,
            v[idxVertices[2]].y - v[idxVertices[0]].y,
            v[idxVertices[2]].z - v[idxVertices[0]].z);

//    for (int i=0; i<n; i++)
//    {

//        j = (i+1)%n;

//        normal.x += ((v[idxVertices[i]].z+v[idxVertices[j]].z)*
//                (v[idxVertices[i]].y-v[idxVertices[j]].y));

//        normal.y += ((v[idxVertices[i]].x+v[idxVertices[j]].x)*
//                (v[idxVertices[i]].z-v[idxVertices[j]].z));

//        normal.z += ((v[idxVertices[i]].y+v[idxVertices[j]].y)*
//                (v[idxVertices[i]].x-v[idxVertices[j]].x));
//    }

    normal.x = (u.y * t.z) - (u.z * t.y);
    normal.y = (u.z * t.x) - (u.x * t.z);
    normal.z = (u.x * t.y) - (u.y * t.x);

//    normal.x *= 0.5;
//    normal.y *= 0.5;
//    normal.z *= 0.5;
//    normal.normalize();
}

void Cara::calculaNormal(vec4 v1, vec4 v2, vec4 v3){

    normal.x=0.0;
    normal.y=0.0;
    normal.z=0.0;

    vec3 u = vec3(v2.x - v1.x,
            v2.y - v1.y,
            v2.z - v1.z);

    vec3 t = vec3(v3.x - v1.x,
            v3.y - v1.y,
            v3.z - v1.z);

    normal.x = (u.y * t.z) - (u.z * t.y);
    normal.y = (u.z * t.x) - (u.x * t.z);
    normal.z = (u.x * t.y) - (u.y * t.x);

}

