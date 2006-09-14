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
 **     class SkyBackground!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &SkyBackgroundBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 SkyBackgroundBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

inline
OSG::UInt16 SkyBackgroundBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the SkyBackground::_sfSphereRes field.

inline
UInt32 &SkyBackgroundBase::editSphereRes(void)
{
    editSField(SphereResFieldMask);

    return _sfSphereRes.getValue();
}

//! Get the value of the SkyBackground::_sfSphereRes field.
inline
const UInt32 &SkyBackgroundBase::getSphereRes(void) const
{
    return _sfSphereRes.getValue();
}

#ifdef OSG_1_COMPAT
inline
UInt32 &SkyBackgroundBase::getSphereRes(void)
{
    return this->editSphereRes();
}
#endif

//! Set the value of the SkyBackground::_sfSphereRes field.
inline
void SkyBackgroundBase::setSphereRes(const UInt32 &value)
{
    editSField(SphereResFieldMask);

    _sfSphereRes.setValue(value);
}

//! Get the value of the SkyBackground::_sfBackTexture field.
inline
TextureChunkPtrConst SkyBackgroundBase::getBackTexture(void) const
{
    return _sfBackTexture.getValue();
}

//! Set the value of the SkyBackground::_sfBackTexture field.
inline
void SkyBackgroundBase::setBackTexture(TextureChunkPtrConstArg value)
{
    editSField(BackTextureFieldMask);

    setRefd(_sfBackTexture.getValue(), value);

}

//! Get the value of the SkyBackground::_sfBottomTexture field.
inline
TextureChunkPtrConst SkyBackgroundBase::getBottomTexture(void) const
{
    return _sfBottomTexture.getValue();
}

//! Set the value of the SkyBackground::_sfBottomTexture field.
inline
void SkyBackgroundBase::setBottomTexture(TextureChunkPtrConstArg value)
{
    editSField(BottomTextureFieldMask);

    setRefd(_sfBottomTexture.getValue(), value);

}

//! Get the value of the SkyBackground::_sfFrontTexture field.
inline
TextureChunkPtrConst SkyBackgroundBase::getFrontTexture(void) const
{
    return _sfFrontTexture.getValue();
}

//! Set the value of the SkyBackground::_sfFrontTexture field.
inline
void SkyBackgroundBase::setFrontTexture(TextureChunkPtrConstArg value)
{
    editSField(FrontTextureFieldMask);

    setRefd(_sfFrontTexture.getValue(), value);

}

//! Get the value of the SkyBackground::_sfLeftTexture field.
inline
TextureChunkPtrConst SkyBackgroundBase::getLeftTexture(void) const
{
    return _sfLeftTexture.getValue();
}

//! Set the value of the SkyBackground::_sfLeftTexture field.
inline
void SkyBackgroundBase::setLeftTexture(TextureChunkPtrConstArg value)
{
    editSField(LeftTextureFieldMask);

    setRefd(_sfLeftTexture.getValue(), value);

}

//! Get the value of the SkyBackground::_sfRightTexture field.
inline
TextureChunkPtrConst SkyBackgroundBase::getRightTexture(void) const
{
    return _sfRightTexture.getValue();
}

//! Set the value of the SkyBackground::_sfRightTexture field.
inline
void SkyBackgroundBase::setRightTexture(TextureChunkPtrConstArg value)
{
    editSField(RightTextureFieldMask);

    setRefd(_sfRightTexture.getValue(), value);

}

//! Get the value of the SkyBackground::_sfTopTexture field.
inline
TextureChunkPtrConst SkyBackgroundBase::getTopTexture(void) const
{
    return _sfTopTexture.getValue();
}

//! Set the value of the SkyBackground::_sfTopTexture field.
inline
void SkyBackgroundBase::setTopTexture(TextureChunkPtrConstArg value)
{
    editSField(TopTextureFieldMask);

    setRefd(_sfTopTexture.getValue(), value);

}
//! Get the value of the SkyBackground::_sfBoxInside field.

