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
 **     class SimpleTexturedMaterial!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILESIMPLETEXTUREDMATERIALINST

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>


#include <OSGGL.h>   // MinFilter default header
#include <OSGGL.h>   // MagFilter default header
#include <OSGGL.h>   // EnvMode default header

#include <OSGImage.h> // Image Class

#include "OSGSimpleTexturedMaterialBase.h"
#include "OSGSimpleTexturedMaterial.h"

OSG_USING_NAMESPACE

// Field descriptions

/*! \var ImagePtr SimpleTexturedMaterialBase::_sfImage
    	Defines the texture image.

*/
/*! \var GLenum SimpleTexturedMaterialBase::_sfMinFilter
    	Defines the minification filter, see glTexParameter for details.          Default: GL_LINEAR_MIPMAP_LINEAR.

*/
/*! \var GLenum SimpleTexturedMaterialBase::_sfMagFilter
    	Defines the magnification filter, see glTexParameter for details.          Default: GL_LINEAR

*/
/*! \var GLenum SimpleTexturedMaterialBase::_sfEnvMode
    	Sets the environment mode, defining how texture and lighting color interact.         Default: GL_REPLACE.

*/
/*! \var bool SimpleTexturedMaterialBase::_sfEnvMap
    	Defines whether to use the texture as a spherical environment map.

*/

void SimpleTexturedMaterialBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL; 


    pDesc = new SFImagePtr::Description(
        SFImagePtr::getClassType(), 
        "image", 
        ImageFieldId, ImageFieldMask,
        false,
        Field::SFDefaultFlags,
        static_cast     <FieldEditMethodSig>(&SimpleTexturedMaterialBase::invalidEditField),
        reinterpret_cast<FieldGetMethodSig >(&SimpleTexturedMaterialBase::getSFImage));

    oType.addInitialDesc(pDesc);

#ifdef OSG_1_COMPAT
    typedef const SFGLenum *(SimpleTexturedMaterialBase::*GetSFMinFilterF)(void) const;

    GetSFMinFilterF GetSFMinFilter = &SimpleTexturedMaterialBase::getSFMinFilter;
#endif

    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(), 
        "minFilter", 
        MinFilterFieldId, MinFilterFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&SimpleTexturedMaterialBase::editSFMinFilter),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFMinFilter));
#else
        reinterpret_cast<FieldGetMethodSig >(&SimpleTexturedMaterialBase::getSFMinFilter));
#endif

    oType.addInitialDesc(pDesc);

#ifdef OSG_1_COMPAT
    typedef const SFGLenum *(SimpleTexturedMaterialBase::*GetSFMagFilterF)(void) const;

    GetSFMagFilterF GetSFMagFilter = &SimpleTexturedMaterialBase::getSFMagFilter;
#endif

    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(), 
        "magFilter", 
        MagFilterFieldId, MagFilterFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&SimpleTexturedMaterialBase::editSFMagFilter),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFMagFilter));
#else
        reinterpret_cast<FieldGetMethodSig >(&SimpleTexturedMaterialBase::getSFMagFilter));
#endif

    oType.addInitialDesc(pDesc);

#ifdef OSG_1_COMPAT
    typedef const SFGLenum *(SimpleTexturedMaterialBase::*GetSFEnvModeF)(void) const;

    GetSFEnvModeF GetSFEnvMode = &SimpleTexturedMaterialBase::getSFEnvMode;
#endif

    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(), 
        "envMode", 
        EnvModeFieldId, EnvModeFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&SimpleTexturedMaterialBase::editSFEnvMode),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFEnvMode));
#else
        reinterpret_cast<FieldGetMethodSig >(&SimpleTexturedMaterialBase::getSFEnvMode));
#endif

    oType.addInitialDesc(pDesc);

#ifdef OSG_1_COMPAT
    typedef const SFBool *(SimpleTexturedMaterialBase::*GetSFEnvMapF)(void) const;

    GetSFEnvMapF GetSFEnvMap = &SimpleTexturedMaterialBase::getSFEnvMap;
#endif

    pDesc = new SFBool::Description(
        SFBool::getClassType(), 
        "envMap", 
        EnvMapFieldId, EnvMapFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&SimpleTexturedMaterialBase::editSFEnvMap),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFEnvMap));
#else
        reinterpret_cast<FieldGetMethodSig >(&SimpleTexturedMaterialBase::getSFEnvMap));
#endif

    oType.addInitialDesc(pDesc);
}


SimpleTexturedMaterialBase::TypeObject SimpleTexturedMaterialBase::_type(true,
    SimpleTexturedMaterialBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    (PrototypeCreateF) &SimpleTexturedMaterialBase::createEmpty,
    SimpleTexturedMaterial::initMethod,
    (InitalInsertDescFunc) &SimpleTexturedMaterialBase::classDescInserter,
    false);

/*------------------------------ get -----------------------------------*/

FieldContainerType &SimpleTexturedMaterialBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &SimpleTexturedMaterialBase::getType(void) const 
{
    return _type;
} 

UInt32 SimpleTexturedMaterialBase::getContainerSize(void) const 
{ 
    return sizeof(SimpleTexturedMaterial); 
}

/*------------------------- decorator get ------------------------------*/


//! Get the SimpleTexturedMaterial::_sfImage field.
const SFImagePtr *SimpleTexturedMaterialBase::getSFImage(void) const
{
    return &_sfImage;
}

SFGLenum *SimpleTexturedMaterialBase::editSFMinFilter(void)
{
    editSField(MinFilterFieldMask);

    return &_sfMinFilter;
}

const SFGLenum *SimpleTexturedMaterialBase::getSFMinFilter(void) const
{
    return &_sfMinFilter;
}

#ifdef OSG_1_COMPAT
SFGLenum *SimpleTexturedMaterialBase::getSFMinFilter(void)
{
    return this->editSFMinFilter();
}
#endif

SFGLenum *SimpleTexturedMaterialBase::editSFMagFilter(void)
{
    editSField(MagFilterFieldMask);

    return &_sfMagFilter;
}

const SFGLenum *SimpleTexturedMaterialBase::getSFMagFilter(void) const
{
    return &_sfMagFilter;
}

#ifdef OSG_1_COMPAT
SFGLenum *SimpleTexturedMaterialBase::getSFMagFilter(void)
{
    return this->editSFMagFilter();
}
#endif

SFGLenum *SimpleTexturedMaterialBase::editSFEnvMode(void)
{
    editSField(EnvModeFieldMask);

    return &_sfEnvMode;
}

const SFGLenum *SimpleTexturedMaterialBase::getSFEnvMode(void) const
{
    return &_sfEnvMode;
}

#ifdef OSG_1_COMPAT
SFGLenum *SimpleTexturedMaterialBase::getSFEnvMode(void)
{
    return this->editSFEnvMode();
}
#endif

SFBool *SimpleTexturedMaterialBase::editSFEnvMap(void)
{
    editSField(EnvMapFieldMask);

    return &_sfEnvMap;
}

const SFBool *SimpleTexturedMaterialBase::getSFEnvMap(void) const
{
    return &_sfEnvMap;
}

#ifdef OSG_1_COMPAT
SFBool *SimpleTexturedMaterialBase::getSFEnvMap(void)
{
    return this->editSFEnvMap();
}
#endif


void SimpleTexturedMaterialBase::pushToField(      FieldContainerPtrConstArg pNewElement,
                                    const UInt32                    uiFieldId  )
{
    Inherited::pushToField(pNewElement, uiFieldId);

    if(uiFieldId == ImageFieldId)
    {
        static_cast<SimpleTexturedMaterial *>(this)->setImage(
            cast_dynamic<ImagePtr>(pNewElement));
    }
}

void SimpleTexturedMaterialBase::insertIntoMField(const UInt32                    uiIndex,
                                               FieldContainerPtrConstArg pNewElement,
                                         const UInt32                    uiFieldId  )
{
    Inherited::insertIntoMField(uiIndex, pNewElement, uiFieldId);

}

void SimpleTexturedMaterialBase::replaceInMField (const UInt32                    uiIndex,
                                               FieldContainerPtrConstArg pNewElement,
                                         const UInt32                    uiFieldId)
{
    Inherited::replaceInMField(uiIndex, pNewElement, uiFieldId);

}

void SimpleTexturedMaterialBase::replaceInMField (      FieldContainerPtrConstArg pOldElement,
                                               FieldContainerPtrConstArg pNewElement,
                                         const UInt32                    uiFieldId  )
{
    Inherited::replaceInMField(pOldElement, pNewElement, uiFieldId);

}

void SimpleTexturedMaterialBase::removeFromMField(const UInt32 uiIndex,
                                         const UInt32 uiFieldId)
{
    Inherited::removeFromMField(uiIndex, uiFieldId);

}

void SimpleTexturedMaterialBase::removeFromMField(      FieldContainerPtrConstArg pElement,
                                         const UInt32                    uiFieldId)
{
    Inherited::removeFromMField(pElement, uiFieldId);

}

void SimpleTexturedMaterialBase::clearField(const UInt32 uiFieldId)
{
    Inherited::clearField(uiFieldId);

    if(uiFieldId == ImageFieldId)
    {
        static_cast<SimpleTexturedMaterial *>(this)->setImage(NullFC);
    }
}



/*------------------------------ access -----------------------------------*/

UInt32 SimpleTexturedMaterialBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ImageFieldMask & whichField))
    {
        returnValue += _sfImage.getBinSize();
    }
    if(FieldBits::NoField != (MinFilterFieldMask & whichField))
    {
        returnValue += _sfMinFilter.getBinSize();
    }
    if(FieldBits::NoField != (MagFilterFieldMask & whichField))
    {
        returnValue += _sfMagFilter.getBinSize();
    }
    if(FieldBits::NoField != (EnvModeFieldMask & whichField))
    {
        returnValue += _sfEnvMode.getBinSize();
    }
    if(FieldBits::NoField != (EnvMapFieldMask & whichField))
    {
        returnValue += _sfEnvMap.getBinSize();
    }

    return returnValue;
}

void SimpleTexturedMaterialBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ImageFieldMask & whichField))
    {
        _sfImage.copyToBin(pMem);
    }
    if(FieldBits::NoField != (MinFilterFieldMask & whichField))
    {
        _sfMinFilter.copyToBin(pMem);
    }
    if(FieldBits::NoField != (MagFilterFieldMask & whichField))
    {
        _sfMagFilter.copyToBin(pMem);
    }
    if(FieldBits::NoField != (EnvModeFieldMask & whichField))
    {
        _sfEnvMode.copyToBin(pMem);
    }
    if(FieldBits::NoField != (EnvMapFieldMask & whichField))
    {
        _sfEnvMap.copyToBin(pMem);
    }
}

void SimpleTexturedMaterialBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ImageFieldMask & whichField))
    {
        _sfImage.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (MinFilterFieldMask & whichField))
    {
        _sfMinFilter.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (MagFilterFieldMask & whichField))
    {
        _sfMagFilter.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (EnvModeFieldMask & whichField))
    {
        _sfEnvMode.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (EnvMapFieldMask & whichField))
    {
        _sfEnvMap.copyFromBin(pMem);
    }
}

//! create an empty new instance of the class, do not copy the prototype
SimpleTexturedMaterialPtr SimpleTexturedMaterialBase::createEmpty(void) 
{ 
    SimpleTexturedMaterialPtr returnValue; 
    
    newPtr<SimpleTexturedMaterial>(returnValue); 

    return returnValue; 
}

FieldContainerPtr SimpleTexturedMaterialBase::shallowCopy(void) const 
{ 
    SimpleTexturedMaterialPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const SimpleTexturedMaterial *>(this)); 

    return returnValue; 
}



/*------------------------- constructors ----------------------------------*/

SimpleTexturedMaterialBase::SimpleTexturedMaterialBase(void) :
    Inherited(),
    _sfImage(),
    _sfMinFilter(GLenum(GL_LINEAR_MIPMAP_LINEAR)),
    _sfMagFilter(GLenum(GL_LINEAR)),
    _sfEnvMode(GLenum(GL_REPLACE)),
    _sfEnvMap(bool(false))
{
}

SimpleTexturedMaterialBase::SimpleTexturedMaterialBase(const SimpleTexturedMaterialBase &source) :
    Inherited(source),
    _sfImage(),
    _sfMinFilter(source._sfMinFilter),
    _sfMagFilter(source._sfMagFilter),
    _sfEnvMode(source._sfEnvMode),
    _sfEnvMap(source._sfEnvMap)
{
}

/*-------------------------- destructors ----------------------------------*/

SimpleTexturedMaterialBase::~SimpleTexturedMaterialBase(void)
{
}

void SimpleTexturedMaterialBase::onCreate(const SimpleTexturedMaterial *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {

        this->setImage(source->getImage());
    }
}

#ifdef OSG_MT_FIELDCONTAINERPTR
void SimpleTexturedMaterialBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo,
                                        UInt32             uiCopyOffset)
{
    this->execSync(static_cast<SimpleTexturedMaterialBase *>(&oFrom),
                   whichField, 
                   syncMode, 
                   uiSyncInfo,
                   uiCopyOffset);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
void SimpleTexturedMaterialBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<SimpleTexturedMaterialBase *>(&oFrom), 
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

#if 0
void SimpleTexturedMaterialBase::execBeginEditV(ConstFieldMaskArg whichField,
                                       UInt32            uiAspect,
                                       UInt32            uiContainerSize)
{
    this->execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
FieldContainerPtr SimpleTexturedMaterialBase::createAspectCopy(void) const
{
    SimpleTexturedMaterialPtr returnValue; 

    newAspectCopy(returnValue, 
                  dynamic_cast<const SimpleTexturedMaterial *>(this)); 

    return returnValue; 
}
#endif

void SimpleTexturedMaterialBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<SimpleTexturedMaterial *>(this)->setImage(NullFC);
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
DataType FieldTraits<SimpleTexturedMaterialPtr>::_type("SimpleTexturedMaterialPtr", "SimpleMaterialPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(SimpleTexturedMaterialPtr)

OSG_FIELD_DLLEXPORT_DEF1(SField, SimpleTexturedMaterialPtr);
OSG_FIELD_DLLEXPORT_DEF1(MField, SimpleTexturedMaterialPtr);

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
    static Char8 cvsid_hpp       [] = OSGSIMPLETEXTUREDMATERIALBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSIMPLETEXTUREDMATERIALBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSIMPLETEXTUREDMATERIALFIELDS_HEADER_CVSID;
}
