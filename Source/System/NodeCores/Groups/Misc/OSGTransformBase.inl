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
 **     class Transform!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &TransformBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 TransformBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

inline
OSG::UInt16 TransformBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the Transform::_sfMatrix field.

inline
Matrixr &TransformBase::editMatrix(void)
{
    editSField(MatrixFieldMask);

    return _sfMatrix.getValue();
}

//! Get the value of the Transform::_sfMatrix field.
inline
const Matrixr &TransformBase::getMatrix(void) const
{
    return _sfMatrix.getValue();
}

#ifdef OSG_1_COMPAT
inline
Matrixr &TransformBase::getMatrix(void)
{
    return this->editMatrix();
}
#endif

//! Set the value of the Transform::_sfMatrix field.
inline
void TransformBase::setMatrix(const Matrixr &value)
{
    editSField(MatrixFieldMask);

    _sfMatrix.setValue(value);
}

//! create a new instance of the class
inline
TransformPtr TransformBase::create(void) 
{
    TransformPtr fc; 

    if(getClassType().getPrototype() != NullFC) 
    {
        fc = OSG::cast_dynamic<Transform::ObjPtr>(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

#ifdef OSG_MT_FIELDCONTAINERPTR
inline
void TransformBase::execSync(      TransformBase *pOther,
                                       ConstFieldMaskArg  whichField,
                                       ConstFieldMaskArg  syncMode  ,
                                 const UInt32             uiSyncInfo,
                                       UInt32             uiCopyOffset)
{
    Inherited::execSync(pOther, whichField, syncMode, uiSyncInfo, uiCopyOffset);

    if(FieldBits::NoField != (MatrixFieldMask & whichField))
        _sfMatrix.syncWith(pOther->_sfMatrix);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
inline
void TransformBase::execSync (      TransformBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (MatrixFieldMask & whichField))
        _sfMatrix.syncWith(pFrom->_sfMatrix);
}
#endif

#if 0
inline
void TransformBase::execBeginEdit(ConstFieldMaskArg whichField,
                                      UInt32            uiAspect,
                                      UInt32            uiContainerSize)
{
    Inherited::execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif


inline
Char8 *TransformBase::getClassname(void)
{
    return "Transform";
}

typedef PointerBuilder<Transform>::ObjPtr          TransformPtr;
typedef PointerBuilder<Transform>::ObjPtrConst     TransformPtrConst;
typedef PointerBuilder<Transform>::ObjConstPtr     TransformConstPtr;

typedef PointerBuilder<Transform>::ObjPtrArg       TransformPtrArg;
typedef PointerBuilder<Transform>::ObjConstPtrArg  TransformConstPtrArg;
typedef PointerBuilder<Transform>::ObjPtrConstArg  TransformPtrConstArg;

OSG_END_NAMESPACE

#define OSGTRANSFORMBASE_INLINE_CVSID "@(#)$Id$"

