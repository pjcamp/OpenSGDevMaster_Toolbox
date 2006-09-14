/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &StencilChunkBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 StencilChunkBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

inline
OSG::UInt16 StencilChunkBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the StencilChunk::_sfStencilFunc field.

inline
GLenum &StencilChunkBase::editStencilFunc(void)
{
    editSField(StencilFuncFieldMask);

    return _sfStencilFunc.getValue();
}

//! Get the value of the StencilChunk::_sfStencilFunc field.
inline
const GLenum &StencilChunkBase::getStencilFunc(void) const
{
    return _sfStencilFunc.getValue();
}

#ifdef OSG_1_COMPAT
inline
GLenum &StencilChunkBase::getStencilFunc(void)
{
    return this->editStencilFunc();
}
#endif

//! Set the value of the StencilChunk::_sfStencilFunc field.
inline
void StencilChunkBase::setStencilFunc(const GLenum &value)
{
    editSField(StencilFuncFieldMask);

    _sfStencilFunc.setValue(value);
}
//! Get the value of the StencilChunk::_sfStencilValue field.

inline
Int32 &StencilChunkBase::editStencilValue(void)
{
    editSField(StencilValueFieldMask);

    return _sfStencilValue.getValue();
}

//! Get the value of the StencilChunk::_sfStencilValue field.
inline
const Int32 &StencilChunkBase::getStencilValue(void) const
{
    return _sfStencilValue.getValue();
}

#ifdef OSG_1_COMPAT
inline
Int32 &StencilChunkBase::getStencilValue(void)
{
    return this->editStencilValue();
}
#endif

//! Set the value of the StencilChunk::_sfStencilValue field.
inline
void StencilChunkBase::setStencilValue(const Int32 &value)
{
    editSField(StencilValueFieldMask);

    _sfStencilValue.setValue(value);
}
//! Get the value of the StencilChunk::_sfStencilMask field.

inline
UInt32 &StencilChunkBase::editStencilMask(void)
{
    editSField(StencilMaskFieldMask);

    return _sfStencilMask.getValue();
}

//! Get the value of the StencilChunk::_sfStencilMask field.
inline
const UInt32 &StencilChunkBase::getStencilMask(void) const
{
    return _sfStencilMask.getValue();
}

#ifdef OSG_1_COMPAT
inline
UInt32 &StencilChunkBase::getStencilMask(void)
{
    return this->editStencilMask();
}
#endif

//! Set the value of the StencilChunk::_sfStencilMask field.
inline
void StencilChunkBase::setStencilMask(const UInt32 &value)
{
    editSField(StencilMaskFieldMask);

    _sfStencilMask.setValue(value);
}
//! Get the value of the StencilChunk::_sfStencilOpFail field.

inline
GLenum &StencilChunkBase::editStencilOpFail(void)
{
    editSField(StencilOpFailFieldMask);

    return _sfStencilOpFail.getValue();
}

//! Get the value of the StencilChunk::_sfStencilOpFail field.
inline
const GLenum &StencilChunkBase::getStencilOpFail(void) const
{
    return _sfStencilOpFail.getValue();
}

#ifdef OSG_1_COMPAT
inline
GLenum &StencilChunkBase::getStencilOpFail(void)
{
    return this->editStencilOpFail();
}
#endif

//! Set the value of the StencilChunk::_sfStencilOpFail field.
inline
void StencilChunkBase::setStencilOpFail(const GLenum &value)
{
    editSField(StencilOpFailFieldMask);

    _sfStencilOpFail.setValue(value);
}
//! Get the value of the StencilChunk::_sfStencilOpZFail field.

inline
GLenum &StencilChunkBase::editStencilOpZFail(void)
{
    editSField(StencilOpZFailFieldMask);

    return _sfStencilOpZFail.getValue();
}

//! Get the value of the StencilChunk::_sfStencilOpZFail field.
inline
const GLenum &StencilChunkBase::getStencilOpZFail(void) const
{
    return _sfStencilOpZFail.getValue();
}

#ifdef OSG_1_COMPAT
inline
GLenum &StencilChunkBase::getStencilOpZFail(void)
{
    return this->editStencilOpZFail();
}
#endif

//! Set the value of the StencilChunk::_sfStencilOpZFail field.
inline
void StencilChunkBase::setStencilOpZFail(const GLenum &value)
{
    editSField(StencilOpZFailFieldMask);

    _sfStencilOpZFail.setValue(value);
}
//! Get the value of the StencilChunk::_sfStencilOpZPass field.

inline
GLenum &StencilChunkBase::editStencilOpZPass(void)
{
    editSField(StencilOpZPassFieldMask);

    return _sfStencilOpZPass.getValue();
}

//! Get the value of the StencilChunk::_sfStencilOpZPass field.
inline
const GLenum &StencilChunkBase::getStencilOpZPass(void) const
{
    return _sfStencilOpZPass.getValue();
}

#ifdef OSG_1_COMPAT
inline
GLenum &StencilChunkBase::getStencilOpZPass(void)
{
    return this->editStencilOpZPass();
}
#endif

