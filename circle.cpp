#include "circle.h"
#include <iostream>
#include <math.h>
#include <stdio.h>

#define _USE_MATH_DEFINES

using namespace std;
using namespace spacefigure;

Circle::Circle()
{
   this->radius = 2;
   this->perimeter = 2 * M_PI * this->radius;
}

Circle::Circle(int radius){

   this->radius = radius;
   this->perimeter = 2 * M_PI * radius;

}

void Circle::getPerimeter(){

   printf("\nPerimeter of a circle with radius %d is %f", this->radius, this->perimeter);
}

void Circle::setRadius(double radius){

   this->radius = radius;
   this->perimeter = 2 * M_PI * radius;

}
