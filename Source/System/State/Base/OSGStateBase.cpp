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
 **     class State!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILESTATEINST

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>



#include <OSGStateChunk.h> // Chunks Class

#include "OSGStateBase.h"
#include "OSGState.h"

OSG_USING_NAMESPACE

// Field descriptions

/*! \var StateChunkPtr StateBase::_mfChunks
    
*/

void StateBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL; 


    pDesc = new MFStateChunkPtr::Description(
        MFStateChunkPtr::getClassType(), 
        "chunks", 
        ChunksFieldId, ChunksFieldMask,
        false,
        Field::MFDefaultFlags,
        static_cast     <FieldEditMethodSig>(&StateBase::invalidEditField),
        reinterpret_cast<FieldGetMethodSig >(&StateBase::getMFChunks));

    oType.addInitialDesc(pDesc);
}


StateBase::TypeObject StateBase::_type(true,
    StateBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    (PrototypeCreateF) &StateBase::createEmpty,
    State::initMethod,
    (InitalInsertDescFunc) &StateBase::classDescInserter,
    false);

/*------------------------------ get -----------------------------------*/

FieldContainerType &StateBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &StateBase::getType(void) const 
{
    return _type;
} 

UInt32 StateBase::getContainerSize(void) const 
{ 
    return sizeof(State); 
}

/*------------------------- decorator get ------------------------------*/


//! Get the State::_mfChunks field.
const MFStateChunkPtr *StateBase::getMFChunks(void) const
{
    return &_mfChunks;
}


void StateBase::pushToField(      FieldContainerPtrConstArg pNewElement,
                                    const UInt32                    uiFieldId  )
{
    Inherited::pushToField(pNewElement, uiFieldId);

    if(uiFieldId == ChunksFieldId)
    {
        static_cast<State *>(this)->pushToChunks(
            cast_dynamic<StateChunkPtr>(pNewElement));
    }
}

void StateBase::insertIntoMField(const UInt32                    uiIndex,
                                               FieldContainerPtrConstArg pNewElement,
                                         const UInt32                    uiFieldId  )
{
    Inherited::insertIntoMField(uiIndex, pNewElement, uiFieldId);

    if(uiFieldId == ChunksFieldId)
    {
        static_cast<State *>(this)->insertIntoChunks(
            uiIndex,
            cast_dynamic<StateChunkPtr>(pNewElement));
    }
}

void StateBase::replaceInMField (const UInt32                    uiIndex,
                                               FieldContainerPtrConstArg pNewElement,
                                         const UInt32                    uiFieldId)
{
    Inherited::replaceInMField(uiIndex, pNewElement, uiFieldId);

    if(uiFieldId == ChunksFieldId)
    {
        static_cast<State *>(this)->replaceInChunks(
            uiIndex,
            cast_dynamic<StateChunkPtr>(pNewElement));
    }
}

void StateBase::replaceInMField (      FieldContainerPtrConstArg pOldElement,
                                               FieldContainerPtrConstArg pNewElement,
                                         const UInt32                    uiFieldId  )
{
    Inherited::replaceInMField(pOldElement, pNewElement, uiFieldId);

    if(uiFieldId == ChunksFieldId)
    {
        static_cast<State *>(this)->replaceInChunks(
            cast_dynamic<StateChunkPtr>(pOldElement),
            cast_dynamic<StateChunkPtr>(pNewElement));
    }
}

void StateBase::removeFromMField(const UInt32 uiIndex,
                                         const UInt32 uiFieldId)
{
    Inherited::removeFromMField(uiIndex, uiFieldId);

    if(uiFieldId == ChunksFieldId)
    {
        static_cast<State *>(this)->removeFromChunks(
            uiIndex);
    }
}

void StateBase::removeFromMField(      FieldContainerPtrConstArg pElement,
                                         const UInt32                    uiFieldId)
{
    Inherited::removeFromMField(pElement, uiFieldId);

    if(uiFieldId == ChunksFieldId)
    {
        static_cast<State *>(this)->removeFromChunks(
            cast_dynamic<StateChunkPtr>(pElement));
    }
}

void StateBase::clearField(const UInt32 uiFieldId)
{
    Inherited::clearField(uiFieldId);

    if(uiFieldId == ChunksFieldId)
    {
        static_cast<State *>(this)->clearChunks();
    }
}

void StateBase::pushToChunks(StateChunkPtrConstArg value)
{
    editMField(ChunksFieldMask, _mfChunks);

    addRef(value);

    _mfChunks.push_back(value);

    if(value == NullFC)
        return;
}

void StateBase::insertIntoChunks(UInt32                uiIndex,
                                             StateChunkPtrConstArg value   )
{
    editMField(ChunksFieldMask, _mfChunks);

    MFStateChunkPtr::iterator fieldIt = _mfChunks.begin();

    addRef(value);

    fieldIt += uiIndex;

    _mfChunks.insert(fieldIt, value);

    if(value == NullFC)
        return;
}

