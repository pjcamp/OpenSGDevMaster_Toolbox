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

    n->addChild(getTransUniformNode());
}

void ScaleManipulator::subHandleGeo(Node *n)
{
    Inherited::subHandleGeo(n);

    n->subChild(getTransUniformNode());
}

void ScaleManipulator::onCreate(const ScaleManipulator* source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        //
        // make the yellow uniform scale transform and handle


        SimpleMaterialRecPtr simpleMat = SimpleMaterial::create();
        simpleMat->setDiffuse(Color3f(1, 1, 0));
        simpleMat->setLit    (true            );
        setMaterialUniform(simpleMat);


        NodeRecPtr pNode = makeHandleGeo();
        dynamic_cast<Geometry *>(pNode->getCore())->setMaterial(getMaterialUniform());
        setHandleUniformNode(pNode);

        pNode = Node::create();
        ComponentTransformUnrecPtr transHandleUniformC = ComponentTransform::create();
        pNode->setCore (transHandleUniformC  );
        pNode->addChild(getHandleUniformNode());
        setTransUniformNode(pNode);

        commitChanges();
    }
}

void ScaleManipulator::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

ScaleManipulator::ScaleManipulator(void) :
    Inherited()
{
}

ScaleManipulator::ScaleManipulator(const ScaleManipulator &source) :
    Inherited(source)
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

bool ScaleManipulator::hasSubHandle(Node * const n)
{
    return ( n == getHandleUniformNode() ||
             Inherited::hasSubHandle(n));
}

NodeTransitPtr ScaleManipulator::makeHandleGeo()
{
    return makeBox(0.5f,0.5f,0.5f, 2, 2, 2);
}

UInt16 ScaleManipulator::getActiveHandle(void) const
{
    //  check for the active handle
    if(getActiveSubHandle() == getHandleXNode())
    {
        return X_AXIS_HANDLE;
    }
    else if(getActiveSubHandle() == getHandleYNode())
    {
        return Y_AXIS_HANDLE;
    }
    else if(getActiveSubHandle() == getHandleZNode())
    {
        return Z_AXIS_HANDLE;
    }
    else if(getActiveSubHandle() == getHandleUniformNode())
    {
        return ALL_AXES_HANDLE;
    }
    return NO_AXES_HANDLE;
}

void ScaleManipulator::updateLength(void)
{
    Vec3f scale(Vec3f(1.0f,1.0f,1.0f) * osgMax(1.0f, getLength().maxValue() * 0.2f));
    dynamic_cast<ComponentTransform*>(getTransUniformNode()->getCore())->setScale(scale);

    Inherited::updateLength();
}

void ScaleManipulator::doMovement(      Transform    *t,
                                  const Int32         coord,
                                  const Real32        value,
                                  const Vec3f        &translation,
                                  const Quaternion   &rotation,
                                  const Vec3f        &scaleFactor,
                                  const Quaternion   &scaleOrientation)
{
    Vec3f scale(1.0f, 1.0f, 1.0f);

    if(coord == ALL_AXES_HANDLE)
    {
        scale += Vec3f(value, value, value);
    }
    else
    {
        scale[coord] += value * getLength()[coord];
    }
    
    Matrix scaleMat;
    scaleMat.setScale(scale);

    Matrix Result(_initialXForm);
    Result.mult(scaleMat);

    t->setMatrix(Result);

    commitChanges();
}

