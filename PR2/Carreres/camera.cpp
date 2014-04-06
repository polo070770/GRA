#include "camera.h"

Camera::Camera()
{
    // view system
    vs.vrp = vec4(0.0, 0.0, 0.0, 1.0); // view reference point
    vs.obs = vec4(0.0, 0.0, 200.0, 1.0); // posicio de l'obs

    // angles de gir del sistema de coordenades del obs
    vs.angx = 0;
    vs.angy = 0;
    vs.angz = 0;

    //capsa 2d del viewport
    vp.a = 600;
    vp.h = 600;
    vp.pmin[0] = 0;
    vp.pmin[1] = 0;

    piram.proj = PARALLELA;
    piram.d = 100;
}

void Camera::ini(int a, int h, Capsa3D capsaMinima)
{
    // Calcul del vrp com el centre de la capsa minima contenedora 3D
    // CAL IMPLEMENTAR
    // CODI A MODIFICAR

    // view system, view reference point
    // lo que quiero mirar, mirare en el centro
    // de la escena
    vec3 centre = calculCentreCapsa(capsaMinima);
    vs.vrp[0] = centre[0];
    vs.vrp[1] = centre[1];
    vs.vrp[2] = centre[2];

    //capsa 2d del viewport
    //el view port sera el tamaño del glwidget, la ventana
    vp.a = a;
    vp.h = h;
    vp.pmin[0] = 0;
    vp.pmin[1] = 0;

}



void Camera::toGPU(QGLShaderProgram *program)
{
 // CAL IMPLEMENTAR

    model_view = program->uniformLocation("model_view");
    glUniformMatrix4fv(model_view, 1, GL_TRUE, modView);

    projection = program->uniformLocation("projection");
    glUniformMatrix4fv(projection, 1, GL_TRUE, proj);

}




// Suposa que les dades d'obs, vrp i vup son correctes en la camera

void Camera::CalculaMatriuModelView()
{
    // CAL IMPLEMENTAR
    // modView = identity();

    // vec4 ang = vec4(vs.angx, vs.angy, vs.angz, 0.0);

    vec4 upVector = vec4(0,1,0,1); // vista TOP
    modView = LookAt(vs.obs, vs.vrp, upVector);
}

void Camera::CalculaMatriuProjection()
{
    // CAL IMPLEMENTAR
    // proj = identity();

    // rango de mostreo, entre 0.1 y 100.0
    piram.dant = 0.1;
    piram.dpost = 100.0;
    piram.alfav = 45.0; // obertura en vertical de 45º
    piram.alfah = 45.0; // obertura en horizontal de 45º

    // Ortho (left, right, bottom, top, near, far)
    // left = 0, anchura empieza en x = 0
    // right = 50, anchura acaba en x = 50
    // bottom = 0, altura empieza en y = 0
    // top = 0, altura termina en y = 50
    // de profundidad: near y far
    // se definen con dant y dpost, atributos de piram

    proj = Ortho(0.0, 50.0, 0.0, 50.0, piram.dant, piram.dpost);

}

/*
void Camera::CalculWindow( Capsa3D c)
{
    // CAL IMPLEMENTAR

    wd.pmin.x = -1;
    wd.pmin.y = -1;

    wd.a = 2;
    wd.h = 2;


}
*/

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

    AmpliaWindow(0.2);      /* marges del 20%  */
    AjustaAspectRatioWd();

}



// Donat un window i un viewport, amplia el window per tal que el seu
// aspect ratio sigui igual al del viewport

void    Camera::AjustaAspectRatioWd()
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


vec3 Camera::CalculVup(double angx, double angy, double angz)
{
  vec3 v;
  int   x, y;

  x = 1.0;
  y = 1.0;

  if (cos(PI*angx/180.)<0.0) y = -1.0;

  if (cos(PI*angy/180.)<0.0) x = -1.0;


  v[0] = x*sin (-PI*angz/180.);
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
    vec3 v;

    v[0] = capsa.pmin.x + (capsa.a / 2);
    v[1] = capsa.pmin.y + (capsa.h / 2);
    v[2] = capsa.pmin.z + (capsa.p / 2);
    return v;

}
