#ifndef TEMPORARYDRAGON
#define TEMPORARYDRAGON

#include <list>
#ifdef WIN32
#include <glew.h>
#include <glut.h>
#else
#include <glew.h>
#include <glut.h>
#endif
#include "renderable.h"
#include "objectloader.h"
#include "glCheck.h"

#include "shader.h"

double go = 0;

int timer;
int counter = -50;
double testscale = 1;
double angle = 0.0;
double angle_ = 0.0;
double angleChange = 0.2;
bool increase = false;
bool up = false;
bool up_ = false;
double flight = 0.0;
double shift = 0.0;
double speed = 2.0;
bool r = false;
bool f = false;
bool fall = false;
// the dragon model drawing and manipulating


const std::string cylinder = "models/backleg_skeleton.obj";
const std::string cylinder2 = "models/backleg_left_skeleton.obj";

const std::string bl = "models/backleg.obj";
const std::string bll = "models/backleg_left.obj";
const std::string l = "models/leg.obj";
const std::string ll = "models/leg_left.obj";
const std::string rw = "models/wing.obj";
const std::string t = "models/torso.obj";
const std::string w = "models/right_wing.obj";
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


	// 50 ms -> 20 -> 10MB
	void load()
	{
		 dispListIndex = glGenLists(9);
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
		/*glNewList(0,GL_COMPILE); 
		dispListI = glGenLists(8);
		/* dispListIndex = glGenLists(1);
		//создать один для 
		
		ObjectLoader objLoader(t);
		if(objLoader.loadObj())
		{
			objLoader.createDisplayList(dispListI+1,0);
		}
		//loaded = true;
		//animate();
		loaded = true;*/
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

	GLuint dispListI;

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

		//glNewList(0,GL_COMPILE);   

		dispListI = glGenLists(9);

	}


	~TemporaryDragon() {};

	

	// inherited from Renderable, should be edited
	virtual void draw()
	{

		if (f || fall)
		{
		glTranslatef(0.0,flight,0.0);
		
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
		}
		else if (!f && timer!=0)
			timer = 0;
		else{

		glTranslatef(0.0,0.0,go);
		if(!loaded) load();
		glCallList(0);
		if(!r)
		glCallList(1);
		if(!r)
		glCallList(2);
		glCallList(3);
		glCallList(4);
		glCallList(5);
		glCallList(6);
		glCallList(7);}
		//		glCallList(1);
		//glTranslatef(0.0,0.0,go);
		/*glCallList(0);
		glCallList(1);
		glCallList(2);
		glCallList(3);
		glCallList(4);
		glCallList(6);
		
		*/
		//flying version
		
		/*

		if(r)
		{
		glTranslatef(0.0,0.0,go);
		glCallList(3);
		glCallList(4);
		glCallList(6);
		glCallList(7);
		glCallList(5);
		glPushMatrix();
		glRotatef(angle,1.0f,1.0,0.0);
		glTranslatef(0,testwalky,testwalkz);
		glCallList(1);
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle_,1.0f,1.0,0.0);
		glTranslatef(0,testwalky_,testwalkz_);
		glCallList(2);
		glPopMatrix();
		}
		else 
		{
		glTranslatef(0.0,0.0,go);
		glCallList(0);
		glCallList(1);
		glCallList(2);
		glCallList(3);
		glCallList(4);
		glCallList(5);
		glCallList(6);
		glCallList(7);
		}
		*/

		if(glIsList(dispListI+7))
		{
			
			glCallList(dispListI+7);
			glCallList(dispListI+8);
			//glCallList(dispListI);
		};

	};

	
	virtual void animate()
	{


		if (f)
		{
			timer++;
			if (flight<10)
			{
				flight+=0.02*speed;
			if (timer>7){
				speed*=1.3;
				timer = 0;}
			}

			
			if (angle>10 || angle<-10)
			increase=!increase;
			if (increase)
				angle+=angleChange*speed;
			else
				angle-=angleChange*speed;

		}
		else if (fall)
		{

			if (flight>0)
				flight-=0.02*speed;

			timer++;
			
			if (timer>10){
				speed*=1.3;
				timer = 0;}
			
		}
		if (r){
			go+=0.1;
			if (shift>0.2 || shift<-0)
				up=!up;
			if (!up)
		shift+=0.03;			
			else shift-=0.03;



			/*if (angle>10 || angle<-10)
				up_=!up_;
			if (!up)
			{
			angle+=angleChange;
			}
			else
			{
			angle-=angleChange;
			}
			/*
			if (counter>=0)
			{
			if (testwalky_>0.2 || testwalky_<-0.2)
			up_=!up_;
			if (!up_)
			{
			testwalky_+=0.008;
			testwalkz_+=0.008;
			angle_+=angleChange;
			}
			else
			{
			testwalky_-=0.008;
			testwalkz_-=0.008;
			angle_-=angleChange;
			}

			}
			else counter++;
			}

			/*	if (angle>5 || angle<-5)
			increase=!increase;
			if (increase)
			angle+=angleChange;
			else
			angle-=angleChange;*/

			//GLuint dispListIndex = glGenLists(1);

			
			glNewList(dispListI+7,GL_COMPILE);   

			//  dispListIndex = glGenLists(1);
			//создать один для 


			ObjectLoader objLoader(cylinder);
			if(objLoader.loadObj())
			{
			//	objLoader.createDisplayList(1,0);
				std::vector<QVector3D> vertices = objLoader.getVertices();
				std::vector<QVector3D> normals = objLoader.getNormals();
				std::vector<QVector2D> texCoords = objLoader.getTexCoords();
				std::vector<Triangle> faces =objLoader.getFaces();
				std::vector<QVector3D> skeleton = objLoader.getSkeleton();

				std::vector<QVector3D> verticesNew=skeleton;
				//verticesNew[0].setY(verticesNew[0].y()+shift);
				verticesNew[1].setY(verticesNew[1].y()+2*shift);
				verticesNew[2].setY(verticesNew[2].y()+2*shift);
				verticesNew[3].setY(verticesNew[3].y()+shift);
				verticesNew[4].setY(verticesNew[4].y());
				verticesNew[5].setY(verticesNew[5].y());

				//verticesNew[0].setZ(verticesNew[0].z()+shift);
				verticesNew[1].setZ(verticesNew[1].z()+2*shift);
				verticesNew[2].setZ(verticesNew[2].z()+2*shift);
				verticesNew[3].setZ(verticesNew[3].z()+shift);
				verticesNew[4].setZ(verticesNew[4].z());
				verticesNew[5].setZ(verticesNew[5].z());
				
				std::vector<double> abs;
				abs.clear();

				glPushMatrix();
				glBegin(GL_TRIANGLES);

				std::vector<QVector3D> newLineCoordinates;
				for(std::vector<Triangle>::const_iterator iter = faces.cbegin(); iter!=faces.cend();iter++)
				{

					
					int ytemp = vertices[iter->v1].y();
					
						glNormal3f(normals[iter->n1].x(),normals[iter->n1].y(),normals[iter->n1].z());
						//glVertexAttrib2f(shaderTexCoord, texCoords[iter->t1].x(),texCoords[iter->t1].y());
						glVertex3f(vertices[iter->v1].x(),meaning(skeleton,verticesNew,vertices[iter->v1].y()),meaning(skeleton,verticesNew,vertices[iter->v1].y(),vertices[iter->v1].z()));

						glNormal3f(normals[iter->n2].x(),normals[iter->n2].y(),normals[iter->n2].z());
						//glVertexAttrib2f(shaderTexCoord, texCoords[iter->t2].x(),texCoords[iter->t2].y());
						glVertex3f(vertices[iter->v2].x(),meaning(skeleton,verticesNew,vertices[iter->v2].y()),meaning(skeleton,verticesNew,vertices[iter->v2].y(),vertices[iter->v2].z()));

						glNormal3f(normals[iter->n3].x(),normals[iter->n3].y(),normals[iter->n3].z());
						// glVertexAttrib2f(shaderTexCoord, texCoords[iter->t3].x(),texCoords[iter->t3].y());
						glVertex3f(vertices[iter->v3].x(),meaning(skeleton,verticesNew,vertices[iter->v3].y()),meaning(skeleton,verticesNew,vertices[iter->v3].y(),vertices[iter->v3].z()));
						//			 glNormal3f(normals[iter->n1].x(),normals[iter->n1].y()+skeleton[i*2].y-newLineCoordinates[i*2].y,normals[iter->n1].z());*/
					}


				}
				glEnd();

				glPopMatrix();
				glEndList();
			
				glNewList(dispListI+8,GL_COMPILE);  
				objLoader.setFilename(cylinder2);
			if(objLoader.loadObj())
			{
			//	objLoader.createDisplayList(1,0);
				std::vector<QVector3D> vertices = objLoader.getVertices();
				std::vector<QVector3D> normals = objLoader.getNormals();
				std::vector<QVector2D> texCoords = objLoader.getTexCoords();
				std::vector<Triangle> faces =objLoader.getFaces();
				std::vector<QVector3D> skeleton = objLoader.getSkeleton();

				std::vector<QVector3D> verticesNew=skeleton;
				//verticesNew[0].setY(verticesNew[0].y()+shift);
				verticesNew[1].setY(verticesNew[1].y()+2*shift);
				verticesNew[2].setY(verticesNew[2].y()+2*shift);
				verticesNew[3].setY(verticesNew[3].y()+shift);
				verticesNew[4].setY(verticesNew[4].y());
				verticesNew[5].setY(verticesNew[5].y());

				//verticesNew[0].setZ(verticesNew[0].z()+shift);
				verticesNew[1].setZ(verticesNew[1].z()+2*shift);
				verticesNew[2].setZ(verticesNew[2].z()+2*shift);
				verticesNew[3].setZ(verticesNew[3].z()+shift);
				verticesNew[4].setZ(verticesNew[4].z());
				verticesNew[5].setZ(verticesNew[5].z());
				
				std::vector<double> abs;
				abs.clear();

				glPushMatrix();
				glBegin(GL_TRIANGLES);

				std::vector<QVector3D> newLineCoordinates;
				for(std::vector<Triangle>::const_iterator iter = faces.cbegin(); iter!=faces.cend();iter++)
				{

					
					int ytemp = vertices[iter->v1].y();
					
						glNormal3f(normals[iter->n1].x(),normals[iter->n1].y(),normals[iter->n1].z());
						//glVertexAttrib2f(shaderTexCoord, texCoords[iter->t1].x(),texCoords[iter->t1].y());
						glVertex3f(vertices[iter->v1].x(),meaning(skeleton,verticesNew,vertices[iter->v1].y()),meaning(skeleton,verticesNew,vertices[iter->v1].y(),vertices[iter->v1].z()));

						glNormal3f(normals[iter->n2].x(),normals[iter->n2].y(),normals[iter->n2].z());
						//glVertexAttrib2f(shaderTexCoord, texCoords[iter->t2].x(),texCoords[iter->t2].y());
						glVertex3f(vertices[iter->v2].x(),meaning(skeleton,verticesNew,vertices[iter->v2].y()),meaning(skeleton,verticesNew,vertices[iter->v2].y(),vertices[iter->v2].z()));

						glNormal3f(normals[iter->n3].x(),normals[iter->n3].y(),normals[iter->n3].z());
						// glVertexAttrib2f(shaderTexCoord, texCoords[iter->t3].x(),texCoords[iter->t3].y());
						glVertex3f(vertices[iter->v3].x(),meaning(skeleton,verticesNew,vertices[iter->v3].y()),meaning(skeleton,verticesNew,vertices[iter->v3].y(),vertices[iter->v3].z()));
						//			 glNormal3f(normals[iter->n1].x(),normals[iter->n1].y()+skeleton[i*2].y-newLineCoordinates[i*2].y,normals[iter->n1].z());*/
					}


				}
				glEnd();

				glPopMatrix();
				glEndList();
			}
			//glCallList(dispListIndex);
			//glCallList(1);
		
	};

	double meaning(std::vector<QVector3D> skeleton,std::vector<QVector3D> verticesNew,float ytemp)
	{
		double newY = 0;
		int i=-1;
					//double sk0 = (skeleton[0].y());
					double sk1 = (skeleton[1].y());
					double sk2 = (skeleton[2].y());
					double sk3 = (skeleton[3].y());
					double sk4 = (skeleton[4].y());
					double sk5 = (skeleton[5].y());
					
					if (ytemp>=sk1 && ytemp<sk2)
						i=1;
					if (ytemp>=sk2 && ytemp<sk3 )
						i=2;
					if (ytemp>=sk3 && ytemp<sk4 )
						i=3;
					if (ytemp>=sk4 && ytemp<sk5 )
						i=4;
					if (i!=-1)
					{
						if (skeleton[i].y()==verticesNew[i].y())
							return ytemp;
						double _y1 = skeleton[i].y();
						double _y2 = skeleton[i+1].y();

						double _y11 = verticesNew[i].y();
						double _y21 = verticesNew[i+1].y();

						double dy = _y2-_y1;

						double yofPoint = (_y2-ytemp)/dy;
						double dy1 = (_y21 - _y11)*yofPoint;
						double Ynew = _y21 -dy1;

						newY = Ynew;
					}

					return newY; 
	
	 };

	double meaning(std::vector<QVector3D> skeleton,std::vector<QVector3D> verticesNew,float ytemp,float ztemp)
	{
		double newY = 0;
		int i=-1;
					//double sk0 = (skeleton[0].y());
					double sk1 = (skeleton[1].y());
					double sk2 = (skeleton[2].y());
					double sk3 = (skeleton[3].y());
					double sk4 = (skeleton[4].y());
					double sk5 = (skeleton[5].y());
					
					if (ytemp>=sk1 && ytemp<sk2)
						i=1;
					if (ytemp>=sk2 && ytemp<sk3 )
						i=2;
					if (ytemp>=sk3 && ytemp<sk4 )
						i=3;
					if (ytemp>=sk4 && ytemp<sk5 )
						i=4;
					if (i!=-1)
					{
						double _y1 = skeleton[i].z();
						double _y2 = skeleton[i+1].z();

						double _y11 = verticesNew[i].z();
						double _y21 = verticesNew[i+1].z();

						double dy = _y2-_y1;

						double yofPoint = (_y2-ztemp)/dy;
						double dy1 = (_y21 - _y11)*yofPoint;
						double Ynew = _y21 -dy1;

						newY = Ynew;
					}

					return newY; 
	
	 };
	
	virtual void keyPressEvent(QKeyEvent* e, Viewer& v) {
		if (e->key()==Qt::Key_W)
			keyWPress();
		else if (e->key()==Qt::Key_Space)
		{
			if (f){
				speed = 3;
				fall = true;
			}
			f=!f;
		}
		else if (e->key()==Qt::Key_A)
			keyAPress();
		else if (e->key()==Qt::Key_S)
			keySPress();
		else if (e->key()==Qt::Key_Plus)			
		{
			if (angleChange<0.5)
				angleChange*=1.1;

		}

		else if (e->key()==Qt::Key_R)
		{
			r=!r;
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




};

#endif // TEMPORARYDRAGON

