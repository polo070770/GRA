#include "terra.h"

Terra::Terra(float amplaria, float profunditat, float y):Objecte(NumVerticesF)
{

    a = amplaria;
    p = profunditat;

    xorig = 0;
    yorig = y;
    zorig = 0;

    xRot = 0;
    yRot = 0;
    zRot = 0;

    vertices[0] = point4( 1., yorig, 1., 1.0 );
    vertices[1] = point4( 1., yorig, -1., 1.0 );

    vertices[2] = point4( -1., yorig, -1., 1.0 );
    vertices[3] = point4( -1., yorig, 1., 1.0 );

    // afegim els vertexs creat al vector vertexs
    vertexs.push_back(vertices[0]);
    vertexs.push_back(vertices[1]);
    vertexs.push_back(vertices[2]);
    vertexs.push_back(vertices[3]);

    Index = 0;

    // fem les dues cares
    Cara cara1;
    cara1.idxVertices.push_back(0);Index++;
    cara1.idxVertices.push_back(1);Index++;
    cara1.idxVertices.push_back(2);Index++;

    Cara cara2;
    cara2.idxVertices.push_back(0);Index++;
    cara2.idxVertices.push_back(2);Index++;
    cara2.idxVertices.push_back(3);Index++;

    // afegim les cares al vector cares
    cares.push_back(cara1);
    cares.push_back(cara2);

    // fem les transformacions
    init();

    this->material = materials.get(TERRA);
}

// Transformacions del terra segons lo demanat
void Terra::init()
{
    Objecte::make();

    calculCapsa3D();

    float ancho = capsa.a * a;
    float profunditat = capsa.p * p;

    escalarFrom1(1); // escalem el terra a 1

    // apliquem transformacio amb les dades rebudes per l'usuari

    mat4 transform = Scale(ancho,1,profunditat);

    // apliquem la transformacio, no cal que sigui centrada
    this->aplicaTGCentrat(transform);

}

void Terra::make(){

    // Recorregut de totes les cares per a posar-les en les estructures de la GPU
    // Cal recorrer l'estructura de l'objecte per a pintar les seves cares

    Index = 0;

    for(unsigned int i=0; i<cares.size(); i++)
    {
        // calculamos las normal de las caras
        cares[i].calculaNormal(vertexs);
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++)
        {
            //cada vertice tiene la misma normal que su cara
            points[Index] = vertexs[cares[i].idxVertices[j]];
            normals[Index] = vec4(cares[i].normal);
            Index++;
        }
    }

}