inline
bool &SkyBackgroundBase::editBoxInside(void)
{
    editSField(BoxInsideFieldMask);

    return _sfBoxInside.getValue();
}

//! Get the value of the SkyBackground::_sfBoxInside field.
inline
const bool &SkyBackgroundBase::getBoxInside(void) const
{
    return _sfBoxInside.getValue();
}

#ifdef OSG_1_COMPAT
inline
bool &SkyBackgroundBase::getBoxInside(void)
{
    return this->editBoxInside();
}
#endif

//! Set the value of the SkyBackground::_sfBoxInside field.
inline
void SkyBackgroundBase::setBoxInside(const bool &value)
{
    editSField(BoxInsideFieldMask);

    _sfBoxInside.setValue(value);
}

//! Get the value of the SkyBackground::_sfBeacon field.
inline
NodePtrConst SkyBackgroundBase::getBeacon(void) const
{
    return _sfBeacon.getValue();
}

//! Set the value of the SkyBackground::_sfBeacon field.
inline
void SkyBackgroundBase::setBeacon(NodePtrConstArg value)
{
    editSField(BeaconFieldMask);

    setRefd(_sfBeacon.getValue(), value);

}

//! Get the value of the \a index element the SkyBackground::_mfSkyColor field.
inline
const Color4f &SkyBackgroundBase::getSkyColor(const UInt32 index) const
{
    return _mfSkyColor[index];
}

inline
Color4f &SkyBackgroundBase::editSkyColor(const UInt32 index)
{
    editMField(SkyColorFieldMask, _mfSkyColor);

    return _mfSkyColor[index];
}

//! Get the SkyBackground::_mfSkyColor field.
inline
MFColor4f &SkyBackgroundBase::editSkyColor(void)
{
    editMField(SkyColorFieldMask, _mfSkyColor);

    return _mfSkyColor;
}

#ifdef OSG_1_COMPAT
inline
Color4f &SkyBackgroundBase::getSkyColor(const UInt32 index)
{
    return this->editSkyColor(index);
}

inline
MFColor4f &SkyBackgroundBase::getSkyColor(void)
{
    return this->editSkyColor();
}

#endif


//! Get the SkyBackground::_mfSkyColor field.
inline
const MFColor4f &SkyBackgroundBase::getSkyColor(void) const
{
    return _mfSkyColor;
}

//! Get the value of the \a index element the SkyBackground::_mfSkyAngle field.
inline
const Real32 &SkyBackgroundBase::getSkyAngle(const UInt32 index) const
{
    return _mfSkyAngle[index];
}

inline
Real32 &SkyBackgroundBase::editSkyAngle(const UInt32 index)
{
    editMField(SkyAngleFieldMask, _mfSkyAngle);

    return _mfSkyAngle[index];
}

//! Get the SkyBackground::_mfSkyAngle field.
inline
MFReal32 &SkyBackgroundBase::editSkyAngle(void)
{
    editMField(SkyAngleFieldMask, _mfSkyAngle);

    return _mfSkyAngle;
}

#ifdef OSG_1_COMPAT
inline
Real32 &SkyBackgroundBase::getSkyAngle(const UInt32 index)
{
    return this->editSkyAngle(index);
}

inline
MFReal32 &SkyBackgroundBase::getSkyAngle(void)
{
    return this->editSkyAngle();
}

#endif


//! Get the SkyBackground::_mfSkyAngle field.
inline
const MFReal32 &SkyBackgroundBase::getSkyAngle(void) const
{
    return _mfSkyAngle;
}

//! Get the value of the \a index element the SkyBackground::_mfGroundColor field.
inline
const Color4f &SkyBackgroundBase::getGroundColor(const UInt32 index) const
{
    return _mfGroundColor[index];
}

inline
Color4f &SkyBackgroundBase::editGroundColor(const UInt32 index)
{
    editMField(GroundColorFieldMask, _mfGroundColor);

    return _mfGroundColor[index];
}

