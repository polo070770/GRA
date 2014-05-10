#ifndef CONJUNTLLUMS_H
#define CONJUNTLLUMS_H

#include <stdio.h>


#include <Common.h>



#include <llum.h>
class ConjuntLlums
{
public:
    ConjuntLlums();
    void add(Llum *llum);
    void toGPU(QGLShaderProgram *program);
    void setAmbientToGPU(QGLShaderProgram *program);
    float ambientGlobal;
    vector<Llum * > getLlums();
private:
    vector<Llum * > listado; // lo llamamos listado y no vector para evitar problemas de nombres
    vector<Llum * >::iterator iterador;
};

#endif // CONJUNTLLUMS_H
