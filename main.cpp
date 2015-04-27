#include "glCheck.h"
#include "viewer.h"
#include "geometryprimitives.h"
#include "dragon.h"
#include "skybox.h"
#include "particles.h"
#include "scene.h"
#include "bezier5.h"

#include <iostream>
#include <qapplication.h>

int main(int argc, char** argv)
{
    // Read command lines arguments.
    QApplication application(argc,argv);

    QGLFormat format;
    //	format.setVersion( 2, 1 );
    //	format.setProfile( QGLFormat::CompatibilityProfile );

    // Instantiate the viewer.
    Viewer viewer( format );

    viewer.setWindowTitle("viewer");

    // build your scene here
    viewer.addRenderable(new Skybox());
    viewer.addRenderable(new Dragon());
    viewer.addRenderable(new Scene());
    viewer.addRenderable(new Bezier5(5.0));

    // Make the viewer window visible on screen.
    viewer.show(); // this function will create the GL context

    // Run main loop.
    return application.exec();
}
