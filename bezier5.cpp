#include "bezier5.h"

#include <GL/glut.h>
#include <cmath>


Bezier5::Bezier5(float precision):precision(precision)
{

}

Bezier5::~Bezier5()
{

}

void Bezier5::draw()
{
    glTranslatef(0.0,30.0,0.0);
    glColor3f(1,1,1);

    int LOD = 80;
    // we will draw lots of little lines to make our curve
    glBegin(GL_LINE_STRIP);

    for(int i=0;i!=LOD;++i) {

        // use the parametric time value 0 to 1
        float t = (float)i/(LOD-1);

        // nice to pre-calculate 1.0f-t because we will need it frequently
        float it = 1.0f-t;

        // calculate blending functions
        float b0 = pow(it,7);
        float b1 = 7*t*pow(it,6);
        float b2 = 21*pow(t,2)*pow(it,5);
        float b3 = 35*pow(t,3)*pow(it,4);
        float b4 = 35*pow(t,4)*pow(it,3);
        float b5 = 21*pow(t,5)*pow(it,2);
        float b6 = 7*pow(t,6)*it;
        float b7 = pow(t,7);

        // calculate the x,y and z of the curve point by summing
        // the Control vertices weighted by their respective blending
        // functions
        //
        float x = b0*Points[0][0] +
                b1*Points[1][0] +
                b2*Points[2][0] +
                b3*Points[3][0] +
                b4*Points[4][0] +
                b5*Points[5][0] +
                b6*Points[6][0] +
                b7*Points[7][0];

        float y = b0*Points[0][1] +
                b1*Points[1][1] +
                b2*Points[2][1] +
                b3*Points[3][1] +
                b4*Points[4][1] +
                b5*Points[5][1] +
                b6*Points[6][1] +
                b7*Points[7][1];

        float z = b0*Points[0][2] +
                b1*Points[1][2] +
                b2*Points[2][2] +
                b3*Points[3][2] +
                b4*Points[4][2] +
                b5*Points[5][2] +
                b6*Points[6][2] +
                b7*Points[7][2];

        // specify the point
        glVertex3f( x,y,z );
    }
    glEnd();

    // draw the Control Vertices
    glColor3f(1,1,1);
    glPointSize(3);
    glBegin(GL_POINTS);
    for(int i=0;i!=6;++i) {
        glVertex3fv( Points[i] );
    }
    glEnd();
}
