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
 **     class PerspectiveCamera!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &PerspectiveCameraBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 PerspectiveCameraBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 PerspectiveCameraBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the PerspectiveCamera::_sfFov field.

inline
Real32 &PerspectiveCameraBase::editFov(void)
{
    editSField(FovFieldMask);

    return _sfFov.getValue();
}

//! Get the value of the PerspectiveCamera::_sfFov field.
inline
const Real32 PerspectiveCameraBase::getFov(void) const
{
    return _sfFov.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Real32              &PerspectiveCameraBase::getFov            (void)
{
    return this->editFov            ();
}
#endif

//! Set the value of the PerspectiveCamera::_sfFov field.
inline
void PerspectiveCameraBase::setFov(const Real32 &value)
{
    editSField(FovFieldMask);

    _sfFov.setValue(value);
}
//! Get the value of the PerspectiveCamera::_sfAspect field.

inline
Real32 &PerspectiveCameraBase::editAspect(void)
{
    editSField(AspectFieldMask);

    return _sfAspect.getValue();
}

//! Get the value of the PerspectiveCamera::_sfAspect field.
inline
const Real32 PerspectiveCameraBase::getAspect(void) const
{
    return _sfAspect.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Real32              &PerspectiveCameraBase::getAspect         (void)
{
    return this->editAspect         ();
}
#endif

//! Set the value of the PerspectiveCamera::_sfAspect field.
inline
void PerspectiveCameraBase::setAspect(const Real32 &value)
{
    editSField(AspectFieldMask);

    _sfAspect.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void PerspectiveCameraBase::execSync (      PerspectiveCameraBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (FovFieldMask & whichField))
        _sfFov.syncWith(pFrom->_sfFov);

    if(FieldBits::NoField != (AspectFieldMask & whichField))
        _sfAspect.syncWith(pFrom->_sfAspect);
}
#endif


inline
Char8 *PerspectiveCameraBase::getClassname(void)
{
    return "PerspectiveCamera";
}
OSG_GEN_CONTAINERPTR(PerspectiveCamera);

OSG_END_NAMESPACE