//! Set the value of the StencilChunk::_sfStencilOpZPass field.
inline
void StencilChunkBase::setStencilOpZPass(const GLenum &value)
{
    editSField(StencilOpZPassFieldMask);

    _sfStencilOpZPass.setValue(value);
}
//! Get the value of the StencilChunk::_sfClearBuffer field.

inline
Int32 &StencilChunkBase::editClearBuffer(void)
{
    editSField(ClearBufferFieldMask);

    return _sfClearBuffer.getValue();
}

//! Get the value of the StencilChunk::_sfClearBuffer field.
inline
const Int32 &StencilChunkBase::getClearBuffer(void) const
{
    return _sfClearBuffer.getValue();
}

#ifdef OSG_1_COMPAT
inline
Int32 &StencilChunkBase::getClearBuffer(void)
{
    return this->editClearBuffer();
}
#endif

//! Set the value of the StencilChunk::_sfClearBuffer field.
inline
void StencilChunkBase::setClearBuffer(const Int32 &value)
{
    editSField(ClearBufferFieldMask);

    _sfClearBuffer.setValue(value);
}

//! create a new instance of the class
inline
StencilChunkPtr StencilChunkBase::create(void) 
{
    StencilChunkPtr fc; 

    if(getClassType().getPrototype() != NullFC) 
    {
        fc = OSG::cast_dynamic<StencilChunk::ObjPtr>(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

#ifdef OSG_MT_FIELDCONTAINERPTR
inline
void StencilChunkBase::execSync(      StencilChunkBase *pOther,
                                       ConstFieldMaskArg  whichField,
                                       ConstFieldMaskArg  syncMode  ,
                                 const UInt32             uiSyncInfo,
                                       UInt32             uiCopyOffset)
{
    Inherited::execSync(pOther, whichField, syncMode, uiSyncInfo, uiCopyOffset);

    if(FieldBits::NoField != (StencilFuncFieldMask & whichField))
        _sfStencilFunc.syncWith(pOther->_sfStencilFunc);

    if(FieldBits::NoField != (StencilValueFieldMask & whichField))
        _sfStencilValue.syncWith(pOther->_sfStencilValue);

    if(FieldBits::NoField != (StencilMaskFieldMask & whichField))
        _sfStencilMask.syncWith(pOther->_sfStencilMask);

    if(FieldBits::NoField != (StencilOpFailFieldMask & whichField))
        _sfStencilOpFail.syncWith(pOther->_sfStencilOpFail);

    if(FieldBits::NoField != (StencilOpZFailFieldMask & whichField))
        _sfStencilOpZFail.syncWith(pOther->_sfStencilOpZFail);

    if(FieldBits::NoField != (StencilOpZPassFieldMask & whichField))
        _sfStencilOpZPass.syncWith(pOther->_sfStencilOpZPass);

    if(FieldBits::NoField != (ClearBufferFieldMask & whichField))
        _sfClearBuffer.syncWith(pOther->_sfClearBuffer);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
inline
void StencilChunkBase::execSync (      StencilChunkBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (StencilFuncFieldMask & whichField))
        _sfStencilFunc.syncWith(pFrom->_sfStencilFunc);

    if(FieldBits::NoField != (StencilValueFieldMask & whichField))
        _sfStencilValue.syncWith(pFrom->_sfStencilValue);

    if(FieldBits::NoField != (StencilMaskFieldMask & whichField))
        _sfStencilMask.syncWith(pFrom->_sfStencilMask);

    if(FieldBits::NoField != (StencilOpFailFieldMask & whichField))
        _sfStencilOpFail.syncWith(pFrom->_sfStencilOpFail);

    if(FieldBits::NoField != (StencilOpZFailFieldMask & whichField))
        _sfStencilOpZFail.syncWith(pFrom->_sfStencilOpZFail);

    if(FieldBits::NoField != (StencilOpZPassFieldMask & whichField))
        _sfStencilOpZPass.syncWith(pFrom->_sfStencilOpZPass);

    if(FieldBits::NoField != (ClearBufferFieldMask & whichField))
        _sfClearBuffer.syncWith(pFrom->_sfClearBuffer);
}
#endif

#if 0
inline
void StencilChunkBase::execBeginEdit(ConstFieldMaskArg whichField,
                                      UInt32            uiAspect,
                                      UInt32            uiContainerSize)
{
    Inherited::execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif


inline
Char8 *StencilChunkBase::getClassname(void)
{
    return "StencilChunk";
}

typedef PointerBuilder<StencilChunk>::ObjPtr          StencilChunkPtr;
typedef PointerBuilder<StencilChunk>::ObjPtrConst     StencilChunkPtrConst;
typedef PointerBuilder<StencilChunk>::ObjConstPtr     StencilChunkConstPtr;

typedef PointerBuilder<StencilChunk>::ObjPtrArg       StencilChunkPtrArg;
typedef PointerBuilder<StencilChunk>::ObjConstPtrArg  StencilChunkConstPtrArg;
typedef PointerBuilder<StencilChunk>::ObjPtrConstArg  StencilChunkPtrConstArg;

OSG_END_NAMESPACE

#define OSGSTENCILCHUNKBASE_INLINE_CVSID "@(#)$Id$"

