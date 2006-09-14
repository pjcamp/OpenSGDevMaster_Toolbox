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
 **     class ShearedStereoCameraDecorator!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILESHEAREDSTEREOCAMERADECORATORINST

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>




#include "OSGShearedStereoCameraDecoratorBase.h"
#include "OSGShearedStereoCameraDecorator.h"

OSG_USING_NAMESPACE

// Field descriptions

/*! \var Real32 ShearedStereoCameraDecoratorBase::_sfZeroParallaxDistance
    	The distance to the zero parallax plane.

*/
/*! \var Real32 ShearedStereoCameraDecoratorBase::_sfOverlap
    	The overlap between left and right eye.

*/

void ShearedStereoCameraDecoratorBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL; 


#ifdef OSG_1_COMPAT
    typedef const SFReal32 *(ShearedStereoCameraDecoratorBase::*GetSFZeroParallaxDistanceF)(void) const;

    GetSFZeroParallaxDistanceF GetSFZeroParallaxDistance = &ShearedStereoCameraDecoratorBase::getSFZeroParallaxDistance;
#endif

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(), 
        "zeroParallaxDistance", 
        ZeroParallaxDistanceFieldId, ZeroParallaxDistanceFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&ShearedStereoCameraDecoratorBase::editSFZeroParallaxDistance),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFZeroParallaxDistance));
#else
        reinterpret_cast<FieldGetMethodSig >(&ShearedStereoCameraDecoratorBase::getSFZeroParallaxDistance));
#endif

    oType.addInitialDesc(pDesc);

#ifdef OSG_1_COMPAT
    typedef const SFReal32 *(ShearedStereoCameraDecoratorBase::*GetSFOverlapF)(void) const;

    GetSFOverlapF GetSFOverlap = &ShearedStereoCameraDecoratorBase::getSFOverlap;
#endif

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(), 
        "overlap", 
        OverlapFieldId, OverlapFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&ShearedStereoCameraDecoratorBase::editSFOverlap),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFOverlap));
#else
        reinterpret_cast<FieldGetMethodSig >(&ShearedStereoCameraDecoratorBase::getSFOverlap));
#endif

    oType.addInitialDesc(pDesc);
}


ShearedStereoCameraDecoratorBase::TypeObject ShearedStereoCameraDecoratorBase::_type(true,
    ShearedStereoCameraDecoratorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    (PrototypeCreateF) &ShearedStereoCameraDecoratorBase::createEmpty,
    ShearedStereoCameraDecorator::initMethod,
    (InitalInsertDescFunc) &ShearedStereoCameraDecoratorBase::classDescInserter,
    false);

/*------------------------------ get -----------------------------------*/

FieldContainerType &ShearedStereoCameraDecoratorBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &ShearedStereoCameraDecoratorBase::getType(void) const 
{
    return _type;
} 

UInt32 ShearedStereoCameraDecoratorBase::getContainerSize(void) const 
{ 
    return sizeof(ShearedStereoCameraDecorator); 
}

/*------------------------- decorator get ------------------------------*/


SFReal32 *ShearedStereoCameraDecoratorBase::editSFZeroParallaxDistance(void)
{
    editSField(ZeroParallaxDistanceFieldMask);

    return &_sfZeroParallaxDistance;
}

const SFReal32 *ShearedStereoCameraDecoratorBase::getSFZeroParallaxDistance(void) const
{
    return &_sfZeroParallaxDistance;
}

#ifdef OSG_1_COMPAT
SFReal32 *ShearedStereoCameraDecoratorBase::getSFZeroParallaxDistance(void)
{
    return this->editSFZeroParallaxDistance();
}
#endif

SFReal32 *ShearedStereoCameraDecoratorBase::editSFOverlap(void)
{
    editSField(OverlapFieldMask);

    return &_sfOverlap;
}

const SFReal32 *ShearedStereoCameraDecoratorBase::getSFOverlap(void) const
{
    return &_sfOverlap;
}

#ifdef OSG_1_COMPAT
SFReal32 *ShearedStereoCameraDecoratorBase::getSFOverlap(void)
{
    return this->editSFOverlap();
}
#endif



/*------------------------------ access -----------------------------------*/

UInt32 ShearedStereoCameraDecoratorBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ZeroParallaxDistanceFieldMask & whichField))
    {
        returnValue += _sfZeroParallaxDistance.getBinSize();
    }
    if(FieldBits::NoField != (OverlapFieldMask & whichField))
    {
        returnValue += _sfOverlap.getBinSize();
    }

    return returnValue;
}

void ShearedStereoCameraDecoratorBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ZeroParallaxDistanceFieldMask & whichField))
    {
        _sfZeroParallaxDistance.copyToBin(pMem);
    }
    if(FieldBits::NoField != (OverlapFieldMask & whichField))
    {
        _sfOverlap.copyToBin(pMem);
    }
}

void ShearedStereoCameraDecoratorBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ZeroParallaxDistanceFieldMask & whichField))
    {
        _sfZeroParallaxDistance.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (OverlapFieldMask & whichField))
    {
        _sfOverlap.copyFromBin(pMem);
    }
}

//! create an empty new instance of the class, do not copy the prototype
ShearedStereoCameraDecoratorPtr ShearedStereoCameraDecoratorBase::createEmpty(void) 
{ 
    ShearedStereoCameraDecoratorPtr returnValue; 
    
    newPtr<ShearedStereoCameraDecorator>(returnValue); 

    return returnValue; 
}

FieldContainerPtr ShearedStereoCameraDecoratorBase::shallowCopy(void) const 
{ 
    ShearedStereoCameraDecoratorPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const ShearedStereoCameraDecorator *>(this)); 

    return returnValue; 
}



/*------------------------- constructors ----------------------------------*/

ShearedStereoCameraDecoratorBase::ShearedStereoCameraDecoratorBase(void) :
    Inherited(),
    _sfZeroParallaxDistance(Real32(1)),
    _sfOverlap(Real32(1))
{
}

ShearedStereoCameraDecoratorBase::ShearedStereoCameraDecoratorBase(const ShearedStereoCameraDecoratorBase &source) :
    Inherited(source),
    _sfZeroParallaxDistance(source._sfZeroParallaxDistance),
    _sfOverlap(source._sfOverlap)
{
}

/*-------------------------- destructors ----------------------------------*/

ShearedStereoCameraDecoratorBase::~ShearedStereoCameraDecoratorBase(void)
{
}


#ifdef OSG_MT_FIELDCONTAINERPTR
void ShearedStereoCameraDecoratorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo,
                                        UInt32             uiCopyOffset)
{
    this->execSync(static_cast<ShearedStereoCameraDecoratorBase *>(&oFrom),
                   whichField, 
                   syncMode, 
                   uiSyncInfo,
                   uiCopyOffset);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
void ShearedStereoCameraDecoratorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<ShearedStereoCameraDecoratorBase *>(&oFrom), 
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

#if 0
void ShearedStereoCameraDecoratorBase::execBeginEditV(ConstFieldMaskArg whichField,
                                       UInt32            uiAspect,
                                       UInt32            uiContainerSize)
{
    this->execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
FieldContainerPtr ShearedStereoCameraDecoratorBase::createAspectCopy(void) const
{
    ShearedStereoCameraDecoratorPtr returnValue; 

    newAspectCopy(returnValue, 
                  dynamic_cast<const ShearedStereoCameraDecorator *>(this)); 

    return returnValue; 
}
#endif

void ShearedStereoCameraDecoratorBase::resolveLinks(void)
{
    Inherited::resolveLinks();
}


#include "OSGSField.ins"
#include "OSGMField.ins"

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_FUNCTION_INSTANTIATION) || \
    defined(OSG_TMPL_STATIC_MEMBER_NEEDS_CLASS_INSTANTIATION   )

#include "OSGSFieldFuncs.ins"
#include "OSGMFieldFuncs.ins"
#endif

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<ShearedStereoCameraDecoratorPtr>::_type("ShearedStereoCameraDecoratorPtr", "StereoCameraDecoratorPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(ShearedStereoCameraDecoratorPtr)

OSG_FIELD_DLLEXPORT_DEF1(SField, ShearedStereoCameraDecoratorPtr);
OSG_FIELD_DLLEXPORT_DEF1(MField, ShearedStereoCameraDecoratorPtr);

OSG_END_NAMESPACE


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGSHEAREDSTEREOCAMERADECORATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHEAREDSTEREOCAMERADECORATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHEAREDSTEREOCAMERADECORATORFIELDS_HEADER_CVSID;
}
