// OpenSG example: ClipPlaneCaps
//
// Demonstrates the use of the ClipPlaneChunk, StencilChunk for capping of
// clipped geometry
//
// This examples allows creation of a box and a torus. Additionally, two clip
// planes can be set up. On clipping the geometry caps are used to repair the
// clipped geometry.
//
// User interface:
//  a) mouse => standard navigator
//  b) keyboard =>
//      '1': enable/disable clip plane 0
//      '2': enable/disable clip plane 1
//      '3': enable/disable box geometry
//      '4': enable/disable torus geometry
//      'n': move clip plane 0 opposite to the normal direction of the plane
//      'm': move clip plane 0 in the normal direction of the plane
//      ',': move clip plane 1 opposite to the normal direction of the plane
//      '.': move clip plane 1 in the normal direction of the plane
//      'q': move box in -x direction
//      'w': move box in +x direction
//      'a': move box in -y direction
//      's': move box in +y direction
//      'y': move box in -z direction
//      'x': move box in +z direction
//      'e': move torus in -x direction
//      'r': move torus in +x direction
//      'd': move torus in -y direction
//      'f': move torus in +y direction
//      'c': move torus in -z direction
//      'v': move torus in +z direction
//
// This example was contributed by Johannes Brunen

#include <vector>

#ifdef OSG_BUILD_INTEGRATED

#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>

#include <OSGMultiSwitch.h>
#include <OSGMaterialGroup.h>
#include <OSGGroupingStage.h>
#include <OSGChunkMaterial.h>
#include <OSGSimpleMaterial.h>
#include <OSGClipPlaneChunk.h>
#include <OSGStencilChunk.h>
#include <OSGInverseTransform.h>
#include <OSGPassiveBackground.h>
#include <OSGFieldContainerUtils.h>

#else // OSG_BUILD_INTEGRATED

#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGPassiveWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include <OpenSG/OSGMultiSwitch.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGGroupingStage.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGClipPlaneChunk.h>
#include <OpenSG/OSGStencilChunk.h>
#include <OpenSG/OSGInverseTransform.h>
#include <OpenSG/OSGPassiveBackground.h>
#include <OpenSG/OSGFieldContainerUtils.h>

#endif // OSG_BUILD_INTEGRATED


OSG_USING_NAMESPACE

typedef std::vector<NodeRefPtr> VecNodesT; // convenience type

//
// transport container for the actual clip plane data
//
struct ClipPlaneData
{
    Vec4f _equation;
    bool  _enabled;
};

typedef std::vector<ClipPlaneData> VecClipPlaneData;

//
// for each clip plane these data are necessary
//
struct ClipPlaneDetails
{
    ClipPlaneChunkRefPtr  _clipPlaneChunk;
    GeometryRefPtr        _planeGeometryCore;
    TransformRefPtr       _planeTrafoCore;
    NodeRefPtr            _planeBeaconNode;
    Color3f               _planeColor;
};

typedef std::vector<ClipPlaneDetails> VecClipPlaneDetailsT;

//
// global state
//
VecClipPlaneData      vecClipPlaneData;      // transport clip plane info
VecClipPlaneDetailsT  vecClipPlaneDetails;   // opensg clip plane state
VecNodesT             vecGeometries;         // box and torus

SimpleSceneManager   *mgr;
NodeRefPtr            scene;

//
// the number of clipping planes supported by the demo. Define a plane color
// for each.
//
const int iNumClipPlanes = 2;
Color3f planeCol[iNumClipPlanes] = { Color3f(0,1,0), Color3f(0,0,1) };

//
// Build the global clip plane state
//
void createClipPlaneDetails(void)
{
    for(int i = 0; i < iNumClipPlanes; ++i)
    {
        ClipPlaneDetails details;

        //
        // Create clip plane chunk
        //
        details._planeBeaconNode = Node::create();

        details._clipPlaneChunk = ClipPlaneChunk::create();
        details._clipPlaneChunk->setEquation(Vec4f(1,0,0,0));
        details._clipPlaneChunk->setEnable(false);
        details._clipPlaneChunk->setBeacon(details._planeBeaconNode);


        //
        // Create plane geometry
        //
        details._planeGeometryCore = makePlaneGeo(100.f, 100.f, 128, 128);

        //
        // Create plane transformation core
        //
        Matrix mat;
        mat.setIdentity();

        details._planeTrafoCore = Transform::create();
        details._planeTrafoCore->setMatrix(mat);

        //
        // Define plane color
        //
        details._planeColor = planeCol[i];

        vecClipPlaneDetails.push_back(details);
    }
}

