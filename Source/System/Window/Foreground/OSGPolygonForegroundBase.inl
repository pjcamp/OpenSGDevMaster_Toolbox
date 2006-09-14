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
 **     class PolygonForeground!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &PolygonForegroundBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 PolygonForegroundBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

inline
OSG::UInt16 PolygonForegroundBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/


//! Get the value of the PolygonForeground::_sfMaterial field.
inline
MaterialPtrConst PolygonForegroundBase::getMaterial(void) const
{
    return _sfMaterial.getValue();
}

//! Set the value of the PolygonForeground::_sfMaterial field.
inline
void PolygonForegroundBase::setMaterial(MaterialPtrConstArg value)
{
    editSField(MaterialFieldMask);

    setRefd(_sfMaterial.getValue(), value);

}
//! Get the value of the PolygonForeground::_sfNormalizedX field.

inline
bool &PolygonForegroundBase::editNormalizedX(void)
{
    editSField(NormalizedXFieldMask);

    return _sfNormalizedX.getValue();
}

//! Get the value of the PolygonForeground::_sfNormalizedX field.
inline
const bool &PolygonForegroundBase::getNormalizedX(void) const
{
    return _sfNormalizedX.getValue();
}

#ifdef OSG_1_COMPAT
inline
bool &PolygonForegroundBase::getNormalizedX(void)
{
    return this->editNormalizedX();
}
#endif

//! Set the value of the PolygonForeground::_sfNormalizedX field.
inline
void PolygonForegroundBase::setNormalizedX(const bool &value)
{
    editSField(NormalizedXFieldMask);

    _sfNormalizedX.setValue(value);
}
//! Get the value of the PolygonForeground::_sfNormalizedY field.

inline
bool &PolygonForegroundBase::editNormalizedY(void)
{
    editSField(NormalizedYFieldMask);

    return _sfNormalizedY.getValue();
}

//! Get the value of the PolygonForeground::_sfNormalizedY field.
inline
const bool &PolygonForegroundBase::getNormalizedY(void) const
{
    return _sfNormalizedY.getValue();
}

#ifdef OSG_1_COMPAT
inline
bool &PolygonForegroundBase::getNormalizedY(void)
{
    return this->editNormalizedY();
}
#endif

//! Set the value of the PolygonForeground::_sfNormalizedY field.
inline
void PolygonForegroundBase::setNormalizedY(const bool &value)
{
    editSField(NormalizedYFieldMask);

    _sfNormalizedY.setValue(value);
}

//! Get the value of the \a index element the PolygonForeground::_mfPositions field.
inline
const Pnt2f &PolygonForegroundBase::getPositions(const UInt32 index) const
{
    return _mfPositions[index];
}

inline
Pnt2f &PolygonForegroundBase::editPositions(const UInt32 index)
{
    editMField(PositionsFieldMask, _mfPositions);

    return _mfPositions[index];
}

//! Get the PolygonForeground::_mfPositions field.
inline
MFPnt2f &PolygonForegroundBase::editPositions(void)
{
    editMField(PositionsFieldMask, _mfPositions);

    return _mfPositions;
}

#ifdef OSG_1_COMPAT
inline
Pnt2f &PolygonForegroundBase::getPositions(const UInt32 index)
{
    return this->editPositions(index);
}

inline
MFPnt2f &PolygonForegroundBase::getPositions(void)
{
    return this->editPositions();
}

#endif


//! Get the PolygonForeground::_mfPositions field.
inline
const MFPnt2f &PolygonForegroundBase::getPositions(void) const
{
    return _mfPositions;
}

//! Get the value of the \a index element the PolygonForeground::_mfTexCoords field.
inline
const Vec3f &PolygonForegroundBase::getTexCoords(const UInt32 index) const
{
    return _mfTexCoords[index];
}

inline
Vec3f &PolygonForegroundBase::editTexCoords(const UInt32 index)
{
    editMField(TexCoordsFieldMask, _mfTexCoords);

    return _mfTexCoords[index];
}

//! Get the PolygonForeground::_mfTexCoords field.
inline
MFVec3f &PolygonForegroundBase::editTexCoords(void)
{
    editMField(TexCoordsFieldMask, _mfTexCoords);

    return _mfTexCoords;
}

#ifdef OSG_1_COMPAT
inline
Vec3f &PolygonForegroundBase::getTexCoords(const UInt32 index)
{
    return this->editTexCoords(index);
}