//! Get the SkyBackground::_mfGroundColor field.
inline
MFColor4f &SkyBackgroundBase::editGroundColor(void)
{
    editMField(GroundColorFieldMask, _mfGroundColor);

    return _mfGroundColor;
}

#ifdef OSG_1_COMPAT
inline
Color4f &SkyBackgroundBase::getGroundColor(const UInt32 index)
{
    return this->editGroundColor(index);
}

inline
MFColor4f &SkyBackgroundBase::getGroundColor(void)
{
    return this->editGroundColor();
}

#endif


//! Get the SkyBackground::_mfGroundColor field.
inline
const MFColor4f &SkyBackgroundBase::getGroundColor(void) const
{
    return _mfGroundColor;
}

//! Get the value of the \a index element the SkyBackground::_mfGroundAngle field.
inline
const Real32 &SkyBackgroundBase::getGroundAngle(const UInt32 index) const
{
    return _mfGroundAngle[index];
}

inline
Real32 &SkyBackgroundBase::editGroundAngle(const UInt32 index)
{
    editMField(GroundAngleFieldMask, _mfGroundAngle);

    return _mfGroundAngle[index];
}

//! Get the SkyBackground::_mfGroundAngle field.
inline
MFReal32 &SkyBackgroundBase::editGroundAngle(void)
{
    editMField(GroundAngleFieldMask, _mfGroundAngle);

    return _mfGroundAngle;
}

#ifdef OSG_1_COMPAT
inline
Real32 &SkyBackgroundBase::getGroundAngle(const UInt32 index)
{
    return this->editGroundAngle(index);
}

inline
MFReal32 &SkyBackgroundBase::getGroundAngle(void)
{
    return this->editGroundAngle();
}

#endif


//! Get the SkyBackground::_mfGroundAngle field.
inline
const MFReal32 &SkyBackgroundBase::getGroundAngle(void) const
{
    return _mfGroundAngle;
}

//! Get the value of the \a index element the SkyBackground::_mfTopTexCoord field.
inline
const Vec3f &SkyBackgroundBase::getTopTexCoord(const UInt32 index) const
{
    return _mfTopTexCoord[index];
}

inline
Vec3f &SkyBackgroundBase::editTopTexCoord(const UInt32 index)
{
    editMField(TopTexCoordFieldMask, _mfTopTexCoord);

    return _mfTopTexCoord[index];
}

//! Get the SkyBackground::_mfTopTexCoord field.
inline
MFVec3f &SkyBackgroundBase::editTopTexCoord(void)
{
    editMField(TopTexCoordFieldMask, _mfTopTexCoord);

    return _mfTopTexCoord;
}

#ifdef OSG_1_COMPAT
inline
Vec3f &SkyBackgroundBase::getTopTexCoord(const UInt32 index)
{
    return this->editTopTexCoord(index);
}

inline
MFVec3f &SkyBackgroundBase::getTopTexCoord(void)
{
    return this->editTopTexCoord();
}

#endif


//! Get the SkyBackground::_mfTopTexCoord field.
inline
const MFVec3f &SkyBackgroundBase::getTopTexCoord(void) const
{
    return _mfTopTexCoord;
}

//! Get the value of the \a index element the SkyBackground::_mfBottomTexCoord field.
inline
const Vec3f &SkyBackgroundBase::getBottomTexCoord(const UInt32 index) const
{
    return _mfBottomTexCoord[index];
}

inline
Vec3f &SkyBackgroundBase::editBottomTexCoord(const UInt32 index)
{
    editMField(BottomTexCoordFieldMask, _mfBottomTexCoord);

    return _mfBottomTexCoord[index];
}

//! Get the SkyBackground::_mfBottomTexCoord field.
inline
MFVec3f &SkyBackgroundBase::editBottomTexCoord(void)
{
    editMField(BottomTexCoordFieldMask, _mfBottomTexCoord);

    return _mfBottomTexCoord;
}

