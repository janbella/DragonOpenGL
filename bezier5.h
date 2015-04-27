#ifndef BEZIER5_H
#define BEZIER5_H

#include "renderable.h"


class Bezier5 : public Renderable
{
private:
    float Points[8][3] = {
        {    0,50, 0 },
        { -300,50,-300 },
        { -300,50, 300 },
        {  400,50, 400},
        {  400,50, 400},
        {  300,50,-300},
        {  300,50, 300},
        {    0,50,0}};
    float precision;
public:
    Bezier5(float precision);
    ~Bezier5();
    virtual void draw();

    QVector2D getBezierLocationPosition(float t);
};

#endif // BEZIER5_H
