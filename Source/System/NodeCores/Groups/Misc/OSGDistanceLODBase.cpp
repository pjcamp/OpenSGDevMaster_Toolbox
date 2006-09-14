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
 **     class DistanceLOD!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILEDISTANCELODINST

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>




#include "OSGDistanceLODBase.h"
#include "OSGDistanceLOD.h"

OSG_USING_NAMESPACE

// Field descriptions

/*! \var Pnt3f DistanceLODBase::_sfCenter
    	The center for distance calculation.

*/
/*! \var Real32 DistanceLODBase::_mfRange
    	The range intervals.

*/

void DistanceLODBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL; 


#ifdef OSG_1_COMPAT
    typedef const SFPnt3f *(DistanceLODBase::*GetSFCenterF)(void) const;

    GetSFCenterF GetSFCenter = &DistanceLODBase::getSFCenter;
#endif

    pDesc = new SFPnt3f::Description(
        SFPnt3f::getClassType(), 
        "center", 
        CenterFieldId, CenterFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&DistanceLODBase::editSFCenter),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFCenter));
#else
        reinterpret_cast<FieldGetMethodSig >(&DistanceLODBase::getSFCenter));
#endif

    oType.addInitialDesc(pDesc);

#ifdef OSG_1_COMPAT
    typedef const MFReal32 *(DistanceLODBase::*GetMFRangeF)(void) const;

    GetMFRangeF GetMFRange = &DistanceLODBase::getMFRange;
#endif

    pDesc = new MFReal32::Description(
        MFReal32::getClassType(), 
        "range", 
        RangeFieldId, RangeFieldMask,
        false,
        Field::MFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&DistanceLODBase::editMFRange),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetMFRange));
#else
        reinterpret_cast<FieldGetMethodSig >(&DistanceLODBase::getMFRange));
#endif

    oType.addInitialDesc(pDesc);
}


DistanceLODBase::TypeObject DistanceLODBase::_type(true,
    DistanceLODBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    (PrototypeCreateF) &DistanceLODBase::createEmpty,
    DistanceLOD::initMethod,
    (InitalInsertDescFunc) &DistanceLODBase::classDescInserter,
    false);

/*------------------------------ get -----------------------------------*/

FieldContainerType &DistanceLODBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &DistanceLODBase::getType(void) const 
{
    return _type;
} 

UInt32 DistanceLODBase::getContainerSize(void) const 
{ 
    return sizeof(DistanceLOD); 
}

/*------------------------- decorator get ------------------------------*/


SFPnt3f *DistanceLODBase::editSFCenter(void)
{
    editSField(CenterFieldMask);

    return &_sfCenter;
}

const SFPnt3f *DistanceLODBase::getSFCenter(void) const
{
    return &_sfCenter;
}

#ifdef OSG_1_COMPAT
SFPnt3f *DistanceLODBase::getSFCenter(void)
{
    return this->editSFCenter();
}
#endif

MFReal32 *DistanceLODBase::editMFRange(void)
{
    editMField(RangeFieldMask, _mfRange);

    return &_mfRange;
}

const MFReal32 *DistanceLODBase::getMFRange(void) const
{
    return &_mfRange;
}

#ifdef OSG_1_COMPAT
MFReal32 *DistanceLODBase::getMFRange(void)
{
    return this->editMFRange();
}
#endif



/*------------------------------ access -----------------------------------*/

UInt32 DistanceLODBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (CenterFieldMask & whichField))
    {
        returnValue += _sfCenter.getBinSize();
    }
    if(FieldBits::NoField != (RangeFieldMask & whichField))
    {
        returnValue += _mfRange.getBinSize();
    }

    return returnValue;
}

void DistanceLODBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (CenterFieldMask & whichField))
    {
        _sfCenter.copyToBin(pMem);
    }
    if(FieldBits::NoField != (RangeFieldMask & whichField))
    {
        _mfRange.copyToBin(pMem);
    }
}

void DistanceLODBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (CenterFieldMask & whichField))
    {
        _sfCenter.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (RangeFieldMask & whichField))
    {
        _mfRange.copyFromBin(pMem);
    }
}

//! create an empty new instance of the class, do not copy the prototype
DistanceLODPtr DistanceLODBase::createEmpty(void) 
{ 
    DistanceLODPtr returnValue; 
    
    newPtr<DistanceLOD>(returnValue); 

    return returnValue; 
}

FieldContainerPtr DistanceLODBase::shallowCopy(void) const 
{ 
    DistanceLODPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const DistanceLOD *>(this)); 

    return returnValue; 
}



/*------------------------- constructors ----------------------------------*/

DistanceLODBase::DistanceLODBase(void) :
    Inherited(),
    _sfCenter(),
    _mfRange()
{
}

DistanceLODBase::DistanceLODBase(const DistanceLODBase &source) :
    Inherited(source),
    _sfCenter(source._sfCenter),
    _mfRange(source._mfRange)
{
}

/*-------------------------- destructors ----------------------------------*/

DistanceLODBase::~DistanceLODBase(void)
{
}


#ifdef OSG_MT_FIELDCONTAINERPTR
void DistanceLODBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo,
                                        UInt32             uiCopyOffset)
{
    this->execSync(static_cast<DistanceLODBase *>(&oFrom),
                   whichField, 
                   syncMode, 
                   uiSyncInfo,
                   uiCopyOffset);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
void DistanceLODBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<DistanceLODBase *>(&oFrom), 
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

#if 0
void DistanceLODBase::execBeginEditV(ConstFieldMaskArg whichField,
                                       UInt32            uiAspect,
                                       UInt32            uiContainerSize)
{
    this->execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
FieldContainerPtr DistanceLODBase::createAspectCopy(void) const
{
    DistanceLODPtr returnValue; 

    newAspectCopy(returnValue, 
                  dynamic_cast<const DistanceLOD *>(this)); 

    return returnValue; 
}
#endif

void DistanceLODBase::resolveLinks(void)
{
    Inherited::resolveLinks();
}


OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<DistanceLODPtr>::_type("DistanceLODPtr", "GroupPtr");
#endif


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
    static Char8 cvsid_hpp       [] = OSGDISTANCELODBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDISTANCELODBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDISTANCELODFIELDS_HEADER_CVSID;
}
