/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEMANIPULATORSLIB

#include "OSGConfig.h"
#include "OSGRenderAction.h"
#include "OSGIntersectAction.h"

#include "OSGRotateManipulator.h"

#include "OSGMultiPassMaterial.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGDepthChunk.h"
#include "OSGBlendChunk.h"
#include "OSGPolygonChunk.h"
#include "OSGClipPlaneChunk.h"
#include "OSGBillboard.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::RotateManipulator
 * The MoveHandle is used for moving objects. It consist of three axis which
 * can be picked and translated and one center box to translate freely in 3D.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RotateManipulator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &RotateManipulator::intersectEnter));

        IntersectAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &RotateManipulator::intersectLeave));

        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &RotateManipulator::renderEnter));

        RenderAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &RotateManipulator::renderLeave));
    }
}

/*! The mouseMove is called by the viewer when the mouse is moved in the
    viewer and this handle is the active one.

    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */
void RotateManipulator::mouseMove(const Int16 x,
                                  const Int16 y)
{
    if(isManipulating())
    {
        Inherited::mouseMove(x,y);

        // get the beacon's core (must be ComponentTransform) and it's center
        if( getTarget() != NULL )
        {
            if( getTarget()->getCore() != NULL )
            {
                //Get the line defined by the screen location of the mouse shooting into the screen
                Line MouseRay;
                getViewport()->getCamera()->calcViewRay(MouseRay, x, y, *getViewport());

                //Get the plane defined by the currently selected axis
                Vec3f HandleDirection(0.0f,0.0f,0.0f);
                HandleDirection[getActiveHandle()] = 1.0f;

                Matrix TargetToWorld(getTarget()->getToWorld());
                Vec3f HandleWorldSpaceDirection = TargetToWorld * HandleDirection;
                    
                Vec3f      translation;       // for matrix decomposition
                Quaternion rotation;
                Vec3f      scaleFactor;
                Quaternion scaleOrientation;
                getTransformation(translation, rotation, scaleFactor, scaleOrientation);

                if(_RotationMethod == ROLL_METHOD)
                {
                    //Get the direction of the view
                    Vec3f ViewDirectionWorldSpace = getViewport()->getCamera()->getBeacon()->getToWorld() * Vec3f(0.0f,0.0f,-1.0f);

                    //Get the plane defined by the currently selected axis
                    Plane HandleRotationPlane(ViewDirectionWorldSpace,_TargetInitialOrigin);

                    //Find the point of intersection
                    Pnt3f PointOfIntersection;
                    if(!HandleRotationPlane.intersect(MouseRay,PointOfIntersection))
                    {
                        return;
                    }

                    Vec3f MouseMoveDisp(_StartManipInitialPosition - PointOfIntersection);

                    Real32 Angle(0.75f* MouseMoveDisp.projectTo(_HandleRollDirection));

                    Quaternion NewRotation(HandleDirection, Angle);
                    
                    rotation = _InitialRotation * NewRotation;
                }
                else if(_RotationMethod == CRANK_METHOD)
                {

                    Plane HandleRotationPlane(HandleWorldSpaceDirection,_TargetInitialOrigin);

                    //Find the point of intersection
                    Pnt3f PointOfIntersection;
                    if(!HandleRotationPlane.intersect(MouseRay,PointOfIntersection))
                    {
                        return;
                    }

                    Matrix WorldToTarget(TargetToWorld);
                    WorldToTarget.invert();

                    Vec3f OriginToCurrent(PointOfIntersection - _TargetInitialOrigin);
                    OriginToCurrent = WorldToTarget * OriginToCurrent;
                    OriginToCurrent.normalize();

                    Vec3f OriginToInitial(_StartManipInitialPosition - _TargetInitialOrigin);
                    OriginToInitial = WorldToTarget * OriginToInitial;
                    OriginToInitial.normalize();

                    //Calculate the rotation needed
                    Quaternion NewRotation(HandleDirection, osgACos(OriginToCurrent.dot(OriginToInitial)));

                    if(HandleDirection.dot(OriginToCurrent.cross(OriginToInitial)) >= 0)
                    {
                        NewRotation.invert();
                    }

                    rotation = _InitialRotation * NewRotation;
                }
                setTransformation(translation, rotation, scaleFactor, Quaternion());
            }
            else
            {
                SWARNING << "handled object has no parent transform!\n";
            }
            callExternalUpdateHandler();
        }
        else
        {
            SWARNING << "Handle has no target.\n";
        }
    }
}

