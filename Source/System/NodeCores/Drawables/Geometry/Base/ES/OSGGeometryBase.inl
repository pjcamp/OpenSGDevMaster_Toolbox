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
 **     class Geometry!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &GeometryBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 GeometryBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

inline
OSG::UInt16 GeometryBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/


//! Get the value of the Geometry::_sfTypes field.
inline
GeoIntegralPropertyPtrConst GeometryBase::getTypes(void) const
{
    return _sfTypes.getValue();
}

//! Set the value of the Geometry::_sfTypes field.
inline
void GeometryBase::setTypes(GeoIntegralPropertyPtrConstArg value)
{
    editSField(TypesFieldMask);

    GeometryPtr thisP = Inherited::constructPtr<Geometry>(
        static_cast<Geometry *>(this));

    if(_sfTypes.getValue() != NullFC)
    {
        _sfTypes.getValue()->subParent(thisP);
    }

    setRefd(_sfTypes.getValue(), value);

    if(_sfTypes.getValue() != NullFC)
    {
        _sfTypes.getValue()->addParent(thisP, TypesFieldMask);
    }

}

//! Get the value of the Geometry::_sfLengths field.
inline
GeoIntegralPropertyPtrConst GeometryBase::getLengths(void) const
{
    return _sfLengths.getValue();
}

//! Set the value of the Geometry::_sfLengths field.
inline
void GeometryBase::setLengths(GeoIntegralPropertyPtrConstArg value)
{
    editSField(LengthsFieldMask);

    GeometryPtr thisP = Inherited::constructPtr<Geometry>(
        static_cast<Geometry *>(this));

    if(_sfLengths.getValue() != NullFC)
    {
        _sfLengths.getValue()->subParent(thisP);
    }

    setRefd(_sfLengths.getValue(), value);

    if(_sfLengths.getValue() != NullFC)
    {
        _sfLengths.getValue()->addParent(thisP, LengthsFieldMask);
    }

}
//! Get the value of the Geometry::_sfClassicGLId field.

inline
Int32 &GeometryBase::editClassicGLId(void)
{
    editSField(ClassicGLIdFieldMask);

    return _sfClassicGLId.getValue();
}

//! Get the value of the Geometry::_sfClassicGLId field.
inline
const Int32 &GeometryBase::getClassicGLId(void) const
{
    return _sfClassicGLId.getValue();
}

#ifdef OSG_1_COMPAT
inline
Int32 &GeometryBase::getClassicGLId(void)
{
    return this->editClassicGLId();
}
#endif

//! Set the value of the Geometry::_sfClassicGLId field.
inline
void GeometryBase::setClassicGLId(const Int32 &value)
{
    editSField(ClassicGLIdFieldMask);

    _sfClassicGLId.setValue(value);
}
//! Get the value of the Geometry::_sfAttGLId field.

inline
Int32 &GeometryBase::editAttGLId(void)
{
    editSField(AttGLIdFieldMask);

    return _sfAttGLId.getValue();
}

//! Get the value of the Geometry::_sfAttGLId field.
inline
const Int32 &GeometryBase::getAttGLId(void) const
{
    return _sfAttGLId.getValue();
}

#ifdef OSG_1_COMPAT
inline
Int32 &GeometryBase::getAttGLId(void)
{
    return this->editAttGLId();
}
#endif

//! Set the value of the Geometry::_sfAttGLId field.
inline
void GeometryBase::setAttGLId(const Int32 &value)
{
    editSField(AttGLIdFieldMask);

    _sfAttGLId.setValue(value);
}

//! Get the value of the \a index element the Geometry::_mfProperties field.
inline
GeoVectorPropertyPtrConst GeometryBase::getProperties(const UInt32 index) const
{
    return _mfProperties[index];
}

//! Get the Geometry::_mfProperties field.
inline
const MFGeoVectorPropertyPtr &GeometryBase::getProperties(void) const
{
    return _mfProperties;
}

//! Get the value of the \a index element the Geometry::_mfPropIndices field.
inline
GeoIntegralPropertyPtrConst GeometryBase::getPropIndices(const UInt32 index) const
{
    return _mfPropIndices[index];
}

