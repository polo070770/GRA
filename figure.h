#ifndef FIGURE_H
#define FIGURE_H

namespace spacefigure{

   class Figure
   {
   public:

       double perimeter;

       Figure();

       virtual void getPerimeter() = 0;

   };

}
#endif // FIGURE_H
