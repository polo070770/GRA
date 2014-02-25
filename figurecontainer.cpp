#include <iostream>
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


   for (i = this->vector_figures.begin(); i < this->vector_figures.end(); i++) {
                //(*i)-> : es un puntero a un puntero y equivalente a
                //(*(*i)).
       sum += (*i)->getPerimeter();
   }


   /*
   for(unsigned int i = 0; i < this->vector_figures.size(); i++ ){
       sum += this->vector_figures[i]->getPerimeter();
   }
   */

   return sum;
}

FigureContainer::~FigureContainer(){

    vector<Figure *>::iterator i;

    for (i = this->vector_figures.begin(); i < this->vector_figures.end(); i++) {
        cout << "deleting container: " << endl;
        delete *i;
    }
}
