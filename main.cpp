#include <iostream>
#include "figure.h"
#include "circle.h"
#include "square.h"
#include "figurecontainer.h"

using namespace std;
using namespace spacefigure;

int main()
{

   Circle * circle = new Circle();
   Square * square = new Square();

   FigureContainer container;

   circle->getPerimeter();
   square->getPerimeter();

   container.addFigure(circle);
   container.addFigure(square);

   double sum = container.getPerimeters();

   cout << "\nSum of perimeters is: " << sum;

   double radius;

   cout << "\nNew circle radius? ";
   cin >> radius;

   circle->setRadius(radius);

   sum = container.getPerimeters();

   cout << "\nSum of perimeters is: " << sum << endl;

}
