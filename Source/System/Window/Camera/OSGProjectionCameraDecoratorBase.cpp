/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class ProjectionCameraDecorator!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILEPROJECTIONCAMERADECORATORINST

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>



#include <OSGNode.h> // User Class

#include "OSGProjectionCameraDecoratorBase.h"
#include "OSGProjectionCameraDecorator.h"

#include "boost/bind.hpp"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ProjectionCameraDecorator
    \ingroup GrpSystemWindowCameraDecoratorsStereo

    The decorator for tracked projection screens, see \ref
    PageSystemWindowCameraDecoratorsStereoProjection for a description.

    The parameters are defined by the _sfUser and _mfSurface fields.

    \dev

    The derived parameters used to actually calculate the matrix are stored in the
    _sfLeft, _sfBottom, _sfNormal, sfWidth and _sfHeight fields.

    \enddev
 */

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

/*! \var NodePtr         ProjectionCameraDecoratorBase::_sfUser
    The coordinate system relative to the camera.
*/

/*! \var Pnt3f           ProjectionCameraDecoratorBase::_mfSurface
    4 points describing the rectangular projection surface, in the camera
    coordinate system. Counterclockwise, starting at lower left corner of the screen.
*/

/*! \var Plane           ProjectionCameraDecoratorBase::_sfLeft
    The left edge direction vector.
*/

/*! \var Plane           ProjectionCameraDecoratorBase::_sfBottom
    The bottom edge direction vector.
*/

/*! \var Plane           ProjectionCameraDecoratorBase::_sfNormal
    The normal of the projection surface.
*/

/*! \var Real32          ProjectionCameraDecoratorBase::_sfWidth
    The width of the projection screen.
*/

/*! \var Real32          ProjectionCameraDecoratorBase::_sfHeight
    The height of the projection screen.
*/


void ProjectionCameraDecoratorBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUnrecNodePtr::Description(
        SFUnrecNodePtr::getClassType(),
        "user",
        "The coordinate system relative to the camera.\n",
        UserFieldId, UserFieldMask,
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&ProjectionCameraDecoratorBase::editHandleUser),
        static_cast<FieldGetMethodSig >(&ProjectionCameraDecoratorBase::getHandleUser));

    oType.addInitialDesc(pDesc);

    pDesc = new MFPnt3f::Description(
        MFPnt3f::getClassType(),
        "surface",
        "4 points describing the rectangular projection surface, in the camera\n"
        "coordinate system. Counterclockwise, starting at lower left corner of the screen.\n",
        SurfaceFieldId, SurfaceFieldMask,
        false,
        Field::MFDefaultFlags,
        static_cast<FieldEditMethodSig>(&ProjectionCameraDecoratorBase::editHandleSurface),
        static_cast<FieldGetMethodSig >(&ProjectionCameraDecoratorBase::getHandleSurface));

    oType.addInitialDesc(pDesc);

    pDesc = new SFPlane::Description(
        SFPlane::getClassType(),
        "left",
        "The left edge direction vector.\n",
        LeftFieldId, LeftFieldMask,
        true,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&ProjectionCameraDecoratorBase::editHandleLeft),
        static_cast<FieldGetMethodSig >(&ProjectionCameraDecoratorBase::getHandleLeft));

    oType.addInitialDesc(pDesc);

    pDesc = new SFPlane::Description(
        SFPlane::getClassType(),
        "bottom",
        "The bottom edge direction vector.\n",
        BottomFieldId, BottomFieldMask,
        true,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&ProjectionCameraDecoratorBase::editHandleBottom),
        static_cast<FieldGetMethodSig >(&ProjectionCameraDecoratorBase::getHandleBottom));

    oType.addInitialDesc(pDesc);

    pDesc = new SFPlane::Description(
        SFPlane::getClassType(),
        "normal",
        "The normal of the projection surface.\n",
        NormalFieldId, NormalFieldMask,
        true,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&ProjectionCameraDecoratorBase::editHandleNormal),
        static_cast<FieldGetMethodSig >(&ProjectionCameraDecoratorBase::getHandleNormal));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "width",
        "The width of the projection screen.\n",
        WidthFieldId, WidthFieldMask,
        true,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&ProjectionCameraDecoratorBase::editHandleWidth),
        static_cast<FieldGetMethodSig >(&ProjectionCameraDecoratorBase::getHandleWidth));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "height",
        "The height of the projection screen.\n",
        HeightFieldId, HeightFieldMask,
        true,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&ProjectionCameraDecoratorBase::editHandleHeight),
        static_cast<FieldGetMethodSig >(&ProjectionCameraDecoratorBase::getHandleHeight));

    oType.addInitialDesc(pDesc);
}


