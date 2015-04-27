#include "objectloader.h"
#include "skeletoncoordinates.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


ObjectLoader::ObjectLoader() : filename("")
{  }

ObjectLoader::ObjectLoader(const std::string& filename) : filename(filename)
{  }

const std::vector<Triangle>& ObjectLoader::getFaces() const
{
    return faces;
}

const std::vector<QVector3D>& ObjectLoader::getVertices() const
{
    return vertices;
}



const std::vector<QVector3D>& ObjectLoader::getNormals() const
{
    return normals;
}

const std::vector<QVector2D>& ObjectLoader::getTexCoords() const
{
    return texCoords;
}

const std::vector<QVector3D>& ObjectLoader::getSkeleton() const
{
	return skeleton;
}

void ObjectLoader::setFilename(const std::string& filename)
{
    this->filename = filename;
}

bool ObjectLoader::loadObj()
{
    if(filename.empty())
    {
        std::cout << "Invalid filename!" << std::endl;
        return false;
    }

    std::ifstream file(filename);

    if(!file.is_open())
    {
        std::cout << "File does not exist!" << std::endl;
        return false;
    }

    //Clear vectors
    vertices.clear();
    normals.clear();
    texCoords.clear();
    faces.clear();
	skeleton.clear();

    // Indices of vertices in obj file starts with 1, not zero
    vertices.push_back(QVector3D());
    normals.push_back(QVector3D());
    texCoords.push_back(QVector2D());
	skeleton.push_back(QVector3D());

    while (!file.fail())
    {
        std::string line_type;
        file >> line_type;

        if (line_type == "v")
        {
            QVector3D vertex;
            float number = 0;
            file >> number;
            vertex.setX(number);
            file >> number;
            vertex.setY(number);
            file >> number;
            vertex.setZ(number);
            vertices.push_back(vertex);
        }
        else if (line_type == "vn")
        {
            QVector3D normal;
            float number = 0;
            file >> number;
            normal.setX(number);
            file >> number;
            normal.setY(number);
            file >> number;
            normal.setZ(number);
            normals.push_back(normal);
        }
        else if (line_type == "vt")
        {
            QVector2D tex_coord;
            float number = 0;
            file >> number;
            tex_coord.setX(number);
            file >> number;
            tex_coord.setY(number);
            texCoords.push_back(tex_coord);
        }
        else if (line_type == "f")
        {
            //Presuming all faces are triangles
            Triangle triangle;
            char slash;

            file >> triangle.v1 >> slash >> triangle.t1 >> slash >> triangle.n1;
            file >> triangle.v2 >> slash >> triangle.t2 >> slash >> triangle.n2;
            file >> triangle.v3 >> slash >> triangle.t3 >> slash >> triangle.n3;

            faces.push_back(triangle);
        }

		else if (line_type =="k")
		{	
			QVector3D vertex;
            float number = 0;
            file >> number;
            vertex.setX(number);
            file >> number;
            vertex.setY(number);
            file >> number;
            vertex.setZ(number);
			skeleton.push_back(vertex);
		}
        else
        {
            // Nothing here
        }

        // Ignore the rest of the line
        file.ignore(100000, '\n');
    }
    file.close();

    return true;
}

