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
 **     class ShaderParameterBool!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILESHADERPARAMETERBOOLINST

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>




#include "OSGShaderParameterBoolBase.h"
#include "OSGShaderParameterBool.h"

OSG_USING_NAMESPACE

// Field descriptions

/*! \var bool ShaderParameterBoolBase::_sfValue
    	parameter value

*/

void ShaderParameterBoolBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL; 


#ifdef OSG_1_COMPAT
    typedef const SFBool *(ShaderParameterBoolBase::*GetSFValueF)(void) const;

    GetSFValueF GetSFValue = &ShaderParameterBoolBase::getSFValue;
#endif

    pDesc = new SFBool::Description(
        SFBool::getClassType(), 
        "value", 
        ValueFieldId, ValueFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&ShaderParameterBoolBase::editSFValue),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFValue));
#else
        reinterpret_cast<FieldGetMethodSig >(&ShaderParameterBoolBase::getSFValue));
#endif

    oType.addInitialDesc(pDesc);
}


ShaderParameterBoolBase::TypeObject ShaderParameterBoolBase::_type(true,
    ShaderParameterBoolBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    (PrototypeCreateF) &ShaderParameterBoolBase::createEmpty,
    ShaderParameterBool::initMethod,
    (InitalInsertDescFunc) &ShaderParameterBoolBase::classDescInserter,
    false);

/*------------------------------ get -----------------------------------*/

FieldContainerType &ShaderParameterBoolBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &ShaderParameterBoolBase::getType(void) const 
{
    return _type;
} 

UInt32 ShaderParameterBoolBase::getContainerSize(void) const 
{ 
    return sizeof(ShaderParameterBool); 
}

/*------------------------- decorator get ------------------------------*/


SFBool *ShaderParameterBoolBase::editSFValue(void)
{
    editSField(ValueFieldMask);

    return &_sfValue;
}

const SFBool *ShaderParameterBoolBase::getSFValue(void) const
{
    return &_sfValue;
}

#ifdef OSG_1_COMPAT
SFBool *ShaderParameterBoolBase::getSFValue(void)
{
    return this->editSFValue();
}
#endif



/*------------------------------ access -----------------------------------*/

UInt32 ShaderParameterBoolBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        returnValue += _sfValue.getBinSize();
    }

    return returnValue;
}

void ShaderParameterBoolBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _sfValue.copyToBin(pMem);
    }
}

void ShaderParameterBoolBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _sfValue.copyFromBin(pMem);
    }
}

//! create an empty new instance of the class, do not copy the prototype
ShaderParameterBoolPtr ShaderParameterBoolBase::createEmpty(void) 
{ 
    ShaderParameterBoolPtr returnValue; 
    
    newPtr<ShaderParameterBool>(returnValue); 

    return returnValue; 
}

FieldContainerPtr ShaderParameterBoolBase::shallowCopy(void) const 
{ 
    ShaderParameterBoolPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const ShaderParameterBool *>(this)); 

    return returnValue; 
}



/*------------------------- constructors ----------------------------------*/

ShaderParameterBoolBase::ShaderParameterBoolBase(void) :
    Inherited(),
    _sfValue()
{
}

ShaderParameterBoolBase::ShaderParameterBoolBase(const ShaderParameterBoolBase &source) :
    Inherited(source),
    _sfValue(source._sfValue)
{
}

/*-------------------------- destructors ----------------------------------*/

ShaderParameterBoolBase::~ShaderParameterBoolBase(void)
{
}


#ifdef OSG_MT_FIELDCONTAINERPTR
void ShaderParameterBoolBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo,
                                        UInt32             uiCopyOffset)
{
    this->execSync(static_cast<ShaderParameterBoolBase *>(&oFrom),
                   whichField, 
                   syncMode, 
                   uiSyncInfo,
                   uiCopyOffset);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
void ShaderParameterBoolBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<ShaderParameterBoolBase *>(&oFrom), 
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

#if 0
void ShaderParameterBoolBase::execBeginEditV(ConstFieldMaskArg whichField,
                                       UInt32            uiAspect,
                                       UInt32            uiContainerSize)
{
    this->execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
FieldContainerPtr ShaderParameterBoolBase::createAspectCopy(void) const
{
    ShaderParameterBoolPtr returnValue; 

    newAspectCopy(returnValue, 
                  dynamic_cast<const ShaderParameterBool *>(this)); 

    return returnValue; 
}
#endif

void ShaderParameterBoolBase::resolveLinks(void)
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
DataType FieldTraits<ShaderParameterBoolPtr>::_type("ShaderParameterBoolPtr", "ShaderParameterPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(ShaderParameterBoolPtr)

OSG_FIELD_DLLEXPORT_DEF1(SField, ShaderParameterBoolPtr);
OSG_FIELD_DLLEXPORT_DEF1(MField, ShaderParameterBoolPtr);

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
    static Char8 cvsid_hpp       [] = OSGSHADERPARAMETERBOOLBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHADERPARAMETERBOOLBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHADERPARAMETERBOOLFIELDS_HEADER_CVSID;
}