ProjectionCameraDecoratorBase::TypeObject ProjectionCameraDecoratorBase::_type(
    ProjectionCameraDecoratorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    (PrototypeCreateF) &ProjectionCameraDecoratorBase::createEmptyLocal,
    ProjectionCameraDecorator::initMethod,
    ProjectionCameraDecorator::exitMethod,
    (InitalInsertDescFunc) &ProjectionCameraDecoratorBase::classDescInserter,
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"ProjectionCameraDecorator\"\n"
    "\tparent=\"StereoCameraDecorator\"\n"
    "\tlibrary=\"Window\"\n"
    "\tpointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "\tsystemcomponent=\"true\"\n"
    "\tparentsystemcomponent=\"true\"\n"
    "\tdecoratable=\"false\"\n"
    ">\n"
    "\\ingroup GrpSystemWindowCameraDecoratorsStereo\n"
    "\n"
    "The decorator for tracked projection screens, see \\ref\n"
    "PageSystemWindowCameraDecoratorsStereoProjection for a description.\n"
    "\n"
    "The parameters are defined by the _sfUser and _mfSurface fields.\n"
    "\n"
    "\\dev\n"
    "\n"
    "The derived parameters used to actually calculate the matrix are stored in the\n"
    "_sfLeft, _sfBottom, _sfNormal, sfWidth and _sfHeight fields.\n"
    "\n"
    "\\enddev\n"
    "\t<Field\n"
    "\t\tname=\"user\"\n"
    "\t\ttype=\"NodePtr\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\tThe coordinate system relative to the camera.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"surface\"\n"
    "\t\ttype=\"Pnt3f\"\n"
    "\t\tcardinality=\"multi\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\t4 points describing the rectangular projection surface, in the camera\n"
    "        coordinate system. Counterclockwise, starting at lower left corner of the screen.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"left\"\n"
    "\t\ttype=\"Plane\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"protected\"\n"
    "\t>\n"
    "\tThe left edge direction vector.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"bottom\"\n"
    "\t\ttype=\"Plane\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"protected\"\n"
    "\t>\n"
    "\tThe bottom edge direction vector.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"normal\"\n"
    "\t\ttype=\"Plane\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"protected\"\n"
    "\t>\n"
    "\tThe normal of the projection surface.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"width\"\n"
    "\t\ttype=\"Real32\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\tThe width of the projection screen.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"height\"\n"
    "\t\ttype=\"Real32\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\tThe height of the projection screen.\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    "\\ingroup GrpSystemWindowCameraDecoratorsStereo\n"
    "\n"
    "The decorator for tracked projection screens, see \\ref\n"
    "PageSystemWindowCameraDecoratorsStereoProjection for a description.\n"
    "\n"
    "The parameters are defined by the _sfUser and _mfSurface fields.\n"
    "\n"
    "\\dev\n"
    "\n"
    "The derived parameters used to actually calculate the matrix are stored in the\n"
    "_sfLeft, _sfBottom, _sfNormal, sfWidth and _sfHeight fields.\n"
    "\n"
    "\\enddev\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ProjectionCameraDecoratorBase::getType(void)
{
    return _type;
}

const FieldContainerType &ProjectionCameraDecoratorBase::getType(void) const
{
    return _type;
}

UInt32 ProjectionCameraDecoratorBase::getContainerSize(void) const
{
    return sizeof(ProjectionCameraDecorator);
}

/*------------------------- decorator get ------------------------------*/


//! Get the ProjectionCameraDecorator::_sfUser field.
const SFUnrecNodePtr *ProjectionCameraDecoratorBase::getSFUser(void) const
{
    return &_sfUser;
}

SFUnrecNodePtr      *ProjectionCameraDecoratorBase::editSFUser           (void)
{
    editSField(UserFieldMask);

    return &_sfUser;
}

MFPnt3f *ProjectionCameraDecoratorBase::editMFSurface(void)
{
    editMField(SurfaceFieldMask, _mfSurface);

    return &_mfSurface;
}

const MFPnt3f *ProjectionCameraDecoratorBase::getMFSurface(void) const
{
    return &_mfSurface;
}

#ifdef OSG_1_GET_COMPAT
MFPnt3f             *ProjectionCameraDecoratorBase::getMFSurface        (void)
{
    return this->editMFSurface        ();
}
#endif

SFPlane *ProjectionCameraDecoratorBase::editSFLeft(void)
{
    editSField(LeftFieldMask);

    return &_sfLeft;
}

const SFPlane *ProjectionCameraDecoratorBase::getSFLeft(void) const
{
    return &_sfLeft;
}

#ifdef OSG_1_GET_COMPAT
SFPlane             *ProjectionCameraDecoratorBase::getSFLeft           (void)
{
    return this->editSFLeft           ();
}
#endif

SFPlane *ProjectionCameraDecoratorBase::editSFBottom(void)
{
    editSField(BottomFieldMask);

    return &_sfBottom;
}

const SFPlane *ProjectionCameraDecoratorBase::getSFBottom(void) const
{
    return &_sfBottom;
}

#ifdef OSG_1_GET_COMPAT
SFPlane             *ProjectionCameraDecoratorBase::getSFBottom         (void)
{
    return this->editSFBottom         ();
}
#endif

SFPlane *ProjectionCameraDecoratorBase::editSFNormal(void)
{
    editSField(NormalFieldMask);

    return &_sfNormal;
}

const SFPlane *ProjectionCameraDecoratorBase::getSFNormal(void) const
{
    return &_sfNormal;
}

#ifdef OSG_1_GET_COMPAT
SFPlane             *ProjectionCameraDecoratorBase::getSFNormal         (void)
{
    return this->editSFNormal         ();
}
#endif

SFReal32 *ProjectionCameraDecoratorBase::editSFWidth(void)
{
    editSField(WidthFieldMask);

    return &_sfWidth;
}

const SFReal32 *ProjectionCameraDecoratorBase::getSFWidth(void) const
{
    return &_sfWidth;
}

#ifdef OSG_1_GET_COMPAT
SFReal32            *ProjectionCameraDecoratorBase::getSFWidth          (void)
{
    return this->editSFWidth          ();
}
#endif

SFReal32 *ProjectionCameraDecoratorBase::editSFHeight(void)
{
    editSField(HeightFieldMask);

    return &_sfHeight;
}

const SFReal32 *ProjectionCameraDecoratorBase::getSFHeight(void) const
{
    return &_sfHeight;
}

#ifdef OSG_1_GET_COMPAT
SFReal32            *ProjectionCameraDecoratorBase::getSFHeight         (void)
{
    return this->editSFHeight         ();
}
#endif





/*------------------------------ access -----------------------------------*/

UInt32 ProjectionCameraDecoratorBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (UserFieldMask & whichField))
    {
        returnValue += _sfUser.getBinSize();
    }
    if(FieldBits::NoField != (SurfaceFieldMask & whichField))
    {
        returnValue += _mfSurface.getBinSize();
    }
    if(FieldBits::NoField != (LeftFieldMask & whichField))
    {
        returnValue += _sfLeft.getBinSize();
    }
    if(FieldBits::NoField != (BottomFieldMask & whichField))
    {
        returnValue += _sfBottom.getBinSize();
    }
    if(FieldBits::NoField != (NormalFieldMask & whichField))
    {
        returnValue += _sfNormal.getBinSize();
    }
    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        returnValue += _sfWidth.getBinSize();
    }
    if(FieldBits::NoField != (HeightFieldMask & whichField))
    {
        returnValue += _sfHeight.getBinSize();
    }

    return returnValue;
}

void ProjectionCameraDecoratorBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (UserFieldMask & whichField))
    {
        _sfUser.copyToBin(pMem);
    }
    if(FieldBits::NoField != (SurfaceFieldMask & whichField))
    {
        _mfSurface.copyToBin(pMem);
    }
    if(FieldBits::NoField != (LeftFieldMask & whichField))
    {
        _sfLeft.copyToBin(pMem);
    }
    if(FieldBits::NoField != (BottomFieldMask & whichField))
    {
        _sfBottom.copyToBin(pMem);
    }
    if(FieldBits::NoField != (NormalFieldMask & whichField))
    {
        _sfNormal.copyToBin(pMem);
    }
    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        _sfWidth.copyToBin(pMem);
    }
    if(FieldBits::NoField != (HeightFieldMask & whichField))
    {
        _sfHeight.copyToBin(pMem);
    }
}

void ProjectionCameraDecoratorBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (UserFieldMask & whichField))
    {
        _sfUser.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (SurfaceFieldMask & whichField))
    {
        _mfSurface.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (LeftFieldMask & whichField))
    {
        _sfLeft.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (BottomFieldMask & whichField))
    {
        _sfBottom.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (NormalFieldMask & whichField))
    {
        _sfNormal.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        _sfWidth.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (HeightFieldMask & whichField))
    {
        _sfHeight.copyFromBin(pMem);
    }
}

