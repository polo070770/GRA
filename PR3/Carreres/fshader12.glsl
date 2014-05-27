#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

in vec4 position;
in vec4 normal;

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
uniform tipusLlum light; // direccional
uniform tipusLlum light2; // puntual
uniform tipusLlum light3; // puntual

uniform mat4 model_view;
uniform mat4 projection;
uniform float ambientGlobal;

float attenuation(tipusLlum l);
float spot_light();
vec3 blinn_phong(tipusLlum l);
vec4 get_color();

float attenuation(tipusLlum l)
{
    // se retorna la atenuacion, calculada a partir de la formula de clase
    float a, b, c, distance;

    distance = length((l.Position - position).xyz);

    a = l.Cuadratica * pow(distance, 2.0);
    b = l.Lineal * distance;
    c = l.Constant;

    return (1.0 /(a + b + c));

}

vec3 blinn_phong(tipusLlum l)
{

    vec3 diffuse, ambient, specular, N, V, L, H;

    // la normal del vertice, normalizada
    N = normalize(normal.xyz);

    // el vector desde el punt fins al viewer
    V = normalize(vec3(model_view * position));

    // el vector direccion desde el punto hasta la fuente de luz, normalizada
    if(l.Tipus == PUNTUAL)
    {
        L = normalize((l.Position - position).xyz);
    }else if(l.Tipus == DIRECCIONAL)
    {
        L = normalize(-l.Direction.xyz);
    }else if (l.Tipus == SPOT)
    {
        L = normalize(-l.Direction.xyz);
    }

    // the halfway, o l'optimitzacio de Blinn
    H = (L+V) / length(L+V);

    // la difusa es el producto de la difusa de la luz por la difusa del material
    diffuse = (l.Diffuse.xyz * material.Diffuse.xyz) * max(dot(L, N), 0.0);

    // la especular es el producto del producto especular de la luz por el del material y  el dot de N y H elevado a E
    specular = (l.Specular.xyz * material.Specular.xyz) * max(pow(dot(N, H), material.Shinines) , 0.0);

    // producto de light ambient y  ambient del material
    ambient = l.Ambient.xyz * material.Ambient.xyz;

    return (ambientGlobal + ambient + diffuse + specular);

}

float spot_light()
{
    // calculamos el coseno del spotlight, a partir del angulo de obertura
    float fConeCosine = cos(light3.Alpha);

    // vector director del punto a la luz
    vec3 vDir = normalize((position - light3.Position).xyz);

    // producto vectorial para calcular el coseno
    float fCosine = dot(light3.Direction, vDir);

    if (fCosine > fConeCosine)
        return 1.0;

    return 0.0;

}

vec4 get_Color()
{

    // calculamos los diferentes tipos de luces
    vec4 color = vec4( blinn_phong(light), 1.0); // direccional
    vec4 color2 = vec4((attenuation(light2) * blinn_phong(light2)), 1.0); // puntual
    vec4 color3 = vec4(spot_light() * blinn_phong(light3), 1.0); // focal

    // la luz total es la suma de las 3 anteriores
    return color + color2 + color3;
}

void main()
{

    gl_FragColor = get_Color();

}