/*! The mouseButtonPress is called by the viewer when the mouse is
    pressed in the viewer above a subhandle of this handle.

    \param button the button pressed
    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */

void RotateManipulator::mouseButtonPress(const UInt16 button,
                                   const Int16  x,
                                   const Int16  y     )
{
    Inherited::mouseButtonPress(button,x,y);

    //get the active handle
    if(isManipulating())
    {

        //Get the origin of the target
        _TargetInitialOrigin = getTarget()->getToWorld() * Pnt3f(0.0f,0.0f,0.0f);           // center of beacon

        //Get the line defined by the screen location of the mouse shooting into the screen
        Line MouseRay;
        getViewport()->getCamera()->calcViewRay(MouseRay, x, y, *getViewport());

        //Get the direction of the handle
        Vec3f HandleDirection(0.0f,0.0f,0.0f);
        HandleDirection[getActiveHandle()] = 1.0f;

        Vec3f HandleWorldSpaceDirection = getTarget()->getToWorld() * HandleDirection;

        //Get the direction of the view
        Vec3f ViewDirectionWorldSpace = getViewport()->getCamera()->getBeacon()->getToWorld() * Vec3f(0.0f,0.0f,-1.0f);

        //Determine whether to use the roll or crank method
        Real32 MinAngleCosForCrankMethod(0.1f);
        if(osgAbs(HandleWorldSpaceDirection.dot(ViewDirectionWorldSpace)) < MinAngleCosForCrankMethod)
        {
            _RotationMethod = ROLL_METHOD;

            _HandleRollDirection = HandleWorldSpaceDirection.cross(ViewDirectionWorldSpace);

            //Get the plane defined by the currently selected axis
            Plane HandleRotationPlane(ViewDirectionWorldSpace,_TargetInitialOrigin);

            //Find the point of intersection
            if(!HandleRotationPlane.intersect(MouseRay,_StartManipInitialPosition))
            {
                return;
            }
        }
        else
        {
            _RotationMethod = CRANK_METHOD;

            //Get the plane defined by the currently selected axis
            Plane HandleRotationPlane(HandleWorldSpaceDirection,_TargetInitialOrigin);

            //Find the point of intersection
            if(!HandleRotationPlane.intersect(MouseRay,_StartManipInitialPosition))
            {
                return;
            }
        }

        //Get the initial rotation
        Vec3f      translation;
        Vec3f      scaleFactor;
        Quaternion scaleOrientation;
        getTransformation(translation, _InitialRotation, scaleFactor, scaleOrientation);
    }
}