#ifdef OSG_1_COMPAT
inline
Vec3f &SkyBackgroundBase::getBottomTexCoord(const UInt32 index)
{
    return this->editBottomTexCoord(index);
}

inline
MFVec3f &SkyBackgroundBase::getBottomTexCoord(void)
{
    return this->editBottomTexCoord();
}

#endif


//! Get the SkyBackground::_mfBottomTexCoord field.
inline
const MFVec3f &SkyBackgroundBase::getBottomTexCoord(void) const
{
    return _mfBottomTexCoord;
}

//! Get the value of the \a index element the SkyBackground::_mfRightTexCoord field.
inline
const Vec3f &SkyBackgroundBase::getRightTexCoord(const UInt32 index) const
{
    return _mfRightTexCoord[index];
}

inline
Vec3f &SkyBackgroundBase::editRightTexCoord(const UInt32 index)
{
    editMField(RightTexCoordFieldMask, _mfRightTexCoord);

    return _mfRightTexCoord[index];
}

//! Get the SkyBackground::_mfRightTexCoord field.
inline
MFVec3f &SkyBackgroundBase::editRightTexCoord(void)
{
    editMField(RightTexCoordFieldMask, _mfRightTexCoord);

    return _mfRightTexCoord;
}

#ifdef OSG_1_COMPAT
inline
Vec3f &SkyBackgroundBase::getRightTexCoord(const UInt32 index)
{
    return this->editRightTexCoord(index);
}

inline
MFVec3f &SkyBackgroundBase::getRightTexCoord(void)
{
    return this->editRightTexCoord();
}

#endif


//! Get the SkyBackground::_mfRightTexCoord field.
inline
const MFVec3f &SkyBackgroundBase::getRightTexCoord(void) const
{
    return _mfRightTexCoord;
}

//! Get the value of the \a index element the SkyBackground::_mfLeftTexCoord field.
inline
const Vec3f &SkyBackgroundBase::getLeftTexCoord(const UInt32 index) const
{
    return _mfLeftTexCoord[index];
}

inline
Vec3f &SkyBackgroundBase::editLeftTexCoord(const UInt32 index)
{
    editMField(LeftTexCoordFieldMask, _mfLeftTexCoord);

    return _mfLeftTexCoord[index];
}

//! Get the SkyBackground::_mfLeftTexCoord field.
inline
MFVec3f &SkyBackgroundBase::editLeftTexCoord(void)
{
    editMField(LeftTexCoordFieldMask, _mfLeftTexCoord);

    return _mfLeftTexCoord;
}

#ifdef OSG_1_COMPAT
inline
Vec3f &SkyBackgroundBase::getLeftTexCoord(const UInt32 index)
{
    return this->editLeftTexCoord(index);
}

inline
MFVec3f &SkyBackgroundBase::getLeftTexCoord(void)
{
    return this->editLeftTexCoord();
}

#endif


//! Get the SkyBackground::_mfLeftTexCoord field.
inline
const MFVec3f &SkyBackgroundBase::getLeftTexCoord(void) const
{
    return _mfLeftTexCoord;
}

//! Get the value of the \a index element the SkyBackground::_mfFrontTexCoord field.
inline
const Vec3f &SkyBackgroundBase::getFrontTexCoord(const UInt32 index) const
{
    return _mfFrontTexCoord[index];
}

inline
Vec3f &SkyBackgroundBase::editFrontTexCoord(const UInt32 index)
{
    editMField(FrontTexCoordFieldMask, _mfFrontTexCoord);

    return _mfFrontTexCoord[index];
}

//! Get the SkyBackground::_mfFrontTexCoord field.
inline
MFVec3f &SkyBackgroundBase::editFrontTexCoord(void)
{
    editMField(FrontTexCoordFieldMask, _mfFrontTexCoord);

    return _mfFrontTexCoord;
}

#ifdef OSG_1_COMPAT
inline
Vec3f &SkyBackgroundBase::getFrontTexCoord(const UInt32 index)
{
    return this->editFrontTexCoord(index);
}

