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
#include "OSGBaseFunctions.h"
#include "OSGSimpleMaterial.h"
#include "OSGTransform.h"
#include "OSGStackedTransform.h"
#include "OSGTranslationTransformationElement.h"
#include "OSGRotationTransformationElement.h"
#include "OSGScaleTransformationElement.h"
#include "OSGGeometry.h"
#include "OSGSimpleGeometry.h"
#include "OSGWindow.h"
#include "OSGNameAttachment.h"
#include "OSGCamera.h"

#include "OSGManipulator.h"
#include "OSGSimpleGeometryExt.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::Manipulator
Baseclass for all Manipulators
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

//! initialize the static features of the class, e.g. action callbacks

void Manipulator::initMethod(InitPhase)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Manipulator::addHandleGeo(Node *n)
{
    n->addChild(getTransXNode());
    n->addChild(getTransYNode());
    n->addChild(getTransZNode());
    n->addChild(getAxisLinesN());
}

void Manipulator::subHandleGeo(Node *n)
{
    n->subChild(getTransXNode());
    n->subChild(getTransYNode());
    n->subChild(getTransZNode());
    n->subChild(getAxisLinesN());
}

void Manipulator::startManip(Node *subHandle)
{
    if(!_isManipulating)
    {
        setActiveSubHandle(subHandle);

        _isManipulating = true;

        getTransformation(_initialXForm);
    }
}

void Manipulator::cancelManip(void)
{
    if(_isManipulating)
    {
        _isManipulating = false;

        setTransformation(_initialXForm);
    }
}

void Manipulator::endManip(void)
{
    if(_isManipulating)
    {
        _isManipulating = false;
    }
}

bool Manipulator::isManipulating(void) const\
{
    return _isManipulating;
}


void Manipulator::reverseTransform()
{
    if ( getTarget() != NULL )
    {
        Matrix     m,n,o;

        Vec3f      translation;
        Quaternion rotation;
        Vec3f      scaleFactor;
        Quaternion scaleOrientation;

        getTransformation(m);
        m.getTransform(translation, rotation, scaleFactor, scaleOrientation);

        if( false == o.invertFrom(m) )
        {
            SWARNING << "Matrix is SINGULAR!!!\n";
        }
        else
        {
            n.setIdentity (           );
            n.setTransform(translation);
            n.setRotate   (rotation   );
            n.multLeft    (o          );

            setMatrix(n);
        }
    }
}

//! output the instance for debug purposes

Pnt2f Manipulator::calcScreenProjection(const Pnt3f    &       p,
                                              Viewport * const port)
{
    Camera  *cam;
    Matrix   proj, projtrans, view;
    Pnt3f    pnt;

    if( port != NULL )
    {
        cam = port->getCamera();

        Matrix WorldToScreen;
        cam->getWorldToScreen(WorldToScreen, *port);

        WorldToScreen.multFull(p, pnt);

        Real32 rx = (pnt[0] + 1.0) /2 * port->getPixelWidth();
        //Real32 ry = port->getPixelHeight() - ((pnt[1] + 1.0) /2 * port->getPixelHeight());
        Real32 ry = (pnt[1] + 1.0) /2 * port->getPixelHeight();

        return Pnt2f(rx, ry);
    }
    else
    {
        SWARNING << "calcScreenProjection(const Pnt3f&, "
                    "Viewport * const port="
                 << port << ")\n";
        return Pnt2f(0.0f, 0.0f);
    }
}

UInt16 Manipulator::getActiveHandle(void) const
{
    //  check for the active handle
    if(     getActiveSubHandle() == getHandleXNode())
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
    return NO_AXES_HANDLE;
}

/*! The mouseMove is called by the viewer when the mouse is moved in the
    viewer and this handle is the active one.

    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */
