#include "llum.h"

Llum::Llum()
{
    // valors experimentals
    intensitat.ambient = vec4(0.2, 0.2, 0.2, 1.0);
    intensitat.difusa = vec4(1.0, 0.8, 0.0, 1.0);
    intensitat.especular = vec4(1.0, 1.0, 1.0, 1.0);
    atenuacio.constant = 0.5;
    atenuacio.lineal = 0.5;
    atenuacio.cuadratica = 0.5;
}
/**
 * Inicia una llum direccional
 * @brief Llum::ini
 * @param direccio
 */
void Llum::ini(vec3 direccio){
    this->tipus = DIRECCIONAL;
    this->direccio = direccio;
}
/**
 * Inicia una llum puntual
 * @brief Llum::ini
 * @param posicio
 */
void Llum::ini(vec4 posicio){
    this->tipus = PUNTUAL;
    this->posicio = posicio;
}
/**
 * Inicia una llum focal(spotlight)
 * @brief Llum::ini
 * @param direccio
 */
void Llum::ini(vec3 direccio, float obertura){
    this->tipus = SPOT;
    this->direccio = direccio;
    this->obertura = obertura;
}


void Llum::toGPU(QGLShaderProgram *program){


    struct{
        GLuint posicio;
        GLuint direccio;
        GLuint obertura;
        GLuint ambient;
        GLuint difusa;
        GLuint especular;
    }gl_ld_Llum;

    gl_ld_Llum.posicio = program->uniformLocation("light.Position");
    gl_ld_Llum.direccio = program->uniformLocation("light.Direction");
    gl_ld_Llum.obertura = program->uniformLocation("light.Alpha");
    gl_ld_Llum.ambient = program->uniformLocation("light.Ambient");
    gl_ld_Llum.difusa = program->uniformLocation("light.Difusse");
    gl_ld_Llum.especular = program->uniformLocation("light.Specular");

    glUniform4fv(gl_ld_Llum.posicio, 1, this->posicio);
    glUniform3fv(gl_ld_Llum.direccio, 1, this->direccio);
    glUniform1f(gl_ld_Llum.obertura,this->obertura);
    glUniform4fv(gl_ld_Llum.ambient, 1, this->intensitat.ambient);
    glUniform4fv(gl_ld_Llum.difusa, 1, this->intensitat.difusa);
    glUniform4fv(gl_ld_Llum.especular, 1, this->intensitat.especular);

}
