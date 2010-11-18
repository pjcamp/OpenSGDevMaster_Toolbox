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
#include "OSGSimpleMaterial.h"

#include "OSGScaleManipulator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ScaleManipulator
 * The ScaleHandle is used for scaleing objects. It consist of three axis
 * which can be picked and scaled and one center box to scale freely in 3D.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ScaleManipulator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &ScaleManipulator::intersectEnter));

        IntersectAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &ScaleManipulator::intersectLeave));

        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&ScaleManipulator::renderEnter));

        RenderAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&ScaleManipulator::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void ScaleManipulator::addHandleGeo(Node *n)
{
    Inherited::addHandleGeo(n);
}

void ScaleManipulator::subHandleGeo(Node *n)
{
    Inherited::subHandleGeo(n);
}

void ScaleManipulator::onCreate(const ScaleManipulator* source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        //
        // make the yellow uniform scale transform and handle


        SimpleMaterialRecPtr simpleMat = SimpleMaterial::create();
        simpleMat->setDiffuse(Color3f(0, 1, 1));
        simpleMat->setLit    (true            );
        setMaterialUniform(simpleMat);

        NodeUnrecPtr UniformAxisManipulator = createAxisManipulator(ALL_AXES_HANDLE);

        _root->addChild(UniformAxisManipulator);
    }
}

void ScaleManipulator::onDestroy()
{
}

UInt32 ScaleManipulator::getAxisCollisionTravMask(UInt16 Axis) const
{
    switch(Axis)
    {
    case X_AXIS_HANDLE:
        return X_AXIS_TRAV_MASK;
        break;
    case Y_AXIS_HANDLE:
        return Y_AXIS_TRAV_MASK;
        break;
    case Z_AXIS_HANDLE:
        return Z_AXIS_TRAV_MASK;
        break;
    case ALL_AXES_HANDLE:
        return ALL_AXIS_TRAV_MASK;
        break;
    default:
        return NONE_TRAV_MASK;
        break;
    }
}

Material* ScaleManipulator::getAxisMaterial(UInt16 Axis) const
{
    switch(Axis)
    {
    case X_AXIS_HANDLE:
        return getMaterialX();
        break;
    case Y_AXIS_HANDLE:
        return getMaterialY();
        break;
    case Z_AXIS_HANDLE:
        return getMaterialZ();
        break;
    case ALL_AXES_HANDLE:
        return getMaterialUniform();
        break;
    default:
        return NULL;
        break;
    }
}
    
MFUnrecGeometryPtr* ScaleManipulator::editAxisGeometries(UInt16 Axis)
{
    switch(Axis)
    {
    case X_AXIS_HANDLE:
        return editMFXGeometries();
        break;
    case Y_AXIS_HANDLE:
        return editMFYGeometries();
        break;
    case Z_AXIS_HANDLE:
        return editMFZGeometries();
        break;
    case ALL_AXES_HANDLE:
        return editMFUniformGeometries();
        break;
    default:
        return NULL;
        break;
    }
}

/*! The mouseMove is called by the viewer when the mouse is moved in the
    viewer and this handle is the active one.

    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */
void ScaleManipulator::mouseMove(const Int16 x,
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

                Vec3f      translation;       // for matrix decomposition
                Quaternion rotation;
                Vec3f      scaleFactor;
                Quaternion scaleOrientation;
                getTransformation(translation, rotation, scaleFactor, scaleOrientation);

                if( getActiveHandle() == X_AXIS_HANDLE ||
                    getActiveHandle() == Y_AXIS_HANDLE ||
                    getActiveHandle() == Z_AXIS_HANDLE)
                {
                    //Get the line defined by the screen location of the mouse shooting into the screen
                    Line MouseRay;
                    getViewport()->getCamera()->calcViewRay(MouseRay, x, y, *getViewport());

                    //Get the line defined by the currently selected axis
                    Vec3f HandleDirection(0.0f,0.0f,0.0f);
                    HandleDirection[getActiveHandle()] = 1.0f;
                    Line HandleRay(_TargetInitialOrigin, getTarget()->getToWorld() * HandleDirection);

                    //Find the closest point between the two lines
                    Pnt3f ClosestMouseLinePosition;
                    Pnt3f ClosestHandleLinePosition;
                    MouseRay.getClosestPoints(HandleRay, ClosestMouseLinePosition, ClosestHandleLinePosition);

                    scaleFactor = _InitialScale;
                    scaleFactor[getActiveHandle()] +=  ((ClosestHandleLinePosition[getActiveHandle()] - _TargetInitialOrigin[getActiveHandle()]) / (_StartManipInitialPosition[getActiveHandle()] - _TargetInitialOrigin[getActiveHandle()])) - 1.0f;

                }
                else if(getActiveHandle() == ALL_AXES_HANDLE)
                {
                    Vec2f CurrentMouseDisplacement(getStartMousePos() - Pnt2f(x,y));

                    if(_StartUniformManip)
                    {
                        _InitialMouseDirection = CurrentMouseDisplacement;
                        
                        if(_InitialMouseDirection != Vec2f(0.0f,0.0f))
                        {
                            _StartUniformManip = false;
                            _InitialMouseDirection.normalize();
                        }
                    }

                    //Determine the scaling factor
                    Real32 ProjectionFactor = CurrentMouseDisplacement.projectTo(_InitialMouseDirection);

                    Real32 ScalarScaleFactor;
                    if(ProjectionFactor >= 0)
                    {
                        ScalarScaleFactor = ProjectionFactor * 0.01f;
                    }
                    else
                    {
                        ScalarScaleFactor = ProjectionFactor * 0.01f;
                    }

                    scaleFactor = _InitialScale + Vec3f(ScalarScaleFactor,ScalarScaleFactor,ScalarScaleFactor);

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

void ScaleManipulator::mouseButtonPress(const UInt16 button,
                                   const Int16  x,
                                   const Int16  y     )
{
    Inherited::mouseButtonPress(button,x,y);

    //get the active handle
    if(isManipulating())
    {
        
        Vec3f      translation;       // for matrix decomposition
        Quaternion rotation;
        Quaternion scaleOrientation;
        getTransformation(translation, rotation, _InitialScale, scaleOrientation);

        //Get the origin of the target
        _TargetInitialOrigin = getTarget()->getToWorld() * Pnt3f(0.0f,0.0f,0.0f);           // center of beacon

        
        if( getActiveHandle() == X_AXIS_HANDLE ||
            getActiveHandle() == Y_AXIS_HANDLE ||
            getActiveHandle() == Z_AXIS_HANDLE)
        {
            //Get the line defined by the screen location of the mouse shooting into the screen
            Line MouseRay;
            getViewport()->getCamera()->calcViewRay(MouseRay, x, y, *getViewport());

            //Get the line defined by the currently selected axis
            Vec3f HandleDirection(0.0f,0.0f,0.0f);
            HandleDirection[getActiveHandle()] = 1.0f;
            Line HandleRay(_TargetInitialOrigin, getTarget()->getToWorld() * HandleDirection);

            //Find the closest point between the two lines
            Pnt3f ClosestMouseLinePosition;
            MouseRay.getClosestPoints(HandleRay, ClosestMouseLinePosition, _StartManipInitialPosition);
        }
        else if(getActiveHandle() == ALL_AXES_HANDLE)
        {
            _StartUniformManip = true;
        }
    }
}

void ScaleManipulator::mouseButtonRelease(const UInt16 button,
                                     const Int16  x,
                                     const Int16  y     )
{
    Inherited::mouseButtonRelease(button,x,y);
}

/*----------------------- constructors & destructors ----------------------*/

ScaleManipulator::ScaleManipulator(void) :
    Inherited(),
    _StartUniformManip(false)
{
}

ScaleManipulator::ScaleManipulator(const ScaleManipulator &source) :
    Inherited(source),
    _StartUniformManip(false)
{
}

ScaleManipulator::~ScaleManipulator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ScaleManipulator::changed(ConstFieldMaskArg whichField,
                               UInt32            origin,
                               BitVector         details   )
{
    Inherited::changed(whichField, origin, details);
}

void ScaleManipulator::dump(      UInt32    uiIndent,
                            const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

NodeTransitPtr ScaleManipulator::makeHandleGeo(Real32 radius, UInt16 axis)
{
    //Make Rendered geometry
    GeometryRecPtr BoxGeo = makeBoxGeo(radius*2.0f,radius*2.0f,radius*2.0f, 2, 2, 2);
    editAxisGeometries(axis)->push_back(BoxGeo);

    BoxGeo->setMaterial(getAxisMaterial(axis));

    NodeRecPtr BoxRenderedNode = makeNodeFor(BoxGeo);
    BoxRenderedNode->setTravMask(NONCOLLIDE_RENDERED_TRAV_MASK);

    //Make collidable geometry
    GeometryRecPtr BoxCollisionGeo = makeBoxGeo(radius*4.0f,radius*4.0f,radius*4.0f, 1, 1, 1);

    NodeRecPtr BoxCollisionNode = makeNodeFor(BoxCollisionGeo);
    BoxCollisionNode->setTravMask(getAxisCollisionTravMask(axis));

    //Handle Node
    ComponentTransformUnrecPtr TransHandleXC = ComponentTransform::create();

    if( axis == X_AXIS_HANDLE ||
        axis == Y_AXIS_HANDLE ||
        axis == Z_AXIS_HANDLE)
    {
        Vec3f Direction(0.0f,0.0f,0.0f);
        Direction[axis] = 1.0f;
        TransHandleXC->setTranslation(Direction * (1.0f + radius));
        TransHandleXC->setRotation   (Quaternion(Vec3f(0.0f,1.0f,0.0f),Direction));
    }

    NodeRecPtr HandleNode = makeNodeFor(TransHandleXC);
    HandleNode->addChild(BoxRenderedNode);
    HandleNode->addChild(BoxCollisionNode);

    return NodeTransitPtr(HandleNode);
}

void ScaleManipulator::updateLength(void)
{
    Inherited::updateLength();
}