void ObjectLoader::createDisplayList(GLuint index, GLint shaderTexCoord)
{
    if(vertices.empty() || normals.empty() || texCoords.empty())
    {
        std::cerr << "Cannot create display list - first need to load vertices, normals and textures!" << std::endl;
    }

    glNewList(index,GL_COMPILE);

    glPushMatrix();

    glBegin(GL_TRIANGLES);

    for(std::vector<Triangle>::const_iterator iter = faces.cbegin(); iter!=faces.cend();iter++)
    {
        glNormal3f(normals[iter->n1].x(),normals[iter->n1].y(),normals[iter->n1].z());
       // glVertexAttrib2f(shaderTexCoord, texCoords[iter->t1].x(),texCoords[iter->t1].y());
        glVertex3f(vertices[iter->v1].x(),vertices[iter->v1].y(),vertices[iter->v1].z());

        glNormal3f(normals[iter->n2].x(),normals[iter->n2].y(),normals[iter->n2].z());
        //glVertexAttrib2f(shaderTexCoord, texCoords[iter->t2].x(),texCoords[iter->t2].y());
        glVertex3f(vertices[iter->v2].x(),vertices[iter->v2].y(),vertices[iter->v2].z());

        glNormal3f(normals[iter->n3].x(),normals[iter->n3].y(),normals[iter->n3].z());
       // glVertexAttrib2f(shaderTexCoord, texCoords[iter->t3].x(),texCoords[iter->t3].y());
        glVertex3f(vertices[iter->v3].x(),vertices[iter->v3].y(),vertices[iter->v3].z());
    }

    glEnd();

    glPopMatrix();
    glEndList();
}


unsigned int ObjectLoader::createVBO(GLuint verticesBO, GLuint normalsBO, GLuint textCoordsBO)
{
    std::vector<GLfloat> verticesBuffer;
    std::vector<GLfloat> normalsBuffer;
    std::vector<GLfloat> texCoordsBuffer;

    for(std::vector<Triangle>::const_iterator iter = faces.cbegin(); iter!=faces.cend();iter++)
    {
        verticesBuffer.push_back(vertices[iter->v1].x());
        verticesBuffer.push_back(vertices[iter->v1].y());
        verticesBuffer.push_back(vertices[iter->v1].z());

        verticesBuffer.push_back(vertices[iter->v2].x());
        verticesBuffer.push_back(vertices[iter->v2].y());
        verticesBuffer.push_back(vertices[iter->v2].z());

        verticesBuffer.push_back(vertices[iter->v3].x());
        verticesBuffer.push_back(vertices[iter->v3].y());
        verticesBuffer.push_back(vertices[iter->v3].z());

        normalsBuffer.push_back(normals[iter->n1].x());
        normalsBuffer.push_back(normals[iter->n1].y());
        normalsBuffer.push_back(normals[iter->n1].z());

        normalsBuffer.push_back(normals[iter->n2].x());
        normalsBuffer.push_back(normals[iter->n2].y());
        normalsBuffer.push_back(normals[iter->n2].z());

        normalsBuffer.push_back(normals[iter->n3].x());
        normalsBuffer.push_back(normals[iter->n3].y());
        normalsBuffer.push_back(normals[iter->n3].z());

        texCoordsBuffer.push_back(texCoords[iter->t1].x());
        texCoordsBuffer.push_back(texCoords[iter->t1].y());

        texCoordsBuffer.push_back(texCoords[iter->t2].x());
        texCoordsBuffer.push_back(texCoords[iter->t2].y());

        texCoordsBuffer.push_back(texCoords[iter->t3].x());
        texCoordsBuffer.push_back(texCoords[iter->t3].y());

    }

    glBindBuffer(GL_ARRAY_BUFFER, verticesBO);

    glBufferData(GL_ARRAY_BUFFER, verticesBuffer.size()*sizeof(GLfloat), &verticesBuffer[0], GL_STATIC_DRAW);
    glVertexPointer(3,GL_FLOAT,0,0);

    glBindBuffer(GL_ARRAY_BUFFER, normalsBO);

    glBufferData(GL_ARRAY_BUFFER, normalsBuffer.size()*sizeof(GLfloat), &normalsBuffer[0], GL_STATIC_DRAW);
    glNormalPointer(GL_FLOAT,0,0);

    glBindBuffer(GL_ARRAY_BUFFER, textCoordsBO);

    glBufferData(GL_ARRAY_BUFFER, texCoordsBuffer.size()*sizeof(GLfloat), &texCoordsBuffer[0], GL_STATIC_DRAW);
    glTexCoordPointer(2,GL_FLOAT,0,0);

    return faces.size() * 3;
}


ObjectLoader::~ObjectLoader()
{

}

