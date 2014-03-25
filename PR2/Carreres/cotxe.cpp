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
    std::cout<< "Estic en el constructor parametritzat del cotxe\n" << endl;

    nom = n;
    Index = 0;
    tam = mida;

    xorig = x0;
    yorig = y0;
    zorig = z0;

    xRot = girx;
    yRot = giry;
    zRot = girz;

    this->direction[0] = xdir;
    this->direction[1] = ydir;
    this->direction[2] = zdir;
    this->direction[3] = 0;

    velocitat = 0.0;
    angle_gir = 0.0;
    accelerant = 0;
    girant = 0;
    reset_rodes = 0;

    carroseria = new Carrosseria(mida, x0, y0, z0,girx, giry, girz, xdir, ydir, zdir);
    roda_dreta_davantera = new Roda(mida, x0, y0, z0,girx, giry, girz, xdir, ydir, zdir);
    roda_dreta_posterior = new Roda(mida, x0, y0, z0,girx, giry, girz, xdir, ydir, zdir);
    roda_esquerra_davantera = new Roda(mida, x0, y0, z0,girx, giry, girz, xdir, ydir, zdir);
    roda_esquerra_posterior = new Roda(mida, x0, y0, z0,girx, giry, girz, xdir, ydir, zdir);

    this->vector_fills.push_back(roda_esquerra_posterior);
    this->vector_fills.push_back(roda_dreta_posterior);
    this->vector_fills.push_back(roda_esquerra_davantera);
    this->vector_fills.push_back(carroseria);
    this->vector_fills.push_back(roda_dreta_davantera);

    readObj(n);

    this->make();

}


Capsa3D Cotxe::calculCapsa3D()
{

    vec3 pmin, pmax;

    vector_fills[0]->calculCapsa3D();
    Capsa3D capsa_init = vector_fills[0]->capsa;

    pmin.x = capsa_init.pmin.x;
    pmin.y = capsa_init.pmin.y;
    pmin.z = capsa_init.pmin.z;

    pmax.x = capsa_init.pmin.x + capsa_init.a;
    pmax.y = capsa_init.pmin.y + capsa_init.h;
    pmax.z = capsa_init.pmin.z + capsa_init.p;

    for ( int i = 1; i < vector_fills.size(); i++ ){
        vector_fills[i]->calculCapsa3D();
        Capsa3D capsa = vector_fills[i]->capsa;
        if(capsa.pmin.x < pmin.x) pmin.x = capsa.pmin.x;
        if(capsa.pmin.y < pmin.y) pmin.y = capsa.pmin.y;
        if(capsa.pmin.z < pmin.z) pmin.z = capsa.pmin.z;

        if(capsa.pmin.x + capsa.a > pmax.x) pmax.x = capsa.pmin.x + capsa.a;
        if(capsa.pmin.y + capsa.h > pmax.y) pmax.y = capsa.pmin.y + capsa.h;
        if(capsa.pmin.z + capsa.p > pmax.z) pmax.z = capsa.pmin.z + capsa.p;
    }


    this->capsa.pmin = pmin;
    this->capsa.a = pmax.x - pmin.x;
    this->capsa.h = pmax.y - pmin.y;
    this->capsa.p = pmax.z - pmin.z;

    return this->capsa;
}

/**
 *Funcio que transforma un objecte al tamany atomic i despres
 *l'escala pel factor de entrada
 * @brief Objecte::escalarFrom1
 * @param factor
 */
void Cotxe:: escalarFrom1(float factor){

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

}

/*
 *Hace un make a la carroceria y a las ruedas;
 */
void Cotxe::make(){

    velocitat = 0.0;
    angle_gir = 0.0;
    accelerant = 0;
    girant = 0;
    reset_rodes = 0;

    //std::cout<< "make del cotxe"<< endl;
    for (fill_iter = this->vector_fills.begin(); fill_iter < this->vector_fills.end(); ++fill_iter) {
        if(*fill_iter!=NULL)(*fill_iter)->make();
    }

    escalarFrom1(this->tam);

    // calculem la nova capsa
    calculCapsa3D();

    //centre del cotxe
    point4 centre = calculCentre();

    // el movem al centre i despres al desti
    mat4 transform = Translate(-centre);
    // apliquem la transformacio, no cal que sigui centrada
    this->aplicaTG(transform);
    // calculem la nova capsa
    calculCapsa3D();

    //movem l'objecte al desti
    //invertimos la direccion
    // tambe serviria l'altura
    float y_desti = yorig + (-capsa.pmin.y);
    point4 desti = point4(xorig * 1, y_desti,zorig * 1 ,0); // vector destino
    this->aplicaTG(Translate(desti));
}

/*
 *Hace un aplicaTG a la carroceria y las ruedas;
 */
void Cotxe::aplicaTG(mat4 trans){
    //std::cout<<"aplicaTG del cotxe"<<endl;
    for (fill_iter = this->vector_fills.begin(); fill_iter < this->vector_fills.end(); ++fill_iter) {
        if(*fill_iter!=NULL)(*fill_iter)->aplicaTG(trans);
    }
}

