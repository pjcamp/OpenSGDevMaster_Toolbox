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
 **     class TiledQuadTreeTerrain!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &TiledQuadTreeTerrainBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 TiledQuadTreeTerrainBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 TiledQuadTreeTerrainBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the TiledQuadTreeTerrain::_sfSizeX field.

inline
UInt32 &TiledQuadTreeTerrainBase::editSizeX(void)
{
    editSField(SizeXFieldMask);

    return _sfSizeX.getValue();
}

//! Get the value of the TiledQuadTreeTerrain::_sfSizeX field.
inline
const UInt32 TiledQuadTreeTerrainBase::getSizeX(void) const
{
    return _sfSizeX.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
UInt32              &TiledQuadTreeTerrainBase::getSizeX          (void)
{
    return this->editSizeX          ();
}
#endif

//! Set the value of the TiledQuadTreeTerrain::_sfSizeX field.
inline
void TiledQuadTreeTerrainBase::setSizeX(const UInt32 &value)
{
    editSField(SizeXFieldMask);

    _sfSizeX.setValue(value);
}
//! Get the value of the TiledQuadTreeTerrain::_sfSizeY field.

inline
UInt32 &TiledQuadTreeTerrainBase::editSizeY(void)
{
    editSField(SizeYFieldMask);

    return _sfSizeY.getValue();
}

//! Get the value of the TiledQuadTreeTerrain::_sfSizeY field.
inline
const UInt32 TiledQuadTreeTerrainBase::getSizeY(void) const
{
    return _sfSizeY.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
UInt32              &TiledQuadTreeTerrainBase::getSizeY          (void)
{
    return this->editSizeY          ();
}
#endif

//! Set the value of the TiledQuadTreeTerrain::_sfSizeY field.
inline
void TiledQuadTreeTerrainBase::setSizeY(const UInt32 &value)
{
    editSField(SizeYFieldMask);

    _sfSizeY.setValue(value);
}
//! Get the value of the TiledQuadTreeTerrain::_sfHeightScale field.

inline
Real32 &TiledQuadTreeTerrainBase::editHeightScale(void)
{
    editSField(HeightScaleFieldMask);

    return _sfHeightScale.getValue();
}

//! Get the value of the TiledQuadTreeTerrain::_sfHeightScale field.
inline
const Real32 TiledQuadTreeTerrainBase::getHeightScale(void) const
{
    return _sfHeightScale.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Real32              &TiledQuadTreeTerrainBase::getHeightScale    (void)
{
    return this->editHeightScale    ();
}
#endif

//! Set the value of the TiledQuadTreeTerrain::_sfHeightScale field.
inline
void TiledQuadTreeTerrainBase::setHeightScale(const Real32 &value)
{
    editSField(HeightScaleFieldMask);

    _sfHeightScale.setValue(value);
}
//! Get the value of the TiledQuadTreeTerrain::_sfVertexSpacing field.

inline
Real32 &TiledQuadTreeTerrainBase::editVertexSpacing(void)
{
    editSField(VertexSpacingFieldMask);

    return _sfVertexSpacing.getValue();
}

//! Get the value of the TiledQuadTreeTerrain::_sfVertexSpacing field.
inline
const Real32 TiledQuadTreeTerrainBase::getVertexSpacing(void) const
{
    return _sfVertexSpacing.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Real32              &TiledQuadTreeTerrainBase::getVertexSpacing  (void)
{
    return this->editVertexSpacing  ();
}
#endif

//! Set the value of the TiledQuadTreeTerrain::_sfVertexSpacing field.
inline
void TiledQuadTreeTerrainBase::setVertexSpacing(const Real32 &value)
{
    editSField(VertexSpacingFieldMask);

    _sfVertexSpacing.setValue(value);
}
//! Get the value of the TiledQuadTreeTerrain::_sfGeoMorphing field.

inline
bool &TiledQuadTreeTerrainBase::editGeoMorphing(void)
{
    editSField(GeoMorphingFieldMask);

    return _sfGeoMorphing.getValue();
}

//! Get the value of the TiledQuadTreeTerrain::_sfGeoMorphing field.
inline
const bool TiledQuadTreeTerrainBase::getGeoMorphing(void) const
{
    return _sfGeoMorphing.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
bool                &TiledQuadTreeTerrainBase::getGeoMorphing    (void)
{
    return this->editGeoMorphing    ();
}
#endif

//! Set the value of the TiledQuadTreeTerrain::_sfGeoMorphing field.
inline
void TiledQuadTreeTerrainBase::setGeoMorphing(const bool &value)
{
    editSField(GeoMorphingFieldMask);

    _sfGeoMorphing.setValue(value);
}
//! Get the value of the TiledQuadTreeTerrain::_sfDetail field.

inline
Real32 &TiledQuadTreeTerrainBase::editDetail(void)
{
    editSField(DetailFieldMask);

    return _sfDetail.getValue();
}

//! Get the value of the TiledQuadTreeTerrain::_sfDetail field.
inline
const Real32 TiledQuadTreeTerrainBase::getDetail(void) const
{
    return _sfDetail.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Real32              &TiledQuadTreeTerrainBase::getDetail         (void)
{
    return this->editDetail         ();
}
#endif

//! Set the value of the TiledQuadTreeTerrain::_sfDetail field.
inline
void TiledQuadTreeTerrainBase::setDetail(const Real32 &value)
{
    editSField(DetailFieldMask);

    _sfDetail.setValue(value);
}
//! Get the value of the TiledQuadTreeTerrain::_sfCurrentX field.

inline
Int32 &TiledQuadTreeTerrainBase::editCurrentX(void)
{
    editSField(CurrentXFieldMask);

    return _sfCurrentX.getValue();
}

//! Get the value of the TiledQuadTreeTerrain::_sfCurrentX field.
inline
const Int32 TiledQuadTreeTerrainBase::getCurrentX(void) const
{
    return _sfCurrentX.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Int32               &TiledQuadTreeTerrainBase::getCurrentX       (void)
{
    return this->editCurrentX       ();
}
#endif

//! Set the value of the TiledQuadTreeTerrain::_sfCurrentX field.
inline
void TiledQuadTreeTerrainBase::setCurrentX(const Int32 &value)
{
    editSField(CurrentXFieldMask);

    _sfCurrentX.setValue(value);
}
//! Get the value of the TiledQuadTreeTerrain::_sfCurrentY field.

inline
Int32 &TiledQuadTreeTerrainBase::editCurrentY(void)
{
    editSField(CurrentYFieldMask);

    return _sfCurrentY.getValue();
}

//! Get the value of the TiledQuadTreeTerrain::_sfCurrentY field.
inline
const Int32 TiledQuadTreeTerrainBase::getCurrentY(void) const
{
    return _sfCurrentY.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Int32               &TiledQuadTreeTerrainBase::getCurrentY       (void)
{
    return this->editCurrentY       ();
}
#endif

//! Set the value of the TiledQuadTreeTerrain::_sfCurrentY field.
inline
void TiledQuadTreeTerrainBase::setCurrentY(const Int32 &value)
{
    editSField(CurrentYFieldMask);

    _sfCurrentY.setValue(value);
}
//! Get the value of the TiledQuadTreeTerrain::_sfSizeROI field.

inline
Int32 &TiledQuadTreeTerrainBase::editSizeROI(void)
{
    editSField(SizeROIFieldMask);

    return _sfSizeROI.getValue();
}

//! Get the value of the TiledQuadTreeTerrain::_sfSizeROI field.
inline
const Int32 TiledQuadTreeTerrainBase::getSizeROI(void) const
{
    return _sfSizeROI.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Int32               &TiledQuadTreeTerrainBase::getSizeROI        (void)
{
    return this->editSizeROI        ();
}
#endif

//! Set the value of the TiledQuadTreeTerrain::_sfSizeROI field.
inline
void TiledQuadTreeTerrainBase::setSizeROI(const Int32 &value)
{
    editSField(SizeROIFieldMask);

    _sfSizeROI.setValue(value);
}
//! Get the value of the TiledQuadTreeTerrain::_sfUpdate field.

inline
bool &TiledQuadTreeTerrainBase::editUpdate(void)
{
    editSField(UpdateFieldMask);

    return _sfUpdate.getValue();
}

//! Get the value of the TiledQuadTreeTerrain::_sfUpdate field.
inline
const bool TiledQuadTreeTerrainBase::getUpdate(void) const
{
    return _sfUpdate.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
bool                &TiledQuadTreeTerrainBase::getUpdate         (void)
{
    return this->editUpdate         ();
}
#endif

//! Set the value of the TiledQuadTreeTerrain::_sfUpdate field.
inline
void TiledQuadTreeTerrainBase::setUpdate(const bool &value)
{
    editSField(UpdateFieldMask);

    _sfUpdate.setValue(value);
}
//! Get the value of the TiledQuadTreeTerrain::_sfUpdateTerrain field.

inline
bool &TiledQuadTreeTerrainBase::editUpdateTerrain(void)
{
    editSField(UpdateTerrainFieldMask);

    return _sfUpdateTerrain.getValue();
}

//! Get the value of the TiledQuadTreeTerrain::_sfUpdateTerrain field.
inline
const bool TiledQuadTreeTerrainBase::getUpdateTerrain(void) const
{
    return _sfUpdateTerrain.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
bool                &TiledQuadTreeTerrainBase::getUpdateTerrain  (void)
{
    return this->editUpdateTerrain  ();
}
#endif

//! Set the value of the TiledQuadTreeTerrain::_sfUpdateTerrain field.
inline
void TiledQuadTreeTerrainBase::setUpdateTerrain(const bool &value)
{
    editSField(UpdateTerrainFieldMask);

    _sfUpdateTerrain.setValue(value);
}
//! Get the value of the TiledQuadTreeTerrain::_sfPerPixelLighting field.

inline
bool &TiledQuadTreeTerrainBase::editPerPixelLighting(void)
{
    editSField(PerPixelLightingFieldMask);

    return _sfPerPixelLighting.getValue();
}

//! Get the value of the TiledQuadTreeTerrain::_sfPerPixelLighting field.
inline
const bool TiledQuadTreeTerrainBase::getPerPixelLighting(void) const
{
    return _sfPerPixelLighting.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
bool                &TiledQuadTreeTerrainBase::getPerPixelLighting(void)
{
    return this->editPerPixelLighting();
}
#endif

//! Set the value of the TiledQuadTreeTerrain::_sfPerPixelLighting field.
inline
void TiledQuadTreeTerrainBase::setPerPixelLighting(const bool &value)
{
    editSField(PerPixelLightingFieldMask);

    _sfPerPixelLighting.setValue(value);
}

//! Get the value of the \a index element the TiledQuadTreeTerrain::_mfHeightTiles field.
inline
ImagePtr TiledQuadTreeTerrainBase::getHeightTiles(const UInt32 index) const
{
    return _mfHeightTiles[index];
}

//! Get the value of the \a index element the TiledQuadTreeTerrain::_mfHeightTextures field.
inline
MaterialPtr TiledQuadTreeTerrainBase::getHeightTextures(const UInt32 index) const
{
    return _mfHeightTextures[index];
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void TiledQuadTreeTerrainBase::execSync (      TiledQuadTreeTerrainBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (HeightTilesFieldMask & whichField))
        _mfHeightTiles.syncWith(pFrom->_mfHeightTiles,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (HeightTexturesFieldMask & whichField))
        _mfHeightTextures.syncWith(pFrom->_mfHeightTextures,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (SizeXFieldMask & whichField))
        _sfSizeX.syncWith(pFrom->_sfSizeX);

    if(FieldBits::NoField != (SizeYFieldMask & whichField))
        _sfSizeY.syncWith(pFrom->_sfSizeY);

    if(FieldBits::NoField != (HeightScaleFieldMask & whichField))
        _sfHeightScale.syncWith(pFrom->_sfHeightScale);

    if(FieldBits::NoField != (VertexSpacingFieldMask & whichField))
        _sfVertexSpacing.syncWith(pFrom->_sfVertexSpacing);

    if(FieldBits::NoField != (GeoMorphingFieldMask & whichField))
        _sfGeoMorphing.syncWith(pFrom->_sfGeoMorphing);

    if(FieldBits::NoField != (DetailFieldMask & whichField))
        _sfDetail.syncWith(pFrom->_sfDetail);

    if(FieldBits::NoField != (CurrentXFieldMask & whichField))
        _sfCurrentX.syncWith(pFrom->_sfCurrentX);

    if(FieldBits::NoField != (CurrentYFieldMask & whichField))
        _sfCurrentY.syncWith(pFrom->_sfCurrentY);

    if(FieldBits::NoField != (SizeROIFieldMask & whichField))
        _sfSizeROI.syncWith(pFrom->_sfSizeROI);

    if(FieldBits::NoField != (UpdateFieldMask & whichField))
        _sfUpdate.syncWith(pFrom->_sfUpdate);

    if(FieldBits::NoField != (UpdateTerrainFieldMask & whichField))
        _sfUpdateTerrain.syncWith(pFrom->_sfUpdateTerrain);

    if(FieldBits::NoField != (PerPixelLightingFieldMask & whichField))
        _sfPerPixelLighting.syncWith(pFrom->_sfPerPixelLighting);
}
#endif


inline
Char8 *TiledQuadTreeTerrainBase::getClassname(void)
{
    return "TiledQuadTreeTerrain";
}
OSG_GEN_CONTAINERPTR(TiledQuadTreeTerrain);

OSG_END_NAMESPACE