void RotateManipulator::mouseButtonRelease(const UInt16 button,
                                     const Int16  x,
                                     const Int16  y     )
{
    Inherited::mouseButtonRelease(button,x,y);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void RotateManipulator::createMaterials(void)
{
    Real32 Alpha(0.5f);

    //Default Depth Chunk
    DepthChunkRecPtr DefaultDepth = DepthChunk::create();
    DefaultDepth->setEnable(false);

    //Default Blend Chunk
    BlendChunkRecPtr DefaultBlend = BlendChunk::create();
    DefaultBlend->setSrcFactor(GL_SRC_ALPHA);
    DefaultBlend->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

    //Default Polygon Chunk
    PolygonChunkRecPtr DefaultPolygon = PolygonChunk::create();
    DefaultPolygon->setCullFace(GL_BACK);

    //Default Clip Plane Chunk
    //_DefaultFrontClipPlane = ClipPlaneChunk::create();
    //_DefaultFrontClipPlane->setEquation(Vec4f(0.0f,0.0f,1.0f,0.1f));

    //_DefaultBackClipPlane = ClipPlaneChunk::create();
    //_DefaultBackClipPlane->setEquation(Vec4f(0.0f,1.0f,0.0f,0.1f));

    ChunkMaterialUnrecPtr pMat;
    MaterialChunkUnrecPtr DefaultMaterialChunk;

    //Back Material
    //DefaultMaterialChunk = MaterialChunk::create();
    //DefaultMaterialChunk->setDiffuse(Color4f(0.3f, 0.3f, 0.3f, Alpha));
    //DefaultMaterialChunk->setLit(true);
    //
    //ChunkMaterialRecPtr BackMat = ChunkMaterial::create();
    //BackMat->addChunk(DefaultMaterialChunk);
    //BackMat->addChunk(DefaultDepth);
    //BackMat->addChunk(DefaultBlend);
    //BackMat->addChunk(DefaultPolygon);
    //BackMat->addChunk(_DefaultBackClipPlane);

    //X-axis Material
    DefaultMaterialChunk = MaterialChunk::create();
    DefaultMaterialChunk->setDiffuse(Color4f(1.0f, 0.0f, 0.0f, Alpha));
    DefaultMaterialChunk->setLit(true);
    
    pMat = ChunkMaterial::create();
    pMat->addChunk(DefaultMaterialChunk);
    pMat->addChunk(DefaultDepth);
    pMat->addChunk(DefaultBlend);
    pMat->addChunk(DefaultPolygon);
    setMaterialX(pMat);
    //pMat->addChunk(_DefaultFrontClipPlane);

    //MultiPassMaterialRecPtr XMat = MultiPassMaterial::create();
    //XMat->addMaterial(pMat);
    //XMat->addMaterial(BackMat);
    //setMaterialX(XMat);

    //Y-axis Material
    DefaultMaterialChunk = MaterialChunk::create();
    DefaultMaterialChunk->setDiffuse(Color4f(0.0f, 1.0f, 0.0f, Alpha));
    DefaultMaterialChunk->setLit(true);
    
    pMat = ChunkMaterial::create();
    pMat->addChunk(DefaultMaterialChunk);
    pMat->addChunk(DefaultDepth);
    pMat->addChunk(DefaultBlend);
    pMat->addChunk(DefaultPolygon);
    setMaterialY(pMat);
    //pMat->addChunk(_DefaultFrontClipPlane);

    //MultiPassMaterialRecPtr YMat = MultiPassMaterial::create();
    //YMat->addMaterial(pMat);
    //YMat->addMaterial(BackMat);
    //setMaterialY(YMat);

    //Z-axis Material
    DefaultMaterialChunk = MaterialChunk::create();
    DefaultMaterialChunk->setDiffuse(Color4f(0.0f, 0.0f, 1.0f, Alpha));
    DefaultMaterialChunk->setLit(true);
    
    pMat = ChunkMaterial::create();
    pMat->addChunk(DefaultMaterialChunk);
    pMat->addChunk(DefaultDepth);
    pMat->addChunk(DefaultBlend);
    pMat->addChunk(DefaultPolygon);
    setMaterialZ(pMat);
    //pMat->addChunk(_DefaultFrontClipPlane);

    //MultiPassMaterialRecPtr ZMat = MultiPassMaterial::create();
    //ZMat->addMaterial(pMat);
    //ZMat->addMaterial(BackMat);
    //setMaterialZ(ZMat);
    
    //Selected-axis Material
    DefaultMaterialChunk = MaterialChunk::create();
    DefaultMaterialChunk->setDiffuse(Color4f(1.0f, 1.0f, 0.0f, 1.0f));
    DefaultMaterialChunk->setLit(true);
    
    pMat = ChunkMaterial::create();
    pMat->addChunk(DefaultMaterialChunk);
    pMat->addChunk(DefaultDepth);
    pMat->addChunk(DefaultBlend);
    pMat->addChunk(DefaultPolygon);
    setMaterialSelected(pMat);
    
    //Rollover-axis Material
    DefaultMaterialChunk = MaterialChunk::create();
    DefaultMaterialChunk->setDiffuse(Color4f(0.5f, 0.5f, 0.0f, 1.0f));
    DefaultMaterialChunk->setLit(true);
    
    pMat = ChunkMaterial::create();
    pMat->addChunk(DefaultMaterialChunk);
    pMat->addChunk(DefaultDepth);
    pMat->addChunk(DefaultBlend);
    pMat->addChunk(DefaultPolygon);
    setMaterialRollover(pMat);
}

void RotateManipulator::onCreate(const RotateManipulator* source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        //BillboardRecPtr MainClipBillboard = Billboard::create();
        //MainClipBillboard->setAxisOfRotation(Vec3f(0.0f,0.0f,0.0f));
        //MainClipBillboard->setAlignToScreen(true);

        //NodeRecPtr MainClipBillboardNode = makeNodeFor(MainClipBillboard);

        //_root->addChild(MainClipBillboardNode);

        //_DefaultFrontClipPlane->setBeacon(MainClipBillboardNode);
        //_DefaultBackClipPlane->setBeacon(MainClipBillboardNode);
    }
}

