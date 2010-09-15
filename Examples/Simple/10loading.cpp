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
#include <OSGTravMaskGraphOp.h>
#include <OSGLODSetupGraphOp.h>
#include "OSGFieldAnimation.h"
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
// Input
#include "OSGWindowUtils.h"
#include "OSGWindowEventProducer.h"

OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
NodeRefPtr scene;


// forward declaration so we can have the interesting stuff upfront
//int setupGLUT( int *argc, char *argv[] );
NodeRecPtr findRoot(FCFileType::FCPtrStore container);
void initializeAnimations(FCFileType::FCPtrStore container, WindowEventProducerRecPtr win );


void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);


void mousePressed(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
	mgr->mouseButtonPress(details->getButton(), details->getLocation().x(), details->getLocation().y());
}
void mouseReleased(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
	mgr->mouseButtonRelease(details->getButton(), details->getLocation().x(), details->getLocation().y());
}

void mouseMoved(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
	mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
}

void mouseDragged(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
	mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
	// load necessary libs for reading files
	preloadSharedObject("OSGFileIO");
	preloadSharedObject("OSGTBFileIO");
    preloadSharedObject("OSGImageFileIO");
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    //int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
		FCFileType::FCPtrStore NewContainers;
        // the connection between GLUT and OpenSG
        /*GLUTWindowRefPtr gwin = GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();*/
    
		// Set up Window
		WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
		TutorialWindow->setUseCallbackForDraw(true);
		TutorialWindow->setUseCallbackForReshape(true);

		//Initialize Window
		TutorialWindow->initWindow();

		// create the SimpleSceneManager helper
		mgr = new SimpleSceneManager;

		TutorialWindow->setDisplayCallback(boost::bind(display, mgr));
		TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, mgr));

		//Attach to events
		TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, mgr));
		TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, mgr));
		TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, mgr));
		TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, mgr));

        // load the scene
    
        if(argc < 2)
        {
            FWARNING(("No file given!\n"));
            FWARNING(("Supported file formats:\n"));
    
            std::list<const char*> suffixes;
            SceneFileHandler::the()->getSuffixList(suffixes);
    
            for(std::list<const char*>::iterator it  = suffixes.begin();
                                                it != suffixes.end();
                                            ++it)
            {
                FWARNING(("%s\n", *it));
            }
    
            scene = makeTorus(.5, 2, 16, 16);
        }
        else
        {
            /*
                All scene file loading is handled via the SceneFileHandler.
            */
            //scene = SceneFileHandler::the()->read(argv[1]);
			  //Read FieldContainers from an XML file
			
			NewContainers = FCFileHandler::the()->read(boost::filesystem::path(argv[1]));
			commitChanges();
			scene = findRoot(NewContainers);
			initializeAnimations(NewContainers,TutorialWindow);

			if(scene == NULL)
			{
				std::cout << "File " << argv[1] << " not found, or file was invalid." << std::endl;
				scene = makeTorus(.5, 2, 16, 16);
			}
        }

        commitChanges();
    

		//TravMaskGraphOpRefPtr colMeshGrOp = TravMaskGraphOp::create();
		//colMeshGrOp->setSearchString("_Col");
		// default values for this graph op will do fine.
		//bool result = colMeshGrOp->traverse(scene);
		//colMeshGrOp->setSearchString("_Mid");
		// result = colMeshGrOp->traverse(scene);
		//colMeshGrOp->setSearchString("_Low");
		// result = colMeshGrOp->traverse(scene);
		//std::cout << "Number of nodes hidden: " << colMeshGrOp->getNumChanged() << std::endl;

		/*LODSetupGraphOpRefPtr LODSetupGrOp = LODSetupGraphOp::create();
		LODSetupGrOp->addLODInfo(0,20.0f,"_High");
		LODSetupGrOp->addLODInfo(1,50.0f,"_Mid");
		LODSetupGrOp->addLODInfo(3,100.0f,"_Low");

		result = LODSetupGrOp->traverse(scene);

		std::cout << "Number of LOD nodes set up: " << LODSetupGrOp->getNumLODSMade() << std::endl;*/

		// tell the manager what to manage
		mgr->setWindow(TutorialWindow );
		mgr->setRoot  (scene);
		mgr->setHeadlight(true);
		mgr->setStatistics(true);
		mgr->getCamera()->setNear(1.0f);
		mgr->getCamera()->setFar(1000.0f);
		//mgr->getRenderAction()->setVolumeDrawing(true);

		// show the whole scene
		mgr->showAll();
		
		FCFileType::FCPtrStore Containers;
		Containers.insert(scene);
		//Use an empty Ignore types vector
		FCFileType::FCTypeVector IgnoreTypes;
		//IgnoreTypes.push_back(Node::getClassType().getId()); 
	    
		//Write the Field Containers to a xml file
		FCFileHandler::the()->write(Containers,BoostPath("C:/Users/danielg/Desktop/10TestOut.xml"),IgnoreTypes);
		
		Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
		Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
		TutorialWindow->openWindow(WinPos,
			WinSize,
			"OpenSG 01Animation Window");

		//Enter main Loop
		TutorialWindow->mainLoop();
    }

	osgExit();

    return 0;
}


