#include <QtGui>
#include <QtOpenGL>

#include <math.h>

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
    vshader->compileSourceCode(shaders[0].source);
    fshader->compileSourceCode(shaders[1].source);
    program = new QGLShaderProgram(this);
    program->addShader(vshader);
    program->addShader(fshader);

    program->bindAttributeLocation("vPosition", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("vColor", PROGRAM_COLOR_ATTRIBUTE);
    program->link();

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
}

void GLWidget::newObjecte(Objecte * obj)
{
    adaptaObjecteTamanyWidget(obj);
    obj->toGPU(program);
    esc->addObjecte(obj);

    updateGL();
}

void GLWidget::newObstacle(int nombre)
{
    // Metode que serveix per a donar d'alta un obstacle amb el punt original a xorig, yorig,zorig
    // d'una certa mida
    // ha d'estar a les ys del pla de la terra

    // Metode a implementar

}
void GLWidget::newTerra(float amplaria, float profunditat, float y)
{
    // Metode que crea un objecte terra poligon amb el punt original a xorig, yorig, zorig
    // (quadrat d'una certa mida amb origen a xorig, yorig, zorig

    // Metode a implementar

 }

void GLWidget::newCotxe(QString fichero, float xorig, float zorig, float mida, float xdirec, float ydirec, float zdirec)
{
    Cotxe *obj;
    // parametres que posen l'objecte cotxe al punt original xorig, yorig, zorig i d'una certa mida
    // Cal modificar-lo per a que es posicioni a la Y correcte
    float yorig = 0;

    obj = new Cotxe(fichero, mida, xorig, yorig, zorig, 0., 0., 0.,xdirec, ydirec, zdirec);
    newObjecte(obj);
}

void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

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


    esc->reset();

    // Metode a modificar per a adaptar tots els objectes de l'escena.

    updateGL();
}

void GLWidget::paintGL()
{

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    qNormalizeAngle(xRot);
    qNormalizeAngle(yRot);
    qNormalizeAngle(zRot);

    mat4 transform = ( RotateX( xRot / 16.0 ) *
                        RotateY( yRot / 16.0 ) *
                        RotateZ( zRot / 16.0 ) );


    if (esc->cotxe!=NULL) {
        esc->cotxe->aplicaTGCentrat(transform);
        esc->draw();
    }
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
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
    if (angle != xRot) {
        xRot = angle;
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        updateGL();
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
        setXRotation(xRot + 8 * dy);
        //setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setYRotation(xRot + 8 * dx);
        setZRotation(zRot + 8 * dy);
    }
    lastPos = event->pos();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    // Metode a implementar
    switch ( event->key() )
    {
    case Qt::Key_Up:

        break;
    case Qt::Key_Down:

        break;
    case Qt::Key_Left:

        break;
    case Qt::Key_Right:

        break;
    }

}
void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    // Metode a implementar en el cas que es doni velocitat al cotxe

}
