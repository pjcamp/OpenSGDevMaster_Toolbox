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
 **     class StencilChunk!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILESTENCILCHUNKINST

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>


#include "OSGGL.h"   // StencilFunc default header
#include "OSGGL.h"   // StencilOpFail default header
#include "OSGGL.h"   // StencilOpZFail default header
#include "OSGGL.h"   // StencilOpZPass default header


#include "OSGStencilChunkBase.h"
#include "OSGStencilChunk.h"

OSG_USING_NAMESPACE

// Field descriptions

/*! \var GLenum StencilChunkBase::_sfStencilFunc
    	The stencilFunc defines how fragments which do not fulfill a certain condition are handled.          See glStencilFunc() for details. GL_NONE is used to disable stencil.

*/
/*! \var Int32 StencilChunkBase::_sfStencilValue
    	The stencilFunc defines how fragments which do not fulfill a certain condition are handled.          See glStencilFunc() for details. GL_NONE is used to disable stencil.

*/
/*! \var UInt32 StencilChunkBase::_sfStencilMask
    	The stencilFunc defines how fragments which do not fulfill a certain condition are handled.          See glStencilFunc() for details. GL_NONE is used to disable stencil.

*/
/*! \var GLenum StencilChunkBase::_sfStencilOpFail
    	The stencilFunc defines how fragments which do not fulfill a certain condition are handled.          See glStencilFunc() for details. GL_NONE is used to disable stencil.

*/
/*! \var GLenum StencilChunkBase::_sfStencilOpZFail
    	The stencilFunc defines how fragments which do not fulfill a certain condition are handled.          See glStencilFunc() for details. GL_NONE is used to disable stencil.

*/
/*! \var GLenum StencilChunkBase::_sfStencilOpZPass
    	The stencilFunc defines how fragments which do not fulfill a certain condition are handled.          See glStencilFunc() for details. GL_NONE is used to disable stencil.

*/
/*! \var Int32 StencilChunkBase::_sfClearBuffer
    	Clear buffer on activate(1) or deactivate(2).

*/

void StencilChunkBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL; 


#ifdef OSG_1_COMPAT
    typedef const SFGLenum *(StencilChunkBase::*GetSFStencilFuncF)(void) const;

    GetSFStencilFuncF GetSFStencilFunc = &StencilChunkBase::getSFStencilFunc;
#endif

    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(), 
        "stencilFunc", 
        StencilFuncFieldId, StencilFuncFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&StencilChunkBase::editSFStencilFunc),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFStencilFunc));
#else
        reinterpret_cast<FieldGetMethodSig >(&StencilChunkBase::getSFStencilFunc));
#endif

    oType.addInitialDesc(pDesc);

#ifdef OSG_1_COMPAT
    typedef const SFInt32 *(StencilChunkBase::*GetSFStencilValueF)(void) const;

    GetSFStencilValueF GetSFStencilValue = &StencilChunkBase::getSFStencilValue;
#endif

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(), 
        "stencilValue", 
        StencilValueFieldId, StencilValueFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&StencilChunkBase::editSFStencilValue),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFStencilValue));
#else
        reinterpret_cast<FieldGetMethodSig >(&StencilChunkBase::getSFStencilValue));
#endif

    oType.addInitialDesc(pDesc);

#ifdef OSG_1_COMPAT
    typedef const SFUInt32 *(StencilChunkBase::*GetSFStencilMaskF)(void) const;

    GetSFStencilMaskF GetSFStencilMask = &StencilChunkBase::getSFStencilMask;
#endif

    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(), 
        "stencilMask", 
        StencilMaskFieldId, StencilMaskFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&StencilChunkBase::editSFStencilMask),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFStencilMask));
#else
        reinterpret_cast<FieldGetMethodSig >(&StencilChunkBase::getSFStencilMask));
#endif

    oType.addInitialDesc(pDesc);

#ifdef OSG_1_COMPAT
    typedef const SFGLenum *(StencilChunkBase::*GetSFStencilOpFailF)(void) const;

    GetSFStencilOpFailF GetSFStencilOpFail = &StencilChunkBase::getSFStencilOpFail;
