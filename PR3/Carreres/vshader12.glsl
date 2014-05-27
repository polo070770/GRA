#version 150

/* definicio de les entrades  */
in vec4 vPosition;
in vec4 vNormal;

/* definicio de les sortides */
out vec4 position;
out vec4 normal;

/* definicio de l'estructura de les dades de la llum */
struct tipusLlum{
    int Tipus;
    vec4 Position;
    vec3 Direction;
    float Alpha;
    vec4 Ambient;
    vec4 Diffuse;
    vec4 Specular;
    float Constant;
    float Lineal;
    float Cuadratica;
};

/* definicio de l'estructura per als materials */
struct tipusMaterial{
    vec4 Ambient;
    vec4 Diffuse;
    vec4 Specular;
    float Shinines;
};

/* uniforms */
uniform tipusMaterial material;
uniform tipusLlum light;
uniform tipusLlum light2;

uniform mat4 model_view;
uniform mat4 projection;
uniform float ambientGlobal;

void main()
{

    position = vPosition;
    normal = vNormal;
    gl_Position = projection * model_view * vPosition;

}

