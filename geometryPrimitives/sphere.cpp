 #include "sphere.h"

Sphere::Sphere():precision(100)
{
    allocateArrays();
}

Sphere::Sphere(int precision):precision(precision)
{
    if(this->precision % 2 == 1) this->precision++;
    allocateArrays();
}

void Sphere::allocateArrays()
{

}

Sphere::~Sphere()
{

}

void Sphere::draw()
{
    glPushMatrix();

    // draw immediate (center sphere)
    drawImmediate();

    // draw arrays (left sphere)
    glTranslatef(-2, 0, 0);
    drawArrays();

    // draw elements (right sphere)
    glTranslatef(+4, 0, 0);
    drawElements();

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

void Sphere::drawArrays()
{
    // vertices coordinates can be stored
//	GLfloat s0[] = {+0.5, -0.5, -0.5};
    GLfloat s1[] = {+0.5, +0.5, -0.5};
    GLfloat s2[] = {-0.5, +0.5, -0.5};
    GLfloat s3[] = {-0.5, -0.5, -0.5};
    GLfloat s4[] = {+0.5, -0.5, +0.5};
    GLfloat s5[] = {+0.5, +0.5, +0.5};
    GLfloat s6[] = {-0.5, +0.5, +0.5};
    GLfloat s7[] = {-0.5, -0.5, +0.5};


    // For each vertex of each face, define its normal then its coordinates
    // - vertices shared by faces must be reset (glVertex3f) for each face
    // - vertices of the same polygon might share the same normal (flat
    //   surface) or have different normals (curved surface)

    glBegin(GL_QUADS);

        // for each face, define a normal (first) the a
        // 0 3 2 1
        glNormal3f(0.0, 0.0, -1.0);	// same normal shared by 4 vertices
        glVertex3f(+0.5, -0.5, -0.5);   // direct coordinates
        glVertex3fv(s1);                // stored coordinates
        glVertex3fv(s2);
        glVertex3fv(s3);

        // 0 4 7 3
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(+0.5, -0.5, -0.5);
        glVertex3fv(s4);
        glVertex3fv(s7);
        glVertex3fv(s3);

        // 1 5 4 0
        glNormal3f(1.0, 0.0, 0.0);
        glVertex3fv(s1);
        glVertex3fv(s5);
        glVertex3fv(s4);
        glVertex3f(+0.5, -0.5, -0.5);

        // 2 6 5 1
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3fv(s2);
        glVertex3fv(s6);
        glVertex3fv(s5);
        glVertex3fv(s1);

        // 3 7 6 2
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3fv(s3);
        glVertex3fv(s7);
        glVertex3fv(s6);
        glVertex3fv(s2);

        // 4 5 6 7
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3fv(s4);
        glVertex3fv(s5);
        glVertex3fv(s6);
        glVertex3fv(s7);

    glEnd();
}

void Sphere::drawElements()
{
    // top face
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f,0.0f,1.0f);
        glVertex3f(0.0f,0.0f,0.5f);
        glVertex3f(0.5f,0.0f,0.5f);

        //std::cout << "New vertex: " << (cos((2.0f*M_PI/precision)*1))/2.0f << ", " << (sin((2.0f*M_PI/precision)*1))/2.0f << ", " << 0.5f << std::endl;
        glVertex3f((cos(2.0f*M_PI/precision))/2.0f,(sin((2.0f*M_PI/precision)*1))/2.0f,0.5f);

        for(float i = 2;i<=precision;i++)
        {
            glNormal3f(0.0f,0.0f,1.0f);
            //std::cout << "New vertex: " << (cos((2.0f*M_PI/precision)*i))/2.0f << ", " << (sin((2.0f*M_PI/precision)*i))/2.0f << ", " << 0.5f << std::endl;
            glVertex3f((cos((2.0f*M_PI/precision)*i))/2.0f,(sin((2.0f*M_PI/precision)*i))/2.0f,0.5f);
        }
    glEnd();


    //middle part
    glBegin(GL_QUAD_STRIP);

        for(float i=0;i<=precision;i++)
        {
            glNormal3f((cos((2.0f*M_PI/precision)*i)),(sin((2.0f*M_PI/precision)*i)),0.0f);
            glVertex3f((cos((2.0f*M_PI/precision)*i))/2.0f,(sin((2.0f*M_PI/precision)*i))/2.0f,0.5f);
            glVertex3f((cos((2.0f*M_PI/precision)*i))/2.0f,(sin((2.0f*M_PI/precision)*i))/2.0f,-0.5f);
        }

    glEnd();

    // bottom face
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f,0.0f,-1.0f);
        glVertex3f(0.0f,0.0f,-0.5f);
        glVertex3f(0.5f,0.0f,-0.5f);

        //std::cout << "New vertex: " << (cos((2.0f*M_PI/precision)*(precision-1)))/2.0f << ", " << (sin((2.0f*M_PI/precision)*(precision-1)))/2.0f << ", " << -0.5f << std::endl;

        glVertex3f((cos((2.0f*M_PI/precision)*(precision-1)))/2.0f,(sin((2.0f*M_PI/precision)*(precision-1)))/2.0f,-0.5f);

        for(float i = (precision-2);i>=0;i--)
        {
            glNormal3f(0.0f,0.0f,-1.0f);
            //std::cout << "New vertex: " << (cos((2.0f*M_PI/precision)*i))/2.0f << ", " << (sin((2.0f*M_PI/precision)*i))/2.0f << ", " << -0.5f << std::endl;
            glVertex3f((cos((2.0f*M_PI/precision)*i))/2.0f,(sin((2.0f*M_PI/precision)*i))/2.0f,-0.5f);
        }
    glEnd();
}
