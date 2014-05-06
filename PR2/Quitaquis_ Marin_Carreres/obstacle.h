#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <Common.h>
#include <objecte.h>

#include <iostream>
class Obstacle: public Objecte
{
public:
    Obstacle(QString n);
    Obstacle(QString n, GLfloat mida, GLfloat x0, GLfloat y0, GLfloat z0,
             double girx, double giry, double girz);
    point4 direction;
    void make();


private:

    static const int NumVerticesF = 1000000;
    static const int NumCares = 3000000;



};

#endif // OBSTACLE_H
