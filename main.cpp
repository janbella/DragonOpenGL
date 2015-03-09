# include "glCheck.h"
# include "viewer.h"
# include "lightsMaterials.h"
# include "geometryprimitives.h"

# include <iostream>
# include <qapplication.h>

int main(int argc, char** argv)
{
	// Read command lines arguments.
	QApplication application(argc,argv);

	QGLFormat format;
//	format.setVersion( 2, 1 );
//	format.setProfile( QGLFormat::CompatibilityProfile );

	// Instantiate the viewer.
	Viewer viewer( format );

	// build your scene here
    viewer.addRenderable(new LightsMaterials());
    //viewer.addRenderable(new Torus());
 
	viewer.setWindowTitle("viewer");

	// Make the viewer window visible on screen.
	viewer.show(); // this function will create the GL context

	// Run main loop.
	return application.exec();
}
