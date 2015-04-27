#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include "triangle.h"

#include <vector>
#include <string>
#include <QVector3D>
#include <QVector2D>

#include <GL/glew.h>
#include <GL/glut.h>

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

    unsigned int createVBO(GLuint verticesBO, GLuint normalsBO, GLuint textCoordsBO);

    const std::vector<Triangle>& getFaces() const;
    const std::vector<QVector3D>& getVertices() const;
    const std::vector<QVector3D>& getNormals() const;
    const std::vector<QVector2D>& getTexCoords() const;
    const std::vector<QVector3D>& getSkeleton() const;


    ~ObjectLoader();
};


#endif // OBJECTLOADER_H