//
// Clean up code
//
void cleanup(void)
{
    vecClipPlaneDetails.clear();
    vecGeometries      .clear();

    delete mgr;
    mgr = NULL;

    scene = NULL;
}

//
// In  case the clip plane data change this function is called
//
void updateClipPlanes(const VecClipPlaneData& vec)
{
    int sz  = vec.size();

    for(int i = 0; i < iNumClipPlanes; ++i)
    {
        ClipPlaneChunk *clipPlaneChunk = vecClipPlaneDetails[i]._clipPlaneChunk;
        clipPlaneChunk->setEnable(false);

        if(i < sz)
        {
            const ClipPlaneData& data = vec[i];

            //
            // Update the clip plane chunk
            //
            clipPlaneChunk->setEquation(data._equation);
            clipPlaneChunk->setEnable  (data._enabled );

            //
            // and the plane transform core
            //
            Matrix rotMat;
            Vec4f v1(0.f, 0.f, -1.f, 0.f);
            Quaternion q(Vec3f(v1), Vec3f(data._equation));
            rotMat.setTransform(q);

            Matrix mat;
            Vec3f v2(0.0f, 0.0f, data._equation[3]);
            mat.setTranslate(v2);

            mat.multLeft(rotMat);

            vecClipPlaneDetails[i]._planeTrafoCore->setMatrix(mat);
        }
    }
}

