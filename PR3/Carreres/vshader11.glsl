#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

/* defiicio de les entrades  */
IN vec4 vPosition;
IN vec4 vNormal;

/* definicio de les sortides */
OUT vec4 color;

/* Definicio dels tipus de llum */
const int PUNTUAL =  0;
const int DIRECCIONAL = 1;
const int SPOT = 2;

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

uniform mat4 model_view;
uniform mat4 projection;
uniform float ambientGlobal;

float attenuation();

void main(){

    vec3 diffuse, ambient, specular, N, V, L, H;

    gl_Position = projection * model_view * vPosition;

    // la normal del vertice, normalizada
    N = normalize(vNormal.xyz);

    // el vector desde el punt fins al viewer
    V = normalize((model_view * vPosition).xyz);

    // el vector direccion desde el punto hasta la fuente de luz, normalizada
    if(light.Tipus == PUNTUAL){
        L = normalize((light.Position - vPosition).xyz);
    }else if(light.Tipus == DIRECCIONAL){
        L = normalize(-light.Direction.xyz);
    }

    // the halfway, o l'optimitzacio de Blinn
    H = (L+V) / length(L+V);

    // la difusa es el producto de la difusa de la luz por la difusa del material
    diffuse = (light.Diffuse.xyz * material.Diffuse.xyz) * max(dot(L, N), 0.0);

    // la especular es el producto del producto especular de la luz por el del material y  el dot de N y H elevado a E
    specular = (light.Specular.xyz * material.Specular.xyz) * max(pow(dot(N, H), material.Shinines) , 0.0);

    // producto de light ambient y  ambient del material
    ambient = light.Ambient.xyz * material.Ambient.xyz;

    // al resultado final le aplicamos la atenuacion
    color = vec4( attenuation() * (ambientGlobal + ambient + diffuse + specular).xyz, 1.0);

}

float attenuation(){
    float a, b, c;
    float distance = length((light.Position - vPosition).xyz);

    a = light.Cuadratica * pow(length((light.Position - vPosition).xyz), 2.0);
    b = light.Lineal * length((light.Position - vPosition).xyz);
    c = light.Constant;

    return (1.0 /(a + b + c));

}