#endif

    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(), 
        "stencilOpFail", 
        StencilOpFailFieldId, StencilOpFailFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&StencilChunkBase::editSFStencilOpFail),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFStencilOpFail));
#else
        reinterpret_cast<FieldGetMethodSig >(&StencilChunkBase::getSFStencilOpFail));
#endif

    oType.addInitialDesc(pDesc);

#ifdef OSG_1_COMPAT
    typedef const SFGLenum *(StencilChunkBase::*GetSFStencilOpZFailF)(void) const;

    GetSFStencilOpZFailF GetSFStencilOpZFail = &StencilChunkBase::getSFStencilOpZFail;
#endif

    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(), 
        "stencilOpZFail", 
        StencilOpZFailFieldId, StencilOpZFailFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&StencilChunkBase::editSFStencilOpZFail),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFStencilOpZFail));
#else
        reinterpret_cast<FieldGetMethodSig >(&StencilChunkBase::getSFStencilOpZFail));
#endif

    oType.addInitialDesc(pDesc);

#ifdef OSG_1_COMPAT
    typedef const SFGLenum *(StencilChunkBase::*GetSFStencilOpZPassF)(void) const;

    GetSFStencilOpZPassF GetSFStencilOpZPass = &StencilChunkBase::getSFStencilOpZPass;
#endif

    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(), 
        "stencilOpZPass", 
        StencilOpZPassFieldId, StencilOpZPassFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&StencilChunkBase::editSFStencilOpZPass),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFStencilOpZPass));
#else
        reinterpret_cast<FieldGetMethodSig >(&StencilChunkBase::getSFStencilOpZPass));
#endif

    oType.addInitialDesc(pDesc);

#ifdef OSG_1_COMPAT
    typedef const SFInt32 *(StencilChunkBase::*GetSFClearBufferF)(void) const;

    GetSFClearBufferF GetSFClearBuffer = &StencilChunkBase::getSFClearBuffer;
#endif

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(), 
        "clearBuffer", 
        ClearBufferFieldId, ClearBufferFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&StencilChunkBase::editSFClearBuffer),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFClearBuffer));
#else
        reinterpret_cast<FieldGetMethodSig >(&StencilChunkBase::getSFClearBuffer));
#endif

    oType.addInitialDesc(pDesc);
}


StencilChunkBase::TypeObject StencilChunkBase::_type(true,
    StencilChunkBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    (PrototypeCreateF) &StencilChunkBase::createEmpty,
    StencilChunk::initMethod,
    (InitalInsertDescFunc) &StencilChunkBase::classDescInserter,
    false);

/*------------------------------ get -----------------------------------*/

FieldContainerType &StencilChunkBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &StencilChunkBase::getType(void) const 
{
    return _type;
} 

UInt32 StencilChunkBase::getContainerSize(void) const 
{ 
    return sizeof(StencilChunk); 
}

/*------------------------- decorator get ------------------------------*/


SFGLenum *StencilChunkBase::editSFStencilFunc(void)
{
    editSField(StencilFuncFieldMask);

    return &_sfStencilFunc;
}

const SFGLenum *StencilChunkBase::getSFStencilFunc(void) const
{
    return &_sfStencilFunc;
}

#ifdef OSG_1_COMPAT
SFGLenum *StencilChunkBase::getSFStencilFunc(void)
{
    return this->editSFStencilFunc();
}
#endif

SFInt32 *StencilChunkBase::editSFStencilValue(void)
{
    editSField(StencilValueFieldMask);

    return &_sfStencilValue;
}

const SFInt32 *StencilChunkBase::getSFStencilValue(void) const
{
    return &_sfStencilValue;
}

#ifdef OSG_1_COMPAT
SFInt32 *StencilChunkBase::getSFStencilValue(void)
{
    return this->editSFStencilValue();
}
#endif

