#include "material.h"

Material::Material(QString nom)
{
    this->nom = nom;
}
void Material::toGPU(QGLShaderProgram *program){

    struct{
        GLuint ambient;
        GLuint difusa;
        GLuint especular;
        GLuint shinines;
    }gl_ld_material;


    gl_ld_material.ambient = program->uniformLocation("material.Ambient");
    gl_ld_material.difusa = program->uniformLocation("material.Difusse");
    gl_ld_material.especular = program->uniformLocation("material.Specular");
    gl_ld_material.shinines = program->uniformLocation("material.Shinines");


    glUniform4fv(gl_ld_material.ambient, 1, this->intensitat.ambient);
    glUniform4fv(gl_ld_material.difusa, 1, this->intensitat.difusa);
    glUniform4fv(gl_ld_material.especular, 1, this->intensitat.especular);
    glUniform1f(gl_ld_material.shinines, this->coefEspecular);
}
