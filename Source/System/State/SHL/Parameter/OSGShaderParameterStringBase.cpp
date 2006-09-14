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
 **     class ShaderParameterString!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILESHADERPARAMETERSTRINGINST

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>




#include "OSGShaderParameterStringBase.h"
#include "OSGShaderParameterString.h"

OSG_USING_NAMESPACE

// Field descriptions

/*! \var std::string ShaderParameterStringBase::_sfValue
    	parameter value

*/

void ShaderParameterStringBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL; 


#ifdef OSG_1_COMPAT
    typedef const SFString *(ShaderParameterStringBase::*GetSFValueF)(void) const;

    GetSFValueF GetSFValue = &ShaderParameterStringBase::getSFValue;
#endif

    pDesc = new SFString::Description(
        SFString::getClassType(), 
        "value", 
        ValueFieldId, ValueFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&ShaderParameterStringBase::editSFValue),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFValue));
#else
        reinterpret_cast<FieldGetMethodSig >(&ShaderParameterStringBase::getSFValue));
#endif

    oType.addInitialDesc(pDesc);
}


ShaderParameterStringBase::TypeObject ShaderParameterStringBase::_type(true,
    ShaderParameterStringBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    (PrototypeCreateF) &ShaderParameterStringBase::createEmpty,
    ShaderParameterString::initMethod,
    (InitalInsertDescFunc) &ShaderParameterStringBase::classDescInserter,
    false);

/*------------------------------ get -----------------------------------*/

FieldContainerType &ShaderParameterStringBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &ShaderParameterStringBase::getType(void) const 
{
    return _type;
} 

UInt32 ShaderParameterStringBase::getContainerSize(void) const 
{ 
    return sizeof(ShaderParameterString); 
}

/*------------------------- decorator get ------------------------------*/


SFString *ShaderParameterStringBase::editSFValue(void)
{
    editSField(ValueFieldMask);

    return &_sfValue;
}

const SFString *ShaderParameterStringBase::getSFValue(void) const
{
    return &_sfValue;
}

#ifdef OSG_1_COMPAT
SFString *ShaderParameterStringBase::getSFValue(void)
{
    return this->editSFValue();
}
#endif



/*------------------------------ access -----------------------------------*/

UInt32 ShaderParameterStringBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        returnValue += _sfValue.getBinSize();
    }

    return returnValue;
}

void ShaderParameterStringBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _sfValue.copyToBin(pMem);
    }
}

void ShaderParameterStringBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _sfValue.copyFromBin(pMem);
    }
}

//! create an empty new instance of the class, do not copy the prototype
ShaderParameterStringPtr ShaderParameterStringBase::createEmpty(void) 
{ 
    ShaderParameterStringPtr returnValue; 
    
    newPtr<ShaderParameterString>(returnValue); 

    return returnValue; 
}

FieldContainerPtr ShaderParameterStringBase::shallowCopy(void) const 
{ 
    ShaderParameterStringPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const ShaderParameterString *>(this)); 

    return returnValue; 
}



/*------------------------- constructors ----------------------------------*/

ShaderParameterStringBase::ShaderParameterStringBase(void) :
    Inherited(),
    _sfValue()
{
}

ShaderParameterStringBase::ShaderParameterStringBase(const ShaderParameterStringBase &source) :
    Inherited(source),
    _sfValue(source._sfValue)
{
}

/*-------------------------- destructors ----------------------------------*/

ShaderParameterStringBase::~ShaderParameterStringBase(void)
{
}


#ifdef OSG_MT_FIELDCONTAINERPTR
void ShaderParameterStringBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo,
                                        UInt32             uiCopyOffset)
{
    this->execSync(static_cast<ShaderParameterStringBase *>(&oFrom),
                   whichField, 
                   syncMode, 
                   uiSyncInfo,
                   uiCopyOffset);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
void ShaderParameterStringBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<ShaderParameterStringBase *>(&oFrom), 
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

#if 0
void ShaderParameterStringBase::execBeginEditV(ConstFieldMaskArg whichField,
                                       UInt32            uiAspect,
                                       UInt32            uiContainerSize)
{
    this->execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
FieldContainerPtr ShaderParameterStringBase::createAspectCopy(void) const
{
    ShaderParameterStringPtr returnValue; 

    newAspectCopy(returnValue, 
                  dynamic_cast<const ShaderParameterString *>(this)); 

    return returnValue; 
}
#endif

void ShaderParameterStringBase::resolveLinks(void)
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
DataType FieldTraits<ShaderParameterStringPtr>::_type("ShaderParameterStringPtr", "ShaderParameterPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(ShaderParameterStringPtr)

OSG_FIELD_DLLEXPORT_DEF1(SField, ShaderParameterStringPtr);
OSG_FIELD_DLLEXPORT_DEF1(MField, ShaderParameterStringPtr);

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
    static Char8 cvsid_hpp       [] = OSGSHADERPARAMETERSTRINGBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHADERPARAMETERSTRINGBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHADERPARAMETERSTRINGFIELDS_HEADER_CVSID;
}
