#include "terra.h"

Terra::Terra(float amplaria, float profunditat, float y):Objecte(NumVerticesF)
{

    a = amplaria;
    p = profunditat;
    y = y;

    xorig = 0;
    yorig = 0;
    zorig = 0;

    xRot = 0;
    yRot = 0;
    zRot = 0;





    vertices[0] = point4( -0.5, 0.0, 0.5, 1.0 );
    vertices[1] = point4(  0.5, 0.0, 0.5, 1.0 );

    vertices[2] = point4(  0.5, 0.0, -0.5, 1.0 );
    vertices[3] = point4( -0.5, 0.0, -0.5, 1.0 );

    // RGBA colors
    vertex_colors[0] =    color4( 0.0, 0.0, 0.0, 1.0 );  // black
    vertex_colors[1] =    color4( 1.0, 0.0, 0.0, 1.0 );  // red
    vertex_colors[2] =    color4( 1.0, 1.0, 1.0, 1.0 );  // white
    vertex_colors[3] =    color4( 0.0, 1.0, 1.0, 1.0 );  // cyan

    make();

}


void Terra::quad( int a, int b, int c, int d )
{

    colors[Index] = vertex_colors[a];
    points[Index] = vertices[a];
    Index++;

    colors[Index] = vertex_colors[b];
    points[Index] = vertices[b];
    Index++;

    colors[Index] = vertex_colors[c];
    points[Index] = vertices[c];
    Index++;

    colors[Index] = vertex_colors[a];
    points[Index] = vertices[a];
    Index++;

    colors[Index] = vertex_colors[c];
    points[Index] = vertices[c];
    Index++;

    colors[Index] = vertex_colors[d];
    points[Index] = vertices[d];
    Index++;

}


// Realitzacio de la geometria del cub en una genList o en el vertex array, segons el que visualitzem

void Terra::make()
{
    std::cout<<"Estic en el make del terra\n";
    // generacio de la geometria dels triangles per a visualitzar-lo
    Index = 0;
    quad( 2, 3, 0, 1 ); // tapa arriba
    //quad( 1, 0, 3, 2 ); // tapa abajo

}
