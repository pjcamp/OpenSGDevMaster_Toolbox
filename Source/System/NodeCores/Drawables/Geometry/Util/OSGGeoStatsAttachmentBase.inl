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
 **     class GeoStatsAttachment!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &GeoStatsAttachmentBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 GeoStatsAttachmentBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

inline
OSG::UInt16 GeoStatsAttachmentBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the GeoStatsAttachment::_sfVertices field.

inline
UInt32 &GeoStatsAttachmentBase::editVertices(void)
{
    editSField(VerticesFieldMask);

    return _sfVertices.getValue();
}

//! Get the value of the GeoStatsAttachment::_sfVertices field.
inline
const UInt32 &GeoStatsAttachmentBase::getVertices(void) const
{
    return _sfVertices.getValue();
}

#ifdef OSG_1_COMPAT
inline
UInt32 &GeoStatsAttachmentBase::getVertices(void)
{
    return this->editVertices();
}
#endif

//! Set the value of the GeoStatsAttachment::_sfVertices field.
inline
void GeoStatsAttachmentBase::setVertices(const UInt32 &value)
{
    editSField(VerticesFieldMask);

    _sfVertices.setValue(value);
}
//! Get the value of the GeoStatsAttachment::_sfPoints field.

inline
UInt32 &GeoStatsAttachmentBase::editPoints(void)
{
    editSField(PointsFieldMask);

    return _sfPoints.getValue();
}

//! Get the value of the GeoStatsAttachment::_sfPoints field.
inline
const UInt32 &GeoStatsAttachmentBase::getPoints(void) const
{
    return _sfPoints.getValue();
}

#ifdef OSG_1_COMPAT
inline
UInt32 &GeoStatsAttachmentBase::getPoints(void)
{
    return this->editPoints();
}
#endif

//! Set the value of the GeoStatsAttachment::_sfPoints field.
inline
void GeoStatsAttachmentBase::setPoints(const UInt32 &value)
{
    editSField(PointsFieldMask);

    _sfPoints.setValue(value);
}
//! Get the value of the GeoStatsAttachment::_sfLines field.

inline
UInt32 &GeoStatsAttachmentBase::editLines(void)
{
    editSField(LinesFieldMask);

    return _sfLines.getValue();
}

//! Get the value of the GeoStatsAttachment::_sfLines field.
inline
const UInt32 &GeoStatsAttachmentBase::getLines(void) const
{
    return _sfLines.getValue();
}

#ifdef OSG_1_COMPAT
inline
UInt32 &GeoStatsAttachmentBase::getLines(void)
{
    return this->editLines();
}
#endif

//! Set the value of the GeoStatsAttachment::_sfLines field.
inline
void GeoStatsAttachmentBase::setLines(const UInt32 &value)
{
    editSField(LinesFieldMask);

    _sfLines.setValue(value);
}
//! Get the value of the GeoStatsAttachment::_sfTriangles field.

inline
UInt32 &GeoStatsAttachmentBase::editTriangles(void)
{
    editSField(TrianglesFieldMask);

    return _sfTriangles.getValue();
}

//! Get the value of the GeoStatsAttachment::_sfTriangles field.
inline
const UInt32 &GeoStatsAttachmentBase::getTriangles(void) const
{
    return _sfTriangles.getValue();
}

#ifdef OSG_1_COMPAT
inline
UInt32 &GeoStatsAttachmentBase::getTriangles(void)
{
    return this->editTriangles();
}
#endif

//! Set the value of the GeoStatsAttachment::_sfTriangles field.
inline
void GeoStatsAttachmentBase::setTriangles(const UInt32 &value)
{
    editSField(TrianglesFieldMask);

    _sfTriangles.setValue(value);
}
//! Get the value of the GeoStatsAttachment::_sfProcessedAttributeBytes field.

inline
UInt32 &GeoStatsAttachmentBase::editProcessedAttributeBytes(void)
{
    editSField(ProcessedAttributeBytesFieldMask);

    return _sfProcessedAttributeBytes.getValue();
}

//! Get the value of the GeoStatsAttachment::_sfProcessedAttributeBytes field.
inline
const UInt32 &GeoStatsAttachmentBase::getProcessedAttributeBytes(void) const
{
    return _sfProcessedAttributeBytes.getValue();
}

#ifdef OSG_1_COMPAT
inline
UInt32 &GeoStatsAttachmentBase::getProcessedAttributeBytes(void)
{
    return this->editProcessedAttributeBytes();
}
#endif

//! Set the value of the GeoStatsAttachment::_sfProcessedAttributeBytes field.
inline
void GeoStatsAttachmentBase::setProcessedAttributeBytes(const UInt32 &value)
{
    editSField(ProcessedAttributeBytesFieldMask);

    _sfProcessedAttributeBytes.setValue(value);
}
//! Get the value of the GeoStatsAttachment::_sfStoredAttributeBytes field.

inline
UInt32 &GeoStatsAttachmentBase::editStoredAttributeBytes(void)
{
    editSField(StoredAttributeBytesFieldMask);

    return _sfStoredAttributeBytes.getValue();
}

//! Get the value of the GeoStatsAttachment::_sfStoredAttributeBytes field.
inline
const UInt32 &GeoStatsAttachmentBase::getStoredAttributeBytes(void) const
{
    return _sfStoredAttributeBytes.getValue();
}

#ifdef OSG_1_COMPAT
inline
UInt32 &GeoStatsAttachmentBase::getStoredAttributeBytes(void)
{
    return this->editStoredAttributeBytes();
}
#endif

