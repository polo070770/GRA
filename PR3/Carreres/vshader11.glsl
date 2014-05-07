#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

struct tipusLlum{
    int tipus;
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

IN vec4 vPosition;
IN vec4 vNormal;
uniform tipusLlum light;
uniform mat4 model_view;
uniform mat4 projection;

OUT vec4 color;


void main() 
{
  float E, IG;
  vec3 ambient, diffuse, specular;
  vec3 Kd, Ks, Ka;
  E = 3;
  IG = 0.01;
  Kd = vec3(0.7,0.7,0.7);
  Ks = vec3(0.7,0.7,0.7);
  Ka = vec3(0.7,0.7,0.7);

  gl_Position = projection * model_view * (vPosition / vPosition.w );


  vec3 N = normalize(vNormal.xyz);
  vec3 L = normalize(light.Position.xyz - (vPosition).xyz);
  vec3 V = max(dot(L, N), 0); // es el vector del rebot de la llum
  vec3 H = normalize((L+V) / abs(L+V));


  diffuse = light.Diffuse * Kd * dot(N, L);
  specular = light.Specular * Ks* pow(dot(N, H), E);
  ambient = light.Ambient * Ka;


  color = vec4(( IG + ambient + diffuse + specular ).xyz, 1.0);
} 