//! create a new instance of the class
ProjectionCameraDecoratorTransitPtr ProjectionCameraDecoratorBase::create(void)
{
    ProjectionCameraDecoratorTransitPtr fc;

    if(getClassType().getPrototype() != NullFC)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<ProjectionCameraDecorator>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ProjectionCameraDecoratorTransitPtr ProjectionCameraDecoratorBase::createLocal(BitVector bFlags)
{
    ProjectionCameraDecoratorTransitPtr fc;

    if(getClassType().getPrototype() != NullFC)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<ProjectionCameraDecorator>(tmpPtr);
    }

    return fc;
}

//! create an empty new instance of the class, do not copy the prototype
ProjectionCameraDecoratorPtr ProjectionCameraDecoratorBase::createEmpty(void)
{
    ProjectionCameraDecoratorPtr returnValue;

    newPtr<ProjectionCameraDecorator>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &= 
        ~Thread::getCurrentLocalFlags(); 

    return returnValue;
}

ProjectionCameraDecoratorPtr ProjectionCameraDecoratorBase::createEmptyLocal(BitVector bFlags)
{
    ProjectionCameraDecoratorPtr returnValue;

    newPtr<ProjectionCameraDecorator>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ProjectionCameraDecoratorBase::shallowCopy(void) const
{
    ProjectionCameraDecoratorPtr tmpPtr;

    newPtr(tmpPtr, 
           dynamic_cast<const ProjectionCameraDecorator *>(this), 
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}

FieldContainerTransitPtr ProjectionCameraDecoratorBase::shallowCopyLocal(
    BitVector bFlags) const
{
    ProjectionCameraDecoratorPtr tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ProjectionCameraDecorator *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

ProjectionCameraDecoratorBase::ProjectionCameraDecoratorBase(void) :
    Inherited(),
    _sfUser                   (NullFC),
    _mfSurface                (),
    _sfLeft                   (),
    _sfBottom                 (),
    _sfNormal                 (),
    _sfWidth                  (),
    _sfHeight                 ()
{
}

ProjectionCameraDecoratorBase::ProjectionCameraDecoratorBase(const ProjectionCameraDecoratorBase &source) :
    Inherited(source),
    _sfUser                   (NullFC),
    _mfSurface                (source._mfSurface                ),
    _sfLeft                   (source._sfLeft                   ),
    _sfBottom                 (source._sfBottom                 ),
    _sfNormal                 (source._sfNormal                 ),
    _sfWidth                  (source._sfWidth                  ),
    _sfHeight                 (source._sfHeight                 )
{
}


/*-------------------------- destructors ----------------------------------*/

ProjectionCameraDecoratorBase::~ProjectionCameraDecoratorBase(void)
{
}

void ProjectionCameraDecoratorBase::onCreate(const ProjectionCameraDecorator *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        ProjectionCameraDecorator *pThis = static_cast<ProjectionCameraDecorator *>(this);

        pThis->setUser(source->getUser());
    }
}

GetFieldHandlePtr ProjectionCameraDecoratorBase::getHandleUser            (void) const
{
    SFUnrecNodePtr::GetHandlePtr returnValue(
        new  SFUnrecNodePtr::GetHandle(
             &_sfUser, 
             this->getType().getFieldDesc(UserFieldId)));

    return returnValue;
}

EditFieldHandlePtr ProjectionCameraDecoratorBase::editHandleUser           (void)
{
    SFUnrecNodePtr::EditHandlePtr returnValue(
        new  SFUnrecNodePtr::EditHandle(
             &_sfUser, 
             this->getType().getFieldDesc(UserFieldId)));

    returnValue->setSetMethod(boost::bind(&ProjectionCameraDecorator::setUser, 
                                          static_cast<ProjectionCameraDecorator *>(this), _1));

    editSField(UserFieldMask);

    return returnValue;
}

GetFieldHandlePtr ProjectionCameraDecoratorBase::getHandleSurface         (void) const
{
    MFPnt3f::GetHandlePtr returnValue(
        new  MFPnt3f::GetHandle(
             &_mfSurface, 
             this->getType().getFieldDesc(SurfaceFieldId)));

    return returnValue;
}

EditFieldHandlePtr ProjectionCameraDecoratorBase::editHandleSurface        (void)
{
    MFPnt3f::EditHandlePtr returnValue(
        new  MFPnt3f::EditHandle(
             &_mfSurface, 
             this->getType().getFieldDesc(SurfaceFieldId)));

    editMField(SurfaceFieldMask, _mfSurface);

    return returnValue;
}

GetFieldHandlePtr ProjectionCameraDecoratorBase::getHandleLeft            (void) const
{
    SFPlane::GetHandlePtr returnValue(
        new  SFPlane::GetHandle(
             &_sfLeft, 
             this->getType().getFieldDesc(LeftFieldId)));

    return returnValue;
}

EditFieldHandlePtr ProjectionCameraDecoratorBase::editHandleLeft           (void)
{
    SFPlane::EditHandlePtr returnValue(
        new  SFPlane::EditHandle(
             &_sfLeft, 
             this->getType().getFieldDesc(LeftFieldId)));

    editSField(LeftFieldMask);

    return returnValue;
}

GetFieldHandlePtr ProjectionCameraDecoratorBase::getHandleBottom          (void) const
{
    SFPlane::GetHandlePtr returnValue(
        new  SFPlane::GetHandle(
             &_sfBottom, 
             this->getType().getFieldDesc(BottomFieldId)));

    return returnValue;
}

EditFieldHandlePtr ProjectionCameraDecoratorBase::editHandleBottom         (void)
{
    SFPlane::EditHandlePtr returnValue(
        new  SFPlane::EditHandle(
             &_sfBottom, 
             this->getType().getFieldDesc(BottomFieldId)));

    editSField(BottomFieldMask);

    return returnValue;
}

GetFieldHandlePtr ProjectionCameraDecoratorBase::getHandleNormal          (void) const
{
    SFPlane::GetHandlePtr returnValue(
        new  SFPlane::GetHandle(
             &_sfNormal, 
             this->getType().getFieldDesc(NormalFieldId)));

    return returnValue;
}

EditFieldHandlePtr ProjectionCameraDecoratorBase::editHandleNormal         (void)
{
    SFPlane::EditHandlePtr returnValue(
        new  SFPlane::EditHandle(
             &_sfNormal, 
             this->getType().getFieldDesc(NormalFieldId)));

    editSField(NormalFieldMask);

    return returnValue;
}

GetFieldHandlePtr ProjectionCameraDecoratorBase::getHandleWidth           (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfWidth, 
             this->getType().getFieldDesc(WidthFieldId)));

    return returnValue;
}