//! Set the value of the GeoStatsAttachment::_sfStoredAttributeBytes field.
inline
void GeoStatsAttachmentBase::setStoredAttributeBytes(const UInt32 &value)
{
    editSField(StoredAttributeBytesFieldMask);

    _sfStoredAttributeBytes.setValue(value);
}
//! Get the value of the GeoStatsAttachment::_sfValid field.

inline
bool &GeoStatsAttachmentBase::editValid(void)
{
    editSField(ValidFieldMask);

    return _sfValid.getValue();
}

//! Get the value of the GeoStatsAttachment::_sfValid field.
inline
const bool &GeoStatsAttachmentBase::getValid(void) const
{
    return _sfValid.getValue();
}

#ifdef OSG_1_COMPAT
inline
bool &GeoStatsAttachmentBase::getValid(void)
{
    return this->editValid();
}
#endif

//! Set the value of the GeoStatsAttachment::_sfValid field.
inline
void GeoStatsAttachmentBase::setValid(const bool &value)
{
    editSField(ValidFieldMask);

    _sfValid.setValue(value);
}

//! create a new instance of the class
inline
GeoStatsAttachmentPtr GeoStatsAttachmentBase::create(void) 
{
    GeoStatsAttachmentPtr fc; 

    if(getClassType().getPrototype() != NullFC) 
    {
        fc = OSG::cast_dynamic<GeoStatsAttachment::ObjPtr>(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

#ifdef OSG_MT_FIELDCONTAINERPTR
inline
void GeoStatsAttachmentBase::execSync(      GeoStatsAttachmentBase *pOther,
                                       ConstFieldMaskArg  whichField,
                                       ConstFieldMaskArg  syncMode  ,
                                 const UInt32             uiSyncInfo,
                                       UInt32             uiCopyOffset)
{
    Inherited::execSync(pOther, whichField, syncMode, uiSyncInfo, uiCopyOffset);

    if(FieldBits::NoField != (VerticesFieldMask & whichField))
        _sfVertices.syncWith(pOther->_sfVertices);

    if(FieldBits::NoField != (PointsFieldMask & whichField))
        _sfPoints.syncWith(pOther->_sfPoints);

    if(FieldBits::NoField != (LinesFieldMask & whichField))
        _sfLines.syncWith(pOther->_sfLines);

    if(FieldBits::NoField != (TrianglesFieldMask & whichField))
        _sfTriangles.syncWith(pOther->_sfTriangles);

    if(FieldBits::NoField != (ProcessedAttributeBytesFieldMask & whichField))
        _sfProcessedAttributeBytes.syncWith(pOther->_sfProcessedAttributeBytes);

    if(FieldBits::NoField != (StoredAttributeBytesFieldMask & whichField))
        _sfStoredAttributeBytes.syncWith(pOther->_sfStoredAttributeBytes);

    if(FieldBits::NoField != (ValidFieldMask & whichField))
        _sfValid.syncWith(pOther->_sfValid);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
inline
void GeoStatsAttachmentBase::execSync (      GeoStatsAttachmentBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (VerticesFieldMask & whichField))
        _sfVertices.syncWith(pFrom->_sfVertices);

    if(FieldBits::NoField != (PointsFieldMask & whichField))
        _sfPoints.syncWith(pFrom->_sfPoints);

    if(FieldBits::NoField != (LinesFieldMask & whichField))
        _sfLines.syncWith(pFrom->_sfLines);

    if(FieldBits::NoField != (TrianglesFieldMask & whichField))
        _sfTriangles.syncWith(pFrom->_sfTriangles);

    if(FieldBits::NoField != (ProcessedAttributeBytesFieldMask & whichField))
        _sfProcessedAttributeBytes.syncWith(pFrom->_sfProcessedAttributeBytes);

    if(FieldBits::NoField != (StoredAttributeBytesFieldMask & whichField))
        _sfStoredAttributeBytes.syncWith(pFrom->_sfStoredAttributeBytes);

    if(FieldBits::NoField != (ValidFieldMask & whichField))
        _sfValid.syncWith(pFrom->_sfValid);
}
#endif

#if 0
inline
void GeoStatsAttachmentBase::execBeginEdit(ConstFieldMaskArg whichField,
                                      UInt32            uiAspect,
                                      UInt32            uiContainerSize)
{
    Inherited::execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif


inline
Char8 *GeoStatsAttachmentBase::getClassname(void)
{
    return "GeoStatsAttachment";
}

typedef PointerBuilder<GeoStatsAttachment>::ObjPtr          GeoStatsAttachmentPtr;
typedef PointerBuilder<GeoStatsAttachment>::ObjPtrConst     GeoStatsAttachmentPtrConst;
typedef PointerBuilder<GeoStatsAttachment>::ObjConstPtr     GeoStatsAttachmentConstPtr;

typedef PointerBuilder<GeoStatsAttachment>::ObjPtrArg       GeoStatsAttachmentPtrArg;
typedef PointerBuilder<GeoStatsAttachment>::ObjConstPtrArg  GeoStatsAttachmentConstPtrArg;
typedef PointerBuilder<GeoStatsAttachment>::ObjPtrConstArg  GeoStatsAttachmentPtrConstArg;

OSG_END_NAMESPACE

#define OSGGEOSTATSATTACHMENTBASE_INLINE_CVSID "@(#)$Id$"
