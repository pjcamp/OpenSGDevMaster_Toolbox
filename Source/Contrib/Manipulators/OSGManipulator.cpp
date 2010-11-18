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

#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGDepthChunk.h"
#include "OSGBlendChunk.h"
#include "OSGPolygonChunk.h"

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
#include "OSGScreenTransform.h"

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
    n->addChild(_root);
}

void Manipulator::subHandleGeo(Node *n)
{
    n->subChild(_root);
}

void Manipulator::startManip(Node *subHandle)
{
    if(getTarget() == NULL) return;

    if(!isManipulating())
    {
        setActiveHandle(getNodeHandle(subHandle));

        applyStateMaterial(getActiveHandle());

        if(getActiveHandle() != NO_AXES_HANDLE)
        {
            getTransformation(_initialXForm);
        }
    }
}

void Manipulator::cancelManip(void)
{
    if(getTarget() == NULL) return;

    if(isManipulating())
    {
        setTransformation(_initialXForm);


        UInt32 ManipAxis(getActiveHandle());

        setActiveHandle(NO_AXES_HANDLE);
        applyStateMaterial(ManipAxis);
    }
}

void Manipulator::endManip(void)
{
    if(getTarget() == NULL) return;

    if(isManipulating())
    {
        UInt32 ManipAxis(getActiveHandle());

        setActiveHandle(NO_AXES_HANDLE);
        applyStateMaterial(ManipAxis);
    }
}

void Manipulator::rolloverHandle(Node *subHandle)
{
    if(getTarget() == NULL) return;

    if(!isRolledOver())
    {
        setRolloverHandle(getNodeHandle(subHandle));

        applyStateMaterial(getRolloverHandle());
    }
}

void Manipulator::exitHandle(void)
{
    if(getTarget() == NULL) return;

    if(isRolledOver())
    {

        UInt32 ManipAxis(getRolloverHandle());

        setRolloverHandle(NO_AXES_HANDLE);
        applyStateMaterial(ManipAxis);
    }
}

bool Manipulator::isRolledOver(void) const
{
    if(getTarget() == NULL) return false;

    return getRolloverHandle() != NO_AXES_HANDLE;
}


UInt16 Manipulator::getNodeHandle(Node* const HandleNode) const
{
    switch(HandleNode->getTravMask())
    {
    case ALL_AXIS_TRAV_MASK:
        return ALL_AXES_HANDLE;
        break;
    case XY_AXES_TRAV_MASK:
        return XY_AXES_HANDLE;
        break;
    case XZ_AXES_TRAV_MASK:
        return XZ_AXES_HANDLE;
        break;
    case YZ_AXES_TRAV_MASK:
        return YZ_AXES_HANDLE;
        break;
    case X_AXIS_TRAV_MASK:
        return X_AXIS_HANDLE;
        break;
    case Y_AXIS_TRAV_MASK:
        return Y_AXIS_HANDLE;
        break;
    case Z_AXIS_TRAV_MASK:
        return Z_AXIS_HANDLE;
        break;
    default:
        return NO_AXES_HANDLE;
        break;
    }
}

void Manipulator::applyStateMaterial(UInt16 Axis)
{
    if(Axis != NO_AXES_HANDLE)
    {
        for(UInt32 i(0) ; i<editAxisGeometries(Axis)->size(); ++i)
        {
            (*editAxisGeometries(Axis))[i]->setMaterial(getCurStateAxisMaterial(Axis));
        }
    }
}

Material* Manipulator::getCurStateAxisMaterial(UInt16 Axis) const
{
    if(isManipulating())
    {
        return getMaterialSelected();
    }
    else if(isRolledOver())
    {
        return getMaterialRollover();
    }
    else
    {
        return getAxisMaterial(Axis);
    }
}