EditFieldHandlePtr ProjectionCameraDecoratorBase::editHandleWidth          (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfWidth, 
             this->getType().getFieldDesc(WidthFieldId)));

    editSField(WidthFieldMask);

    return returnValue;
}

GetFieldHandlePtr ProjectionCameraDecoratorBase::getHandleHeight          (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfHeight, 
             this->getType().getFieldDesc(HeightFieldId)));

    return returnValue;
}

EditFieldHandlePtr ProjectionCameraDecoratorBase::editHandleHeight         (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfHeight, 
             this->getType().getFieldDesc(HeightFieldId)));

    editSField(HeightFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void ProjectionCameraDecoratorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<ProjectionCameraDecoratorBase *>(&oFrom),
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainerPtr ProjectionCameraDecoratorBase::createAspectCopy(void) const
{
    ProjectionCameraDecoratorPtr returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const ProjectionCameraDecorator *>(this));

    return returnValue;
}
#endif

void ProjectionCameraDecoratorBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<ProjectionCameraDecorator *>(this)->setUser(NullFC);

#ifdef OSG_MT_CPTR_ASPECT
    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);
#endif

#ifdef OSG_MT_CPTR_ASPECT
    _mfSurface.terminateShare(Thread::getCurrentAspect(), 
                                      oOffsets);
#endif
}


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<ProjectionCameraDecoratorPtr>::_type("ProjectionCameraDecoratorPtr", "StereoCameraDecoratorPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(ProjectionCameraDecoratorPtr)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           ProjectionCameraDecoratorPtr, 
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           ProjectionCameraDecoratorPtr, 
                           0);

OSG_END_NAMESPACE
