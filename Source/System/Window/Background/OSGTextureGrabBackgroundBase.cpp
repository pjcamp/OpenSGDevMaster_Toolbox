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
 **     class TextureGrabBackground!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILETEXTUREGRABBACKGROUNDINST

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>



#include <OSGTextureObjChunk.h> // Texture Class

#include "OSGTextureGrabBackgroundBase.h"
#include "OSGTextureGrabBackground.h"

#include "boost/bind.hpp"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::TextureGrabBackground
    \ingroup GrpSystemWindowBackgrounds

    A background that grabs what's underneath it into a texture before it clears 
    the viewport to a constant color.

    The color of the background is given by the _sfColor field, the texture to
    grab into by the _sfTexture field.
 */

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

/*! \var TextureObjChunkPtr TextureGrabBackgroundBase::_sfTexture
    The texture to grab into.
*/

/*! \var bool            TextureGrabBackgroundBase::_sfAutoResize
    Automatically resize the texture when the viewport size changes.
*/

/*! \var GLenum          TextureGrabBackgroundBase::_sfBindTarget
    Enum to use for glBindTexture, if GL_NONE chosen from texture dimensionality.
*/

/*! \var GLenum          TextureGrabBackgroundBase::_sfCopyTarget
    Enum to use for glCopyTexture, if GL_NONE chosen from texture dimensionality.
    Mainly useful to grab into the different parts of a CubeTexture.
*/


void TextureGrabBackgroundBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUnrecTextureObjChunkPtr::Description(
        SFUnrecTextureObjChunkPtr::getClassType(),
        "texture",
        "The texture to grab into.\n",
        TextureFieldId, TextureFieldMask,
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&TextureGrabBackgroundBase::editHandleTexture),
        static_cast<FieldGetMethodSig >(&TextureGrabBackgroundBase::getHandleTexture));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "autoResize",
        "Automatically resize the texture when the viewport size changes.\n",
        AutoResizeFieldId, AutoResizeFieldMask,
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&TextureGrabBackgroundBase::editHandleAutoResize),
        static_cast<FieldGetMethodSig >(&TextureGrabBackgroundBase::getHandleAutoResize));

    oType.addInitialDesc(pDesc);

    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(),
        "bindTarget",
        "Enum to use for glBindTexture, if GL_NONE chosen from texture dimensionality.\n",
        BindTargetFieldId, BindTargetFieldMask,
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&TextureGrabBackgroundBase::editHandleBindTarget),
        static_cast<FieldGetMethodSig >(&TextureGrabBackgroundBase::getHandleBindTarget));

    oType.addInitialDesc(pDesc);

    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(),
        "copyTarget",
        "Enum to use for glCopyTexture, if GL_NONE chosen from texture dimensionality.\n"
        "Mainly useful to grab into the different parts of a CubeTexture.\n",
        CopyTargetFieldId, CopyTargetFieldMask,
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&TextureGrabBackgroundBase::editHandleCopyTarget),
        static_cast<FieldGetMethodSig >(&TextureGrabBackgroundBase::getHandleCopyTarget));

    oType.addInitialDesc(pDesc);
}


