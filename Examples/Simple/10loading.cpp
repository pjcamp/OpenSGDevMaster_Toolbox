// OpenSG Tutorial Example: Loading
//
// This example shows how to load a scene file using OpenSG.
// The supported formats right now are VRML97, OBJ, OFF and RAW, so just
// calling this program with a scene file as a parameter should load the scene
// file.
//

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGContainerPtrFuncs.h>
//#include <OSGFCFileType.h>

#include <OSGAction.h>

#include <OSGFCFileHandler.h>
// New Headers

// the general scene file loading handler
#include <OSGSceneFileHandler.h>
#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGAction.h>

// New Headers

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>
#endif

#include <boost/bind.hpp>

// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManager *mgr;
OSG::NodeRefPtr scene;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );
OSG::NodeRecPtr findRoot(OSG::FCFileType::FCPtrStore container);

#ifdef OSG_BUILD_ACTIVE
// helper class to find a named node
// names are handled as simple attachments, get the header for that
#include <OSGNameAttachment.h>
#else
// helper class to find a named node
// names are handled as simple attachments, get the header for that
#include <OpenSG/OSGNameAttachment.h>
#endif

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
	// load necessary libs for reading files
	OSG::preloadSharedObject("OSGFileIO");
    OSG::preloadSharedObject("OSGImageFileIO");
    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // load the scene
    
        if(argc < 2)
        {
            FWARNING(("No file given!\n"));
            FWARNING(("Supported file formats:\n"));
    
            std::list<const char*> suffixes;
            OSG::SceneFileHandler::the()->getSuffixList(suffixes);
    
            for(std::list<const char*>::iterator it  = suffixes.begin();
                                                it != suffixes.end();
                                            ++it)
            {
                FWARNING(("%s\n", *it));
            }
    
            scene = OSG::makeTorus(.5, 2, 16, 16);
        }
        else
        {
            /*
                All scene file loading is handled via the SceneFileHandler.
            */
            //scene = OSG::SceneFileHandler::the()->read(argv[1]);
			  //Read FieldContainers from an XML file
			OSG::FCFileType::FCPtrStore NewContainers;
			NewContainers = OSG::FCFileHandler::the()->read(boost::filesystem::path(argv[1]));
			OSG::commitChanges();
			scene = findRoot(NewContainers);

			if(scene == NULL)
			{
				std::cout << "File " << argv[1] << " not found, or file was invalid." << std::endl;
				scene = OSG::makeTorus(.5, 2, 16, 16);
			}
        }

        OSG::commitChanges();
    

		
		// create the SimpleSceneManager helper
		mgr = new OSG::SimpleSceneManager;
    
		// tell the manager what to manage
		mgr->setWindow(gwin );
		mgr->setRoot  (scene);
		mgr->setHeadlight(true);
		mgr->setStatistics(true);
		//mgr->getRenderAction()->setVolumeDrawing(true);

		// show the whole scene
		mgr->showAll();
		
		OSG::FCFileType::FCPtrStore Containers;
		Containers.insert(scene);
		//Use an empty Ignore types vector
		OSG::FCFileType::FCTypeVector IgnoreTypes;
		//IgnoreTypes.push_back(Node::getClassType().getId());
	    
		//Write the Field Containers to a xml file
		OSG::FCFileHandler::the()->write(Containers,OSG::BoostPath("C:/Users/danielg/Desktop/10TestOut.xml"),IgnoreTypes);
		
    }

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
    mgr->idle();
    mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{

    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);

    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{

    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
        case 27:
        {
            // clean up global variables
            delete mgr;
            
            OSG::osgExit();
            exit(0);
        }
        break;

        case 'f':
        {
            mgr->setNavigationMode(OSG::Navigator::FLY);
        }
        break;

        case 't':
        {
            mgr->setNavigationMode(OSG::Navigator::TRACKBALL);
        }
        break;

    case 's':
       {
          mgr->setStatistics(!mgr->getStatistics());
       }
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}

OSG::NodeRecPtr findRoot(OSG::FCFileType::FCPtrStore container)
{
	// just iterating through the container and finding a node without a parent
	for(OSG::FCFileType::FCPtrStore::iterator it = container.begin(); it != container.end(); it++)
	{
		OSG::Node *cur = OSG::dynamic_pointer_cast<OSG::Node>((*it));
		if(cur != NULL)
		{
			if(cur->getParent() == NULL) return cur;
		}
	}

	return NULL;
}
