#include "circle.h"
#include <iostream>
#include <math.h>
#include <stdio.h>

#define _USE_MATH_DEFINES

using namespace std;
using namespace spacefigure;

Circle::Circle()
{
   //Inicializamos el circulo con radio 0
   this->radius = 0;
   this->setPerimeter();
}

Circle::Circle(int radius){

   this->radius = radius;
   this->setPerimeter();

}

void Circle::setPerimeter(){
    this->perimeter = 2 * M_PI * radius;
}

void Circle::printPerimeter(){

   printf("\nPerimeter of a circle with radius %d is %f", this->radius, this->perimeter);
}

void Circle::setRadius(double radius){

   this->radius = radius;
   this->setPerimeter();

}

double Circle::getPerimeter(){
    return this->perimeter;
}
