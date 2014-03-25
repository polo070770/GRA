#include "objecte.h"
#include "readfile.h"

Objecte::Objecte(int npoints, QObject *parent) : numPoints(npoints) ,
    QObject(parent)
{
    std::cout<< "Estic en el constructor default\n";
    points = new point4[npoints];
    colors = new color4[npoints];
}

Objecte::Objecte(int npoints, QString n, GLdouble tamanio, GLdouble x0, GLdouble y0, GLdouble z0, double girx, double giry, double girz) : numPoints(npoints)
{
    points = new point4[npoints];
    colors = new color4[npoints];
    tam = tamanio;
    //std::cout<< "Estic en el constructor parametritzat de l'objecte";
    xorig = x0;
    yorig = y0;
    zorig = z0;

    xRot = girx;
    yRot = giry;
    zRot = girz;


    nom = n;
    Index = 0;

    readObj(n);

    make();

}


Objecte::~Objecte()
{
    delete points;
    delete colors;
}

/**
 *Funcio que transforma un objecte al tamany atomic i despres
 *l'escala pel factor de entrada
 * @brief Objecte::escalarFrom1
 * @param factor
 */
void Objecte:: escalarFrom1(float factor){
    cout << "escalo objecte a " << factor << endl;
    Capsa3D capsa = calculCapsa3D();

    float max = capsa.a;
    if (capsa.h > max){
        max = capsa.h;
    }else if(capsa.p > max){
        max = capsa.p;
    }

    max = factor * (1./max);

    mat4 transform = Scale(max,max,max);

    aplicaTGCentrat(transform);
    // calculem la nova capsa
    calculCapsa3D();

}


Capsa3D Objecte::calculCapsa3D()
{
    vec3 pmin, pmax;

    // Metode a implementar: calcula la capsa mínima contenidora d'un objecte
    pmin.x = points[0].x;
    pmin.y = points[0].y;
    pmin.z = points[0].z;

    pmax.x = points[0].x;
    pmax.y = points[0].y;
    pmax.z = points[0].z;

    for ( int i = 1; i < Index; ++i ){
        if(points[i].x < pmin.x) pmin.x = points[i].x;
        if(points[i].y < pmin.y) pmin.y = points[i].y;
        if(points[i].z < pmin.z) pmin.z = points[i].z;

        if(points[i].x > pmax.x) pmax.x = points[i].x;
        if(points[i].y > pmax.y) pmax.y = points[i].y;
        if(points[i].z > pmax.z) pmax.z = points[i].z;
    }

    capsa.pmin = pmin;
    capsa.a = pmax.x - pmin.x;
    capsa.h = pmax.y - pmin.y;
    capsa.p = pmax.z - pmin.z;

    return capsa;
}




void Objecte::aplicaTG(mat4 m)
{
    aplicaTGPoints(m);

    // Actualitzacio del vertex array per a preparar per pintar
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4) * Index,
                     &points[0] );

}


void Objecte::aplicaTGPoints(mat4 m)
{
    point4  *transformed_points = new point4[Index];

    for ( int i = 0; i < Index; ++i ) {
        transformed_points[i] = m * points[i];
    }

    transformed_points = &transformed_points[0];
    points = &points[0];

    for ( int i = 0; i < Index; ++i )
    {
        points[i] = transformed_points[i];
    }

    delete transformed_points;
}


point4 Objecte::calculCentre(){
    centre.x = capsa.pmin.x + (capsa.a / 2);
    centre.y = capsa.pmin.y + (capsa.h / 2);
    centre.z = capsa.pmin.z + (capsa.p / 2);
    return centre;
}

void Objecte::aplicaTGCentrat(mat4 m){
    // calculamos el centro
    calculCapsa3D();
    point4 centre = calculCentre();

    // montamos la matriz en orden inverso al que queremos aplicar las
    // transformaciones
    mat4 transform_centrada = ( Translate(centre) * m * Translate(-centre) );


    // aplicmos las transformaciones
    aplicaTG(transform_centrada);

}

void Objecte::toGPU(QGLShaderProgram *pr){

    program = pr;

    std::cout<<"Passo les dades de l'objecte a la GPU\n";

    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(point4) * Index + sizeof(color4) * Index,
                  NULL, GL_STATIC_DRAW );
    program->link();

    program->bind();
    glEnable( GL_DEPTH_TEST );
}

// Pintat en la GPU.
void Objecte::draw()
{

    // cal activar el buffer de l'objecte. Potser que ja n'hi hagi un altre actiu
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // per si han canviat les coordenades dels punts
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4) * Index, &points[0] );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4) * Index, sizeof(color4) * Index, &colors[0] );

    // Per a conservar el buffer
    int vertexLocation = program->attributeLocation("vPosition");
    int colorLocation = program->attributeLocation("vColor");

    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer("vPosition", GL_FLOAT, 0, 4);

    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer("vColor", GL_FLOAT, sizeof(point4) * Index, 4);


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
    glDrawArrays( GL_TRIANGLES, 0, Index );

    // Abans nomes es feia: glDrawArrays( GL_TRIANGLES, 0, NumVerticesP );
}

