#include "cotxe.h"
#include "readfile.h"

Cotxe::Cotxe(QString n) : Objecte(NumVerticesF)
{
    nom = n;
    Index = 0;
    tam = 1;

    xorig = 0;
    yorig = 0;
    zorig = 0;

    xRot = 0;
    yRot = 0;
    zRot = 0;

    this->direction[0] = -1;
    this->direction[1] = 0;
    this->direction[2] = 0;
    this->direction[3] = 0;
    readObj(n);

    make();
}

Cotxe::Cotxe(QString n, GLfloat mida, GLfloat x0, GLfloat y0, GLfloat z0,
             double girx, double giry, double girz,
             float xdir, float ydir, float zdir):Objecte(NumVerticesF){
    // El seguent codi escala el cotxe entre 0 i 1 i el situa el seu centre  0,0,0. aixo fa que es vegi en la primera visualització
    //
    // Cal modificar el codi seguent




    tam = mida;
    std::cout<< "Estic en el constructor parametritzat del cotxe\n" << endl;
    xorig = x0;
    yorig = y0;
    zorig = z0;

    xRot = xdir;
    yRot = ydir;
    zRot = zdir;


    nom = n;
    Index = 0;

    //roda_esquerra_davantera = new Roda(mida, x0, y0, z0,girx, giry, girz, xdir, ydir, zdir);

    carroseria = new Carrosseria(mida, x0, y0, z0,girx, giry, girz, xdir, ydir, zdir);
    roda_dreta_davantera = new Roda(mida, x0, y0, z0,girx, giry, girz, xdir, ydir, zdir);
    roda_dreta_posterior = new Roda(mida, x0, y0, z0,girx, giry, girz, xdir, ydir, zdir);;
    roda_esquerra_davantera = new Roda(mida, x0, y0, z0,girx, giry, girz, xdir, ydir, zdir);;
    roda_esquerra_posterior = new Roda(mida, x0, y0, z0,girx, giry, girz, xdir, ydir, zdir);;

    this->vector_fills.push_back(roda_esquerra_posterior);
    this->vector_fills.push_back(roda_dreta_posterior);
    this->vector_fills.push_back(roda_esquerra_davantera);
    this->vector_fills.push_back(carroseria);
    this->vector_fills.push_back(roda_dreta_davantera);

    readObj(n);

    this->make();

    double escalaX = 1.0 / 4.6;
    mat4 trans = Translate(-1.93*escalaX, (+0.26)*escalaX, -2.16*escalaX)*Scale(escalaX, escalaX, escalaX)*Translate(+1.93, -0.26, 2.16);


    this->aplicaTG(trans);


}



/*
 *Hace un make a la carroceria y a las ruedas;
 */
void Cotxe::make(){

    for (fill_iter = this->vector_fills.begin(); fill_iter < this->vector_fills.end(); ++fill_iter) {
        (*fill_iter)->make();
    }
}
/*
 *Hace un aplicaTG a la carroceria y las ruedas;
 */

void Cotxe::aplicaTG(mat4 trans){

    for (fill_iter = this->vector_fills.begin(); fill_iter < this->vector_fills.end(); ++fill_iter) {
        (*fill_iter)->aplicaTG(trans);
    }
}

void Cotxe::toGPU(QGLShaderProgram *program){
    for (fill_iter = this->vector_fills.begin(); fill_iter < this->vector_fills.end(); ++fill_iter) {
        (*fill_iter)->toGPU(program);
    }
}
void Cotxe::draw(){
    for (fill_iter = this->vector_fills.begin(); fill_iter < this->vector_fills.end(); ++fill_iter) {
        (*fill_iter)->draw();
    }
}

void Cotxe::aplicaTGCentrat(mat4 trans){
    for (fill_iter = this->vector_fills.begin(); fill_iter < this->vector_fills.end(); ++fill_iter) {
        (*fill_iter)->aplicaTGCentrat(trans);
    }
}

void Cotxe::forward(){
    // Metode a implementar per fer el moviment del cotxe
}

void Cotxe::backward(){
    // Metode a implementar per fer el moviment del cotxe

}

void Cotxe::turnleft(){
    // Metode a implementar per fer el moviment del cotxe

}

void Cotxe::turnright(){
    // Metode a implementar per fer el moviment del cotxe

}
void Cotxe::readObj(QString filename)
{   Objecte *current;
    std::cout<< "Estic en el readobjdel cotxe del cotxe\n" << endl;
    FILE *fp = fopen(filename.toLocal8Bit(),"rb");
    if (!fp)
    {
        cout << "No puc obrir el fitxer " << endl;
    }
    else {

        int vindexAct = 0;
        int vindexUlt = 0;
        int currentObj = -1;

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
                                current = vector_fills[currentObj];
                                current->vertexs.push_back(point4(x, y, z, 1));
                                vindexAct++;


                            }
                            else if (!strcmp (first_word, "vn")) {
                            }
                            else if (!strcmp (first_word, "vt")) {
                            }
                            else if (!strcmp (first_word, "f")) {
                                current = vector_fills[currentObj];
                                // S'afegeix la cara a l'objecte
                                construeix_cara (&ReadFile::words[1], nwords-1, current, vindexUlt);
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
                            else if (!strcmp (first_word, "o")) {
                                //cada nou objecte s'actualitza aquest i­ndex
                                currentObj++;
                                vindexUlt = vindexAct;
                            }
                            // fadded
                            else {
                                //fprintf (stderr, "Do not recognize: '%s'\n", str_orig);
                            }

                            //free(words);
                        }
                    }
}
