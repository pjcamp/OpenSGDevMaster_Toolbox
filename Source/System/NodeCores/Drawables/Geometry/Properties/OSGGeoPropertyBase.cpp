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
 **     class GeoProperty!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILEGEOPROPERTYINST

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>


#include <OSGGLEXT.h>   // Usage default header


#include "OSGGeoPropertyBase.h"
#include "OSGGeoProperty.h"

OSG_USING_NAMESPACE

// Field descriptions

/*! \var bool GeoPropertyBase::_sfUseVBO
    	The id used to register with the Window, 0 if not set up yet.

*/
/*! \var UInt32 GeoPropertyBase::_sfGLId
    	The id used to register with the Window, 0 if not set up yet.

*/
/*! \var Int32 GeoPropertyBase::_sfUsage
    	The usage pattern, only valid for VBO use.

*/

void GeoPropertyBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL; 


#ifdef OSG_1_COMPAT
    typedef const SFBool *(GeoPropertyBase::*GetSFUseVBOF)(void) const;

    GetSFUseVBOF GetSFUseVBO = &GeoPropertyBase::getSFUseVBO;
#endif

    pDesc = new SFBool::Description(
        SFBool::getClassType(), 
        "useVBO", 
        UseVBOFieldId, UseVBOFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&GeoPropertyBase::editSFUseVBO),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFUseVBO));
#else
        reinterpret_cast<FieldGetMethodSig >(&GeoPropertyBase::getSFUseVBO));
#endif

    oType.addInitialDesc(pDesc);

#ifdef OSG_1_COMPAT
    typedef const SFUInt32 *(GeoPropertyBase::*GetSFGLIdF)(void) const;

    GetSFGLIdF GetSFGLId = &GeoPropertyBase::getSFGLId;
#endif

    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(), 
        "GLId", 
        GLIdFieldId, GLIdFieldMask,
        true,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&GeoPropertyBase::editSFGLId),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFGLId));
#else
        reinterpret_cast<FieldGetMethodSig >(&GeoPropertyBase::getSFGLId));
#endif

    oType.addInitialDesc(pDesc);

#ifdef OSG_1_COMPAT
    typedef const SFInt32 *(GeoPropertyBase::*GetSFUsageF)(void) const;

    GetSFUsageF GetSFUsage = &GeoPropertyBase::getSFUsage;
#endif

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(), 
        "usage", 
        UsageFieldId, UsageFieldMask,
        true,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&GeoPropertyBase::editSFUsage),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFUsage));
#else
        reinterpret_cast<FieldGetMethodSig >(&GeoPropertyBase::getSFUsage));
#endif

    oType.addInitialDesc(pDesc);
}


GeoPropertyBase::TypeObject GeoPropertyBase::_type(true,
    GeoPropertyBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    NULL, 
    GeoProperty::initMethod,
    (InitalInsertDescFunc) &GeoPropertyBase::classDescInserter,
    false);

/*------------------------------ get -----------------------------------*/

FieldContainerType &GeoPropertyBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &GeoPropertyBase::getType(void) const 
{
    return _type;
} 

UInt32 GeoPropertyBase::getContainerSize(void) const 
{ 
    return sizeof(GeoProperty); 
}

/*------------------------- decorator get ------------------------------*/


SFBool *GeoPropertyBase::editSFUseVBO(void)
{
    editSField(UseVBOFieldMask);

    return &_sfUseVBO;
}

const SFBool *GeoPropertyBase::getSFUseVBO(void) const
{
    return &_sfUseVBO;
}

#ifdef OSG_1_COMPAT
SFBool *GeoPropertyBase::getSFUseVBO(void)
{
    return this->editSFUseVBO();
}
#endif

SFUInt32 *GeoPropertyBase::editSFGLId(void)
{
    editSField(GLIdFieldMask);

    return &_sfGLId;
}

const SFUInt32 *GeoPropertyBase::getSFGLId(void) const
{
    return &_sfGLId;
}

#ifdef OSG_1_COMPAT
SFUInt32 *GeoPropertyBase::getSFGLId(void)
{
    return this->editSFGLId();
}
#endif

SFInt32 *GeoPropertyBase::editSFUsage(void)
{
    editSField(UsageFieldMask);

    return &_sfUsage;
}

const SFInt32 *GeoPropertyBase::getSFUsage(void) const
{
    return &_sfUsage;
}

#ifdef OSG_1_COMPAT
SFInt32 *GeoPropertyBase::getSFUsage(void)
{
    return this->editSFUsage();
}
#endif



/*------------------------------ access -----------------------------------*/

UInt32 GeoPropertyBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (UseVBOFieldMask & whichField))
    {
        returnValue += _sfUseVBO.getBinSize();
    }
    if(FieldBits::NoField != (GLIdFieldMask & whichField))
    {
        returnValue += _sfGLId.getBinSize();
    }
    if(FieldBits::NoField != (UsageFieldMask & whichField))
    {
        returnValue += _sfUsage.getBinSize();
    }

    return returnValue;
}

void GeoPropertyBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (UseVBOFieldMask & whichField))
    {
        _sfUseVBO.copyToBin(pMem);
    }
    if(FieldBits::NoField != (GLIdFieldMask & whichField))
    {
        _sfGLId.copyToBin(pMem);
    }
    if(FieldBits::NoField != (UsageFieldMask & whichField))
    {
        _sfUsage.copyToBin(pMem);
    }
}

void GeoPropertyBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (UseVBOFieldMask & whichField))
    {
        _sfUseVBO.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (GLIdFieldMask & whichField))
    {
        _sfGLId.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (UsageFieldMask & whichField))
    {
        _sfUsage.copyFromBin(pMem);
    }
}



/*------------------------- constructors ----------------------------------*/

GeoPropertyBase::GeoPropertyBase(void) :
    Inherited(),
    _sfUseVBO(bool(false)),
    _sfGLId(UInt32(0)),
    _sfUsage(Int32(GL_STATIC_DRAW_ARB))
{
}

GeoPropertyBase::GeoPropertyBase(const GeoPropertyBase &source) :
    Inherited(source),
    _sfUseVBO(source._sfUseVBO),
    _sfGLId(source._sfGLId),
    _sfUsage(source._sfUsage)
{
}

/*-------------------------- destructors ----------------------------------*/

GeoPropertyBase::~GeoPropertyBase(void)
{
}


#ifdef OSG_MT_FIELDCONTAINERPTR
void GeoPropertyBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo,
                                        UInt32             uiCopyOffset)
{
    this->execSync(static_cast<GeoPropertyBase *>(&oFrom),
                   whichField, 
                   syncMode, 
                   uiSyncInfo,
                   uiCopyOffset);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
void GeoPropertyBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<GeoPropertyBase *>(&oFrom), 
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

#if 0
void GeoPropertyBase::execBeginEditV(ConstFieldMaskArg whichField,
                                       UInt32            uiAspect,
                                       UInt32            uiContainerSize)
{
    this->execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif


void GeoPropertyBase::resolveLinks(void)
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
DataType FieldTraits<GeoPropertyPtr>::_type("GeoPropertyPtr", "StateChunkPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(GeoPropertyPtr)

OSG_FIELD_DLLEXPORT_DEF1(SField, GeoPropertyPtr);
OSG_FIELD_DLLEXPORT_DEF1(MField, GeoPropertyPtr);

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
    static Char8 cvsid_hpp       [] = OSGGEOPROPERTYBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGEOPROPERTYBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGEOPROPERTYFIELDS_HEADER_CVSID;
}
