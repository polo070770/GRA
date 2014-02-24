#include "square.h"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace spacefigure;

Square::Square()
{
   this->length = 4;
   this->perimeter = 4 * this->length;
}

Square::Square(int length){

   this->length = length;
   this->perimeter = 4 * length;

}

void Square::getPerimeter(){

   printf("\nPerimeter of a square with length %d is %f", this->length, this->perimeter);

}
