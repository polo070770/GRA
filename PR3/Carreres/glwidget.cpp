#include <QtGui>
#include <QtOpenGL>
#include <QSet>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include "glwidget.h"
//#include <QGlobal.h>
#include <QTime>

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    setFocusPolicy( Qt::StrongFocus );
    esc = new escena();

    xRot = 0;
    yRot = 0;
    zRot = 0;

    a = 50.0;
    h = 50.0;
    p = 50.0;

    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

    program = 0;

    // timer para controlar los frames
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(accions_timer()));
    timer->start(20);

    // variables para controlar el movimiento del coche
    acceleracio_lliberada_cotxe_1 = false;
    gir_lliberat_cotxe_1 = false;
    acceleracio_lliberada_cotxe_2 = false;
    gir_lliberat_cotxe_2 = false;

    // cambiamos los valores del tamaño en la escena
    int w = this->size().width();
    int h = this->size().height();
    esc->setWidthGLWidget(w);
    esc->setHeightGLWidget(h);
}

GLWidget::~GLWidget()
{
    makeCurrent();
}

//  Metode per a carregar de fitxers el vertex i el fragment shader
void GLWidget::InitShader(const char* vShaderFile, const char* fShaderFile)
{

    struct Shader {
        const char*  filename;
        GLenum       type;
        GLchar*      source;
    }  shaders[2] = {
    { vShaderFile, GL_VERTEX_SHADER, NULL },
    { fShaderFile, GL_FRAGMENT_SHADER, NULL }
};

    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);

    // Es llegeixen els dos shaders: el vertex i el fragment shader
    for ( int i = 0; i < 2; ++i ) {
        Shader& s = shaders[i];
        s.source = Common::readShaderSource( s.filename );
        if ( shaders[i].source == NULL ) {
            std::cerr << "Failed to read " << s.filename << std::endl;
            exit( EXIT_FAILURE );
        }
    }

    // Es compilen els programes en temps d'execucio de l'aplicacio
    vshader->compileSourceCode(shaders[0].source);
    fshader->compileSourceCode(shaders[1].source);

    // S'afegeixen unes variables de classe
    program = new QGLShaderProgram(this);
    program->addShader(vshader);
    program->addShader(fshader);

    program->bindAttributeLocation("vPosition", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("vColor", PROGRAM_COLOR_ATTRIBUTE);

    // Es munta el programa
    program->link();

    // Es vincula el programa al context de GL per a ser executat amb les comandes GL
    program->bind();

}

// Metode per inicialitzar els shaders de l'aplicacio
void GLWidget::initShadersGPU()
{
    // Carrega dels shaders i posa a punt per utilitzar els programes carregats a la GPU
    InitShader( "../Carreres/vshader11.glsl", "../Carreres/fshader11.glsl" );

}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

// Metodes per a poder rotar l'escena

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::adaptaObjecteTamanyWidget(Objecte *obj) {

    // Metode a implementar

    float factorAdapta = 2. / 50; // longitud real de la escena / longitud logica de la escena

    point4 centre = obj->calculCentre();

    mat4 traslada_centre = Translate(-centre);

    mat4 escala = Scale(factorAdapta, factorAdapta, factorAdapta);

    // trasladamos el centro relativamente respecto a
    // la longitud de adaptacion del widget
    mat4 traslada_relatiu = Translate(centre.x * factorAdapta,
                                      centre.y * factorAdapta,
                                      centre.z * factorAdapta);

    mat4 transformAdapta = traslada_relatiu * escala * traslada_centre;

    // Atencion aqui llega un Objecte, que puede ser obstacle, cotxe, terra
    // depende cual, llamara a su propio aplicaTG o al de Objecte
    obj->aplicaTG(transformAdapta);

}

void GLWidget::newObjecte(Objecte * obj)
{
    //adaptaObjecteTamanyWidget(obj); // se supone que ya no es necesario
    obj->toGPU(program);
    esc->addObjecte(obj);
    updateGL(); // actualiza display
}

void GLWidget::newObstacle(QString fichero, int nombre)
{
    // Metode que serveix per a donar d'alta un obstacle amb el punt original a xorig, yorig,zorig
    // d'una certa mida
    // ha d'estar a les ys del pla de la terra
    GLfloat yorig = esc->getYOrig();
    // Metode a implementar
    Obstacle *obj;
    GLfloat xorig, zorig;
    float  mida;
    xorig = 0;
    zorig = 0;
    mida = 2;
    for(int i = 0; i < nombre; i++ ){
        xorig = (rand() % 40) - 20;
        zorig = (rand() % 40) - 20;
        obj = new Obstacle(fichero, mida, xorig, yorig, zorig, 0., 0., 0.);
        newObjecte(obj);
    }


}

