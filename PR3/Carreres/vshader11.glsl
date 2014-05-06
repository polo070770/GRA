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
//IN vec4 vColor;
IN vec4 vNormal;
uniform tipusLlum light;
uniform mat4 model_view;
uniform mat4 projection;

OUT vec4 color;


void main() 
{
  float brillo = 3;
  vec4 ambient, diffuse, specular;
  gl_Position = projection * model_view * (vPosition / vPosition.w );


  vec3 N = normalize(vNormal.xyz);
  vec3 L = normalize(light.Position.xyz - (vPosition).xyz);
  vec3 E = -normalize((vPosition).xyz);
  vec3 H = normalize(L+E);

  float Kd = max(dot(L, N), 0.0);
  float Ks = pow(max(dot(N, H), 0.0), brillo);

  ambient = light.Ambient;
  diffuse = Kd * light.Diffuse;
  specular = max(pow(max(dot(N, H), 0.0), brillo) * light.Specular, 0.0);


  color = vec4((ambient + diffuse + specular).xyz, 1.0);

} 
