#include "camera.h"

Camera::Camera()
{

    // view system
    vs.vrp = vec4(0.0, 0.0, 0.0, 1.0); // view reference point
    vs.obs = vec4(0.0, 0.0, 0.0, 1.0); // punt posicio de l'obs

    // angles de gir del sistema de coordenades del obs
    vs.angx = 0;
    vs.angy = 0;
    vs.angz = 0;

    //capsa 2d del viewport
    vp.a = 600;
    vp.h = 600;
    vp.pmin.x = 0;
    vp.pmin.y = 0;

    piram.proj = PERSPECTIVA;
    piram.d = 100;

    CalculaMatriuModelView();
    CalculaMatriuProjection();
}

void Camera::ini(int a, int h, Capsa3D capsaMinima, bool person)
{
    this->person = person;
    // CAL IMPLEMENTAR
    // CODI A MODIFICAR

    // VIEW SYSTEM
    vec3 centre = calculCentreCapsa(capsaMinima);

    // view reference point
    // miramos al centro de la caja
    vs.vrp.x = centre.x;
    vs.vrp.y = centre.y;
    vs.vrp.z = centre.z;

    if(!person){
        piram.proj = PARALLELA;
    }else{
        piram.proj = PERSPECTIVA;
    }




    /*

            (piram.dant) -----        -----
    P(x,y,z) ----------> |   |        |   |
    (cotxe)              -----        |   |
    piram.d      (piram.dpost)        |   |
             ------------------------>|   |
                                      -----
    */





    // VIEWPORT
    // A viewport defines in normalized coordinates a rectangular area
    // on the display device where the image of the data appears.
    // We can have our stuff take up the entire display device or
    // show it in only a portion, say the upper-right part.
    // el view port sera el tamaño del glwidget, la ventana por defecto inicial es
    // a -> 640p de GLWdiget
    // h -> 480p de GLWdiget
    setViewport(0, 0, a, h);

    // WINDOW
    // A window defines a rectangular area in world coordinates.
    // The window can be defined to be larger than, the same size as
    // or smaller than the actual range of data values, depending on
    // whether we want to show all of the data or only part of the data
    CalculWindow(capsaMinima);
    AjustaAspectRatioWd();
    //wd.a = capsaMinima.a;
    //wd.h = capsaMinima.h;
    //wd.pmin.x = capsaMinima.pmin.x;
    //wd.pmin.y = capsaMinima.pmin.y;

    // A window and a viewport are related by the linear transformation
    // that maps the window onto the viewport. A line segment in the
    // the window is mapped to a line segment in the viewport such the relative
    // positions are preserved

    CalculaMatriuModelView();
    CalculaMatriuProjection();
}

/**
 *funcio que posa la camara a mode top view
 */
void Camera::resetTopView(){

    // definicio top view
    vs.angx = -90;
    vs.angy = 0;
    vs.angz = 0;

    piram.d = 100;  //distancia observador a pla proj
    // rango de muestreo, entre 0.1 y 100.0
    piram.dant = 1;
    piram.dpost = 200;

    piram.alfav = 45;
    piram.alfah = 45;



    CalculaMatriuModelView();
    CalculaMatriuProjection();
}

/**
  funcio que configura la camara pera a veure en tercera persona
 * @brief Camera::resetLookCotxe
 * @param capsaCotxe
 */
void Camera::resetLookCotxe(Capsa3D capsaCotxe){

    piram.d = 2 ; //distancia observador a pla proj
    // rango de muestreo, entre 0.1 y 100.0
    piram.dant = 3;
    piram.dpost = 500;

    piram.alfav = 45;
    piram.alfah = 45;



    CalculWindow(capsaCotxe);
    CalculaMatriuProjection();
}

