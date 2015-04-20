#ifndef _TEXTURES_H_
#define _TEXTURES_H_

#include "renderable.h"
#include "shader.h"
#include <QImage>

class Textures : public Renderable
{
    public:
        Textures();
        void init(Viewer& v);
        void draw();
        void keyPressEvent(QKeyEvent *e, Viewer&);

    private:

        // ---------------------------------------------------------
        // METHODS TO IMPLEMENT / MODIFY IN THE PRATICAL SESSION
        // init and draw a plane with the grass texture
        void drawGrassPlane(float size);

        // init and draw a crate with texture on each face
        void drawCrate(float size);

        // use multi-texturing
        void drawMultiTexturing();

        // use billboards
        void drawBillBoard();

        // ---------------------------------------------------------
        // YOU MAY ADD ADDITIONAL STATES HERE
        // textures used in this practical (you can add more)
        GLuint tex_grass, tex_mipmap;
        GLuint tex_crate;

        // texture unit shader binding
        GLint texture0;
        GLint texture1;

        // texture coordinate bindings
        GLint texcoord0;
        GLint texcoord1;

        // ---------------------------------------------------------
        // METHODS AND ATTRIBUTES YOU MAY USE WITHOUT MODIFYING
        // shader program
        ShaderProgram program;

        // load a single texture file to associate with a Textureid
        GLuint loadTexture(const char *filename, bool mipmap=false);

        // draw a quad centered in the XY place (z=0), of size s
        void drawPlane(float s = 10.0);

        // mipmap example
        void initMipmapExample();
        void drawMipmapExample();

        // change texture filtering modes
        void toggleFiltering();		// using the 'f' key
        void toggleMipMapFiltering();	// using the 'm' key

        // filtering mode feedback
        void printFilteringMode(int mode);

        // filtering mode states
        GLint filteringMode;
        GLint mipmapFilteringMode;

        // use setFiltering(filteringMode) if using regular texture
        // use setFiltering(mipmapFilteringMode) if using mipmap texture
        void setFiltering(int mode);

        // state to know if we are showing mipmap example
        bool show_mipmap_example;

};

#endif