inline
MFVec3f &SkyBackgroundBase::getFrontTexCoord(void)
{
    return this->editFrontTexCoord();
}

#endif


//! Get the SkyBackground::_mfFrontTexCoord field.
inline
const MFVec3f &SkyBackgroundBase::getFrontTexCoord(void) const
{
    return _mfFrontTexCoord;
}

//! Get the value of the \a index element the SkyBackground::_mfBackTexCoord field.
inline
const Vec3f &SkyBackgroundBase::getBackTexCoord(const UInt32 index) const
{
    return _mfBackTexCoord[index];
}

inline
Vec3f &SkyBackgroundBase::editBackTexCoord(const UInt32 index)
{
    editMField(BackTexCoordFieldMask, _mfBackTexCoord);

    return _mfBackTexCoord[index];
}

//! Get the SkyBackground::_mfBackTexCoord field.
inline
MFVec3f &SkyBackgroundBase::editBackTexCoord(void)
{
    editMField(BackTexCoordFieldMask, _mfBackTexCoord);

    return _mfBackTexCoord;
}

#ifdef OSG_1_COMPAT
inline
Vec3f &SkyBackgroundBase::getBackTexCoord(const UInt32 index)
{
    return this->editBackTexCoord(index);
}

inline
MFVec3f &SkyBackgroundBase::getBackTexCoord(void)
{
    return this->editBackTexCoord();
}

#endif


//! Get the SkyBackground::_mfBackTexCoord field.
inline
const MFVec3f &SkyBackgroundBase::getBackTexCoord(void) const
{
    return _mfBackTexCoord;
}