//
// build geometry scenegraph Tree
//
//
// We need 3 material groups for the clip plane capping trick:
//
//                        scene
//                          |
//     +--------------------+--------------------+
//     |                    |                    |
//  group1 (mat1)        group2 (mat2)        group3 (mat3)
//     |                    |                    |
// geometry (geo1)      geometry (geo2)      geometry (geo1)
//
//    geo1 : actual geometry to draw
//    geo2 : plane geometry coincident with the clip plane
//
//    mat1 : has a stencil chunk that clears the stencil buffer first, than
//           does the inversion, and has a clip plane chunk that enables one
//           clip plane. Sortkey 0.
//    mat2 : has a stencil chunk and settings for drawing the clip plane
//           geometry. All clip planes but the one coincident with the plane
//           are activated. Sortkey 1.
//    mat3 : the material used for the actual geometry. All clip planes are
//           activated. Sortkey 3.
//
//    For each active clip plane copies of the left two branches need to be
//    added.
//
NodeTransitPtr buildGeoTree(Node *scene, Geometry *geo1, const Matrix& matrix)
{
    // if using a sort key, for each geometry we must ensure that the sortkeys
    // are independent. However, using a StateSortingGroup parent node does
    // make the use of sortkeys not necessary.
    static int k = 0;

    //
    // Parent nodes for the left two branches
    //
    VecNodesT vecMaterialNodes1;
    VecNodesT vecMaterialNodes2;

    for(int i = 0; i < iNumClipPlanes; ++i) // foreach clip plane
    {
        //
        // Branch 1: Imprint the geometry clip plane intersection into the
        //           stencil buffer.
        //
        NodeRefPtr geomNode = Node::create();
        geomNode->setCore(geo1);

        NodeRefPtr materialNode1 = Node::create();
        //
        // Create stencil material core
        //
        StencilChunkRefPtr stencilChunk1 = StencilChunk::create();
        stencilChunk1->setClearBuffer(1);
        stencilChunk1->setStencilFunc(GL_NEVER);
        stencilChunk1->setStencilValue(1);
        stencilChunk1->setStencilMask(1);
        stencilChunk1->setStencilOpFail(GL_INVERT);
        stencilChunk1->setStencilOpZFail(GL_INVERT);
        stencilChunk1->setStencilOpZPass(GL_INVERT);

        ChunkMaterialRefPtr mat1 = ChunkMaterial::create();
        mat1->addChunk(stencilChunk1);
        mat1->addChunk(vecClipPlaneDetails[i]._clipPlaneChunk);
        mat1->setSortKey(2 * i + 0);
        //mat1->setSortKey(k*(2*iNumClipPlanes + 1) + 2*i + 0);

        MaterialGroupRefPtr mgrp1 = MaterialGroup::create();
        mgrp1->setMaterial(mat1);

        materialNode1->setCore(mgrp1);
        materialNode1->addChild(geomNode);  // the primary geometry

        vecMaterialNodes1.push_back(materialNode1);

        //
        // Branch 2: Draw plane at places were the stencil buffer is set
        //
        NodeRefPtr         materialNode2 = Node        ::create();
        StencilChunkRefPtr stencilChunk2 = StencilChunk::create();

        stencilChunk2->setStencilFunc(GL_EQUAL);
        stencilChunk2->setStencilValue(1);
        stencilChunk2->setStencilMask(1);
        stencilChunk2->setStencilOpFail(GL_KEEP);
        stencilChunk2->setStencilOpZFail(GL_ZERO);
        stencilChunk2->setStencilOpZPass(GL_ZERO);

        SimpleMaterialRefPtr mat2 = SimpleMaterial::create();
        mat2->setDiffuse(vecClipPlaneDetails[i]._planeColor);
        mat2->setSpecular(Color3f(1,1,1));
        mat2->setLit(true);

        //
        // Do clip the plane with all clip planes but the one coincident
        // with the plane.
        //
        for(int j = 0; j < iNumClipPlanes; ++j)
        {
            if(i != j)
            {
                mat2->addChunk(vecClipPlaneDetails[j]._clipPlaneChunk);
            }
        }
        mat2->addChunk(stencilChunk2);
        mat2->setSortKey(2 * i + 1);
        //mat2->setSortKey(k*(2*iNumClipPlanes + 1) + 2*i + 1);

        NodeRefPtr planeGeoNode = Node::create();
        planeGeoNode->setCore(vecClipPlaneDetails[i]._planeGeometryCore);

        NodeRefPtr planeTrafoNode = Node::create();
        planeTrafoNode->setCore(vecClipPlaneDetails[i]._planeTrafoCore);
        planeTrafoNode->addChild(planeGeoNode);

        //
        // Neutralize the summed up transformation at this point in the
        // scenegraph since we are describing the plane in the same frame
        // as the clip planes, i.e. world coordinates.
        //
        NodeRefPtr planeRootNode = Node::create();
        planeRootNode->setCore(InverseTransform::create());
        planeRootNode->addChild(planeTrafoNode);

        MaterialGroupRefPtr mgrp2 = MaterialGroup::create();
        mgrp2->setMaterial(mat2);

        materialNode2->setCore(mgrp2);
        materialNode2->addChild(planeRootNode); // plane geometry

        vecMaterialNodes2.push_back(materialNode2);
    }

    //
    // Finally, set up a branch for drawing the primary geometry
    //
    NodeRefPtr           materialNode3 = Node          ::create();
    SimpleMaterialRefPtr mat3          = SimpleMaterial::create();

    mat3->setDiffuse(Color3f(1,0,0));
    mat3->setSpecular(Color3f(1,1,1));
    mat3->setLit(true);

    //
    // Clip the geometry with each clip plane
    //
    for(int i = 0; i < iNumClipPlanes; ++i)\
    {
        mat3->addChunk(vecClipPlaneDetails[i]._clipPlaneChunk);
    }
    mat3->setSortKey(2 * iNumClipPlanes);
    //mat3->setSortKey(k*(2*iNumClipPlanes + 1) + iNumClipPlanes * 2);

    MaterialGroupRefPtr mgrp3 = MaterialGroup::create();
    mgrp3->setMaterial(mat3);

    NodeRefPtr geometryNode = Node::create();
    geometryNode->setCore(geo1);

    materialNode3->setCore (mgrp3);
    materialNode3->addChild(geometryNode);

    //
    // The multi switch core is not actually used in this
    // example. However it could be used to define multiple
    // render branches and selectively activate and deactivate
    // them in a given context.
    //
    MultiSwitchRefPtr selectCore = MultiSwitch::create();
    selectCore->setSwitchMode(MultiSwitch::ALL);

    //
    // Add the branches to some parent node.
    //
    NodeRefPtr selectNode = Node::create();
    selectNode->setCore(selectCore);

    for(int i = 0; i < iNumClipPlanes; ++i)
    {
        selectNode->addChild(vecMaterialNodes1[i]);
        selectNode->addChild(vecMaterialNodes2[i]);
    }

    selectNode->addChild(materialNode3);

    //
    // In order to avoid sort keys which grow with the number of primary
    // geometry nodes, a node carrying a Stage core is inserted
    // into the tree.
    //
    PassiveBackgroundRefPtr passBkg = PassiveBackground::create();

    GroupingStageRefPtr stageCore;
    NodeRefPtr          stageNode = makeCoredNode<GroupingStage>(&stageCore);
//    stageCore->setInheritedTarget(true);
//    stageCore->setCamera    (mgr->getCamera());
//    stageCore->setBackground(passBkg         );
    stageNode->addChild(selectNode);

    //
    // Finally, the geometry should be transformable
    //
    TransformRefPtr transfCore;
    NodeRefPtr      transfNode = makeCoredNode<Transform>(&transfCore);

    transfCore->setMatrix(matrix);
    transfNode->addChild(stageNode);
    //trafoNode->addChild(selectNode); // if using sort keys use this
                                       // instead of the former line.

    k++;

    return NodeTransitPtr(transfNode);
}