void Cotxe::toGPU(QGLShaderProgram *program){
    //std::cout<<"toGPU del cotxe"<<endl;
    for (fill_iter = this->vector_fills.begin(); fill_iter < this->vector_fills.end(); ++fill_iter) {
        if(*fill_iter!=NULL)(*fill_iter)->toGPU(program);
    }
}

void Cotxe::draw(){
    //std::cout<<"draw del cotxe"<<endl;
    for (fill_iter = this->vector_fills.begin(); fill_iter < this->vector_fills.end(); ++fill_iter) {
        if(*fill_iter!=NULL)(*fill_iter)->draw();
    }
}

void Cotxe::aplicaTGPoints(mat4 trans){
    for (fill_iter = this->vector_fills.begin(); fill_iter < this->vector_fills.end(); ++fill_iter) {
        if(*fill_iter!=NULL)(*fill_iter)->aplicaTGPoints(trans);
    }
}

void Cotxe::aplicaTGCentrat(mat4 trans){
    // calculamos el centro del coche
    point4 centre = calculCentre();

    // montamos la matriz en orden inverso al que queremos aplicar las

    // transformaciones
    mat4 transform_centrada = ( Translate(centre) * trans * Translate(-centre) );

    this->aplicaTG(transform_centrada);

}

void Cotxe::moviment(){

    point4 desti = point4(
                this->direction[0] * velocitat * FACTOR_VELOCITAT,
                this->direction[1] * velocitat * FACTOR_VELOCITAT,
                this->direction[2] * velocitat * FACTOR_VELOCITAT,
                this->direction[3] * velocitat * FACTOR_VELOCITAT
                );

    mat4 moviment = (Translate(desti));
    this->aplicaTG(moviment);
    //apliquem moviment a les rodes
    this->avansar_rodes();

}
void Cotxe::avansar_rodes(){
    mat4 moviment_roda = RotateZ(velocitat);
    this->roda_dreta_davantera->aplicaTGCentrat(moviment_roda);
    this->roda_esquerra_davantera->aplicaTGCentrat(moviment_roda);
    this->roda_dreta_posterior->aplicaTGCentrat(moviment_roda);
    this->roda_esquerra_posterior->aplicaTGCentrat(moviment_roda);
}

void Cotxe::girar_rodes_davanteres(){
    this->roda_dreta_davantera->fer_gir(angle_gir);
    this->roda_esquerra_davantera->fer_gir(angle_gir);


}

void Cotxe::forward(){
    accelerant = 1;

    if(velocitat < MAX_VELOCITAT){
        //anem cap endarrere i estem accelerant , el cotxe frena accelerant
        if(velocitat <= 0)velocitat += 2 * FACTOR_ROSAMENT;
        //estem accelerant cap endevant
        else if(velocitat >= 0) velocitat  += 1;
    }
}

void Cotxe::backward(){
    accelerant = 1;
    if(velocitat > MIN_VELOCITAT){
        //estem accelerant cap endarrere
        if(velocitat <= 0)velocitat  -= 1;
        //anem cap endevant y estem frenant
        else if(velocitat >= 0) velocitat -= 2 * FACTOR_ROSAMENT;
    }
}

void Cotxe::turnleft(){
    if(girant == 0){
        angle_gir = 1 * MIN_ANGLE;
        this->girar_rodes_davanteres();
        girant = 1;
    }
}

void Cotxe::turnright(){
    if(girant == 0){
        angle_gir = 1 * MAX_ANGLE;
        this->girar_rodes_davanteres();
        girant = 1;
    }
}


void Cotxe::temps(){


    // si ja no estem girant fem un reset dels angles
    if(reset_rodes == 1){
        this->roda_dreta_davantera->reset_angle();
        this->roda_esquerra_davantera->reset_angle();
        reset_rodes = 0;
    }

    //apliquem el rossament
    if(accelerant == 0){
        if(velocitat > 0){
            velocitat -= FACTOR_ROSAMENT;
        }else if(velocitat < 0 ){
            velocitat += FACTOR_ROSAMENT;
        }

        // donem un marge
        float marge = 2 * FACTOR_ROSAMENT;

        if(velocitat >  -marge && velocitat <  marge ){
            //parem el cotxe
            velocitat = 0;
        }
    }

    moviment();
}

void Cotxe::llibera_acceleracio(){
    accelerant = 0;
}

void Cotxe::llibera_gir(){
    /*
     *para liberar el giro hemos de girar las ruedas en el sentido contrario al que
     *
     **/
    if(girant == 1){
        // aixo ho fem per tornar les rodes a la seva posicio natural
        angle_gir = -angle_gir;
        this->girar_rodes_davanteres();
        girant = 0;
        reset_rodes = 1;
    }
}

void Cotxe::readObj(QString filename)
{   Objecte *current;
    //std::cout<< "Estic en el readobjdel cotxe del cotxe\n" << endl;
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