//! Get the Geometry::_mfPropIndices field.
inline
const MFGeoIntegralPropertyPtr &GeometryBase::getPropIndices(void) const
{
    return _mfPropIndices;
}

//! create a new instance of the class
inline
GeometryPtr GeometryBase::create(void) 
{
    GeometryPtr fc; 

    if(getClassType().getPrototype() != NullFC) 
    {
        fc = OSG::cast_dynamic<Geometry::ObjPtr>(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

#ifdef OSG_MT_FIELDCONTAINERPTR
inline
void GeometryBase::execSync(      GeometryBase *pOther,
                                       ConstFieldMaskArg  whichField,
                                       ConstFieldMaskArg  syncMode  ,
                                 const UInt32             uiSyncInfo,
                                       UInt32             uiCopyOffset)
{
    Inherited::execSync(pOther, whichField, syncMode, uiSyncInfo, uiCopyOffset);

    if(FieldBits::NoField != (TypesFieldMask & whichField))
        _sfTypes.syncWith(pOther->_sfTypes);

    if(FieldBits::NoField != (LengthsFieldMask & whichField))
        _sfLengths.syncWith(pOther->_sfLengths);

    if(FieldBits::NoField != (PropertiesFieldMask & whichField))
        _mfProperties.syncWith(pOther->_mfProperties, 
                                syncMode,
                                uiSyncInfo,
                                uiCopyOffset);

    if(FieldBits::NoField != (PropIndicesFieldMask & whichField))
        _mfPropIndices.syncWith(pOther->_mfPropIndices, 
                                syncMode,
                                uiSyncInfo,
                                uiCopyOffset);

    if(FieldBits::NoField != (ClassicGLIdFieldMask & whichField))
        _sfClassicGLId.syncWith(pOther->_sfClassicGLId);

    if(FieldBits::NoField != (AttGLIdFieldMask & whichField))
        _sfAttGLId.syncWith(pOther->_sfAttGLId);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
inline
void GeometryBase::execSync (      GeometryBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (TypesFieldMask & whichField))
        _sfTypes.syncWith(pFrom->_sfTypes);

    if(FieldBits::NoField != (LengthsFieldMask & whichField))
        _sfLengths.syncWith(pFrom->_sfLengths);

    if(FieldBits::NoField != (PropertiesFieldMask & whichField))
        _mfProperties.syncWith(pFrom->_mfProperties, 
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (PropIndicesFieldMask & whichField))
        _mfPropIndices.syncWith(pFrom->_mfPropIndices, 
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (ClassicGLIdFieldMask & whichField))
        _sfClassicGLId.syncWith(pFrom->_sfClassicGLId);

    if(FieldBits::NoField != (AttGLIdFieldMask & whichField))
        _sfAttGLId.syncWith(pFrom->_sfAttGLId);
}
#endif

#if 0
inline
void GeometryBase::execBeginEdit(ConstFieldMaskArg whichField,
                                      UInt32            uiAspect,
                                      UInt32            uiContainerSize)
{
    Inherited::execBeginEdit(whichField, uiAspect, uiContainerSize);

    if(FieldBits::NoField != (PropertiesFieldMask & whichField))
    {
        _mfProperties.beginEdit(uiAspect, uiContainerSize);
    }

    if(FieldBits::NoField != (PropIndicesFieldMask & whichField))
    {
        _mfPropIndices.beginEdit(uiAspect, uiContainerSize);
    }
}
#endif


inline
Char8 *GeometryBase::getClassname(void)
{
    return "Geometry";
}

typedef PointerBuilder<Geometry>::ObjPtr          GeometryPtr;
typedef PointerBuilder<Geometry>::ObjPtrConst     GeometryPtrConst;
typedef PointerBuilder<Geometry>::ObjConstPtr     GeometryConstPtr;

typedef PointerBuilder<Geometry>::ObjPtrArg       GeometryPtrArg;
typedef PointerBuilder<Geometry>::ObjConstPtrArg  GeometryConstPtrArg;
typedef PointerBuilder<Geometry>::ObjPtrConstArg  GeometryPtrConstArg;

OSG_END_NAMESPACE

#define OSGGEOMETRYBASE_INLINE_CVSID "@(#)$Id$"