void Manipulator::mouseMove(const Int16 x,
                            const Int16 y)
{
    //SLOG << "Manipulator::mouseMove() enter\n" << std::flush;

    // get the beacon's core (must be ComponentTransform) and it's center
    if( getTarget() != NULL )
    {
        if( getTarget()->getCore() != NULL )
        {
            UInt16     coord(0);          // active coordinate: X=0, Y=1, Z=2

            Vec3f      centerV;           // center of beacon

            Vec3f      translation;       // for matrix decomposition
            Quaternion rotation;
            Vec3f      scaleFactor;
            Quaternion scaleOrientation;

            // TODO: das ist ja schon ein wenig haesslich
            static const Vec3f coordVector[3] = {
                Vec3f(1.0f, 0.0f, 0.0f),
                Vec3f(0.0f, 1.0f, 0.0f),
                Vec3f(0.0f, 0.0f, 1.0f)
            };

            //get the active handle
            coord = getActiveHandle();
            OSG_ASSERT(coord != NO_AXES_HANDLE);

            // set the vector resulting from user mouse movement and calc its length
            
            getTransformation(translation, rotation, scaleFactor,
                                        scaleOrientation);


            // calculate the camera coordinate of the center
            centerV            = translation;
            Pnt2f centerPixPos = calcScreenProjection(centerV.addToZero(),
                                                      getViewport());


            // calculate the camera coordinate of the handle center
            Real32 value;
            if(coord == ALL_AXES_HANDLE)
            {
                value = getStartMousePos().dist(Pnt2f(x,y)) * 0.01f;
            }
            else
            {
                Vec2f movedMouseProj(Pnt2f(x,y) - getStartMousePos());
                movedMouseProj.projectTo(_handleScreenDir);

                Real32 s = static_cast<Real32>(osgSgn(_handleScreenDir.dot(Pnt2f(x,y) - getStartMousePos()))) * movedMouseProj.length();
                
                value = s  * 0.01f;
            }

            doMovement(coord, value, translation,
                       rotation, scaleFactor, scaleOrientation);
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

    reverseTransform();

    //SLOG << "Manipulator::mouseMove() leave\n" << std::flush;
}

/*! The mouseButtonPress is called by the viewer when the mouse is
    pressed in the viewer above a subhandle of this handle.

    \param button the button pressed
    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */

void Manipulator::mouseButtonPress(const UInt16 button,
                                   const Int16  x,
                                   const Int16  y     )
{
    setStartMousePos(Pnt2f(x, y));

    //get the active handle
    if(getActiveSubHandle() != NULL)
    {

        Pnt3f      center(getTarget()->getToWorld() * Pnt3f(0.0f,0.0f,0.0f));           // center of beacon
        Pnt3f      handleCenter(getActiveSubHandle()->getToWorld() * Pnt3f(0.0f,0.0f,0.0f));

        // calculate the camera coordinate of the center
        Pnt2f centerStartScreenPos = calcScreenProjection(center,
                                                  getViewport());


        Pnt2f handleCenterPixPos = calcScreenProjection(handleCenter,
                                                        getViewport());


        _handleScreenDir = handleCenterPixPos - centerStartScreenPos;
        _handleScreenDir.normalize();

        Vec2f mouseProj(getStartMousePos() - centerStartScreenPos);
        mouseProj.projectTo(_handleScreenDir);

        _startMouseProj = centerStartScreenPos + mouseProj;
    }

    setActive(true);
}

void Manipulator::mouseButtonRelease(const UInt16 button,
                                     const Int16  x,
                                     const Int16  y     )
{
    setActive(false);
}

bool Manipulator::hasSubHandle(Node * const n)
{
    return ( n == getHandleXNode() ||
             n == getHandleYNode() ||
             n == getHandleZNode() );
}

const Matrix& Manipulator::getInitialXForm(void) const
{
    return _initialXForm;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void Manipulator::dump(      UInt32    ,
                       const BitVector ) const
{
    SLOG << "Dump Manipulator NI" << std::endl;
}

void Manipulator::onCreate(const Manipulator* source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        SimpleMaterialUnrecPtr pMat = SimpleMaterial::create();

        setMaterialX(pMat);

        pMat = SimpleMaterial::create();

        setMaterialY(pMat);

        pMat = SimpleMaterial::create();

        setMaterialZ(pMat);

        SimpleMaterial *simpleMat;
        Geometry       *geo;

        setExternalUpdateHandler(NULL);

        // add a name attachment
        NameUnrecPtr nameN = Name::create();
        nameN->editFieldPtr()->setValue("XManipulator");
        addAttachment(nameN);

        // make the axis lines
        NodeUnrecPtr pNode = makeCoordAxis(getLength()[0], 2.0, false);
        setAxisLinesN(pNode);

        // make the red x-axis transform and handle

        pNode = Node::create();
        setTransXNode(pNode);
        ComponentTransformUnrecPtr transHandleXC = ComponentTransform::create();

        pNode = makeHandleGeo();
        setHandleXNode(pNode);
        pMat = SimpleMaterial::create();
        setMaterialX  (pMat );

        getTransXNode()->setCore (transHandleXC  );
        getTransXNode()->addChild(getHandleXNode());

        transHandleXC->setTranslation(Vec3f(getLength()[0], 0, 0)                   );
        transHandleXC->setRotation   (Quaternion(Vec3f(0, 0, 1), osgDegree2Rad(-90)));

        simpleMat = dynamic_cast<SimpleMaterial *>(getMaterialX());

        simpleMat->setDiffuse(Color3f(1, 0, 0));
        simpleMat->setLit    (true            );

        geo = dynamic_cast<Geometry *>(getHandleXNode()->getCore());
        geo->setMaterial(simpleMat);

        //
        // make the green y-axis transform and handle

        pNode = Node::create();
        setTransYNode(pNode);
        ComponentTransformUnrecPtr transHandleYC = ComponentTransform::create();
        pNode = makeHandleGeo();
        setHandleYNode(pNode);
        pMat = SimpleMaterial::create();
        setMaterialY(pMat);

        getTransYNode()->setCore (transHandleYC  );
        getTransYNode()->addChild(getHandleYNode());

        transHandleYC->setTranslation(Vec3f(0, getLength()[1], 0)                    );
        //    transHandleYC->setRotation   ( Quaternion(Vec3f(0, 0, 1), osgDegree2Rad(-90)));

        simpleMat = dynamic_cast<SimpleMaterial *>(getMaterialY());
        simpleMat->setDiffuse(Color3f(0, 1, 0));
        simpleMat->setLit    (true            );

        geo = dynamic_cast<Geometry *>(getHandleYNode()->getCore());
        geo->setMaterial(simpleMat);

        //
        // make the blue z-axis transform and handle

        pNode = Node::create();
        setTransZNode(pNode);
        ComponentTransformUnrecPtr transHandleZC = ComponentTransform::create();
        pNode = makeHandleGeo();
        setHandleZNode(pNode);
        pMat = SimpleMaterial::create();
        setMaterialZ  (pMat);

        getTransZNode()->setCore (transHandleZC);
        getTransZNode()->addChild(getHandleZNode());

        transHandleZC->setTranslation(Vec3f(0, 0, getLength()[2])                  );
        transHandleZC->setRotation   (Quaternion(Vec3f(1, 0, 0), osgDegree2Rad(90)));

        simpleMat = dynamic_cast<SimpleMaterial *>(getMaterialZ());
        simpleMat->setDiffuse(Color3f(0, 0, 1));
        simpleMat->setLit    (true            );

        geo = dynamic_cast<Geometry *>(getHandleZNode()->getCore());
        geo->setMaterial(simpleMat);

    }
}

void Manipulator::updateLength(void)
{
    Vec3f scale(Vec3f(1.0f,1.0f,1.0f) * osgMax(1.0f, getLength().maxValue() * 0.2f));
    dynamic_cast<ComponentTransform*>(getTransXNode()->getCore())->setTranslation(Vec3f(getLength()[0], 0, 0));
    dynamic_cast<ComponentTransform*>(getTransXNode()->getCore())->setScale(scale);
    dynamic_cast<ComponentTransform*>(getTransYNode()->getCore())->setTranslation(Vec3f(0, getLength()[1], 0));
    dynamic_cast<ComponentTransform*>(getTransYNode()->getCore())->setScale(scale);
    dynamic_cast<ComponentTransform*>(getTransZNode()->getCore())->setTranslation(Vec3f(0, 0, getLength()[2]));
    dynamic_cast<ComponentTransform*>(getTransZNode()->getCore())->setScale(scale);

    //Update the Axes
    NodeUnrecPtr pNode = makeCoordAxis(getLength()[0], 2.0, false);
    setAxisLinesN(pNode);

    Node *parent;

    if ( !getParents().empty() )
    {
        parent = dynamic_cast<Node *>(getParents()[0]); // Dangerous! multiple parents?
    }
    else
    {
        parent = NULL;
    }
    if ( NULL != parent )
    {
        // remove old childs
        while(parent->getNChildren() > 0)
        {
            parent->subChild(parent->getChild(0));
        }
        addHandleGeo(parent);
    }
}

void Manipulator::updateParent(void)
{
    Node *parent;

    if ( !getParents().empty() )
    {
        parent = dynamic_cast<Node *>(getParents()[0]); // Dangerous! multiple parents?
    }
    else
    {
        parent = NULL;
    }


    if ( parent != _activeParent )
    {
        if ( NULL != parent )
        {
            // remove old childs
            while(parent->getNChildren() > 0)
            {
                parent->subChild(parent->getChild(0));
            }
            addHandleGeo(parent);
        }

        if ( _activeParent != NULL )
        {
            subHandleGeo(_activeParent);
        }

        _activeParent = parent;
    }
}

void Manipulator::onDestroy()
{
}

void Manipulator::resolveLinks(void)
{
    Inherited::resolveLinks();

    _activeParent  = NULL;
}

void Manipulator::getTransformation(Vec3f        &translation,
                                    Quaternion   &rotation,
                                    Vec3f        &scaleFactor,
                                    Quaternion   &scaleOrientation) const
{
    Matrix     m;
    getTransformation(m);
    m.getTransform(translation, rotation, scaleFactor, scaleOrientation);
}
    
void Manipulator::getTransformation(Matrix        &mat) const
{
    if(getTarget()->getCore()->getType() == Transform::getClassType())
    {
        Transform *t = dynamic_cast<Transform *>(getTarget()->getCore());
        mat = t->getMatrix();
    }
    else if(getTarget()->getCore()->getType() == StackedTransform::getClassType())
    {
        mat.setIdentity();
        StackedTransform *t = dynamic_cast<StackedTransform *>(getTarget()->getCore());
        t->accumulateMatrix(mat);
    }
}

void Manipulator::setTransformation(const Matrix        &mat)
{
    Vec3f      translation;
    Quaternion rotation;
    Vec3f      scaleFactor;
    Quaternion scaleOrientation;

    mat.getTransform(translation,rotation,scaleFactor,scaleOrientation);
    setTransformation(translation,rotation,scaleFactor,scaleOrientation);
}

void Manipulator::setTransformation(const Vec3f        &translation,
                                    const Quaternion   &rotation,
                                    const Vec3f        &scaleFactor,
                                    const Quaternion   &scaleOrientation)
{
    if(getTarget()->getCore()->getType() == Transform::getClassType())
    {
        Transform *t = dynamic_cast<Transform *>(getTarget()->getCore());
        Matrix m;
        m.setTransform(translation, rotation, scaleFactor, scaleOrientation);
        t->setMatrix(m);
    }
    else if(getTarget()->getCore()->getType() == StackedTransform::getClassType())
    {
        Vec3f EulerRot;
        rotation.getEulerAngleDeg(EulerRot);
        StackedTransform *StackTrans = dynamic_cast<StackedTransform *>(getTarget()->getCore());


        //Translate
        TranslationTransformationElementRecPtr Trans = StackTrans->getElement<TranslationTransformationElement>(StackedTransform::TranslateName);
        if(Trans == NULL)
        {
            Trans = TranslationTransformationElement::create();
            StackTrans->insertIntoNamedTransformElements(0, Trans, StackedTransform::TranslateName);
        }
        Trans->setTranslation(translation);

        //Rotate
        RotationTransformationElementRecPtr RotZ = StackTrans->getElement<RotationTransformationElement>(StackedTransform::RotateZName);
        if(RotZ == NULL)
        {
            RotZ = RotationTransformationElement::create();
            StackTrans->insertIntoNamedTransformElements(1, RotZ, StackedTransform::RotateZName);
            RotZ->setAxis(Vec3f(0.0f,0.0f,1.0f));
        }
        RotZ->setAngle(EulerRot.z());

        RotationTransformationElementRecPtr RotY = StackTrans->getElement<RotationTransformationElement>(StackedTransform::RotateYName);
        if(RotY == NULL)
        {
            RotY = RotationTransformationElement::create();
            StackTrans->insertIntoNamedTransformElements(2, RotY, StackedTransform::RotateYName);
            RotY->setAxis(Vec3f(0.0f,1.0f,0.0f));
        }
        RotY->setAngle(EulerRot.y());

        RotationTransformationElementRecPtr RotX = StackTrans->getElement<RotationTransformationElement>(StackedTransform::RotateXName);
        if(RotX == NULL)
        {
            RotX = RotationTransformationElement::create();
            StackTrans->insertIntoNamedTransformElements(3, RotX, StackedTransform::RotateXName);
            RotX->setAxis(Vec3f(1.0f,0.0f,0.0f));
        }
        RotX->setAngle(EulerRot.x());

        //Scale Orientation
        //Scale Factor
        ScaleTransformationElementRecPtr Scale = StackTrans->getElement<ScaleTransformationElement>(StackedTransform::ScaleName);
        if(Scale == NULL)
        {
            Scale = ScaleTransformationElement::create();
            StackTrans->pushToNamedTransformElements(Scale, StackedTransform::ScaleName);
        }
        Scale->setScale(scaleFactor);
    }
}

/*----------------------- constructors & destructors ----------------------*/

Manipulator::Manipulator(void) :
    Inherited(),
    _activeParent( NULL ),
    _externalUpdateHandler( NULL ),
    _isManipulating(false)
{
}

Manipulator::Manipulator(const Manipulator &source) :
    Inherited(source),
    _isManipulating(false)

{
    //TODO: empty copy constructor?!?!?!?
}

Manipulator::~Manipulator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Manipulator::setExternalUpdateHandler(ExternalUpdateHandler* h)
{
    _externalUpdateHandler = h;
}

void Manipulator::callExternalUpdateHandler()
{
    if ( NULL != _externalUpdateHandler )
    {
        _externalUpdateHandler->update(this->getTarget());
    }
}

//! react to field changes

void Manipulator::changed(ConstFieldMaskArg whichField,
                          UInt32            origin,
                          BitVector         details    )
{
    Inherited::changed(whichField, origin, details);

    if ( whichField & TargetFieldMask )
    {
        reverseTransform();
    }

    if ( whichField & ParentsFieldMask )
    {
        updateParent();
    }

    if (whichField & LengthFieldMask)
    {
        updateLength();
    }
}

