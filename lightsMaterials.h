#ifndef _LIGHTS_MATERIALS_
#define _LIGHTS_MATERIALS_

# include "renderable.h"
# include "shader.h"

#include <QVector4D>

#include "vector4.h"

/**
 * @brief The LightsMaterials class scene with 12 spheres
 */
class LightsMaterials : public Renderable
{
    private:
        ShaderProgram program; // shader program

    public:
        /**
         * @brief LightsMaterials constructor.
         */
        LightsMaterials();

        /**
         * @brief draw implementation of Renderable draw method
         */
        virtual void draw();

        /**
         * @brief init implementation of Renderable init method
         */
        virtual void init(Viewer &);

    private:
        // draw 12 spheres with different materials set with glMaterial*
        // Exemple adapted from the OpenGL Programming Guide (The Red Book)
        void exampleMaterial();
};

#endif

