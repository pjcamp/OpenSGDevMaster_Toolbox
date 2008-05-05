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
 **     class Billboard!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &BillboardBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 BillboardBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 BillboardBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the Billboard::_sfAxisOfRotation field.

inline
Vec3f &BillboardBase::editAxisOfRotation(void)
{
    editSField(AxisOfRotationFieldMask);

    return _sfAxisOfRotation.getValue();
}

//! Get the value of the Billboard::_sfAxisOfRotation field.
inline
const Vec3f BillboardBase::getAxisOfRotation(void) const
{
    return _sfAxisOfRotation.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Vec3f               &BillboardBase::getAxisOfRotation (void)
{
    return this->editAxisOfRotation ();
}
#endif

//! Set the value of the Billboard::_sfAxisOfRotation field.
inline
void BillboardBase::setAxisOfRotation(const Vec3f &value)
{
    editSField(AxisOfRotationFieldMask);

    _sfAxisOfRotation.setValue(value);
}
//! Get the value of the Billboard::_sfFocusOnCamera field.

inline
bool &BillboardBase::editFocusOnCamera(void)
{
    editSField(FocusOnCameraFieldMask);

    return _sfFocusOnCamera.getValue();
}

//! Get the value of the Billboard::_sfFocusOnCamera field.
inline
const bool BillboardBase::getFocusOnCamera(void) const
{
    return _sfFocusOnCamera.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
bool                &BillboardBase::getFocusOnCamera  (void)
{
    return this->editFocusOnCamera  ();
}
#endif

//! Set the value of the Billboard::_sfFocusOnCamera field.
inline
void BillboardBase::setFocusOnCamera(const bool &value)
{
    editSField(FocusOnCameraFieldMask);

    _sfFocusOnCamera.setValue(value);
}
//! Get the value of the Billboard::_sfAlignToScreen field.

inline
bool &BillboardBase::editAlignToScreen(void)
{
    editSField(AlignToScreenFieldMask);

    return _sfAlignToScreen.getValue();
}

//! Get the value of the Billboard::_sfAlignToScreen field.
inline
const bool BillboardBase::getAlignToScreen(void) const
{
    return _sfAlignToScreen.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
bool                &BillboardBase::getAlignToScreen  (void)
{
    return this->editAlignToScreen  ();
}
#endif

//! Set the value of the Billboard::_sfAlignToScreen field.
inline
void BillboardBase::setAlignToScreen(const bool &value)
{
    editSField(AlignToScreenFieldMask);

    _sfAlignToScreen.setValue(value);
}
//! Get the value of the Billboard::_sfMinAngle field.

inline
Real32 &BillboardBase::editMinAngle(void)
{
    editSField(MinAngleFieldMask);

    return _sfMinAngle.getValue();
}

//! Get the value of the Billboard::_sfMinAngle field.
inline
const Real32 BillboardBase::getMinAngle(void) const
{
    return _sfMinAngle.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Real32              &BillboardBase::getMinAngle       (void)
{
    return this->editMinAngle       ();
}
#endif

//! Set the value of the Billboard::_sfMinAngle field.
inline
void BillboardBase::setMinAngle(const Real32 &value)
{
    editSField(MinAngleFieldMask);

    _sfMinAngle.setValue(value);
}
//! Get the value of the Billboard::_sfMaxAngle field.

inline
Real32 &BillboardBase::editMaxAngle(void)
{
    editSField(MaxAngleFieldMask);

    return _sfMaxAngle.getValue();
}

//! Get the value of the Billboard::_sfMaxAngle field.
inline
const Real32 BillboardBase::getMaxAngle(void) const
{
    return _sfMaxAngle.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Real32              &BillboardBase::getMaxAngle       (void)
{
    return this->editMaxAngle       ();
}
#endif

//! Set the value of the Billboard::_sfMaxAngle field.
inline
void BillboardBase::setMaxAngle(const Real32 &value)
{
    editSField(MaxAngleFieldMask);

    _sfMaxAngle.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void BillboardBase::execSync (      BillboardBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (AxisOfRotationFieldMask & whichField))
        _sfAxisOfRotation.syncWith(pFrom->_sfAxisOfRotation);

    if(FieldBits::NoField != (FocusOnCameraFieldMask & whichField))
        _sfFocusOnCamera.syncWith(pFrom->_sfFocusOnCamera);

    if(FieldBits::NoField != (AlignToScreenFieldMask & whichField))
        _sfAlignToScreen.syncWith(pFrom->_sfAlignToScreen);

    if(FieldBits::NoField != (MinAngleFieldMask & whichField))
        _sfMinAngle.syncWith(pFrom->_sfMinAngle);

    if(FieldBits::NoField != (MaxAngleFieldMask & whichField))
        _sfMaxAngle.syncWith(pFrom->_sfMaxAngle);
}
#endif


inline
Char8 *BillboardBase::getClassname(void)
{
    return "Billboard";
}
OSG_GEN_CONTAINERPTR(Billboard);

OSG_END_NAMESPACE

