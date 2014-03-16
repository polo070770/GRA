#PR1
##Ej 1 :OK
##Ej 2 : TERRA :pendiente
####Archivos a crear
* terra.h
* terra.cpp

####Archivos a incluir
* QGLShaderProgram
* Common.h
* Object.h

####Que?
Terra hereda de Objecte
Definimos los 4 vertices y los colores en el constructor.
Tambien definimos la funcion make() como publica y la funcion quad() como privada

#####Make()
llama al a funcio quad() con los indices de los 4 vertices en el orden para realizar su normal
#####Quad()
Añade a los arrays colors[] y points[], que son de Objecte, los datos de los arrays vertex_colors y vertices, que son propios del objeto terra, en el mismo indice.
####Pendientes
Queda pendiente todo lo relativo a ajustar el tamaño etc en funcion de los parametros de entrada

##Ej 2 : ESCENA :pendiente
####Añadir i/o modificar
* cotxe pasa a ser un objeto CotxeContainer
* todos los metodos que añaden y o aplican cambios a elementos deben aplicarlos tmb a cada subelemento del vector_cotxes
* añadir vector_obstacles
* todos los metodos que añaden y o aplican cambios a los elementos deben tmb aplicarlo a cada subelemtn del vector_obstacles

##Ej 4: COTXE :pendiente
####Clases a crear
* Carrosseria
* Roda

####Clases a modficar
* Cotxe

####Que?
El cotxe pasa a tener 5 atributos que son 
* carrosseria
* roda_davantera/posterior_esquerra/dreta * 4

Todos heredan de objecte
La funcio readobj del coche ahora tiene que gestionar que parte del coche esta leyendo, para ello utilizamos el codigo suministrado en clase, y un contador que indica que puntero del vector_fills estamos utilizando

####Funciones a sobrecargar en Cotxe de Objecte
* readoObj() --> OK
* make() --> OK
* aplicaTg(mat4 trans) --> OK
* draw() --> OK
* toGPU() --> Ok
* aplicaTGCentrar() --> OK

####Pendientes
* calculCapsa3D
* 
