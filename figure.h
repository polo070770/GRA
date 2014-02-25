#ifndef FIGURE_H
#define FIGURE_H

namespace spacefigure{

   class Figure
   {
   protected:

       double perimeter;

   public:
       Figure();
       ~Figure();

       /*
        * Funcion que imprime el perimetro por pantalla
        */
       virtual void printPerimeter() = 0;

       /*
        * Funcion que devuelve el perimetro
        */
       virtual double getPerimeter() = 0;

    private:
       virtual void setPerimeter() = 0;

   };

}
#endif // FIGURE_H
