//#include "dragon.h"
//#include "geometryprimitives.h"
//#include "objectloader.h"
//#include "glCheck.h"

//Dragon::Dragon()
//{
//#ifdef USE_VBO
//    initVBOs();
//#else
//    initDispLists();
//#endif
//}

//void Dragon::init(Viewer& v)
//{
//}


//void Dragon::initDispLists()
//{
//    dispListIndex = glGenLists(8);

//    ObjectLoader objLoader(bodyObj);
//    if(objLoader.loadObj())
//    {
//        objLoader.createDisplayList(dispListIndex + BODY);
//    }

//    objLoader.setFilename(leftWingObj);
//    if(objLoader.loadObj())
//    {
//        objLoader.createDisplayList(dispListIndex + LEFTWING);
//    }

//    objLoader.setFilename(rightWingObj);
//    if(objLoader.loadObj())
//    {
//        objLoader.createDisplayList(dispListIndex + RIGHTWING);
//    }

//    objLoader.setFilename(leftFrontLegObj);
//    if(objLoader.loadObj())
//    {
//        objLoader.createDisplayList(dispListIndex + LEFTFRONTLEG);
//    }

//    objLoader.setFilename(rightFrontLegObj);
//    if(objLoader.loadObj())
//    {
//        objLoader.createDisplayList(dispListIndex + RIGHTFRONTLEG);
//    }

//    objLoader.setFilename(leftBackLegObj);
//    if(objLoader.loadObj())
//    {
//        objLoader.createDisplayList(dispListIndex + LEFTBACKLEG);
//    }

//    objLoader.setFilename(rightBackLegObj);
//    if(objLoader.loadObj())
//    {
//        objLoader.createDisplayList(dispListIndex + RIGHTBACKLEG);
//    }
//}

//void Dragon::initVBOs()
//{
//    glGenBuffers(8,&vertVBOIndex);
//    glGenBuffers(8,&normVBOIndex);
//    glGenBuffers(8,&texVBOIndex);

//    numVBOitems.reserve(8);

//    ObjectLoader objLoader(bodyObj);

//    if(objLoader.loadObj())
//    {
//        numVBOitems[BODY] = objLoader.createVBO(vertVBOIndex + BODY,vertVBOIndex + BODY,vertVBOIndex + BODY);
//    }

//    objLoader.setFilename(leftWingObj);
//    if(objLoader.loadObj())
//    {
//        numVBOitems[LEFTWING] = objLoader.createVBO(vertVBOIndex + LEFTWING,vertVBOIndex + LEFTWING,vertVBOIndex + LEFTWING);
//    }

//    objLoader.setFilename(rightWingObj);
//    if(objLoader.loadObj())
//    {
//        numVBOitems[RIGHTWING] = objLoader.createVBO(vertVBOIndex + RIGHTWING,vertVBOIndex + RIGHTWING,vertVBOIndex + RIGHTWING);
//    }

//    objLoader.setFilename(leftFrontLegObj);
//    if(objLoader.loadObj())
//    {
//        numVBOitems[LEFTFRONTLEG] = objLoader.createVBO(vertVBOIndex + LEFTFRONTLEG,vertVBOIndex + LEFTFRONTLEG,vertVBOIndex + LEFTWING);
//    }

//    objLoader.setFilename(rightFrontLegObj);
//    if(objLoader.loadObj())
//    {
//        numVBOitems[RIGHTFRONTLEG] = objLoader.createVBO(vertVBOIndex + RIGHTFRONTLEG,vertVBOIndex + RIGHTFRONTLEG,vertVBOIndex + RIGHTFRONTLEG);
//    }

//    objLoader.setFilename(leftBackLegObj);
//    if(objLoader.loadObj())
//    {
//        numVBOitems[LEFTBACKLEG] = objLoader.createVBO(vertVBOIndex + LEFTBACKLEG,vertVBOIndex + LEFTBACKLEG,vertVBOIndex + LEFTBACKLEG);
//    }

//    objLoader.setFilename(rightBackLegObj);
//    if(objLoader.loadObj())
//    {
//        numVBOitems[RIGHTBACKLEG] = objLoader.createVBO(vertVBOIndex + RIGHTBACKLEG,vertVBOIndex + RIGHTBACKLEG,vertVBOIndex + RIGHTBACKLEG);
//    }
//}

//Dragon::~Dragon()
//{
//}

//// inherited from Renderable, should be edited
//void Dragon::draw()
//{
//#ifdef USE_VBO
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_NORMAL_ARRAY);
//    //    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

//    glDrawArrays(GL_TRIANGLES , 0, numVBO);

//    glDisableClientState(GL_COLOR_ARRAY);
//    glDisableClientState(GL_NORMAL_ARRAY);
////    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//#else
//    for(size_t i =0;i<8;i++)
//    {
//        glPushMatrix();
//        glRotatef(0,0,1,0);
//            glCallList(this->dispListIndex + i);
//        glPopMatrix();
//    }
//#endif

//}

//// inherited from Renderable, should be edited
//void Dragon::animate()
//{

//}


//// inherited from Renderable, should be edited
//void Dragon::keyPressEvent(QKeyEvent*, Viewer&)
//{
//}


//// inherited from Renderable, should be edited
//void Dragon::mouseMoveEvent(QMouseEvent*, Viewer&)
//{
//}
