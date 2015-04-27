#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include "triangle.h"
#include "SkeletonCoordinates.h"

#include <vector>
#include <string>
#include <QVector3D>
#include <QVector2D>

#ifdef WIN32
#include <glew.h>
#include <glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

class ObjectLoader
{
private:
    std::vector<QVector3D> vertices;
    std::vector<QVector3D> normals;
    std::vector<QVector2D> texCoords;
    std::vector<Triangle> faces;
	std::vector<QVector3D> skeleton;
    std::string filename;
public:

    ObjectLoader();
    ObjectLoader(const std::string& filename);
    void setFilename(const std::string& filename);
    bool loadObj();

    void createDisplayList(GLuint index, GLint shaderTexCoord);
	void ObjectLoader::createDisplayListAnilam(GLuint index, GLint shaderTexCoord, std::vector<QVector3D> vertices,std::vector<QVector3D> normals,std::vector<QVector2D> texCoords,std::vector<Triangle> faces );


    unsigned int createVBO(GLuint verticesBO, GLuint normalsBO, GLuint textCoordsBO);

    const std::vector<Triangle>& getFaces() const;
    const std::vector<QVector3D>& getVertices() const;
    const std::vector<QVector3D>& getNormals() const;
    const std::vector<QVector2D>& getTexCoords() const;
	const std::vector<QVector3D>& getSkeleton() const;
	

    ~ObjectLoader();
};


#endif // OBJECTLOADER_H