void Camera::resetLookCockpit(Capsa3D capsaCotxe){
    double cockpit_camera_offset = 1.5;
    double cockpit_viewer_offset = 0.4;
    vec3 centre = calculCentreCapsa(capsaCotxe);

    piram.d = 0 ; //distancia observador a pla proj
    // rango de muestreo, entre 3 y 500
    piram.dant = cockpit_camera_offset; // situamos el plano anterior justo donde esta el piloto
    piram.dpost = 500;

    piram.alfav = 120;
    piram.alfah = 120;

/*
    // colocamos al observador como piloto, retrasando la x tanto como el offset de la camara
    // i avanznadolo el offset del viewer ya que el centro del coche no es exactamente el hueco del piloto
    vs.obs.x = centre.x + cockpit_camera_offset - (cockpit_viewer_offset);
    vs.obs.z = centre.z ;
    vs.obs.y = capsaCotxe.pmin.y + (3.5 * (capsaCotxe.h / 5));

    // miramos al infinito centrado a nivel de suelo
    vs.vrp.x = capsaCotxe.pmin.x - 20;
    vs.vrp.y = capsaCotxe.pmin.y;
    vs.vrp.z = centre.z;
*/
    //camara tv
    vs.obs.x = centre.x;
    vs.obs.z = 10 ;
    vs.obs.y = 2;

    // miramos al centro del coche
    vs.vrp.x = centre.x;
    vs.vrp.y = centre.y;
    vs.vrp.z = centre.z;

    CalculWindow(capsaCotxe);
    CalculaMatriuProjection();

}

/**
 *funcio que actualitza les dades de la camara en tercera persona
 * @brief Camera::actualitzaCameraThirdPerson
 * @param capsaCotxe
 */
void Camera::actualitzaCameraThirdPerson(Capsa3D capsaCotxe){

    vec3 centre = calculCentreCapsa(capsaCotxe);

    // colocamos al observador un poco mas atras del coche, ligeramente por encima y centrado en z
    vs.obs.x = centre.x + (capsaCotxe.a * 2);
    vs.obs.z = centre.z ;
    vs.obs.y = centre.y + (capsaCotxe.h * 2.5);

    // miramos a la parte delantera inferior centrada en z
    vs.vrp.x = capsaCotxe.pmin.x;
    vs.vrp.y = capsaCotxe.pmin.y;
    vs.vrp.z = centre.z;

    CalculaMatriuModelView();

}

void Camera::actualitzaCameraCockpit(Capsa3D capsaCotxe, vec4 direction){


    double cockpit_camera_offset = 1.5;
    double cockpit_viewer_offset = 0.4;

    vec3 centre = calculCentreCapsa(capsaCotxe);

    // colocamos al observador como piloto, retrasando la x tanto como el offset de la camara
    // i avanznadolo el offset del viewer ya que el centro del coche no es exactamente el hueco del piloto

    vs.obs.x = centre.x + cockpit_camera_offset - (cockpit_viewer_offset);
    vs.obs.z = centre.z ;
    vs.obs.y = capsaCotxe.pmin.y + (3.5 * (capsaCotxe.h / 5));
/*
    // miramos al infinito centrado a nivel de suelo
    vs.vrp.x = capsaCotxe.pmin.x - 20;
    vs.vrp.y = capsaCotxe.pmin.y;
    vs.vrp.z = centre.z;
*/
    // miramos al centro del coche
    vs.vrp.x = centre.x * direction.x;
    vs.vrp.y = centre.y;
    vs.vrp.z = centre.z * direction.z;


    CalculaMatriuModelView();

}
void Camera::toGPU(QGLShaderProgram *program)
{
    // CAL IMPLEMENTAR
    this->setModelView(program, modView);
    this->setProjection(program, proj);

}

// Suposa que les dades d'obs, vrp i vup son correctes en la camera

void Camera::CalculaMatriuModelView()
{
    // CAL IMPLEMENTAR

    // cameraPosition = vs.obs, the position of your camera, in world space
    // cameraTarget = vs.vrp, where you want to look at, in world space

    // posicio de l'observador
    if(!person)
        vs.obs = CalculObs(vs.vrp, piram.d, vs.angx, vs.angy);

    // verticalitat de la camera
    vec3 vup = CalculVup(0.0, 0.0, 0.0);

    modView = LookAt(vs.obs, vs.vrp, vup);
    //printm(modView);fflush(stdout);

}

