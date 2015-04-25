#include "glCheck.h"
#include "viewer.h"
#include "lightsMaterials.h"
#include "geometryprimitives.h"
#include "textures.h"
#include "dragon.h"
#include "skybox.h"
#include "temporarydragon.h"

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
//    viewer.addRenderable(new Textures());
    //viewer.addRenderable(new Cube());
    viewer.addRenderable(new Skybox());
    //viewer.addRenderable(new LightsMaterials());

    viewer.addRenderable(new TemporaryDragon());

    // Make the viewer window visible on screen.
    viewer.show(); // this function will create the GL context

    //viewer.addRenderable(new Dragon());

    // Run main loop.
    return application.exec();
}
