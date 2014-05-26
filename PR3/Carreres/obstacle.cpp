#include "obstacle.h"

Obstacle::Obstacle(QString n, GLfloat mida, GLfloat x0, GLfloat y0, GLfloat z0,
                   double girx, double giry, double girz):
    Objecte(NumVerticesF){

    nom = n;
    Index = 0;
    tam = mida;

    xorig = x0;
    yorig = y0;
    zorig = z0;

    xRot = girx;
    yRot = giry;
    zRot = girz;

    readObj(n);

    // transformacions necesaries a l'obstacle
    init();

    this->material = this->materials.get(OBSTACLE);

}

// Realitzacions de les transformacions necesaries demanades
void Obstacle::init(){

    //cridem al make
    make();

    escalarFrom1(this->tam); // escalem l'obstacle a mida

    //centre del cotxe
    point4 centre = calculCentre();

    // apliquem la transformacio al centre, no cal que sigui centrada
    this->aplicaTG(Translate(-centre));

    //movem l'objecte al desti
    this->calculCapsa3D();
    point4 desti = point4(xorig, yorig + (-capsa.pmin.y), zorig, 0.0); // vector destino
    this->aplicaTG(Translate(desti));

}

void Obstacle::make(){

    // GOURAUD

    Index=0;

    vector <int> points_idxVec;
    vector <vec3 * > vec_normals (vertexs.size());

    for(unsigned int i=0; i<cares.size(); i++)
    {
        cares[i].calculaNormal(vertexs);
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++)
        {
            points[Index] = vertexs[cares[i].idxVertices[j]];

            points_idxVec.push_back(cares[i].idxVertices[j]);
            Index++;

            if (!vec_normals[cares[i].idxVertices[j]]){
                vec_normals[cares[i].idxVertices[j]] = &cares[i].normal;
            }else{
                vec_normals[cares[i].idxVertices[j]]->operator += (cares[i].normal);
            }

        }
    }

    for (unsigned int i=0; i<Index; ++i)
    {
        normals[i] = *vec_normals[points_idxVec[i]] / length((*vec_normals[points_idxVec[i]]));
    }

}
