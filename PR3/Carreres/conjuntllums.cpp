#include "conjuntllums.h"

using namespace std;
ConjuntLlums::ConjuntLlums(){}

/**
 * @brief ConjuntLlums::add
 * @param llum
 */
void ConjuntLlums::add(Llum *llum){
    this->listado.push_back((Llum*)llum);
}
/**
 * @brief setAmbientToGPU
 * @param program
 */
void ConjuntLlums::setAmbientToGPU(QGLShaderProgram *program){
    GLuint GL_ambientGlobal = program->uniformLocation("ambientGlobal");
    glUniform1f(GL_ambientGlobal,  this->ambientGlobal);
}
void ConjuntLlums::toGPU(QGLShaderProgram *program){
    for (iterador = this->listado.begin(); iterador < this->listado.end(); ++iterador) {
        if(*iterador!=NULL)(*iterador)->toGPU(program);
    }
}
