#include <iostream>
#include <vector>
#include "primera.h"
#include "hijo1.h"
#include "hija2.h"
#define _USE_MATH_DEFINES

using namespace std; //con esto evitamos hacer std::cout
using namespace miespacio;

namespace operaciones{ //namespace propio
    int sum(int x, int y){return x+y;}
    int sumpunt(int *x, int *y){return *x + *y;}
}


int main()
{
    int x, y;
    cout << "x: ";
    cin >> x;
    cout << "y: ";
    cin >> y;

    string hola = "Hello!";
    vector <int> miVector;

    miVector.push_back(x);
    miVector.push_back(y);

    int sumaEntero = operaciones::sumpunt(&x,&y);
    cout << hola << endl;
    cout << "Suma: " << sumaEntero << endl;
    //cout << "Suma vector" << sum(miVector);

    Hijo1 miClase; // instancia la clase no se como


    miClase.setValues(8,9);

    //instancia la clase mediante punteros
    Hija2 *miOtraClase;
    miOtraClase = new Hija2();
    miOtraClase->setValues(9,7);

    Primera *miPuntero;

    vector <Primera*> miVector2;
    miVector2.push_back(&miClase);
    miVector2.push_back(miOtraClase);

    delete miOtraClase; // la saca de memoria

    return 0;
}