void Camera::CalculaMatriuProjection()
{
    // CAL IMPLEMENTAR

    //CalculAngleOberturaVertical(); // obertura en vertical
    //CalculAngleOberturaHoritzontal(); // obertura en horizontal

    // Ortho (left, right, bottom, top, near, far)

    // left = 0, anchura empieza en x = 0
    // right = 50, anchura acaba en x = 50
    // bottom = 0, altura empieza en y = 0
    // top = 0, altura termina en y = 50
    // de profundidad: near y far
    // se definen con dant y dpost, atributos de piram

    GLfloat left, right, bottom, top;
    left = wd.pmin.x;
    right = wd.pmin.x + wd.a;
    bottom = wd.pmin.y;
    top = wd.pmin.y + wd.h;
    if(!person){
        proj = Ortho(left, right, bottom, top, piram.dant, piram.dpost);
    }else{
        proj = Frustum(left, right, bottom, top, piram.dant, piram.dpost);
    }


    //printm(proj);fflush(stdout);

}

void Camera::setAngX_Vup(double angle){

    if (angle != vs.angx) {
        vs.angx += angle;
        CalculaMatriuModelView();
        CalculaMatriuProjection();
    }
}

void Camera::setAngY_Vup(double angle){

    if (angle != vs.angy) {
        vs.angy += angle;
        CalculaMatriuModelView();
        CalculaMatriuProjection();
    }

}

void Camera::setAngZ_Vup(double delta){
    vs.angz = delta;
    CalculaMatriuModelView();
    CalculaMatriuProjection();
}

void Camera::panning_2D_X(double delta){

    wd.pmin.x += delta;
    CalculaMatriuModelView();
    CalculaMatriuProjection();

}

void Camera::panning_2D_Y(double delta){

    wd.pmin.y += delta;
    CalculaMatriuModelView();
    CalculaMatriuProjection();

}

void Camera::zoom(double dy){
    //cout << " dy : " << dy << endl;
    AmpliaWindow(dy);
    CalculaMatriuProjection();
}

void Camera::setViewport(int x, int y, int a, int h)
{
    vp.pmin[0] = x;
    vp.pmin[1] = y;
    vp.a = a;
    vp.h = h;
}

void Camera::setModelView(QGLShaderProgram *program, mat4 m)
{

    // CAL IMPLEMENTAR
    modView = m;
    model_view = program->uniformLocation("model_view");
    glUniformMatrix4fv(model_view, 1, GL_TRUE, modView);

}

void Camera::setProjection(QGLShaderProgram *program, mat4 p)
{

    // CAL IMPLEMENTAR

    proj = p;
    projection = program->uniformLocation("projection");
    glUniformMatrix4fv(projection, 1, GL_TRUE, proj);

}

void  Camera::AmpliaWindow(double r)
{
    // Pre r = 1.5 => amplia a 150%
    double na, da;

    na  = wd.a * (1.0 + r);
    da = na - wd.a;
    wd.pmin[0] = wd.pmin[0] - 0.5*da;
    wd.a  = na;
    na  = wd.h * (1.0 + r);
    da = na - wd.h;
    wd.pmin[1] = wd.pmin[1] - 0.5*da;
    wd.h  = na;

}

// procediment que calcula el semi angle d'obertura vertical
// a partir de l'alcada total del window (h) i la distancia
// a l'observador
void Camera::CalculAngleOberturaVertical()
{
    piram.alfav =  180.0 * atan2(wd.h/2.0, piram.d)/PI;

}

// procediment que calcula el semi angle d'obertura horitzontal
// a partir de l'amplada total del window (a) i la distancia
// a l'observador
void Camera::CalculAngleOberturaHoritzontal()
{

    piram.alfah =  180.0 * atan2(wd.a/2.0, piram.d)/PI;

}

