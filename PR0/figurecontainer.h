#ifndef FIGURECONTAINER_H
#define FIGURECONTAINER_H

#include "figure.h"
#include <vector>

using namespace std;

namespace spacefigure {

   class FigureContainer
   {
   private:

       vector<Figure*> vector_figures;

   public:

       FigureContainer();
       ~FigureContainer();
       void addFigure(Figure * figure);

       double getPerimeters();

   };

}
#endif // FIGURECONTAINER_H