// Redraw the window
void display(SimpleSceneManager *mgr)
{
	mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
	mgr->resize(Size.x(), Size.y());
}

// react to mouse button presses
//void mouse(int button, int state, int x, int y)
//{
//
//    if (state)
//        mgr->mouseButtonRelease(button, x, y);
//    else
//        mgr->mouseButtonPress(button, x, y);
//
//    glutPostRedisplay();
//}
//
//// react to mouse motions with pressed buttons
//void motion(int x, int y)
//{
//
//    mgr->mouseMove(x, y);
//    glutPostRedisplay();
//}
//
//// react to keys
//void keyboard(unsigned char k, int , int )
//{
//    switch(k)
//    {
//        case 27:
//        {
//            // clean up global variables
//            delete mgr;
//            
//            osgExit();
//            exit(0);
//        }
//        break;
//
//        case 'f':
//        {
//            mgr->setNavigationMode(Navigator::FLY);
//        }
//        break;
//
//        case 't':
//        {
//            mgr->setNavigationMode(Navigator::TRACKBALL);
//        }
//        break;
//
//    case 's':
//       {
//          mgr->setStatistics(!mgr->getStatistics());
//       }
//    }
//}
//
//// setup the GLUT library which handles the windows for us
//int setupGLUT(int *argc, char *argv[])
//{
//    glutInit(argc, argv);
//    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
//
//    int winid = glutCreateWindow("OpenSG");
//
//    glutReshapeFunc(reshape);
//    glutDisplayFunc(display);
//    glutIdleFunc(display);
//    glutMouseFunc(mouse);
//    glutMotionFunc(motion);
//    glutKeyboardFunc(keyboard);
//
//    return winid;
//}

NodeRecPtr findRoot(FCFileType::FCPtrStore container)
{
	// just iterating through the container and finding a node without a parent
	for(FCFileType::FCPtrStore::iterator it = container.begin(); it != container.end(); it++)
	{
		Node *cur = dynamic_pointer_cast<Node>((*it));
		if(cur != NULL)
		{
			if(cur->getParent() == NULL) return cur;
		}
	}

	return NULL;
}

void initializeAnimations(FCFileType::FCPtrStore container, WindowEventProducerRecPtr win )
{
	// just iterating through the container and finding a node without a parent
	for(FCFileType::FCPtrStore::iterator it = container.begin(); it != container.end(); it++)
	{
		FieldAnimation * anim = dynamic_pointer_cast<FieldAnimation>((*it));
		if(anim != NULL)
		{
			anim->attachUpdateProducer(win);
			anim->start();
		}
	}
}
