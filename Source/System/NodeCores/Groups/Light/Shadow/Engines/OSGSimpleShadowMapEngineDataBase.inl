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
 **     class SimpleShadowMapEngineData!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &SimpleShadowMapEngineDataBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 SimpleShadowMapEngineDataBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 SimpleShadowMapEngineDataBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/


//! Get the value of the SimpleShadowMapEngineData::_sfCamera field.
inline
CameraPtr SimpleShadowMapEngineDataBase::getCamera(void) const
{
    return _sfCamera.getValue();
}

//! Set the value of the SimpleShadowMapEngineData::_sfCamera field.
inline
void SimpleShadowMapEngineDataBase::setCamera(const CameraPtr value)
{
    editSField(CameraFieldMask);

    _sfCamera.setValue(value);
}

//! Get the value of the SimpleShadowMapEngineData::_sfTexChunk field.
inline
TextureObjChunkPtr SimpleShadowMapEngineDataBase::getTexChunk(void) const
{
    return _sfTexChunk.getValue();
}

//! Set the value of the SimpleShadowMapEngineData::_sfTexChunk field.
inline
void SimpleShadowMapEngineDataBase::setTexChunk(const TextureObjChunkPtr value)
{
    editSField(TexChunkFieldMask);

    _sfTexChunk.setValue(value);
}

//! Get the value of the SimpleShadowMapEngineData::_sfTexBuffer field.
inline
TextureBufferPtr SimpleShadowMapEngineDataBase::getTexBuffer(void) const
{
    return _sfTexBuffer.getValue();
}

//! Set the value of the SimpleShadowMapEngineData::_sfTexBuffer field.
inline
void SimpleShadowMapEngineDataBase::setTexBuffer(const TextureBufferPtr value)
{
    editSField(TexBufferFieldMask);

    _sfTexBuffer.setValue(value);
}

//! Get the value of the SimpleShadowMapEngineData::_sfLightChunk field.
inline
LightChunkPtr SimpleShadowMapEngineDataBase::getLightChunk(void) const
{
    return _sfLightChunk.getValue();
}

//! Set the value of the SimpleShadowMapEngineData::_sfLightChunk field.
inline
void SimpleShadowMapEngineDataBase::setLightChunk(const LightChunkPtr value)
{
    editSField(LightChunkFieldMask);

    _sfLightChunk.setValue(value);
}

//! Get the value of the SimpleShadowMapEngineData::_sfBlendChunk field.
inline
BlendChunkPtr SimpleShadowMapEngineDataBase::getBlendChunk(void) const
{
    return _sfBlendChunk.getValue();
}

//! Set the value of the SimpleShadowMapEngineData::_sfBlendChunk field.
inline
void SimpleShadowMapEngineDataBase::setBlendChunk(const BlendChunkPtr value)
{
    editSField(BlendChunkFieldMask);

    _sfBlendChunk.setValue(value);
}

//! Get the value of the SimpleShadowMapEngineData::_sfTexGenChunk field.
inline
TexGenChunkPtr SimpleShadowMapEngineDataBase::getTexGenChunk(void) const
{
    return _sfTexGenChunk.getValue();
}

//! Set the value of the SimpleShadowMapEngineData::_sfTexGenChunk field.
inline
void SimpleShadowMapEngineDataBase::setTexGenChunk(const TexGenChunkPtr value)
{
    editSField(TexGenChunkFieldMask);

    _sfTexGenChunk.setValue(value);
}

//! Get the value of the SimpleShadowMapEngineData::_sfPolyChunk field.
inline
PolygonChunkPtr SimpleShadowMapEngineDataBase::getPolyChunk(void) const
{
    return _sfPolyChunk.getValue();
}

//! Set the value of the SimpleShadowMapEngineData::_sfPolyChunk field.
inline
void SimpleShadowMapEngineDataBase::setPolyChunk(const PolygonChunkPtr value)
{
    editSField(PolyChunkFieldMask);

    _sfPolyChunk.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void SimpleShadowMapEngineDataBase::execSync (      SimpleShadowMapEngineDataBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (CameraFieldMask & whichField))
        _sfCamera.syncWith(pFrom->_sfCamera);

    if(FieldBits::NoField != (TexChunkFieldMask & whichField))
        _sfTexChunk.syncWith(pFrom->_sfTexChunk);

    if(FieldBits::NoField != (TexBufferFieldMask & whichField))
        _sfTexBuffer.syncWith(pFrom->_sfTexBuffer);

    if(FieldBits::NoField != (LightChunkFieldMask & whichField))
        _sfLightChunk.syncWith(pFrom->_sfLightChunk);

    if(FieldBits::NoField != (BlendChunkFieldMask & whichField))
        _sfBlendChunk.syncWith(pFrom->_sfBlendChunk);

    if(FieldBits::NoField != (TexGenChunkFieldMask & whichField))
        _sfTexGenChunk.syncWith(pFrom->_sfTexGenChunk);

    if(FieldBits::NoField != (PolyChunkFieldMask & whichField))
        _sfPolyChunk.syncWith(pFrom->_sfPolyChunk);
}
#endif


inline
Char8 *SimpleShadowMapEngineDataBase::getClassname(void)
{
    return "SimpleShadowMapEngineData";
}
OSG_GEN_CONTAINERPTR(SimpleShadowMapEngineData);

OSG_END_NAMESPACE

