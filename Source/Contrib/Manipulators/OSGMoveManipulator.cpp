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

#include "OSGMoveManipulator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::MoveManipulator
 * The MoveHandle is used for moving objects. It consist of three axis which
 * can be picked and translated and one center box to translate freely in 3D.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MoveManipulator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &MoveManipulator::intersectEnter));

        IntersectAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &MoveManipulator::intersectLeave));

        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&MoveManipulator::renderEnter));

        RenderAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&MoveManipulator::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MoveManipulator::MoveManipulator(void) :
    Inherited()
{
}

MoveManipulator::MoveManipulator(const MoveManipulator &source) :
    Inherited(source)
{
}

MoveManipulator::~MoveManipulator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MoveManipulator::changed(ConstFieldMaskArg whichField,
                              UInt32            origin,
                              BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MoveManipulator::dump(      UInt32    uiIndent,
                           const BitVector bvFlags ) const
{
    Inherited::dump(uiIndent, bvFlags);
}

NodeTransitPtr MoveManipulator::makeHandleGeo(Real32 radius,
                                              UInt16 axis)
{
    //Make Rendered geometry
    GeometryRecPtr ConeGeo = makeConeGeo(radius*4.0f, radius, 12, true, true);
    editAxisGeometries(axis)->push_back(ConeGeo);

    ConeGeo->setMaterial(getAxisMaterial(axis));

    NodeRecPtr ConeRenderedNode = makeNodeFor(ConeGeo);
    ConeRenderedNode->setTravMask(NONCOLLIDE_RENDERED_TRAV_MASK);

    //Make collidable geometry
    GeometryRecPtr ConeCollisionGeo = makeConeGeo(radius*8.0f, radius*2.0f, 8, true, true);

    NodeRecPtr ConeCollisionNode = makeNodeFor(ConeCollisionGeo);
    ConeCollisionNode->setTravMask(getAxisCollisionTravMask(axis));

    //Handle Node
    ComponentTransformUnrecPtr TransHandleXC = ComponentTransform::create();

    Vec3f Direction(0.0f,0.0f,0.0f);
    Direction[axis] = 1.0f;
    TransHandleXC->setTranslation(Direction * (1.0f + radius*2.0f));
    TransHandleXC->setRotation   (Quaternion(Vec3f(0.0f,1.0f,0.0f),Direction));

    NodeRecPtr HandleNode = makeNodeFor(TransHandleXC);
    HandleNode->addChild(ConeRenderedNode);
    HandleNode->addChild(ConeCollisionNode);

    return NodeTransitPtr(HandleNode);
}

/*! The mouseMove is called by the viewer when the mouse is moved in the
    viewer and this handle is the active one.

    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */
void MoveManipulator::mouseMove(const Int16 x,
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

                //Get the line defined by the currently selected axis
                Vec3f HandleDirection(0.0f,0.0f,0.0f);
                HandleDirection[getActiveHandle()] = 1.0f;
                Line HandleRay(_TargetInitialOrigin, getTarget()->getToWorld() * HandleDirection);

                //Find the closest point between the two lines
                Pnt3f ClosestMouseLinePosition;
                Pnt3f ClosestHandleLinePosition;
                MouseRay.getClosestPoints(HandleRay, ClosestMouseLinePosition, ClosestHandleLinePosition);

                Vec3f      translation;       // for matrix decomposition
                Quaternion rotation;
                Vec3f      scaleFactor;
                Quaternion scaleOrientation;
                getTransformation(translation, rotation, scaleFactor, scaleOrientation);

                translation = _TargetInitialOrigin.subZero() + (ClosestHandleLinePosition - _StartManipInitialPosition);

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

void MoveManipulator::mouseButtonPress(const UInt16 button,
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

        //Get the line defined by the currently selected axis
        Vec3f HandleDirection(0.0f,0.0f,0.0f);
        HandleDirection[getActiveHandle()] = 1.0f;
        Line HandleRay(_TargetInitialOrigin, getTarget()->getToWorld() * HandleDirection);

        //Find the closest point between the two lines
        Pnt3f ClosestMouseLinePosition;
        MouseRay.getClosestPoints(HandleRay, ClosestMouseLinePosition, _StartManipInitialPosition);
    }
}

void MoveManipulator::mouseButtonRelease(const UInt16 button,
                                     const Int16  x,
                                     const Int16  y     )
{
    Inherited::mouseButtonRelease(button,x,y);
}
