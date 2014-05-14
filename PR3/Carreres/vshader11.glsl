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

void main(){

    vec3 ambient, diffuse, specular, N, V, L, H, R;

    gl_Position = projection * model_view * (vPosition / vPosition.w );

    N = normalize(vNormal.xyz);  // la normal del vertice, pasada por normalize para ser uniforme

    V = -normalize((model_view * vPosition).xyz); // el vector desde el punt fins al viewer

    //vec3 H = normalize((L+V).xyz); // the halway, o l'optimitzacio de Blinn

    if(light.Tipus == PUNTUAL){

        L = normalize((light.Position - vPosition).xyz); // el vector unitario desde el punto a la luz

    }else if(light.Tipus == DIRECCIONAL){

        L = normalize(light.Direction.xyz); // el vector unitario desde el punto a la luz
        //L = dot(reflect(-light.Direction, N), V);

    }

    H = normalize((L+V) / length(L+V)); // the halway, o l'optimitzacio de Blinn
    //R = max(dot(L, N), 0.0); es el vector del rebot de la llum , si es negativo pasa a ser 0

    // la difusa es el producto de V por la difusa de la luz y la difusa del mterial
    diffuse = max(dot(L, N), 0.0) * (light.Diffuse.xyz * material.Diffuse.xyz);

    // la especular es el dot de N y H elevado a E por el producto de la especular de la luz
    // y del material, evitamos que sea un valor negativo
    specular = (light.Specular.xyz * material.Specular.xyz) * max(pow(dot(N, H), material.Shinines) , 0.0);

    // producto de light ambient y la reflectividad del material
    ambient = light.Ambient.xyz * material.Ambient.xyz;

    float att, a, b, c;

    a = light.Cuadratica * pow(length(light.Direction.xyz), 2.0);
    b = light.Lineal * length(light.Direction.xyz);
    c = light.Constant;

    att = 1.0 /(a + b + c);

    color = vec4( att * (ambientGlobal + ambient + diffuse + specular).xyz, 1.0);

} 
