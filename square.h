#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"

namespace spacefigure{

   class Square : public Figure
   {
   public:

       int length;

       Square();
       Square(int length);

       void getPerimeter();

   };

}
#endif // SQUARE_H