bool Manipulator::isManipulating(void) const
{
    return getActiveHandle() != NO_AXES_HANDLE;
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

/*! The mouseMove is called by the viewer when the mouse is moved in the
    viewer and this handle is the active one.

    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */
void Manipulator::mouseMove(const Int16 x,
                            const Int16 y)
{
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
}

void Manipulator::mouseButtonRelease(const UInt16 button,
                                     const Int16  x,
                                     const Int16  y     )
{
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

void Manipulator::createMaterials(void)
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

    ChunkMaterialUnrecPtr pMat;
    MaterialChunkUnrecPtr DefaultMaterialChunk;

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

void Manipulator::onCreate(const Manipulator* source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        createMaterials();

        NodeUnrecPtr XAxisManipulator = createXAxisManipulator();
        NodeUnrecPtr YAxisManipulator = createYAxisManipulator();
        NodeUnrecPtr ZAxisManipulator = createZAxisManipulator();

        ScreenTransformRecPtr TheScreenTransform = ScreenTransform::create();
        Matrix ScreenTransformView;
        ScreenTransformView.setTranslate(0.0f,0.0f,-getManipulatorScreenDepth());
        TheScreenTransform->setView(ScreenTransformView);
        TheScreenTransform->setApplyBeaconRotation(true);
        TheScreenTransform->setApplyBeaconScreenTranslation(true);
        TheScreenTransform->setInvertWorldTransform(true);
        TheScreenTransform->setInvertViewTransform(true);

        _root = makeNodeFor(TheScreenTransform);
        _root->addChild(XAxisManipulator);
        _root->addChild(YAxisManipulator);
        _root->addChild(ZAxisManipulator);
    }
}

void Manipulator::updateLength(void)
{
    //Vec3f scale(Vec3f(1.0f,1.0f,1.0f) * getLength().maxValue());
    //dynamic_cast<ComponentTransform*>(_root->getCore())->setScale(scale);

    //Node *parent;

    //if ( !getParents().empty() )
    //{
    //    parent = dynamic_cast<Node *>(getParents()[0]); // Dangerous! multiple parents?
    //}
    //else
    //{
    //    parent = NULL;
    //}
    //if ( NULL != parent )
    //{
    //    // remove old childs
    //    while(parent->getNChildren() > 0)
    //    {
    //        parent->subChild(parent->getChild(0));
    //    }
    //    addHandleGeo(parent);
    //}
}

void Manipulator::updateWidth(void)
{
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
    _root = NULL;
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

NodeTransitPtr Manipulator::createAxisManipulator(UInt16 Axis)
{
    NodeUnrecPtr RootXManip = makeCoredNode<Group>();

    //Make axis Geometry
    if( Axis == X_AXIS_HANDLE ||
        Axis == Y_AXIS_HANDLE ||
        Axis == Z_AXIS_HANDLE)
    {
        Vec3f Direction(0.0f,0.0f,0.0f);
        Direction[Axis] = 1.0f;

        GeometryUnrecPtr AxisCylendarGeo = makeCylinderGeo(1.0f, getWidth()[Axis], 16, true, false,false);
        AxisCylendarGeo->setMaterial(getAxisMaterial(Axis));
        editAxisGeometries(Axis)->push_back(AxisCylendarGeo);

        NodeUnrecPtr AxisCylendarNode = makeNodeFor(AxisCylendarGeo);
        AxisCylendarNode->setTravMask(NONCOLLIDE_RENDERED_TRAV_MASK);

        Matrix AxisMat;
        AxisMat.setTransform(Direction * 0.5f, Quaternion(Vec3f(0.0f,1.0f,0.0f),Direction));

        TransformUnrecPtr AxisTransform = Transform::create();
        AxisTransform->setMatrix(AxisMat);

        NodeUnrecPtr AxisNode = makeNodeFor(AxisTransform);
        AxisNode->addChild(AxisCylendarNode);

        //Make axis collision geometry
        GeometryUnrecPtr AxisCylendarCollisionGeo = makeCylinderGeo(1.0f, getWidth()[Axis]*2.0f, 10, true, false,false);

        NodeUnrecPtr AxisCylendarCollisionNode = makeNodeFor(AxisCylendarCollisionGeo);
        AxisCylendarCollisionNode->setTravMask(getAxisCollisionTravMask(Axis));

        AxisNode->addChild(AxisCylendarCollisionNode);
        
        RootXManip->addChild(AxisNode);
    }

    //Make the handle Geometry
    NodeUnrecPtr HandleGeoNode = makeHandleGeo(0.1f, Axis);

    RootXManip->addChild(HandleGeoNode);

    return NodeTransitPtr(RootXManip);
}

NodeTransitPtr Manipulator::createXAxisManipulator(void)
{
    return createAxisManipulator(X_AXIS_HANDLE);
}

NodeTransitPtr Manipulator::createYAxisManipulator(void)
{
    return createAxisManipulator(Y_AXIS_HANDLE);
}

NodeTransitPtr Manipulator::createZAxisManipulator(void)
{
    return createAxisManipulator(Z_AXIS_HANDLE);
}

UInt32 Manipulator::getAxisCollisionTravMask(UInt16 Axis) const
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
    default:
        return NONE_TRAV_MASK;
        break;
    }
}

Material* Manipulator::getAxisMaterial(UInt16 Axis) const
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
    default:
        return NULL;
        break;
    }
}
    
MFUnrecGeometryPtr* Manipulator::editAxisGeometries(UInt16 Axis)
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
    default:
        return NULL;
        break;
    }
}

/*----------------------- constructors & destructors ----------------------*/

Manipulator::Manipulator(void) :
    Inherited(),
    _activeParent( NULL ),
    _root( NULL ),
    _externalUpdateHandler( NULL )
{
}

Manipulator::Manipulator(const Manipulator &source) :
    Inherited(source),
    _activeParent( NULL ),
    _root( NULL ),
    _externalUpdateHandler( NULL )
{
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
        dynamic_cast<ScreenTransform*>(_root->getCore())->setBeacon(getTarget());
        //reverseTransform();
    }
    if ( whichField & ManipulatorScreenDepthFieldMask )
    {
        dynamic_cast<ScreenTransform*>(_root->getCore())->editView().setTranslate(Vec3f(0.0f,0.0f,-getManipulatorScreenDepth()));
    }
    if ( whichField & MaintainScreenSizeFieldMask )
    {
        dynamic_cast<ScreenTransform*>(_root->getCore())->setApplyBeaconScreenTranslation(getMaintainScreenSize());
        dynamic_cast<ScreenTransform*>(_root->getCore())->setInvertWorldTransform(getMaintainScreenSize());
        dynamic_cast<ScreenTransform*>(_root->getCore())->setInvertViewTransform(getMaintainScreenSize());
    }

    if ( whichField & ParentsFieldMask )
    {
        updateParent();
    }

    if (whichField & LengthFieldMask)
    {
        updateLength();
    }
    if (whichField & WidthFieldMask)
    {
        updateWidth();
    }
}

