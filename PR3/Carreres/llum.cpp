#include "llum.h"

Llum::Llum(){
}

/**
 * Inicia una llum direccional
 * @brief Llum::ini
 * @param direccio
 */
void Llum::ini(vec3 direccio, char * light){
    this->tipus = DIRECCIONAL;
    this->direccio = direccio;
    this->light = light;

    this->intensitat.difusa = vec4(0.5, 0.5, 0.5, 1.0); // intensidad RGBA que una fuente de luz añade a la escena
    this->intensitat.especular = vec4(0.0, 0.0, 0.0, 1.0); // provoca el brillo puntual del objeto
    this->intensitat.ambient = vec4(0.0, 0.0, 0.0, 1.0);

}

/**
 * Inicia una llum puntual
 * @brief Llum::ini
 * @param posicio
 */
void Llum::ini(vec4 posicio, char * light){
    this->tipus = PUNTUAL;
    this->posicio = posicio;
    this->light = light;

    this->intensitat.difusa = vec4(1.0, 1.0, 1.0, 1.0); // intensidad RGBA que una fuente de luz añade a la escena
    this->intensitat.especular = vec4(1.0, 1.0, 1.0, 1.0); // provoca el brillo puntual del objeto
    this->intensitat.ambient = vec4(0.0, 0.0, 0.0, 1.0);

    this->atenuacio.constant = 1.0;
    this->atenuacio.lineal = 0.09;
    this->atenuacio.cuadratica = 0.032;
}

/**
 * Inicia una llum focal(spotlight)
 * @brief Llum::ini
 * @param direccio
 */
void Llum::ini(vec4 posicio, vec3 direccio, float obertura, char * light){
    this->tipus = SPOT;
    this->posicio = posicio;
    this->direccio = direccio;
    this->obertura = obertura;
    this->light = light;

    this->intensitat.difusa = vec4(1.0, 1.0, 1.0, 1.0); // intensidad RGBA que una fuente de luz añade a la escena
    this->intensitat.especular = vec4(1.0, 1.0, 1.0, 1.0); // provoca el brillo puntual del objeto
    this->intensitat.ambient = vec4(0.0, 0.0, 0.0, 1.0);

    this->atenuacio.constant = 1.0;
    this->atenuacio.lineal = 0.09;
    this->atenuacio.cuadratica = 0.032;
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

    const char * attribute ;

    char light_tipus [20];
    strcpy(light_tipus, this->light);
    strcat(light_tipus, ".Tipus");
    attribute = (const char *) light_tipus;
    gl_ld_Llum.tipus = program->uniformLocation(attribute);

    char light_position [20];
    strcpy(light_position, this->light);
    strcat(light_position, ".Position");
    attribute = light_position;
    gl_ld_Llum.posicio = program->uniformLocation(attribute);

    char light_direction [20];
    strcpy(light_direction, this->light);
    strcat(light_direction, ".Direction");
    attribute = light_direction;
    gl_ld_Llum.direccio = program->uniformLocation(attribute);

    char light_alpha [20];
    strcpy(light_alpha, this->light);
    strcat(light_alpha, ".Alpha");
    attribute = light_alpha;
    gl_ld_Llum.obertura = program->uniformLocation(attribute);

    char light_ambient [20];
    strcpy(light_ambient, this->light);
    strcat(light_ambient, ".Ambient");
    attribute = light_ambient;
    gl_ld_Llum.ambient = program->uniformLocation(attribute);

    char light_difusa [20];
    strcpy(light_difusa, this->light);
    strcat(light_difusa, ".Diffuse");
    attribute = light_difusa;
    gl_ld_Llum.difusa = program->uniformLocation(attribute);

    char light_specular [20];
    strcpy(light_specular, this->light);
    strcat(light_specular, ".Specular");
    attribute = light_specular;
    gl_ld_Llum.especular = program->uniformLocation(attribute);

    char light_constant [20];
    strcpy(light_constant, this->light);
    strcat(light_constant, ".Constant");
    attribute = light_constant;
    gl_ld_Llum.constant = program->uniformLocation(attribute);

    char light_lineal [20];
    strcpy(light_lineal, this->light);
    strcat(light_lineal, ".Lineal");
    attribute = light_lineal;
    gl_ld_Llum.lineal = program->uniformLocation(attribute);

    char light_cuadratica [20];
    strcpy(light_cuadratica, this->light);
    strcat(light_cuadratica, ".Cuadratica");
    attribute = light_cuadratica;
    gl_ld_Llum.cuadratica = program->uniformLocation(attribute);

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