void Objecte::make(){

    static vec3  base_colors[] = {
        vec3( 1.0, 0.0, 0.0 ),
        vec3( 0.0, 1.0, 0.0 ),
        vec3( 0.0, 0.0, 1.0 ),
        vec3( 1.0, 1.0, 0.0 )
    };
    // Recorregut de totes les cares per a posar-les en les estructures de la GPU
    // Cal recorrer l'estructura de l'objecte per a pintar les seves cares

    float llargadaMax = 0;

    Index = 0;

    for(unsigned int i=0; i<cares.size(); i++)
    {
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++)
        {
            points[Index] = vertexs[cares[i].idxVertices[j]];
            colors[Index] = base_colors[i%4];
            Index++;
        }
    }

    // S'ha de dimensionar uniformement l'objecte a la capsa de l'escena i s'ha posicionar en el lloc corresponent
}

float Objecte::getYOrig() {
    return this->yorig;
}

void Objecte::setYorig(float orig){
    this->yorig = orig;
}

// Llegeix un fitxer .obj
//  Si el fitxer referencia fitxers de materials (.mtl), encara no es llegeixen
//  Tots els elements del fitxer es llegeixen com a un unic objecte.
//

// Llegeix un fitxer .obj
//  Si el fitxer referencia fitxers de materials (.mtl), tambe es llegeixen.
//  Tots els elements del fitxer es llegeixen com a un unic objecte.
//

void Objecte::readObj(QString filename)
{

    FILE *fp = fopen(filename.toLocal8Bit(),"rb");
    if (!fp)
    {
        cout << "No puc obrir el fitxer " << endl;
    }
    else {

        int vindexAct = 0;
        int vindexUlt = 0;

        while (true)
        {
            char *comment_ptr = ReadFile::fetch_line (fp);

            if (comment_ptr == (char *) -1)  /* end-of-file */
                break;

            /* did we get a comment? */
            if (comment_ptr) {
                //make_comment (comment_ptr);
                continue;
            }

            /* if we get here, the line was not a comment */
            int nwords = ReadFile::fetch_words();

            /* skip empty lines */
            if (nwords == 0)
                continue;

            char *first_word = ReadFile::words[0];

            if (!strcmp (first_word, "v"))
            {
                if (nwords < 4)
                {
                    fprintf (stderr, "Too few coordinates");//: '%s'", str_orig);
                    exit (-1);
                }
                QString sx(ReadFile::words[1]);
                QString sy(ReadFile::words[2]);




                QString sz(ReadFile::words[3]);
                double x = sx.toDouble();
                double y = sy.toDouble();
                double z = sz.toDouble();

                if (nwords == 5)
                {
                    QString sw(ReadFile::words[4]);
                    double w = sw.toDouble();
                    x/=w;
                    y/=w;
                    z/=w;
                }
                // S'afegeix el vertex a l'objecte
                vertexs.push_back(point4(x, y, z, 1));
                vindexAct++;

            }
            else if (!strcmp (first_word, "vn")) {
            }
            else if (!strcmp (first_word, "vt")) {
            }
            else if (!strcmp (first_word, "f")) {
                // S'afegeix la cara a l'objecte
                construeix_cara (&ReadFile::words[1], nwords-1, this, vindexUlt);
            }
            // added
            else if (!strcmp (first_word, "mtllib")) {
                //read_mtllib (&words[1], nwords-1, matlib, filename);
            }
            else if (!strcmp (first_word, "usemtl")) {
                //int size = strlen(words[1])-1;
                //while (size && (words[1][size]=='\n' || words[1][size]=='\r') ) words[1][size--]=0;
                //currentMaterial = matlib.index(words[1]);
            }
            /*else if (!strcmp (first_word, "o")) {
                //cada nou objecte s'actualitza aquest Ã­ndex
                vindexUlt = vindexAct;
            }*/
            // fadded
            else {
                //fprintf (stderr, "Do not recognize: '%s'\n", str_orig);
            }

            //free(words);
            }
        }
}


void Objecte::construeix_cara ( char **words, int nwords, Objecte*objActual, int vindexUlt)
{
    Cara face;
    for (int i = 0; i < nwords; i++)
    {
        int vindex;
        int nindex;
        int tindex;

        if ((words[i][0]>='0')&&(words[i][0]<='9'))
        {
            ReadFile::get_indices (words[i], &vindex, &tindex, &nindex);

#if 0
            printf ("vtn: %d %d %d\n", vindex, tindex, nindex);
#endif

            /* store the vertex index */

            if (vindex > 0)       /* indices are from one, not zero */
                face.idxVertices.push_back(vindex - 1 - vindexUlt);
            else if (vindex < 0)  /* negative indices mean count backwards */
                face.idxVertices.push_back(objActual->vertexs.size() + vindex - vindexUlt);
            else
            {
                fprintf (stderr, "Zero indices not allowed");//: '%s'\n", str_orig);
                exit (-1);
            }
        }
    }
    face.color = vec4(1.0, 0.0, 0.0, 1.0);
    objActual->cares.push_back(face);
}





