#ifndef _LIGHTS_MATERIALS_
#define _LIGHTS_MATERIALS_

# include "renderable.h"
# include "shader.h"
# include <vec.h>

class LightsMaterials : public Renderable
{
	public:
		LightsMaterials();
		virtual void draw();
		virtual void init(Viewer &);

	private:
		// draw 12 spheres with different materials set with glMaterial*
		// Exemple adapted from the OpenGL Programming Guide (The Red Book)
		void exampleMaterial();
        ShaderProgram program;
};

#endif