//
// redraw the window
//
void display(void)
{
    // render

    mgr->redraw();

    // all done, swap
    glutSwapBuffers();
}

//
// react to size changes
//
void reshape(int w, int h)
{
    mgr->resize(w,h);
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

//
// react to mouse motions with pressed buttons
//
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

//
// react to keys
//
void keyboard(unsigned char k, int, int)
{
    static Real32 val0 = 0.f;
    static Real32 val1 = 0.f;

    static Real32 x1 = 0.f;
    static Real32 y1 = 0.f;
    static Real32 z1 = 0.f;

    static Real32 x2 = 0.f;
    static Real32 y2 = 0.f;
    static Real32 z2 = 0.f;

    switch(k)
    {
    case ' ':
        {
            SceneGraphPrinter sgp(mgr->getRoot());
            sgp.printDownTree(std::cout);
        }
        break;

    case '1':   // enable/disable clip plane 0
        {
            vecClipPlaneData[0]._enabled = !vecClipPlaneData[0]._enabled;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case '2':   // enable/disable clip plane 1
        {
            vecClipPlaneData[1]._enabled = !vecClipPlaneData[1]._enabled;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case '3':   // enable/disable box geometry
        {
            if(vecGeometries[0] == NULL)
            {
                Matrix matrix;
                Vec3f v(10.f,  0.f, 15.f);
                matrix.setTranslate(v);

                GeometryRefPtr boxGeo  = makeBoxGeo(15, 15, 15, 1, 1, 1);
                NodeRefPtr     boxTree = buildGeoTree(scene, boxGeo, matrix);

                vecGeometries[0] = boxTree;
                scene->addChild(boxTree);
            }
            else
            {
                scene->subChild(vecGeometries[0]);
                vecGeometries[0] = NULL;
            }

//             mgr->showAll();
//             mgr->redraw();
        }
        break;
    case '4':   // enable/disable torus geometry
        {
            if (vecGeometries[1] == NULL)
            {
                Matrix matrix;
                Vec3f v( 0.f, 10.f, 0.f);
                matrix.setTranslate(v);

                GeometryRefPtr torusGeo  = makeTorusGeo(2, 6, 8, 16);
                NodeRefPtr     torusTree = buildGeoTree(scene, torusGeo, matrix);

                vecGeometries[1] = torusTree;
                scene->addChild(torusTree);
            }
            else
            {
                scene->subChild(vecGeometries[1]);
                vecGeometries[1] = NULL;
            }

//             mgr->showAll();
//             mgr->redraw();
        }
        break;
    case 'n':   // move clip plane 0 opposite to the normal direction of the plane
        {
            val0 -= 0.2;
            vecClipPlaneData[0]._equation[3] = val0;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case 'm':   // move clip plane 0 in the normal direction of the plane
        {
            val0 += 0.2;
            vecClipPlaneData[0]._equation[3] = val0;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case ',':   // move clip plane 1 opposite to the normal direction of the plane
        {
            val1 -= 0.2;
            vecClipPlaneData[1]._equation[3] = val1;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case '.':   // move clip plane 1 in the normal direction of the plane
        {
            val1 += 0.2;
            vecClipPlaneData[1]._equation[3] = val1;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case 'q':   // move box in -x direction
        {
            x1 -= 0.2f;

            Matrix matrix;
            Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                TransformRefPtr transformCore =
                    dynamic_cast<Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'w':   // move box in +x direction
        {
            x1 += 0.2f;

            Matrix matrix;
            Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                TransformRefPtr transformCore =
                    dynamic_cast<Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'a':   // move box in -y direction
        {
            y1 -= 0.2f;

            Matrix matrix;
            Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                TransformRefPtr transformCore =
                    dynamic_cast<Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 's':   // move box in +y direction
        {
            y1 += 0.2f;

            Matrix matrix;
            Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                TransformRefPtr transformCore =
                    dynamic_cast<Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'y':   // move box in -z direction
        {
            z1 -= 0.2f;

            Matrix matrix;
            Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                TransformRefPtr transformCore =
                    dynamic_cast<Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'x':   // move box in +z direction
        {
            z1 += 0.2f;

            Matrix matrix;
            Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                TransformRefPtr transformCore =
                    dynamic_cast<Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'e':   // move torus in -x direction
        {
            x2 -= 0.2f;

            Matrix matrix;
            Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                TransformRefPtr transformCore =
                    dynamic_cast<Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'r':   // move torus in +x direction
        {
            x2 += 0.2f;

            Matrix matrix;
            Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                TransformRefPtr transformCore =
                    dynamic_cast<Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'd':   // move torus in -y direction
        {
            y2 -= 0.2f;

            Matrix matrix;
            Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                TransformRefPtr transformCore =
                    dynamic_cast<Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'f':   // move torus in +y direction
        {
            y2 += 0.2f;

            Matrix matrix;
            Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                TransformRefPtr transformCore =
                    dynamic_cast<Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'c':   // move torus in -z direction
        {
            z2 -= 0.2f;

            Matrix matrix;
            Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                TransformRefPtr transformCore =
                    dynamic_cast<Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'v':   // move torus in +z direction
        {
            z2 += 0.2f;

            Matrix matrix;
            Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                TransformRefPtr transformCore =
                    dynamic_cast<Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 27:
        {
            cleanup();

            osgExit();
            exit(0);
        }
        break;
    }
    
    glutPostRedisplay();
}

int doMain(int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);

    glutCreateWindow("OpenSG");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    PassiveWindowRefPtr pwin=PassiveWindow::create();
    pwin->init();

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin);

    //
    // Implementation details:
    //      For each clip plane we provide a ClipPlaneChunk, the plane geometry,
    //      the plane transform core and at least a plane color conveniently in
    //      a vector of type VecClipPlaneDetailsT. The next function call
    //      initializes this data structure.
    //
    createClipPlaneDetails();

    //
    // The scene
    //
    scene = Node::create();
    scene->setCore(Group::create());

    //
    // A place for accessing the box and torus.
    //
    vecGeometries.push_back(NULL);
    vecGeometries.push_back(NULL);

    //
    // Build concrete clipping planes and update the clip plane details.
    //
    ClipPlaneData data1;
    ClipPlaneData data2;

    data1._equation = Vec4f(0,0,1,0);
    data1._enabled  = true;

    data2._equation = Vec4f(1,0,0,0);
    data2._enabled  = false;

    vecClipPlaneData.push_back(data1);
    vecClipPlaneData.push_back(data2);

    updateClipPlanes(vecClipPlaneData);

    keyboard('3',-1,-1);
    keyboard('4',-1,-1);

    // tell the manager what to manage
    mgr->setRoot(scene);

    // show the whole scene
    mgr->showAll();
    mgr->redraw();

    pwin->dumpExtensions();

    return 0;
}

int main(int argc, char *argv[])
{
    doMain(argc, argv);

    // GLUT main loop
    glutMainLoop();

    //
    // Clean up the global held data
    //
    cleanup();

    osgExit();

    return 0;
}