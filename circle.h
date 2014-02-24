#ifndef CIRCLE_H
#define CIRCLE_H

#include "figure.h"

namespace spacefigure{

   class Circle : public Figure
   {
   private:
       int radius;

   public:

       //int radius;

       Circle();
       Circle(int radius);

       void getPerimeter();

       void setRadius(double radius);

   };

}
#endif // CIRCLE_H
