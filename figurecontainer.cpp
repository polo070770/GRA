#include "figurecontainer.h"
#include <vector>

using namespace spacefigure;
using namespace std;

FigureContainer::FigureContainer()
{

}

void FigureContainer::addFigure(Figure * figure){

   this->vector_figures.push_back(figure);

}

double FigureContainer::getPerimeters(){

   double sum = 0.0;
   vector<Figure *>::iterator i;

   for (i = this->vector_figures.begin(); i != this->vector_figures.end(); ++i) {
       sum += (*i)->perimeter;
   }

   return sum;
}