SFUInt32 *StencilChunkBase::editSFStencilMask(void)
{
    editSField(StencilMaskFieldMask);

    return &_sfStencilMask;
}

const SFUInt32 *StencilChunkBase::getSFStencilMask(void) const
{
    return &_sfStencilMask;
}

#ifdef OSG_1_COMPAT
SFUInt32 *StencilChunkBase::getSFStencilMask(void)
{
    return this->editSFStencilMask();
}
#endif

SFGLenum *StencilChunkBase::editSFStencilOpFail(void)
{
    editSField(StencilOpFailFieldMask);

    return &_sfStencilOpFail;
}

const SFGLenum *StencilChunkBase::getSFStencilOpFail(void) const
{
    return &_sfStencilOpFail;
}

#ifdef OSG_1_COMPAT
SFGLenum *StencilChunkBase::getSFStencilOpFail(void)
{
    return this->editSFStencilOpFail();
}
#endif

SFGLenum *StencilChunkBase::editSFStencilOpZFail(void)
{
    editSField(StencilOpZFailFieldMask);

    return &_sfStencilOpZFail;
}

const SFGLenum *StencilChunkBase::getSFStencilOpZFail(void) const
{
    return &_sfStencilOpZFail;
}

#ifdef OSG_1_COMPAT
SFGLenum *StencilChunkBase::getSFStencilOpZFail(void)
{
    return this->editSFStencilOpZFail();
}
#endif

SFGLenum *StencilChunkBase::editSFStencilOpZPass(void)
{
    editSField(StencilOpZPassFieldMask);

    return &_sfStencilOpZPass;
}

const SFGLenum *StencilChunkBase::getSFStencilOpZPass(void) const
{
    return &_sfStencilOpZPass;
}

#ifdef OSG_1_COMPAT
SFGLenum *StencilChunkBase::getSFStencilOpZPass(void)
{
    return this->editSFStencilOpZPass();
}
#endif

SFInt32 *StencilChunkBase::editSFClearBuffer(void)
{
    editSField(ClearBufferFieldMask);

    return &_sfClearBuffer;
}

const SFInt32 *StencilChunkBase::getSFClearBuffer(void) const
{
    return &_sfClearBuffer;
}

#ifdef OSG_1_COMPAT
SFInt32 *StencilChunkBase::getSFClearBuffer(void)
{
    return this->editSFClearBuffer();
}
#endif



/*------------------------------ access -----------------------------------*/

UInt32 StencilChunkBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (StencilFuncFieldMask & whichField))
    {
        returnValue += _sfStencilFunc.getBinSize();
    }
    if(FieldBits::NoField != (StencilValueFieldMask & whichField))
    {
        returnValue += _sfStencilValue.getBinSize();
    }
    if(FieldBits::NoField != (StencilMaskFieldMask & whichField))
    {
        returnValue += _sfStencilMask.getBinSize();
    }
    if(FieldBits::NoField != (StencilOpFailFieldMask & whichField))
    {
        returnValue += _sfStencilOpFail.getBinSize();
    }
    if(FieldBits::NoField != (StencilOpZFailFieldMask & whichField))
    {
        returnValue += _sfStencilOpZFail.getBinSize();
    }
    if(FieldBits::NoField != (StencilOpZPassFieldMask & whichField))
    {
        returnValue += _sfStencilOpZPass.getBinSize();
    }
    if(FieldBits::NoField != (ClearBufferFieldMask & whichField))
    {
        returnValue += _sfClearBuffer.getBinSize();
    }

    return returnValue;
}

void StencilChunkBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (StencilFuncFieldMask & whichField))
    {
        _sfStencilFunc.copyToBin(pMem);
    }
    if(FieldBits::NoField != (StencilValueFieldMask & whichField))
    {
        _sfStencilValue.copyToBin(pMem);
    }
    if(FieldBits::NoField != (StencilMaskFieldMask & whichField))
    {
        _sfStencilMask.copyToBin(pMem);
    }
    if(FieldBits::NoField != (StencilOpFailFieldMask & whichField))
    {
        _sfStencilOpFail.copyToBin(pMem);
    }
    if(FieldBits::NoField != (StencilOpZFailFieldMask & whichField))
    {
        _sfStencilOpZFail.copyToBin(pMem);
    }
    if(FieldBits::NoField != (StencilOpZPassFieldMask & whichField))
    {
        _sfStencilOpZPass.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ClearBufferFieldMask & whichField))
    {
        _sfClearBuffer.copyToBin(pMem);
    }
}

void StencilChunkBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (StencilFuncFieldMask & whichField))
    {
        _sfStencilFunc.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (StencilValueFieldMask & whichField))
    {
        _sfStencilValue.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (StencilMaskFieldMask & whichField))
    {
        _sfStencilMask.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (StencilOpFailFieldMask & whichField))
    {
        _sfStencilOpFail.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (StencilOpZFailFieldMask & whichField))
    {
        _sfStencilOpZFail.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (StencilOpZPassFieldMask & whichField))
    {
        _sfStencilOpZPass.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ClearBufferFieldMask & whichField))
    {
        _sfClearBuffer.copyFromBin(pMem);
    }
}

//! create an empty new instance of the class, do not copy the prototype
StencilChunkPtr StencilChunkBase::createEmpty(void) 
{ 
    StencilChunkPtr returnValue; 
    
    newPtr<StencilChunk>(returnValue); 

    return returnValue; 
}

FieldContainerPtr StencilChunkBase::shallowCopy(void) const 
{ 
    StencilChunkPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const StencilChunk *>(this)); 

    return returnValue; 
}



/*------------------------- constructors ----------------------------------*/

StencilChunkBase::StencilChunkBase(void) :
    Inherited(),
    _sfStencilFunc(GLenum(GL_NONE)),
    _sfStencilValue(Int32(0)),
    _sfStencilMask(UInt32(0x1)),
    _sfStencilOpFail(GLenum(GL_KEEP)),
    _sfStencilOpZFail(GLenum(GL_KEEP)),
    _sfStencilOpZPass(GLenum(GL_KEEP)),
    _sfClearBuffer(Int32(0))
{
}

StencilChunkBase::StencilChunkBase(const StencilChunkBase &source) :
    Inherited(source),
    _sfStencilFunc(source._sfStencilFunc),
    _sfStencilValue(source._sfStencilValue),
    _sfStencilMask(source._sfStencilMask),
    _sfStencilOpFail(source._sfStencilOpFail),
    _sfStencilOpZFail(source._sfStencilOpZFail),
    _sfStencilOpZPass(source._sfStencilOpZPass),
    _sfClearBuffer(source._sfClearBuffer)
{
}

/*-------------------------- destructors ----------------------------------*/

StencilChunkBase::~StencilChunkBase(void)
{
}


#ifdef OSG_MT_FIELDCONTAINERPTR
void StencilChunkBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo,
                                        UInt32             uiCopyOffset)
{
    this->execSync(static_cast<StencilChunkBase *>(&oFrom),
                   whichField, 
                   syncMode, 
                   uiSyncInfo,
                   uiCopyOffset);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
void StencilChunkBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<StencilChunkBase *>(&oFrom), 
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

#if 0
void StencilChunkBase::execBeginEditV(ConstFieldMaskArg whichField,
                                       UInt32            uiAspect,
                                       UInt32            uiContainerSize)
{
    this->execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
FieldContainerPtr StencilChunkBase::createAspectCopy(void) const
{
    StencilChunkPtr returnValue; 

    newAspectCopy(returnValue, 
                  dynamic_cast<const StencilChunk *>(this)); 

    return returnValue; 
}
#endif

void StencilChunkBase::resolveLinks(void)
{
    Inherited::resolveLinks();
}


OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<StencilChunkPtr>::_type("StencilChunkPtr", "StateChunkPtr");
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
    static Char8 cvsid_hpp       [] = OSGSTENCILCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSTENCILCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSTENCILCHUNKFIELDS_HEADER_CVSID;
}