//! create a new instance of the class
inline
SkyBackgroundPtr SkyBackgroundBase::create(void) 
{
    SkyBackgroundPtr fc; 

    if(getClassType().getPrototype() != NullFC) 
    {
        fc = OSG::cast_dynamic<SkyBackground::ObjPtr>(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

#ifdef OSG_MT_FIELDCONTAINERPTR
inline
void SkyBackgroundBase::execSync(      SkyBackgroundBase *pOther,
                                       ConstFieldMaskArg  whichField,
                                       ConstFieldMaskArg  syncMode  ,
                                 const UInt32             uiSyncInfo,
                                       UInt32             uiCopyOffset)
{
    Inherited::execSync(pOther, whichField, syncMode, uiSyncInfo, uiCopyOffset);

    if(FieldBits::NoField != (SkyColorFieldMask & whichField))
        _mfSkyColor.syncWith(pOther->_mfSkyColor, 
                                syncMode,
                                uiSyncInfo,
                                uiCopyOffset);

    if(FieldBits::NoField != (SkyAngleFieldMask & whichField))
        _mfSkyAngle.syncWith(pOther->_mfSkyAngle, 
                                syncMode,
                                uiSyncInfo,
                                uiCopyOffset);

    if(FieldBits::NoField != (GroundColorFieldMask & whichField))
        _mfGroundColor.syncWith(pOther->_mfGroundColor, 
                                syncMode,
                                uiSyncInfo,
                                uiCopyOffset);

    if(FieldBits::NoField != (GroundAngleFieldMask & whichField))
        _mfGroundAngle.syncWith(pOther->_mfGroundAngle, 
                                syncMode,
                                uiSyncInfo,
                                uiCopyOffset);

    if(FieldBits::NoField != (SphereResFieldMask & whichField))
        _sfSphereRes.syncWith(pOther->_sfSphereRes);

    if(FieldBits::NoField != (BackTextureFieldMask & whichField))
        _sfBackTexture.syncWith(pOther->_sfBackTexture);

    if(FieldBits::NoField != (BottomTextureFieldMask & whichField))
        _sfBottomTexture.syncWith(pOther->_sfBottomTexture);

    if(FieldBits::NoField != (FrontTextureFieldMask & whichField))
        _sfFrontTexture.syncWith(pOther->_sfFrontTexture);

    if(FieldBits::NoField != (LeftTextureFieldMask & whichField))
        _sfLeftTexture.syncWith(pOther->_sfLeftTexture);

    if(FieldBits::NoField != (RightTextureFieldMask & whichField))
        _sfRightTexture.syncWith(pOther->_sfRightTexture);

    if(FieldBits::NoField != (TopTextureFieldMask & whichField))
        _sfTopTexture.syncWith(pOther->_sfTopTexture);

    if(FieldBits::NoField != (BoxInsideFieldMask & whichField))
        _sfBoxInside.syncWith(pOther->_sfBoxInside);

    if(FieldBits::NoField != (TopTexCoordFieldMask & whichField))
        _mfTopTexCoord.syncWith(pOther->_mfTopTexCoord, 
                                syncMode,
                                uiSyncInfo,
                                uiCopyOffset);

    if(FieldBits::NoField != (BottomTexCoordFieldMask & whichField))
        _mfBottomTexCoord.syncWith(pOther->_mfBottomTexCoord, 
                                syncMode,
                                uiSyncInfo,
                                uiCopyOffset);

    if(FieldBits::NoField != (RightTexCoordFieldMask & whichField))
        _mfRightTexCoord.syncWith(pOther->_mfRightTexCoord, 
                                syncMode,
                                uiSyncInfo,
                                uiCopyOffset);

    if(FieldBits::NoField != (LeftTexCoordFieldMask & whichField))
        _mfLeftTexCoord.syncWith(pOther->_mfLeftTexCoord, 
                                syncMode,
                                uiSyncInfo,
                                uiCopyOffset);

    if(FieldBits::NoField != (FrontTexCoordFieldMask & whichField))
        _mfFrontTexCoord.syncWith(pOther->_mfFrontTexCoord, 
                                syncMode,
                                uiSyncInfo,
                                uiCopyOffset);

    if(FieldBits::NoField != (BackTexCoordFieldMask & whichField))
        _mfBackTexCoord.syncWith(pOther->_mfBackTexCoord, 
                                syncMode,
                                uiSyncInfo,
                                uiCopyOffset);

    if(FieldBits::NoField != (BeaconFieldMask & whichField))
        _sfBeacon.syncWith(pOther->_sfBeacon);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
inline
void SkyBackgroundBase::execSync (      SkyBackgroundBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (SkyColorFieldMask & whichField))
        _mfSkyColor.syncWith(pFrom->_mfSkyColor, 
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (SkyAngleFieldMask & whichField))
        _mfSkyAngle.syncWith(pFrom->_mfSkyAngle, 
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (GroundColorFieldMask & whichField))
        _mfGroundColor.syncWith(pFrom->_mfGroundColor, 
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (GroundAngleFieldMask & whichField))
        _mfGroundAngle.syncWith(pFrom->_mfGroundAngle, 
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (SphereResFieldMask & whichField))
        _sfSphereRes.syncWith(pFrom->_sfSphereRes);

    if(FieldBits::NoField != (BackTextureFieldMask & whichField))
        _sfBackTexture.syncWith(pFrom->_sfBackTexture);

    if(FieldBits::NoField != (BottomTextureFieldMask & whichField))
        _sfBottomTexture.syncWith(pFrom->_sfBottomTexture);

    if(FieldBits::NoField != (FrontTextureFieldMask & whichField))
        _sfFrontTexture.syncWith(pFrom->_sfFrontTexture);

    if(FieldBits::NoField != (LeftTextureFieldMask & whichField))
        _sfLeftTexture.syncWith(pFrom->_sfLeftTexture);

    if(FieldBits::NoField != (RightTextureFieldMask & whichField))
        _sfRightTexture.syncWith(pFrom->_sfRightTexture);

    if(FieldBits::NoField != (TopTextureFieldMask & whichField))
        _sfTopTexture.syncWith(pFrom->_sfTopTexture);

    if(FieldBits::NoField != (BoxInsideFieldMask & whichField))
        _sfBoxInside.syncWith(pFrom->_sfBoxInside);

    if(FieldBits::NoField != (TopTexCoordFieldMask & whichField))
        _mfTopTexCoord.syncWith(pFrom->_mfTopTexCoord, 
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (BottomTexCoordFieldMask & whichField))
        _mfBottomTexCoord.syncWith(pFrom->_mfBottomTexCoord, 
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (RightTexCoordFieldMask & whichField))
        _mfRightTexCoord.syncWith(pFrom->_mfRightTexCoord, 
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (LeftTexCoordFieldMask & whichField))
        _mfLeftTexCoord.syncWith(pFrom->_mfLeftTexCoord, 
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (FrontTexCoordFieldMask & whichField))
        _mfFrontTexCoord.syncWith(pFrom->_mfFrontTexCoord, 
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (BackTexCoordFieldMask & whichField))
        _mfBackTexCoord.syncWith(pFrom->_mfBackTexCoord, 
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (BeaconFieldMask & whichField))
        _sfBeacon.syncWith(pFrom->_sfBeacon);
}
#endif

#if 0
inline
void SkyBackgroundBase::execBeginEdit(ConstFieldMaskArg whichField,
                                      UInt32            uiAspect,
                                      UInt32            uiContainerSize)
{
    Inherited::execBeginEdit(whichField, uiAspect, uiContainerSize);

    if(FieldBits::NoField != (SkyColorFieldMask & whichField))
    {
        _mfSkyColor.beginEdit(uiAspect, uiContainerSize);
    }

    if(FieldBits::NoField != (SkyAngleFieldMask & whichField))
    {
        _mfSkyAngle.beginEdit(uiAspect, uiContainerSize);
    }

    if(FieldBits::NoField != (GroundColorFieldMask & whichField))
    {
        _mfGroundColor.beginEdit(uiAspect, uiContainerSize);
    }

    if(FieldBits::NoField != (GroundAngleFieldMask & whichField))
    {
        _mfGroundAngle.beginEdit(uiAspect, uiContainerSize);
    }

    if(FieldBits::NoField != (TopTexCoordFieldMask & whichField))
    {
        _mfTopTexCoord.beginEdit(uiAspect, uiContainerSize);
    }

    if(FieldBits::NoField != (BottomTexCoordFieldMask & whichField))
    {
        _mfBottomTexCoord.beginEdit(uiAspect, uiContainerSize);
    }

    if(FieldBits::NoField != (RightTexCoordFieldMask & whichField))
    {
        _mfRightTexCoord.beginEdit(uiAspect, uiContainerSize);
    }

    if(FieldBits::NoField != (LeftTexCoordFieldMask & whichField))
    {
        _mfLeftTexCoord.beginEdit(uiAspect, uiContainerSize);
    }

    if(FieldBits::NoField != (FrontTexCoordFieldMask & whichField))
    {
        _mfFrontTexCoord.beginEdit(uiAspect, uiContainerSize);
    }

    if(FieldBits::NoField != (BackTexCoordFieldMask & whichField))
    {
        _mfBackTexCoord.beginEdit(uiAspect, uiContainerSize);
    }
}
#endif


inline
Char8 *SkyBackgroundBase::getClassname(void)
{
    return "SkyBackground";
}

typedef PointerBuilder<SkyBackground>::ObjPtr          SkyBackgroundPtr;
typedef PointerBuilder<SkyBackground>::ObjPtrConst     SkyBackgroundPtrConst;
typedef PointerBuilder<SkyBackground>::ObjConstPtr     SkyBackgroundConstPtr;

typedef PointerBuilder<SkyBackground>::ObjPtrArg       SkyBackgroundPtrArg;
typedef PointerBuilder<SkyBackground>::ObjConstPtrArg  SkyBackgroundConstPtrArg;
typedef PointerBuilder<SkyBackground>::ObjPtrConstArg  SkyBackgroundPtrConstArg;

OSG_END_NAMESPACE

#define OSGSKYBACKGROUNDBASE_INLINE_CVSID "@(#)$Id$"