void GLWidget::newTerra(float amplaria, float profunditat, float y)
{
    // Metode que crea un objecte terra poligon amb el punt original a xorig, yorig, zorig
    // (quadrat d'una certa mida amb origen a xorig, yorig, zorig

    // Metode a implementar

    Terra *obj;
    obj = new Terra(amplaria, profunditat, y);
    newObjecte(obj);

}

void GLWidget::newCotxe(QString fichero, float xorig, float zorig, float mida, float xdirec, float ydirec, float zdirec)
{
    Cotxe *obj;
    // parametres que posen l'objecte cotxe al punt original xorig, yorig, zorig i d'una certa mida
    // Cal modificar-lo per a que es posicioni a la Y correcte
    float yorig = esc->getYOrig();

    obj = new Cotxe(fichero, mida, xorig, yorig, zorig, 0., 0., 0.,xdirec, ydirec, zdirec);
    newObjecte(obj);
}

void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    std::cout<<"Estic inicialitzant el shaders"<<std::ends;
    initShadersGPU();

    // A canviar per posar una imatge de fons: Estrelles...
    qglClearColor(qtPurple.dark());
}

void GLWidget::resetView()
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

    // Metode a modificar per a adaptar tots els objectes de l'escena.

    vector <Cotxe *> listado_cotxes = esc->getCotxes();

    for(int i = 0; i < listado_cotxes.size(); i++){
        if (listado_cotxes.at(i) != NULL)
            adaptaObjecteTamanyWidget(listado_cotxes.at(i));
    }

    vector <Obstacle *> listado_obs = esc->getObstacles();
    for(int i = 0; i < listado_obs.size(); i++){
        if (listado_obs.at(i) != NULL)
            adaptaObjecteTamanyWidget(listado_obs.at(i));
    }

    if (esc->terra != NULL)
        adaptaObjecteTamanyWidget(esc->terra);

    esc->reset();
    esc->camera_toGPU(program);
    esc->llum_toGPU(program);
    updateGL();
}

void GLWidget::paintGL()
{

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    qNormalizeAngle(xRot);
    qNormalizeAngle(yRot);
    qNormalizeAngle(zRot);

    //    mat4 transform = ( RotateX( xRot / 16.0 ) *
    //                       RotateY( yRot / 16.0 ) *
    //                       RotateZ( zRot / 16.0 ) );

    //    esc->aplicaTGCentrat(transform);

    esc->camera_toGPU(program);
    esc->llum_toGPU(program); //las luces se crean al principio
    esc->draw();
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);

    esc->setWidgetSize(this->size().width(), this->size().height());

    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-150, +150, -150, +150, 0.0, 150.0);
#else
    glOrtho(-150, +150, -150, +150, 0.0, 150.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    esc->mou_EixXCamera(angle);
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    esc->mou_EixYCamera(angle);
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
    }
}

void GLWidget::zoom(double in, int dy){
    //cout << "in : " << in << " dy : " << dy <<endl;
    esc->zoom_camera(in * abs(dy));
}