inline
MFVec3f &PolygonForegroundBase::getTexCoords(void)
{
    return this->editTexCoords();
}

#endif


//! Get the PolygonForeground::_mfTexCoords field.
inline
const MFVec3f &PolygonForegroundBase::getTexCoords(void) const
{
    return _mfTexCoords;
}

//! create a new instance of the class
inline
PolygonForegroundPtr PolygonForegroundBase::create(void) 
{
    PolygonForegroundPtr fc; 

    if(getClassType().getPrototype() != NullFC) 
    {
        fc = OSG::cast_dynamic<PolygonForeground::ObjPtr>(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

#ifdef OSG_MT_FIELDCONTAINERPTR
inline
void PolygonForegroundBase::execSync(      PolygonForegroundBase *pOther,
                                       ConstFieldMaskArg  whichField,
                                       ConstFieldMaskArg  syncMode  ,
                                 const UInt32             uiSyncInfo,
                                       UInt32             uiCopyOffset)
{
    Inherited::execSync(pOther, whichField, syncMode, uiSyncInfo, uiCopyOffset);

    if(FieldBits::NoField != (MaterialFieldMask & whichField))
        _sfMaterial.syncWith(pOther->_sfMaterial);

    if(FieldBits::NoField != (PositionsFieldMask & whichField))
        _mfPositions.syncWith(pOther->_mfPositions, 
                                syncMode,
                                uiSyncInfo,
                                uiCopyOffset);

    if(FieldBits::NoField != (TexCoordsFieldMask & whichField))
        _mfTexCoords.syncWith(pOther->_mfTexCoords, 
                                syncMode,
                                uiSyncInfo,
                                uiCopyOffset);

    if(FieldBits::NoField != (NormalizedXFieldMask & whichField))
        _sfNormalizedX.syncWith(pOther->_sfNormalizedX);

    if(FieldBits::NoField != (NormalizedYFieldMask & whichField))
        _sfNormalizedY.syncWith(pOther->_sfNormalizedY);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
inline
void PolygonForegroundBase::execSync (      PolygonForegroundBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (MaterialFieldMask & whichField))
        _sfMaterial.syncWith(pFrom->_sfMaterial);

    if(FieldBits::NoField != (PositionsFieldMask & whichField))
        _mfPositions.syncWith(pFrom->_mfPositions, 
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (TexCoordsFieldMask & whichField))
        _mfTexCoords.syncWith(pFrom->_mfTexCoords, 
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (NormalizedXFieldMask & whichField))
        _sfNormalizedX.syncWith(pFrom->_sfNormalizedX);

    if(FieldBits::NoField != (NormalizedYFieldMask & whichField))
        _sfNormalizedY.syncWith(pFrom->_sfNormalizedY);
}
#endif

#if 0
inline
void PolygonForegroundBase::execBeginEdit(ConstFieldMaskArg whichField,
                                      UInt32            uiAspect,
                                      UInt32            uiContainerSize)
{
    Inherited::execBeginEdit(whichField, uiAspect, uiContainerSize);

    if(FieldBits::NoField != (PositionsFieldMask & whichField))
    {
        _mfPositions.beginEdit(uiAspect, uiContainerSize);
    }

    if(FieldBits::NoField != (TexCoordsFieldMask & whichField))
    {
        _mfTexCoords.beginEdit(uiAspect, uiContainerSize);
    }
}
#endif


inline
Char8 *PolygonForegroundBase::getClassname(void)
{
    return "PolygonForeground";
}

typedef PointerBuilder<PolygonForeground>::ObjPtr          PolygonForegroundPtr;
typedef PointerBuilder<PolygonForeground>::ObjPtrConst     PolygonForegroundPtrConst;
typedef PointerBuilder<PolygonForeground>::ObjConstPtr     PolygonForegroundConstPtr;

typedef PointerBuilder<PolygonForeground>::ObjPtrArg       PolygonForegroundPtrArg;
typedef PointerBuilder<PolygonForeground>::ObjConstPtrArg  PolygonForegroundConstPtrArg;
typedef PointerBuilder<PolygonForeground>::ObjPtrConstArg  PolygonForegroundPtrConstArg;

OSG_END_NAMESPACE

#define OSGPOLYGONFOREGROUNDBASE_INLINE_CVSID "@(#)$Id$"

