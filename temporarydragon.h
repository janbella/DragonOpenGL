#ifndef TEMPORARYDRAGON
#define TEMPORARYDRAGON

#include <list>
#include <glew.h>
#include <glut.h>

#include "renderable.h"
#include "objectloader.h"
#include "glCheck.h"

#include "shader.h"


double angle = 0.0;
double angleChange = 0.1;
bool increase = false;
// the dragon model drawing and manipulating

    const std::string bl = "dragon2/backleg.obj";
	const std::string bll = "dragon2/backleg_left.obj";
	const std::string l = "dragon2/leg.obj";
	const std::string ll = "dragon2/leg_left.obj";
	const std::string rw = "dragon2/wing.obj";
	const std::string t = "dragon2/torso.obj";
	const std::string w = "dragon2/right_wing.obj";
    const char* dragonTexture = "textures/Dragon_ground_color.jpg";
    const char* texturePath = "textures/skybox.jpg";
	bool loaded = false;

class TemporaryDragon : public Renderable
{
public:

    TemporaryDragon()
    {

        loaded = false;
    };

    void load()
    {
        dispListIndex = glGenLists(8);

        ObjectLoader objLoader(bl);
        if(objLoader.loadObj())
        {
            objLoader.createDisplayList(dispListIndex, texcoord);
        }

		
        objLoader.setFilename(bll);
        if(objLoader.loadObj())
        {
            objLoader.createDisplayList(dispListIndex+1, texcoord);
        }

		
        objLoader.setFilename(l);
        if(objLoader.loadObj())
        {
            objLoader.createDisplayList(dispListIndex+2, texcoord);
        }
		
        objLoader.setFilename(ll);
        if(objLoader.loadObj())
        {
            objLoader.createDisplayList(dispListIndex+3, texcoord);
        }
		
        objLoader.setFilename(rw);
        if(objLoader.loadObj())
        {
            objLoader.createDisplayList(dispListIndex+4, texcoord);
        }
		
        objLoader.setFilename(t);
        if(objLoader.loadObj())
        {
            objLoader.createDisplayList(dispListIndex+5, texcoord);
        }
		
        objLoader.setFilename(w);
        if(objLoader.loadObj())
        {
            objLoader.createDisplayList(dispListIndex+6, texcoord);
        }
        loaded = true;
    }

    GLuint loadTexture(const char *filename)
    {
        // generates an OpenGL texture id, and store it
        GLuint id;
        GLCHECK(glGenTextures(1, &id));

        // load a texture file as a QImage
        QImage img = QGLWidget::convertToGLFormat(QImage(filename));

        // specify the texture(2D texture, rgba, single file)
        GLCHECK(glBindTexture(GL_TEXTURE_2D, id));

        GLCHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0,
                        GL_RGBA, GL_UNSIGNED_BYTE, img.bits()));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        return id;
    }

    virtual void init(Viewer&)
    {
        // load textures
        textureId = loadTexture(dragonTexture);

        program.load("shaders/texture.vert", "shaders/texture.frag");
        // get the program id and use it to have access to uniforms
        GLint program_id = (GLint)program;
        GLCHECK(glUseProgram( program_id ) );
        // get uniform locations (see the fragment shader)
        GLCHECK(texture = glGetUniformLocation( program_id, "texture0"));
        // get vertex texture coordinate locations
        GLCHECK(texcoord = glGetAttribLocation( program_id, "texcoord0"));
        // tex0 on the sampler will use the texture unit #0
        GLCHECK(glUniform1i( texture, 0 ) );
    }


    ~TemporaryDragon() {};
	
    // inherited from Renderable, should be edited
    virtual void draw()
    {
        if(!loaded) load();
       /* GLCHECK(glUseProgram( (GLint)program ));

        GLCHECK(glActiveTexture(GL_TEXTURE0));

        // bind the crate texture for texture unit 0
        GLCHECK(glBindTexture(GL_TEXTURE_2D, textureId));

        // set the texture sampler id in shader to active texture unit number
        GLCHECK(glUniform1i(texture, 0));
		*/
		glCallList(0);
		glCallList(1);
		glCallList(2);
		glCallList(3);
		glCallList(4);
		glCallList(6);
		glPushMatrix();

		glRotatef(angle, 0.0f, -1.0f, -1.0f);		
        glPushMatrix();
		glCallList(5);
		glPopMatrix();
		glPopMatrix();
		

		glRotatef(angle, 0.0f, 1.0f, 1.0f);
		glPushMatrix();
		glCallList(7);
		
	//	glPopMatrix();
        glPopMatrix();


    };

	virtual void animate()
    {
		if (angle>10 || angle<-10)
			increase=!increase;
		if (increase)
			angle+=angleChange;
		else
			angle-=angleChange;
    };

	virtual void keyPressEvent(QKeyEvent* e, Viewer& v) {
		if (e->key()==Qt::Key_W)
			keyWPress();
		else if (e->key()==Qt::Key_Space)
			keySpacePress();
		else if (e->key()==Qt::Key_A)
			keyAPress();
		else if (e->key()==Qt::Key_S)
			keySPress();
		else if (e->key()==Qt::Key_Plus)			
		{
			if (angleChange<0.7)
			angleChange*=1.1;
			
		}
		else if (e->key()==Qt::Key_Minus)
		{
			angleChange/=1.1;
		}
	};

	void keyWPress(){
	
	};
	void keySpacePress(){
	
	};
	void keyAPress(){};
	void keySPress(){};
	void keyDPress(){};
	void keyPlusPress(){
	
	};
	void keyMinusPress(){};


private:
	GLuint dispListIndex;

    GLuint textureId;

    // texture unit shader binding
    GLint texture;

    // texture coordinate bindings
    GLint texcoord;

    // shader program
    ShaderProgram program;

    // load a single texture file to associate with a Textureid
};

#endif // TEMPORARYDRAGON