void  Camera::CalculWindowAmbRetallat()
{

    Capsa2D c;

    if (piram.proj == PARALLELA) {
        /* Projeccio paral.lela:
         el window ve donat: amplada o alcada o tots dos. */

        if( fabs(wd.h) <EPS ) {
            c.a = wd.a;
            c.h = ((float)(vp.h)/ (float)(vp.a) ) * wd.a;
        }
        else {
            c.h = wd.h;
            c.a = ((float)(vp.a)/ (float)(vp.h) ) * wd.h;
        }
    }
    else {

        /* Projeccio perspectiva:
         el window ve donat pels angles d'obertura de la camera: el
         vertical, l'horitzontal o tots dos.  */

        if( fabs(piram.alfav) <EPS ) {
            c.a = 2.0  * piram.d * tan( PI*piram.alfah/180.);
            c.h = ((float)(vp.h)/ (float)(vp.a) ) * c.a;
        }
        else {
            if (fabs(piram.alfah) <EPS ) {
                c.h = 2.0  * piram.d * tan( PI*piram.alfav/180.);
                c.a = ((float)(vp.a)/ (float)(vp.h) ) * c.h;
            }
            else {
                c.a = 2.0  * piram.d * tan( PI*piram.alfah/180.);
                c.h = 2.0  * piram.d * tan( PI*piram.alfav/180.);
            }
        }
    }
    c.pmin[0] = -0.5 * c.a;
    c.pmin[1] = -0.5 * c.h;

    wd.pmin[0] = c.pmin[0];
    wd.pmin[1] = c.pmin[1];
    wd.a = c.a;
    wd.h = c.h;
}


void Camera::CalculWindow( Capsa3D c)
{
    vec4  vaux[8], vaux2[8];
    vec4 vup = vec4(0.0, 1.0, 0.0, 0.0);
    mat4  MDP;
    int i;

    modView = LookAt(vs.obs, vs.vrp, vup);

    if (piram.proj==PERSPECTIVA) {
        CreaMatDp(MDP);
        modView = MDP*modView;
    }

    /* Passo els 8 vertexs de la capsa per MVIS */
    VertexCapsa3D(c, vaux);

    for(i=0; i<8; i++) {
        vaux2[i]= modView*vaux[i];
    }
    wd = CapsaMinCont2DXYVert(vaux2, 8);

    //AmpliaWindow(0.2);      /* marges del 20%  */
    AjustaAspectRatioWd();

}



// Donat un window i un viewport, amplia el window per tal que el seu
// aspect ratio sigui igual al del viewport

void Camera::AjustaAspectRatioWd()
{

    double arvp, arwd;

    arvp = ((double) vp.h)/((double)(vp.a));
    arwd = wd.h/wd.a;
    if(arwd > arvp) {
        wd.a = wd.h/arvp;
    }
    else if (arwd <arvp) {
        wd.h = wd.a *arvp;

    }
    wd.pmin[0] = -0.5*wd.a;
    wd.pmin[1] = -0.5*wd.h;
}



// Accio que crea la matriu de visualitzacio 3D

void Camera::CreaMatVis(mat4 &MVIS)
{
    MVIS = RotateZ(-vs.angz)*RotateX(-vs.angx)*RotateY(-vs.angy)*Translate(-vs.vrp);

}


// Accio que crea la matriu del proces invers de  visualitzacio 3D

void Camera::CreaMatSiv(mat4 &MSIV)
{
    MSIV = Translate(vs.vrp);*RotateY(vs.angy)*RotateX(vs.angx)*RotateZ(vs.angz);
}


// Accio que crea la matriu de deformacio perspectiva

void Camera::CreaMatDp(mat4 &MDP)
{
    MDP = identity();
    MDP[3][2] = -1/piram.d;
}



Capsa2D  Camera::CapsaMinCont2DXYVert( vec4 *v, int nv)
{
    Capsa2D c;
    vec2    pmin, pmax;
    int     i;

    pmin[0] = v[0][0];       pmin[1] = v[0][1];
    pmax[0] = v[0][0];       pmax[1] = v[0][1];
    for(i=1; i<nv; i++) {
        if(v[i][0] <pmin[0])
            pmin[0] = v[i][0];
        if(v[i][1] <pmin[1])
            pmin[1] = v[i][1];
        if(v[i][0] >pmax[0])
            pmax[0] = v[i][0];
        if(v[i][1] >pmax[1])
            pmax[1] = v[i][1];
    }

    c.a = pmax[0]-pmin[0]+1;
    c.h = pmax[1]-pmin[1]+1;
    c.pmin[0] = -c.a/2.0;
    c.pmin[1] = -c.h/2.0;
    return c;
}