TextureGrabBackgroundBase::TypeObject TextureGrabBackgroundBase::_type(
    TextureGrabBackgroundBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    (PrototypeCreateF) &TextureGrabBackgroundBase::createEmptyLocal,
    TextureGrabBackground::initMethod,
    TextureGrabBackground::exitMethod,
    (InitalInsertDescFunc) &TextureGrabBackgroundBase::classDescInserter,
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"TextureGrabBackground\"\n"
    "\tparent=\"SolidBackground\"\n"
    "\tlibrary=\"Window\"\n"
    "\tpointerfieldtypes=\"none\"\n"
    "\tstructure=\"concrete\"\n"
    "\tsystemcomponent=\"true\"\n"
    "\tparentsystemcomponent=\"true\"\n"
    "\tdecoratable=\"false\"\n"
    ">\n"
    "\\ingroup GrpSystemWindowBackgrounds\n"
    "\n"
    "A background that grabs what's underneath it into a texture before it clears \n"
    "the viewport to a constant color.\n"
    "\n"
    "The color of the background is given by the _sfColor field, the texture to\n"
    "grab into by the _sfTexture field.\n"
    "\t<Field\n"
    "\t\tname=\"texture\"\n"
    "\t\ttype=\"TextureObjChunkPtr\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\tThe texture to grab into.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"autoResize\"\n"
    "\t\ttype=\"bool\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"true\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "        Automatically resize the texture when the viewport size changes.\n"
    "\t</Field>\n"
    "       \t<Field\n"
    "\t\tname=\"bindTarget\"\n"
    "\t\ttype=\"GLenum\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"GL_NONE\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "        Enum to use for glBindTexture, if GL_NONE chosen from texture dimensionality.\n"
    "\t</Field>\n"
    "       \t<Field\n"
    "\t\tname=\"copyTarget\"\n"
    "\t\ttype=\"GLenum\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"GL_NONE\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "        Enum to use for glCopyTexture, if GL_NONE chosen from texture dimensionality.\n"
    "        Mainly useful to grab into the different parts of a CubeTexture.\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    "\\ingroup GrpSystemWindowBackgrounds\n"
    "\n"
    "A background that grabs what's underneath it into a texture before it clears \n"
    "the viewport to a constant color.\n"
    "\n"
    "The color of the background is given by the _sfColor field, the texture to\n"
    "grab into by the _sfTexture field.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &TextureGrabBackgroundBase::getType(void)
{
    return _type;
}

const FieldContainerType &TextureGrabBackgroundBase::getType(void) const
{
    return _type;
}

UInt32 TextureGrabBackgroundBase::getContainerSize(void) const
{
    return sizeof(TextureGrabBackground);
}

/*------------------------- decorator get ------------------------------*/


//! Get the TextureGrabBackground::_sfTexture field.
const SFUnrecTextureObjChunkPtr *TextureGrabBackgroundBase::getSFTexture(void) const
{
    return &_sfTexture;
}

SFUnrecTextureObjChunkPtr *TextureGrabBackgroundBase::editSFTexture        (void)
{
    editSField(TextureFieldMask);

    return &_sfTexture;
}

SFBool *TextureGrabBackgroundBase::editSFAutoResize(void)
{
    editSField(AutoResizeFieldMask);

    return &_sfAutoResize;
}

const SFBool *TextureGrabBackgroundBase::getSFAutoResize(void) const
{
    return &_sfAutoResize;
}

#ifdef OSG_1_GET_COMPAT
SFBool              *TextureGrabBackgroundBase::getSFAutoResize     (void)
{
    return this->editSFAutoResize     ();
}
#endif

SFGLenum *TextureGrabBackgroundBase::editSFBindTarget(void)
{
    editSField(BindTargetFieldMask);

    return &_sfBindTarget;
}

const SFGLenum *TextureGrabBackgroundBase::getSFBindTarget(void) const
{
    return &_sfBindTarget;
}

#ifdef OSG_1_GET_COMPAT
SFGLenum            *TextureGrabBackgroundBase::getSFBindTarget     (void)
{
    return this->editSFBindTarget     ();
}
#endif

SFGLenum *TextureGrabBackgroundBase::editSFCopyTarget(void)
{
    editSField(CopyTargetFieldMask);

    return &_sfCopyTarget;
}

const SFGLenum *TextureGrabBackgroundBase::getSFCopyTarget(void) const
{
    return &_sfCopyTarget;
}

#ifdef OSG_1_GET_COMPAT
SFGLenum            *TextureGrabBackgroundBase::getSFCopyTarget     (void)
{
    return this->editSFCopyTarget     ();
}
#endif





/*------------------------------ access -----------------------------------*/

UInt32 TextureGrabBackgroundBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (TextureFieldMask & whichField))
    {
        returnValue += _sfTexture.getBinSize();
    }
    if(FieldBits::NoField != (AutoResizeFieldMask & whichField))
    {
        returnValue += _sfAutoResize.getBinSize();
    }
    if(FieldBits::NoField != (BindTargetFieldMask & whichField))
    {
        returnValue += _sfBindTarget.getBinSize();
    }
    if(FieldBits::NoField != (CopyTargetFieldMask & whichField))
    {
        returnValue += _sfCopyTarget.getBinSize();
    }

    return returnValue;
}

void TextureGrabBackgroundBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (TextureFieldMask & whichField))
    {
        _sfTexture.copyToBin(pMem);
    }
    if(FieldBits::NoField != (AutoResizeFieldMask & whichField))
    {
        _sfAutoResize.copyToBin(pMem);
    }
    if(FieldBits::NoField != (BindTargetFieldMask & whichField))
    {
        _sfBindTarget.copyToBin(pMem);
    }
    if(FieldBits::NoField != (CopyTargetFieldMask & whichField))
    {
        _sfCopyTarget.copyToBin(pMem);
    }
}

void TextureGrabBackgroundBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (TextureFieldMask & whichField))
    {
        _sfTexture.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (AutoResizeFieldMask & whichField))
    {
        _sfAutoResize.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (BindTargetFieldMask & whichField))
    {
        _sfBindTarget.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (CopyTargetFieldMask & whichField))
    {
        _sfCopyTarget.copyFromBin(pMem);
    }
}

//! create a new instance of the class
TextureGrabBackgroundTransitPtr TextureGrabBackgroundBase::create(void)
{
    TextureGrabBackgroundTransitPtr fc;

    if(getClassType().getPrototype() != NullFC)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<TextureGrabBackground>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
TextureGrabBackgroundTransitPtr TextureGrabBackgroundBase::createLocal(BitVector bFlags)
{
    TextureGrabBackgroundTransitPtr fc;

    if(getClassType().getPrototype() != NullFC)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<TextureGrabBackground>(tmpPtr);
    }

    return fc;
}

//! create an empty new instance of the class, do not copy the prototype
TextureGrabBackgroundPtr TextureGrabBackgroundBase::createEmpty(void)
{
    TextureGrabBackgroundPtr returnValue;

    newPtr<TextureGrabBackground>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &= 
        ~Thread::getCurrentLocalFlags(); 

    return returnValue;
}

