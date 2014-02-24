#include "square.h"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace spacefigure;

Square::Square()
{
   this->length = 0;
}

Square::Square(int length){

   this->length = length;
   this->setPerimeter();

}

void::Square::setPerimeter(){
    this->perimeter = 4 * length;
}

void Square::printPerimeter(){

   printf("\nPerimeter of a square with length %d is %f", this->length, this->perimeter);

}
double Square::getPerimeter(){
    return this->perimeter;
}