void RotateManipulator::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

RotateManipulator::RotateManipulator(void) :
    Inherited()
{
}

RotateManipulator::RotateManipulator(const RotateManipulator &source) :
    Inherited(source)
{
}

RotateManipulator::~RotateManipulator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RotateManipulator::changed(ConstFieldMaskArg whichField,
                                UInt32            origin,
                                BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void RotateManipulator::dump(      UInt32    uiIndent,
                             const BitVector bvFlags ) const
{
    Inherited::dump(uiIndent, bvFlags);
}

NodeTransitPtr RotateManipulator::makeHandleGeo(Real32 radius, UInt16 axis)
{
    //Make Rendered geometry
    GeometryRecPtr TorusGeo = makeTorusGeo(radius*0.15f, 1.0f,24,32);
    //GeometryRecPtr TorusGeo = makeCylinderGeo(radius*0.5f, 1.0f, 64, true, false,false);
    editAxisGeometries(axis)->push_back(TorusGeo);

    TorusGeo->setMaterial(getAxisMaterial(axis));

    NodeRecPtr TorusRenderedNode = makeNodeFor(TorusGeo);
    TorusRenderedNode->setTravMask(NONCOLLIDE_RENDERED_TRAV_MASK);

    //Make collidable geometry
    GeometryRecPtr TorusCollisionGeo = makeTorusGeo(radius*0.5f, 1.0f,16,16);
    //GeometryRecPtr TorusCollisionGeo = makeCylinderGeo(radius, 1.0f, 32, true, false,false);

    NodeRecPtr TorusCollisionNode = makeNodeFor(TorusCollisionGeo);
    TorusCollisionNode->setTravMask(getAxisCollisionTravMask(axis));

    //Handle Node
    ComponentTransformUnrecPtr TransHandleXC = ComponentTransform::create();

    if( axis == X_AXIS_HANDLE ||
        axis == Y_AXIS_HANDLE ||
        axis == Z_AXIS_HANDLE)
    {
        Vec3f Direction(0.0f,0.0f,0.0f);
        Direction[axis] = 1.0f;
        TransHandleXC->setRotation   (Quaternion(Vec3f(0.0f,0.0f,1.0f),Direction));
    }

    NodeRecPtr HandleNode = makeNodeFor(TransHandleXC);
    HandleNode->addChild(TorusRenderedNode);
    HandleNode->addChild(TorusCollisionNode);

    return NodeTransitPtr(HandleNode);
}

NodeTransitPtr RotateManipulator::createAxisManipulator(UInt16 Axis)
{
    NodeUnrecPtr RootXManip = makeCoredNode<Group>();

    //Make the handle Geometry
    NodeUnrecPtr HandleGeoNode = makeHandleGeo(0.1f, Axis);

    RootXManip->addChild(HandleGeoNode);

    return NodeTransitPtr(RootXManip);
}