void StateBase::replaceInChunks(UInt32                uiIndex,
                                                 StateChunkPtrConstArg value   )
{
    if(uiIndex >= _mfChunks.size())
        return;

    editMField(ChunksFieldMask, _mfChunks);

    addRef(value);

    subRef(_mfChunks[uiIndex]);

    _mfChunks[uiIndex] = value;

    if(value == NullFC)
        return;
}

void StateBase::replaceInChunks(StateChunkPtrConstArg pOldElem,
                                                  StateChunkPtrConstArg pNewElem)
{
    Int32  elemIdx = _mfChunks.findIndex(pOldElem);

    if(elemIdx != -1)
    {
        editMField(ChunksFieldMask, _mfChunks);

        MFStateChunkPtr::iterator fieldIt = _mfChunks.begin();

        fieldIt += elemIdx;

        addRef(pNewElem);
        subRef(pOldElem);

        (*fieldIt) = pNewElem;
    }
}

void StateBase::removeFromChunks(UInt32 uiIndex)
{
    if(uiIndex < _mfChunks.size())
    {
        editMField(ChunksFieldMask, _mfChunks);

        MFStateChunkPtr::iterator fieldIt = _mfChunks.begin();

        fieldIt += uiIndex;

        subRef(*fieldIt);

        *fieldIt = NullFC;
    }
}

void StateBase::removeFromChunks(StateChunkPtrConstArg value)
{
    Int32 iElemIdx = _mfChunks.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(ChunksFieldMask, _mfChunks);

        MFStateChunkPtr::iterator fieldIt = _mfChunks.begin();

        fieldIt += iElemIdx;

        subRef(*fieldIt);

        *fieldIt = NullFC;
    }
}
void StateBase::clearChunks(void)
{
    editMField(ChunksFieldMask, _mfChunks);

    MFStateChunkPtr::iterator       fieldIt  = _mfChunks.begin();
    MFStateChunkPtr::const_iterator fieldEnd = _mfChunks.end  ();

    while(fieldIt != fieldEnd)
    {
        subRef(*fieldIt);

        *fieldIt = NullFC;

        ++fieldIt;
    }

    _mfChunks.clear();
}



/*------------------------------ access -----------------------------------*/

UInt32 StateBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ChunksFieldMask & whichField))
    {
        returnValue += _mfChunks.getBinSize();
    }

    return returnValue;
}

void StateBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ChunksFieldMask & whichField))
    {
        _mfChunks.copyToBin(pMem);
    }
}

void StateBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ChunksFieldMask & whichField))
    {
        _mfChunks.copyFromBin(pMem);
    }
}

//! create an empty new instance of the class, do not copy the prototype
StatePtr StateBase::createEmpty(void) 
{ 
    StatePtr returnValue; 
    
    newPtr<State>(returnValue); 

    return returnValue; 
}

FieldContainerPtr StateBase::shallowCopy(void) const 
{ 
    StatePtr returnValue; 

    newPtr(returnValue, dynamic_cast<const State *>(this)); 

    return returnValue; 
}



/*------------------------- constructors ----------------------------------*/

StateBase::StateBase(void) :
    Inherited(),
    _mfChunks()
{
}

StateBase::StateBase(const StateBase &source) :
    Inherited(source),
    _mfChunks()
{
}

/*-------------------------- destructors ----------------------------------*/

StateBase::~StateBase(void)
{
}

void StateBase::onCreate(const State *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {

        MFStateChunkPtr::const_iterator ChunksIt  = 
            source->_mfChunks.begin();
        MFStateChunkPtr::const_iterator ChunksEnd = 
            source->_mfChunks.end  ();

        while(ChunksIt != ChunksEnd)
        {
            this->pushToChunks(*ChunksIt);

            ++ChunksIt;
        }
    }
}

#ifdef OSG_MT_FIELDCONTAINERPTR
void StateBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo,
                                        UInt32             uiCopyOffset)
{
    this->execSync(static_cast<StateBase *>(&oFrom),
                   whichField, 
                   syncMode, 
                   uiSyncInfo,
                   uiCopyOffset);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
void StateBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<StateBase *>(&oFrom), 
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

#if 0
void StateBase::execBeginEditV(ConstFieldMaskArg whichField,
                                       UInt32            uiAspect,
                                       UInt32            uiContainerSize)
{
    this->execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
FieldContainerPtr StateBase::createAspectCopy(void) const
{
    StatePtr returnValue; 

    newAspectCopy(returnValue, 
                  dynamic_cast<const State *>(this)); 

    return returnValue; 
}
#endif

void StateBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<State *>(this)->clearChunks();
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
DataType FieldTraits<StatePtr>::_type("StatePtr", "FieldContainerPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(StatePtr)

OSG_FIELD_DLLEXPORT_DEF1(SField, StatePtr);
OSG_FIELD_DLLEXPORT_DEF1(MField, StatePtr);

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
    static Char8 cvsid_hpp       [] = OSGSTATEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSTATEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSTATEFIELDS_HEADER_CVSID;
}
