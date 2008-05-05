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
 **     class MaterialChunk!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &MaterialChunkBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 MaterialChunkBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 MaterialChunkBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the MaterialChunk::_sfDiffuse field.

inline
Color4r &MaterialChunkBase::editDiffuse(void)
{
    editSField(DiffuseFieldMask);

    return _sfDiffuse.getValue();
}

//! Get the value of the MaterialChunk::_sfDiffuse field.
inline
const Color4r MaterialChunkBase::getDiffuse(void) const
{
    return _sfDiffuse.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Color4r             &MaterialChunkBase::getDiffuse        (void)
{
    return this->editDiffuse        ();
}
#endif

//! Set the value of the MaterialChunk::_sfDiffuse field.
inline
void MaterialChunkBase::setDiffuse(const Color4r &value)
{
    editSField(DiffuseFieldMask);

    _sfDiffuse.setValue(value);
}
//! Get the value of the MaterialChunk::_sfAmbient field.

inline
Color4r &MaterialChunkBase::editAmbient(void)
{
    editSField(AmbientFieldMask);

    return _sfAmbient.getValue();
}

//! Get the value of the MaterialChunk::_sfAmbient field.
inline
const Color4r MaterialChunkBase::getAmbient(void) const
{
    return _sfAmbient.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Color4r             &MaterialChunkBase::getAmbient        (void)
{
    return this->editAmbient        ();
}
#endif

//! Set the value of the MaterialChunk::_sfAmbient field.
inline
void MaterialChunkBase::setAmbient(const Color4r &value)
{
    editSField(AmbientFieldMask);

    _sfAmbient.setValue(value);
}
//! Get the value of the MaterialChunk::_sfSpecular field.

inline
Color4r &MaterialChunkBase::editSpecular(void)
{
    editSField(SpecularFieldMask);

    return _sfSpecular.getValue();
}

//! Get the value of the MaterialChunk::_sfSpecular field.
inline
const Color4r MaterialChunkBase::getSpecular(void) const
{
    return _sfSpecular.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Color4r             &MaterialChunkBase::getSpecular       (void)
{
    return this->editSpecular       ();
}
#endif

//! Set the value of the MaterialChunk::_sfSpecular field.
inline
void MaterialChunkBase::setSpecular(const Color4r &value)
{
    editSField(SpecularFieldMask);

    _sfSpecular.setValue(value);
}
//! Get the value of the MaterialChunk::_sfEmission field.

inline
Color4r &MaterialChunkBase::editEmission(void)
{
    editSField(EmissionFieldMask);

    return _sfEmission.getValue();
}

//! Get the value of the MaterialChunk::_sfEmission field.
inline
const Color4r MaterialChunkBase::getEmission(void) const
{
    return _sfEmission.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Color4r             &MaterialChunkBase::getEmission       (void)
{
    return this->editEmission       ();
}
#endif

//! Set the value of the MaterialChunk::_sfEmission field.
inline
void MaterialChunkBase::setEmission(const Color4r &value)
{
    editSField(EmissionFieldMask);

    _sfEmission.setValue(value);
}
//! Get the value of the MaterialChunk::_sfShininess field.

inline
Real &MaterialChunkBase::editShininess(void)
{
    editSField(ShininessFieldMask);

    return _sfShininess.getValue();
}

//! Get the value of the MaterialChunk::_sfShininess field.
inline
const Real MaterialChunkBase::getShininess(void) const
{
    return _sfShininess.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Real                &MaterialChunkBase::getShininess      (void)
{
    return this->editShininess      ();
}
#endif

//! Set the value of the MaterialChunk::_sfShininess field.
inline
void MaterialChunkBase::setShininess(const Real &value)
{
    editSField(ShininessFieldMask);

    _sfShininess.setValue(value);
}
//! Get the value of the MaterialChunk::_sfLit field.

inline
bool &MaterialChunkBase::editLit(void)
{
    editSField(LitFieldMask);

    return _sfLit.getValue();
}

//! Get the value of the MaterialChunk::_sfLit field.
inline
const bool MaterialChunkBase::getLit(void) const
{
    return _sfLit.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
bool                &MaterialChunkBase::getLit            (void)
{
    return this->editLit            ();
}
#endif

//! Set the value of the MaterialChunk::_sfLit field.
inline
void MaterialChunkBase::setLit(const bool &value)
{
    editSField(LitFieldMask);

    _sfLit.setValue(value);
}
//! Get the value of the MaterialChunk::_sfColorMaterial field.

inline
GLenum &MaterialChunkBase::editColorMaterial(void)
{
    editSField(ColorMaterialFieldMask);

    return _sfColorMaterial.getValue();
}

//! Get the value of the MaterialChunk::_sfColorMaterial field.
inline
const GLenum MaterialChunkBase::getColorMaterial(void) const
{
    return _sfColorMaterial.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
GLenum              &MaterialChunkBase::getColorMaterial  (void)
{
    return this->editColorMaterial  ();
}
#endif

//! Set the value of the MaterialChunk::_sfColorMaterial field.
inline
void MaterialChunkBase::setColorMaterial(const GLenum &value)
{
    editSField(ColorMaterialFieldMask);

    _sfColorMaterial.setValue(value);
}
//! Get the value of the MaterialChunk::_sfBackMaterial field.

inline
bool &MaterialChunkBase::editBackMaterial(void)
{
    editSField(BackMaterialFieldMask);

    return _sfBackMaterial.getValue();
}

//! Get the value of the MaterialChunk::_sfBackMaterial field.
inline
const bool MaterialChunkBase::getBackMaterial(void) const
{
    return _sfBackMaterial.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
bool                &MaterialChunkBase::getBackMaterial   (void)
{
    return this->editBackMaterial   ();
}
#endif

//! Set the value of the MaterialChunk::_sfBackMaterial field.
inline
void MaterialChunkBase::setBackMaterial(const bool &value)
{
    editSField(BackMaterialFieldMask);

    _sfBackMaterial.setValue(value);
}
//! Get the value of the MaterialChunk::_sfBackDiffuse field.

inline
Color4r &MaterialChunkBase::editBackDiffuse(void)
{
    editSField(BackDiffuseFieldMask);

    return _sfBackDiffuse.getValue();
}

//! Get the value of the MaterialChunk::_sfBackDiffuse field.
inline
const Color4r MaterialChunkBase::getBackDiffuse(void) const
{
    return _sfBackDiffuse.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Color4r             &MaterialChunkBase::getBackDiffuse    (void)
{
    return this->editBackDiffuse    ();
}
#endif

//! Set the value of the MaterialChunk::_sfBackDiffuse field.
inline
void MaterialChunkBase::setBackDiffuse(const Color4r &value)
{
    editSField(BackDiffuseFieldMask);

    _sfBackDiffuse.setValue(value);
}
//! Get the value of the MaterialChunk::_sfBackAmbient field.

inline
Color4r &MaterialChunkBase::editBackAmbient(void)
{
    editSField(BackAmbientFieldMask);

    return _sfBackAmbient.getValue();
}

//! Get the value of the MaterialChunk::_sfBackAmbient field.
inline
const Color4r MaterialChunkBase::getBackAmbient(void) const
{
    return _sfBackAmbient.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Color4r             &MaterialChunkBase::getBackAmbient    (void)
{
    return this->editBackAmbient    ();
}
#endif

//! Set the value of the MaterialChunk::_sfBackAmbient field.
inline
void MaterialChunkBase::setBackAmbient(const Color4r &value)
{
    editSField(BackAmbientFieldMask);

    _sfBackAmbient.setValue(value);
}
//! Get the value of the MaterialChunk::_sfBackSpecular field.

inline
Color4r &MaterialChunkBase::editBackSpecular(void)
{
    editSField(BackSpecularFieldMask);

    return _sfBackSpecular.getValue();
}

//! Get the value of the MaterialChunk::_sfBackSpecular field.
inline
const Color4r MaterialChunkBase::getBackSpecular(void) const
{
    return _sfBackSpecular.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Color4r             &MaterialChunkBase::getBackSpecular   (void)
{
    return this->editBackSpecular   ();
}
#endif

//! Set the value of the MaterialChunk::_sfBackSpecular field.
inline
void MaterialChunkBase::setBackSpecular(const Color4r &value)
{
    editSField(BackSpecularFieldMask);

    _sfBackSpecular.setValue(value);
}
//! Get the value of the MaterialChunk::_sfBackEmission field.

inline
Color4r &MaterialChunkBase::editBackEmission(void)
{
    editSField(BackEmissionFieldMask);

    return _sfBackEmission.getValue();
}

//! Get the value of the MaterialChunk::_sfBackEmission field.
inline
const Color4r MaterialChunkBase::getBackEmission(void) const
{
    return _sfBackEmission.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Color4r             &MaterialChunkBase::getBackEmission   (void)
{
    return this->editBackEmission   ();
}
#endif

//! Set the value of the MaterialChunk::_sfBackEmission field.
inline
void MaterialChunkBase::setBackEmission(const Color4r &value)
{
    editSField(BackEmissionFieldMask);

    _sfBackEmission.setValue(value);
}
//! Get the value of the MaterialChunk::_sfBackShininess field.

inline
Real &MaterialChunkBase::editBackShininess(void)
{
    editSField(BackShininessFieldMask);

    return _sfBackShininess.getValue();
}

//! Get the value of the MaterialChunk::_sfBackShininess field.
inline
const Real MaterialChunkBase::getBackShininess(void) const
{
    return _sfBackShininess.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Real                &MaterialChunkBase::getBackShininess  (void)
{
    return this->editBackShininess  ();
}
#endif

//! Set the value of the MaterialChunk::_sfBackShininess field.
inline
void MaterialChunkBase::setBackShininess(const Real &value)
{
    editSField(BackShininessFieldMask);

    _sfBackShininess.setValue(value);
}
//! Get the value of the MaterialChunk::_sfBackColorMaterial field.

inline
GLenum &MaterialChunkBase::editBackColorMaterial(void)
{
    editSField(BackColorMaterialFieldMask);

    return _sfBackColorMaterial.getValue();
}

//! Get the value of the MaterialChunk::_sfBackColorMaterial field.
inline
const GLenum MaterialChunkBase::getBackColorMaterial(void) const
{
    return _sfBackColorMaterial.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
GLenum              &MaterialChunkBase::getBackColorMaterial(void)
{
    return this->editBackColorMaterial();
}
#endif

//! Set the value of the MaterialChunk::_sfBackColorMaterial field.
inline
void MaterialChunkBase::setBackColorMaterial(const GLenum &value)
{
    editSField(BackColorMaterialFieldMask);

    _sfBackColorMaterial.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void MaterialChunkBase::execSync (      MaterialChunkBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (DiffuseFieldMask & whichField))
        _sfDiffuse.syncWith(pFrom->_sfDiffuse);

    if(FieldBits::NoField != (AmbientFieldMask & whichField))
        _sfAmbient.syncWith(pFrom->_sfAmbient);

    if(FieldBits::NoField != (SpecularFieldMask & whichField))
        _sfSpecular.syncWith(pFrom->_sfSpecular);

    if(FieldBits::NoField != (EmissionFieldMask & whichField))
        _sfEmission.syncWith(pFrom->_sfEmission);

    if(FieldBits::NoField != (ShininessFieldMask & whichField))
        _sfShininess.syncWith(pFrom->_sfShininess);

    if(FieldBits::NoField != (LitFieldMask & whichField))
        _sfLit.syncWith(pFrom->_sfLit);

    if(FieldBits::NoField != (ColorMaterialFieldMask & whichField))
        _sfColorMaterial.syncWith(pFrom->_sfColorMaterial);

    if(FieldBits::NoField != (BackMaterialFieldMask & whichField))
        _sfBackMaterial.syncWith(pFrom->_sfBackMaterial);

    if(FieldBits::NoField != (BackDiffuseFieldMask & whichField))
        _sfBackDiffuse.syncWith(pFrom->_sfBackDiffuse);

    if(FieldBits::NoField != (BackAmbientFieldMask & whichField))
        _sfBackAmbient.syncWith(pFrom->_sfBackAmbient);

    if(FieldBits::NoField != (BackSpecularFieldMask & whichField))
        _sfBackSpecular.syncWith(pFrom->_sfBackSpecular);

    if(FieldBits::NoField != (BackEmissionFieldMask & whichField))
        _sfBackEmission.syncWith(pFrom->_sfBackEmission);

    if(FieldBits::NoField != (BackShininessFieldMask & whichField))
        _sfBackShininess.syncWith(pFrom->_sfBackShininess);

    if(FieldBits::NoField != (BackColorMaterialFieldMask & whichField))
        _sfBackColorMaterial.syncWith(pFrom->_sfBackColorMaterial);
}
#endif


inline
Char8 *MaterialChunkBase::getClassname(void)
{
    return "MaterialChunk";
}
OSG_GEN_CONTAINERPTR(MaterialChunk);

OSG_END_NAMESPACE

