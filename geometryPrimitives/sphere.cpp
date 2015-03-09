 #include "sphere.h"

Sphere::Sphere():precision(100)
{

}

Sphere::Sphere(int precision):precision(precision)
{
    if(this->precision % 2 == 1) this->precision++;
}


Sphere::~Sphere()
{

}

void Sphere::draw()
{
    glPushMatrix();

    // draw immediate (center sphere)
    drawImmediate();

    glPopMatrix();
}

// Based on from: http://www.cburch.com/cs/490/sched/feb8/
// just small edits
void Sphere::drawImmediate()
{
    for(int i = 0; i <= precision; i++)
    {
        float lat0 = M_PI * (-0.5f + (i - 1.0f) / (float)precision);
        float z0  = sin(lat0);
        float zr0 =  cos(lat0);

        float lat1 = M_PI * (-0.5f + i / (float)precision);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
            for(int j = 0; j <= precision; j++)
            {
                float lng = (2.0f * M_PI * (j - 1)) / precision;
                double x = cos(lng);
                double y = sin(lng);

                glNormal3f(x * zr0 , y * zr0 , z0);
                glVertex3f(x * zr0 / 2.0f, y * zr0 / 2.0f, z0/ 2.0f);
                glNormal3f(x * zr1 , y * zr1 , z1);
                glVertex3f(x * zr1 / 2.0f, y * zr1 / 2.0f, z1/ 2.0f);
            }
        glEnd();
     }
}
