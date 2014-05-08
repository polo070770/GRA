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
const int DIRECCINAL = 1;
const int SPOT = 2;

/* definicio de l'estructura de les dades de la llum */

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
/* uniforms */
uniform tipusLlum light;
uniform mat4 model_view;
uniform mat4 projection;





void main(){
  vec4 ambient, diffuse, specular;
  ///----------EXPERIMENTALS
  /* valores expermimentales del material */
  vec4 Kd, Ks, Ka;
  Kd = vec4(0.9, 0.9, 0.9, 1.0); // difusa
  Ks = vec4(0.9, 0.9, 0.9, 1.0); // specular
  Ka = vec4(0.9, 0.9, 0.9, 1.0); // ambient
  float E = 3.0; //shinines


  /* valor experimental intensidad global */
  float IG = 0.01;

  gl_Position = projection * model_view * (vPosition / vPosition.w );

  if(light.tipus == PUNTUAL){
      vec3 N = normalize(vNormal.xyz);  // la normal del vertice, pasada por normalize para ser uniforme
      vec3 L = normalize((light.Position - vPosition).xyz); // el vector unitario desde el punto a la luz
      vec3 R = max(dot(L, N), 0.0); // es el vector del rebot de la llum , si es negativo pasa a ser 0
      vec3 V = -normalize((model_view * vPosition).xyz ); // el vector desde el punt fins al viewer
      //vec3 H = normalize((L+V) / abs(L+V)); // the halway, o l'optimitzacio de Blinn
      vec3 H = normalize((L+V).xyz); // the halway, o l'optimitzacio de Blinn



      // la difusa es el producto de V por la difusa de la luz y la difusa del mterial
      diffuse =  R * (light.Diffuse * Kd);

      // la especular es el dot de N y H elevado a E por el producto de la especular de la luz
      // y del material, evitamos que sea un valor negativo
      specular = max(pow(dot(N, H), E) * (light.Specular * Ks), 0.0);

      // producto de light ambient y la reflectividad del material
      ambient = light.Ambient * Ka;
}

  color = vec4( min(IG + ambient + diffuse + specular, 1.0).xyz, 1.0);
} 