//   Calcul del observador:
//   obs es el vrp translladat en la direccio del vector de visio  d'una
//   distancia d = distancia (obs, vrp) si la projeccio es perspectiva
//   i d'una distancia prou gran si la projeccio es paral.lela

vec4 Camera::CalculObs(vec4 vrp, double d, double angx, double angy)
{
    vec4 obs2;
    vec3 v;
    double norma;

    /* Calcul del vector de visio a partir dels angles */

    v[0] = sin (PI*angy/180.) * cos (PI*angx/180.);
    v[2] = cos (PI*angy/180.) * cos (PI*angx/180.);
    v[1]= - sin (PI*angx/180.);

    norma = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);

    v[0] = v[0]/norma;
    v[1] = v[1]/norma;
    v[2] = v[2]/norma;


    obs2[0] = vrp[0] + v[0] *d;
    obs2[1] = vrp[1] + v[1] *d;
    obs2[2] = vrp[2] + v[2] *d;
    obs2[3] = 1.0;

    return(obs2);

}

vec4 Camera::CalculObs2(vec4 obs, double d, double angx, double angy)
{
    vec4 obs2;
    vec3 v;
    double norma;

    /* Calcul del vector de visio a partir dels angles */

    v[0] = sin (PI*angy/180.) * cos (PI*angx/180.);
    v[2] = cos (PI*angy/180.) * cos (PI*angx/180.);
    v[1]= - sin (PI*angx/180.);

    norma = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);

    v[0] = v[0]/norma;
    v[1] = v[1]/norma;
    v[2] = v[2]/norma;


    obs2[0] = obs[0] + v[0] *d;
    obs2[1] = obs[1] + v[1] *d;
    obs2[2] = obs[2] + v[2] *d;
    obs2[3] = 1.0;

    return(obs2);

}

vec3 Camera::CalculVup(double angx, double angy, double angz)
{
    vec3 v;
    int   x, y;

    x = 1.0;
    y = 1.0;

    if (cos(PI*angx/180.)<0.0) y = -1.0;

    if (cos(PI*angy/180.)<0.0) x = -1.0;


    v[0] = x*sin( -PI*angz/180.);
    v[1] = y*cos( -PI*angz/180.);
    v[2] = 0.0;

    return(v);

}

void Camera::VertexCapsa3D(Capsa3D capsaMinima, vec4 vaux[8])
{
    vec3 ptfi;

    ptfi[0] = capsaMinima.pmin[0]+capsaMinima.a;
    ptfi[1] = capsaMinima.pmin[1]+capsaMinima.h;
    ptfi[2] = capsaMinima.pmin[2]+capsaMinima.p;

    vaux[0] = vec4(capsaMinima.pmin[0], capsaMinima.pmin[1], capsaMinima.pmin[2], 1.0);
    vaux[1] = vec4(capsaMinima.pmin[0], capsaMinima.pmin[1], ptfi[2], 1.0);
    vaux[2] = vec4(capsaMinima.pmin[0],  ptfi[1], capsaMinima.pmin[2],1.0);
    vaux[3] = vec4(capsaMinima.pmin[0], ptfi[1], ptfi[2], 1.0);
    vaux[4] = vec4(ptfi[0],capsaMinima.pmin[1], capsaMinima.pmin[2],1.0);
    vaux[5] = vec4(ptfi[0], capsaMinima.pmin[1], ptfi[2],1.0);
    vaux[6] = vec4(ptfi[0], ptfi[1], capsaMinima.pmin[2], 1.0);
    vaux[7] = vec4(ptfi[0], ptfi[1], ptfi[2], 1.0);
}

vec3 Camera::calculCentreCapsa(Capsa3D capsa){

    return vec3(capsa.pmin.x + (capsa.a / 2),
                capsa.pmin.y + (capsa.h / 2),
                capsa.pmin.z + (capsa.p / 2));

}
