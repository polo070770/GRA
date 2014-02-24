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

       void printPerimeter();
       double getPerimeter();
   private:
       void setPerimeter();

   };

}
#endif // SQUARE_H
