// OpenSG Tutorial Example: Materials
//
// This example shows how to create a material. Materials define the surface
// properties of the geometry, and change how they look.
//
// This example shows the usage of SimpleMaterial and SimpleTexturedMaterial.
// Call it with an image filename as a parameter.
//

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGFCFileHandler.h>
#include <OSGCgFXMaterial.h>
#include <OSGSceneFileHandler.h>
// new headers: 

// the headers for the SimpleMaterials
#include <OSGSimpleMaterial.h>
#include <OSGSimpleTexturedMaterial.h>
#include <OSGImage.h>
#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>

// new headers: 

// the headers for the SimpleMaterials
#include <OpenSG/OSGCgFXMaterial.h>
#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGImage.h>
#endif

// a separate transformation for every object
OSG::TransformRefPtr cyltrans, tortrans;


// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT(int *argc, char *argv[]);

// redraw the window
void display(void)
{    
    mgr->redraw();
}


// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
	OSG::preloadSharedObject("OSGFileIO");
	OSG::preloadSharedObject("OSGTBFileIO");
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
    
        // create the scene
        
        // create a pretty simple graph: a Group with two Transforms as children,
        // each of which carries a single Geometry.
        
        // The scene group
        
        OSG::NodeRefPtr  scene = OSG::Node::create();
        OSG::GroupRefPtr g     = OSG::Group::create();
        
        scene->setCore(g);
        
        // The cylinder and its transformation
        OSG::NodeRefPtr     cyl    = OSG::Node::create();
        OSG::GeometryRefPtr cylgeo = OSG::makeCylinderGeo( 1.4f, .3f, 64, 
                                                           true, true, true );
        
        cyl->setCore(cylgeo);
    
        cyltrans = OSG::Transform::create();
    
        OSG::NodeRefPtr cyltransnode = OSG::Node::create();
        cyltransnode->setCore (cyltrans);
        cyltransnode->addChild(cyl     );
        
        // add it to the scene
        scene->addChild(cyltransnode);
        
        // The torus and its transformation
        OSG::NodeRefPtr     torus    = OSG::Node::create();
        OSG::GeometryRefPtr torusgeo = OSG::makeTorusGeo( .2f, 1, 32, 64 );
        
        torus->setCore(torusgeo);
            
        tortrans = OSG::Transform::create();
    
        OSG::NodeRefPtr tortransnode = OSG::Node::create();
        tortransnode->setCore (tortrans);
        tortransnode->addChild(torus   );
        
        // add it to the scene
        scene->addChild(tortransnode);
    
        // create the materials: Here, just using cgfx materials.
        OSG::CgFXMaterialRefPtr mat1 = OSG::CgFXMaterial::create();
        if(argc > 1)
        {
        	mat1->setEffectFile(argv[1]);
        }
        
    
        // assign the material to the geometry
        cylgeo->setMaterial(mat1);
        
        // assign the material to the geometry
        torusgeo->setMaterial(mat1);
    
        OSG::commitChanges();
    
        // create the SimpleSceneManager helper
        mgr = new OSG::SimpleSceneManager;
    
        // tell the manager what to manage
        mgr->setWindow(gwin );
        
    

        
        // file io
		OSG::FCFileType::FCPtrStore Containers;
		Containers.insert(scene);
		//Use an empty Ignore types vector
		OSG::FCFileType::FCTypeVector IgnoreTypes;
		//IgnoreTypes.push_back(Node::getClassType().getId());
	    
		//Write the Field Containers to a xml file
		OSG::FCFileHandler::the()->write(Containers,OSG::BoostPath("C:/Users/danielg/Desktop/test.xml"),IgnoreTypes);

        //Read FieldContainers from an XML file
        OSG::FCFileType::FCPtrStore NewContainers;
        NewContainers = OSG::FCFileHandler::the()->read(OSG::BoostPath("C://Users//danielg//Documents//VirtualCellData//trunk//Artwork//Models//Vehicles_and_Tools//Protein_Ship//Ship_Export_Test.dae"));

        //Write the read FieldContainers to an XML file
       // OSG::FCFileHandler::the()->write(NewContainers,OSG::BoostPath("C:/Users/danielg/Desktop/test2.xml"),IgnoreTypes);

		//NewContainers.clear();

		// NewContainers = OSG::FCFileHandler::the()->read(OSG::BoostPath("C:/Users/danielg/Desktop/test2.xml"));

		OSG::FCFileType::FCPtrStore::iterator itor = NewContainers.begin();
		OSG::FCFileType::FCPtrStore::iterator endIt = NewContainers.end();
		OSG::NodeRefPtr root;
		for(; itor != endIt; itor++)
		{
			OSG::Node *cur = OSG::dynamic_pointer_cast<OSG::Node>((*itor));
			if(cur != NULL)
			{
				if(cur->getParent() == NULL) 
				{
					root = cur; //mgr->setRoot(cur);
					break;
				}
			}
		}

		std::string filepath("C://Users//danielg//Desktop//test.osb");
		OSG::SceneFileHandler::the()->write(root,filepath.c_str());

		root = OSG::SceneFileHandler::the()->read(filepath.c_str());

		if(root != NULL)
		{
			mgr->setRoot(root);
		} else
		{
			std::cout << std::endl << "ERROR READING THE OSB FILE BACK IN~~~~!" << std::endl;
		}

		// show the whole scene
        mgr->showAll();
    }

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

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
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:    
        {
            // clean up global variables
            cyltrans = NULL;
            tortrans = NULL;
            delete mgr;
        
            OSG::osgExit();
            exit(0);
        }
        break;

        case 's':
        {
            mgr->setStatistics(!mgr->getStatistics());
        }
        break;
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
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return winid;
}
