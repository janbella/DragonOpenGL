#include <QKeyEvent>

#ifndef __APPLE__
#include <GL/glew.h>
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "viewer.h"
#include "renderable.h"

bool _isAnimationStarted;

Viewer::Viewer( const QGLFormat& format )
    : QGLViewer( format )
{
    setAnimationPeriod(100);
}

Viewer::~Viewer()
{
    for (std::list<Renderable *>::iterator it = renderableList.begin(),
         end = renderableList.end(); it != end; ++ it ) {
        delete(*it);
    }
    renderableList.clear();
}

void Viewer::addRenderable(Renderable *r)
{
    renderableList.push_back(r);
}

void Viewer::init()
{
    // glut initialisation (mandatory)
    int dum = 0;
    glutInit(&dum, NULL);

#ifndef __APPLE__
    // glew initialization for extensions
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }
#endif

    //=== VIEWING PARAMETERS
    restoreStateFromFile();   // Restore previous viewer state.

    toogleWireframe = false;  // filled faces
    toogleLight = true;       // light on
    help();                   // display help

    if (toogleLight == true)
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);

    setSceneRadius(1000.0f);
    this->camera()->setFlySpeed(1);


    for (std::list<Renderable *>::iterator it = renderableList.begin(),
         end = renderableList.end(); it != end; ++ it ) {
        (*it)->init(*this);
    }

    glClearColor(0.5, 0.5, 0.5, 1);
    glClearDepth(1);
    GLfloat density = 0.3;
    GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_FOG);
    glFogi (GL_FOG_MODE, GL_EXP2);
    glFogfv (GL_FOG_COLOR, fogColor);
    glFogf (GL_FOG_DENSITY, density);
    glHint (GL_FOG_HINT, GL_NICEST);

}


void Viewer::draw()
{  
    // draw every objects in renderableList
    for (std::list<Renderable *>::iterator it = renderableList.begin(), end = renderableList.end(); it != end; ++ it )
    {
        (*it)->draw();
        if (!_isAnimationStarted)
        {
        startAnimation();
        _isAnimationStarted = true;
        }
    }
}


void Viewer::animate()
{
    // animate every objects in renderableList
    for (std::list<Renderable *>::iterator it = renderableList.begin(),
         end = renderableList.end(); it != end; ++ it )
    {
        (*it)->animate();
    }

    // this code might change if some rendered objets (stored as
    // attributes) need to be specifically updated with common
    // attributes, like real CPU time (?)
}


void Viewer::mouseMoveEvent(QMouseEvent *e)
{
    // all renderables may respond to key events
    for (std::list<Renderable *>::iterator it = renderableList.begin(), end = renderableList.end(); it != end; ++ it )
    {
        (*it)->mouseMoveEvent(e, *this);
    }

    // default QGLViewer behaviour
    QGLViewer::mouseMoveEvent(e);
    updateGL();
}

void Viewer::keyPressEvent(QKeyEvent *e)
{
    // Get event modifiers key
    const Qt::KeyboardModifiers modifiers = e->modifiers();

    // all renderables may respond to key events
    for (std::list<Renderable *>::iterator it = renderableList.begin(), end = renderableList.end(); it != end; ++ it )
    {
        (*it)->keyPressEvent(e, *this);
    }

    if ((e->key()==Qt::Key_W) && (modifiers==Qt::NoButton))
    {
        // events with modifiers: CTRL+W, ALT+W, ... to handle separately
        toogleWireframe = !toogleWireframe;
        if (toogleWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else if ((e->key()==Qt::Key_L) && (modifiers==Qt::NoButton))
    {
        toogleLight = !toogleLight;
        if (toogleLight == true)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);
        // ... and so on with all events to handle here!

    }
    else
    {
        // if the event is not handled here, process it as default
        QGLViewer::keyPressEvent(e);
    }


    updateGL();
}

void Viewer::keyReleaseEvent(QKeyEvent* e, Viewer&)
{
    // Get event modifiers key
    const Qt::KeyboardModifiers modifiers = e->modifiers();

    // all renderables may respond to key events
    for (std::list<Renderable *>::iterator it = renderableList.begin(), end = renderableList.end(); it != end; ++ it )
    {
        (*it)->keyReleaseEvent(e, *this);
    }
}

QString Viewer::helpString() const
{
    // Some usefull hints...
    QString text("<h2>V i e w e r</h2>");
    text += "Use the mouse to move the camera around the object. ";
    text += "You can respectively revolve around, zoom and translate with the three mouse buttons. ";
    text += "Left and middle buttons pressed together rotate around the camera view direction axis<br><br>";
    text += "Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
    text += "Simply press the function key again to restore it. Several keyFrames define a ";
    text += "camera path. Paths are saved when you quit the application and restored at next start.<br><br>";
    text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
    text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. ";
    text += "See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>";
    text += "Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). ";
    text += "A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>";
    text += "A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. ";
    text += "See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>";
    text += "Press <b>Escape</b> to exit the viewer.";
    return text;
}