void GLWidget::pan(int dx, int dy){

    if (dx > 0){
        // RIGHT PANNING
        esc->panning_dx(0.25);
    }else if(dx < 0){
        // LEFT PANNING
        esc->panning_dx(-0.25);
    }

    if (dy > 0){
        // UP PANNING
        esc->panning_dy(0.25);
    }else if(dy < 0){
        // DOWN PANNING
        esc->panning_dy(-0.25);
    }

}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        // Es canvien els angles de visio de la camera segons el desplacament
        // Si hi ha un desplacament en X del viewport, es canviara l angle Y
        // Si hi ha un desplacament en Y del viewport, es canviara l angle X
        setYRotation(xRot + 8 * dx);
        setXRotation(yRot + 8 * dy);

    } else if (event->buttons() & Qt::RightButton) {

        // panning
        pan(dx, dy);

    } else if (event->buttons() & Qt::MidButton) {

        // zoom
        if (lastPos.y() > event->y())
            zoom(-0.05, dy);
        else
            zoom(0.05, dy);
    }

    lastPos = event->pos();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    // Metode a implementar
    switch ( event->key() )
    {
    case Qt::Key_Up:
        pulsaciones.insert((Qt::Key_Up));
        break;
    case Qt::Key_Down:
        pulsaciones.insert((Qt::Key_Down));
        break;
    case Qt::Key_Left:
        pulsaciones.insert((Qt::Key_Left));
        break;
    case Qt::Key_Right:
        pulsaciones.insert((Qt::Key_Right));
        break;
    case Qt::Key_W:
        pulsaciones.insert((Qt::Key_W));
        break;
    case Qt::Key_S:
        pulsaciones.insert((Qt::Key_S));
        break;
    case Qt::Key_A:
        pulsaciones.insert((Qt::Key_A));
        break;
    case Qt::Key_D:
        pulsaciones.insert((Qt::Key_D));
        break;
    case Qt::Key_Escape:
        pulsaciones.insert((Qt::Key_Escape));
        break;
    case Qt::Key_1:
        pulsaciones.insert((Qt::Key_1));
        break;
    }

}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    //cout << "release" << endl;
    //AQUEST METODE TE UN FUNCIONAMENT EXTRANY

    // Metode a implementar
    switch ( event->key() )
    {
    case Qt::Key_Up:
        pulsaciones.remove((Qt::Key_Up));
        break;
    case Qt::Key_Down:
        pulsaciones.remove((Qt::Key_Down));
        break;
    case Qt::Key_Left:
        pulsaciones.remove((Qt::Key_Left));
        break;
    case Qt::Key_Right:
        pulsaciones.remove((Qt::Key_Right));
        break;
    case Qt::Key_W:
        pulsaciones.remove((Qt::Key_W));
        break;
    case Qt::Key_S:
        pulsaciones.remove((Qt::Key_S));
        break;
    case Qt::Key_A:
        pulsaciones.remove((Qt::Key_A));
        break;
    case Qt::Key_D:
        pulsaciones.remove((Qt::Key_D));
        break;
    }

}

void GLWidget::accions_timer(){
    int cotxe = 0;

    if (pulsaciones.contains(Qt::Key_W)){
        esc->accelera_cotxe(cotxe);
        acceleracio_lliberada_cotxe_1 = false;
    }else if (pulsaciones.contains(Qt::Key_S)){
        esc->desaccelera_cotxe(cotxe);
        acceleracio_lliberada_cotxe_1 = false;
    }else if(!acceleracio_lliberada_cotxe_1){
        acceleracio_lliberada_cotxe_1 = true;
        esc->llibera_acceleracio_cotxe(cotxe);
    }

    if (pulsaciones.contains(Qt::Key_A)){
        esc->gira_esquerra_cotxe(cotxe);
        gir_lliberat_cotxe_1 = false;
    }else if(pulsaciones.contains(Qt::Key_D)){
        esc->gira_dreta_cotxe(cotxe);
        gir_lliberat_cotxe_1 = false;
    }else if(!gir_lliberat_cotxe_1){
        gir_lliberat_cotxe_1 = true;
        esc->llibera_gir_cotxe(cotxe);
    }


    cotxe = 1;

    if (pulsaciones.contains(Qt::Key_Up)){
        esc->accelera_cotxe(cotxe);
        acceleracio_lliberada_cotxe_2 = false;
    }else if (pulsaciones.contains(Qt::Key_Down)){
        esc->desaccelera_cotxe(cotxe);
        acceleracio_lliberada_cotxe_2 = false;
    }else if(!acceleracio_lliberada_cotxe_2){
        acceleracio_lliberada_cotxe_2 = true;
        esc->llibera_acceleracio_cotxe(cotxe);
    }

    if (pulsaciones.contains(Qt::Key_Left)){
        esc->gira_esquerra_cotxe(cotxe);
        gir_lliberat_cotxe_2 = false;
    }else if(pulsaciones.contains(Qt::Key_Right)){
        esc->gira_dreta_cotxe(cotxe);
        gir_lliberat_cotxe_2 = false;
    }else if(!gir_lliberat_cotxe_2){
        gir_lliberat_cotxe_2 = true;
        esc->llibera_gir_cotxe(cotxe);
    }

    //activem la vista en tercera

    if(pulsaciones.contains(Qt::Key_Escape)){
        esc->initLookAtCotxe();
        pulsaciones.remove(Qt::Key_Escape);
    }
    if(pulsaciones.contains(Qt::Key_1)){
        esc->initLookAtCockpit();
        pulsaciones.remove(Qt::Key_1);
    }
    esc->temps();
    updateGL();
}
