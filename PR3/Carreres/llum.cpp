#include "llum.h"

Llum::Llum(){
}

/**
 * Inicia una llum direccional
 * @brief Llum::ini
 * @param direccio
 */
void Llum::ini(vec3 direccio){
    cout << "LLUM DIRECCIONAL" << endl;
    this->tipus = DIRECCIONAL;
    this->direccio = direccio;
}

/**
 * Inicia una llum puntual
 * @brief Llum::ini
 * @param posicio
 */
void Llum::ini(vec4 posicio){
    cout << "LLUM PUNTUAL" << endl;
    this->tipus = PUNTUAL;
    this->posicio = posicio;
}

/**
 * Inicia una llum focal(spotlight)
 * @brief Llum::ini
 * @param direccio
 */
void Llum::ini(vec4 posicio, vec3 direccio, float obertura){
    this->tipus = SPOT;
    this->posicio = posicio;
    this->direccio = direccio;
    this->obertura = obertura;
}

void Llum::toGPU(QGLShaderProgram *program){

    struct{
        GLuint tipus;
        GLuint posicio;
        GLuint direccio;
        GLuint obertura;
        GLuint ambient;
        GLuint difusa;
        GLuint especular;
        GLuint constant;
        GLuint lineal;
        GLuint cuadratica;

    }gl_ld_Llum;

    gl_ld_Llum.tipus = program->uniformLocation("light.Tipus");
    gl_ld_Llum.posicio = program->uniformLocation("light.Position");
    gl_ld_Llum.direccio = program->uniformLocation("light.Direction");
    gl_ld_Llum.obertura = program->uniformLocation("light.Alpha");
    gl_ld_Llum.ambient = program->uniformLocation("light.Ambient");
    gl_ld_Llum.difusa = program->uniformLocation("light.Difusse");
    gl_ld_Llum.especular = program->uniformLocation("light.Specular");
    gl_ld_Llum.constant = program->uniformLocation("light.Constant");
    gl_ld_Llum.lineal = program->uniformLocation("light.Lineal");
    gl_ld_Llum.cuadratica = program->uniformLocation("light.Cuadratica");

    glUniform1i(gl_ld_Llum.tipus,  this->tipus);
    glUniform4fv(gl_ld_Llum.posicio, 1, this->posicio);
    glUniform3fv(gl_ld_Llum.direccio, 1, this->direccio);
    glUniform1f(gl_ld_Llum.obertura,this->obertura);
    glUniform4fv(gl_ld_Llum.ambient, 1, this->intensitat.ambient);
    glUniform4fv(gl_ld_Llum.difusa, 1, this->intensitat.difusa);
    glUniform4fv(gl_ld_Llum.especular, 1, this->intensitat.especular);
    glUniform1f(gl_ld_Llum.constant,  this->atenuacio.constant);
    glUniform1f(gl_ld_Llum.lineal,  this->atenuacio.lineal);
    glUniform1f(gl_ld_Llum.cuadratica, this->atenuacio.cuadratica);
}