TextureGrabBackgroundPtr TextureGrabBackgroundBase::createEmptyLocal(BitVector bFlags)
{
    TextureGrabBackgroundPtr returnValue;

    newPtr<TextureGrabBackground>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr TextureGrabBackgroundBase::shallowCopy(void) const
{
    TextureGrabBackgroundPtr tmpPtr;

    newPtr(tmpPtr, 
           dynamic_cast<const TextureGrabBackground *>(this), 
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}

FieldContainerTransitPtr TextureGrabBackgroundBase::shallowCopyLocal(
    BitVector bFlags) const
{
    TextureGrabBackgroundPtr tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const TextureGrabBackground *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

TextureGrabBackgroundBase::TextureGrabBackgroundBase(void) :
    Inherited(),
    _sfTexture                (NullFC),
    _sfAutoResize             (bool(true)),
    _sfBindTarget             (GLenum(GL_NONE)),
    _sfCopyTarget             (GLenum(GL_NONE))
{
}

TextureGrabBackgroundBase::TextureGrabBackgroundBase(const TextureGrabBackgroundBase &source) :
    Inherited(source),
    _sfTexture                (NullFC),
    _sfAutoResize             (source._sfAutoResize             ),
    _sfBindTarget             (source._sfBindTarget             ),
    _sfCopyTarget             (source._sfCopyTarget             )
{
}


/*-------------------------- destructors ----------------------------------*/

TextureGrabBackgroundBase::~TextureGrabBackgroundBase(void)
{
}

void TextureGrabBackgroundBase::onCreate(const TextureGrabBackground *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        TextureGrabBackground *pThis = static_cast<TextureGrabBackground *>(this);

        pThis->setTexture(source->getTexture());
    }
}

GetFieldHandlePtr TextureGrabBackgroundBase::getHandleTexture         (void) const
{
    SFUnrecTextureObjChunkPtr::GetHandlePtr returnValue(
        new  SFUnrecTextureObjChunkPtr::GetHandle(
             &_sfTexture, 
             this->getType().getFieldDesc(TextureFieldId)));

    return returnValue;
}

EditFieldHandlePtr TextureGrabBackgroundBase::editHandleTexture        (void)
{
    SFUnrecTextureObjChunkPtr::EditHandlePtr returnValue(
        new  SFUnrecTextureObjChunkPtr::EditHandle(
             &_sfTexture, 
             this->getType().getFieldDesc(TextureFieldId)));

    returnValue->setSetMethod(boost::bind(&TextureGrabBackground::setTexture, 
                                          static_cast<TextureGrabBackground *>(this), _1));

    editSField(TextureFieldMask);

    return returnValue;
}

GetFieldHandlePtr TextureGrabBackgroundBase::getHandleAutoResize      (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfAutoResize, 
             this->getType().getFieldDesc(AutoResizeFieldId)));

    return returnValue;
}

EditFieldHandlePtr TextureGrabBackgroundBase::editHandleAutoResize     (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfAutoResize, 
             this->getType().getFieldDesc(AutoResizeFieldId)));

    editSField(AutoResizeFieldMask);

    return returnValue;
}

GetFieldHandlePtr TextureGrabBackgroundBase::getHandleBindTarget      (void) const
{
    SFGLenum::GetHandlePtr returnValue(
        new  SFGLenum::GetHandle(
             &_sfBindTarget, 
             this->getType().getFieldDesc(BindTargetFieldId)));

    return returnValue;
}

EditFieldHandlePtr TextureGrabBackgroundBase::editHandleBindTarget     (void)
{
    SFGLenum::EditHandlePtr returnValue(
        new  SFGLenum::EditHandle(
             &_sfBindTarget, 
             this->getType().getFieldDesc(BindTargetFieldId)));

    editSField(BindTargetFieldMask);

    return returnValue;
}

GetFieldHandlePtr TextureGrabBackgroundBase::getHandleCopyTarget      (void) const
{
    SFGLenum::GetHandlePtr returnValue(
        new  SFGLenum::GetHandle(
             &_sfCopyTarget, 
             this->getType().getFieldDesc(CopyTargetFieldId)));

    return returnValue;
}

EditFieldHandlePtr TextureGrabBackgroundBase::editHandleCopyTarget     (void)
{
    SFGLenum::EditHandlePtr returnValue(
        new  SFGLenum::EditHandle(
             &_sfCopyTarget, 
             this->getType().getFieldDesc(CopyTargetFieldId)));

    editSField(CopyTargetFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void TextureGrabBackgroundBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<TextureGrabBackgroundBase *>(&oFrom),
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainerPtr TextureGrabBackgroundBase::createAspectCopy(void) const
{
    TextureGrabBackgroundPtr returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const TextureGrabBackground *>(this));

    return returnValue;
}
#endif

void TextureGrabBackgroundBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<TextureGrabBackground *>(this)->setTexture(NullFC);


}


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<TextureGrabBackgroundPtr>::_type("TextureGrabBackgroundPtr", "SolidBackgroundPtr");
#endif


OSG_END_NAMESPACE
