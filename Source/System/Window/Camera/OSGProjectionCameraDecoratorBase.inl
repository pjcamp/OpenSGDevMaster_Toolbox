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
 **     class ProjectionCameraDecorator!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &ProjectionCameraDecoratorBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 ProjectionCameraDecoratorBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 ProjectionCameraDecoratorBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/


//! Get the value of the ProjectionCameraDecorator::_sfUser field.
inline
NodePtr ProjectionCameraDecoratorBase::getUser(void) const
{
    return _sfUser.getValue();
}

//! Set the value of the ProjectionCameraDecorator::_sfUser field.
inline
void ProjectionCameraDecoratorBase::setUser(const NodePtr value)
{
    editSField(UserFieldMask);

    _sfUser.setValue(value);
}
//! Get the value of the ProjectionCameraDecorator::_sfLeft field.

inline
Plane &ProjectionCameraDecoratorBase::editLeft(void)
{
    editSField(LeftFieldMask);

    return _sfLeft.getValue();
}

//! Get the value of the ProjectionCameraDecorator::_sfLeft field.
inline
const Plane ProjectionCameraDecoratorBase::getLeft(void) const
{
    return _sfLeft.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Plane               &ProjectionCameraDecoratorBase::getLeft           (void)
{
    return this->editLeft           ();
}
#endif

//! Set the value of the ProjectionCameraDecorator::_sfLeft field.
inline
void ProjectionCameraDecoratorBase::setLeft(const Plane &value)
{
    editSField(LeftFieldMask);

    _sfLeft.setValue(value);
}
//! Get the value of the ProjectionCameraDecorator::_sfBottom field.

inline
Plane &ProjectionCameraDecoratorBase::editBottom(void)
{
    editSField(BottomFieldMask);

    return _sfBottom.getValue();
}

//! Get the value of the ProjectionCameraDecorator::_sfBottom field.
inline
const Plane ProjectionCameraDecoratorBase::getBottom(void) const
{
    return _sfBottom.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Plane               &ProjectionCameraDecoratorBase::getBottom         (void)
{
    return this->editBottom         ();
}
#endif

//! Set the value of the ProjectionCameraDecorator::_sfBottom field.
inline
void ProjectionCameraDecoratorBase::setBottom(const Plane &value)
{
    editSField(BottomFieldMask);

    _sfBottom.setValue(value);
}
//! Get the value of the ProjectionCameraDecorator::_sfNormal field.

inline
Plane &ProjectionCameraDecoratorBase::editNormal(void)
{
    editSField(NormalFieldMask);

    return _sfNormal.getValue();
}

//! Get the value of the ProjectionCameraDecorator::_sfNormal field.
inline
const Plane ProjectionCameraDecoratorBase::getNormal(void) const
{
    return _sfNormal.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Plane               &ProjectionCameraDecoratorBase::getNormal         (void)
{
    return this->editNormal         ();
}
#endif

//! Set the value of the ProjectionCameraDecorator::_sfNormal field.
inline
void ProjectionCameraDecoratorBase::setNormal(const Plane &value)
{
    editSField(NormalFieldMask);

    _sfNormal.setValue(value);
}
//! Get the value of the ProjectionCameraDecorator::_sfWidth field.

inline
Real32 &ProjectionCameraDecoratorBase::editWidth(void)
{
    editSField(WidthFieldMask);

    return _sfWidth.getValue();
}

//! Get the value of the ProjectionCameraDecorator::_sfWidth field.
inline
const Real32 ProjectionCameraDecoratorBase::getWidth(void) const
{
    return _sfWidth.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Real32              &ProjectionCameraDecoratorBase::getWidth          (void)
{
    return this->editWidth          ();
}
#endif

//! Set the value of the ProjectionCameraDecorator::_sfWidth field.
inline
void ProjectionCameraDecoratorBase::setWidth(const Real32 &value)
{
    editSField(WidthFieldMask);

    _sfWidth.setValue(value);
}
//! Get the value of the ProjectionCameraDecorator::_sfHeight field.

inline
Real32 &ProjectionCameraDecoratorBase::editHeight(void)
{
    editSField(HeightFieldMask);

    return _sfHeight.getValue();
}

//! Get the value of the ProjectionCameraDecorator::_sfHeight field.
inline
const Real32 ProjectionCameraDecoratorBase::getHeight(void) const
{
    return _sfHeight.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Real32              &ProjectionCameraDecoratorBase::getHeight         (void)
{
    return this->editHeight         ();
}
#endif

//! Set the value of the ProjectionCameraDecorator::_sfHeight field.
inline
void ProjectionCameraDecoratorBase::setHeight(const Real32 &value)
{
    editSField(HeightFieldMask);

    _sfHeight.setValue(value);
}

//! Get the value of the \a index element the ProjectionCameraDecorator::_mfSurface field.
inline
const Pnt3f ProjectionCameraDecoratorBase::getSurface(const UInt32 index) const
{
    return _mfSurface[index];
}

inline
Pnt3f &ProjectionCameraDecoratorBase::editSurface(const UInt32 index)
{
    editMField(SurfaceFieldMask, _mfSurface);

    return _mfSurface[index];
}

#ifdef OSG_1_GET_COMPAT
inline
Pnt3f               &ProjectionCameraDecoratorBase::getSurface        (const UInt32 index)
{
    return this->editSurface        (index);
}

inline
MFPnt3f             &ProjectionCameraDecoratorBase::getSurface        (void)
{
    return this->editSurface        ();
}

#endif



#ifdef OSG_MT_CPTR_ASPECT
inline
void ProjectionCameraDecoratorBase::execSync (      ProjectionCameraDecoratorBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (UserFieldMask & whichField))
        _sfUser.syncWith(pFrom->_sfUser);

    if(FieldBits::NoField != (SurfaceFieldMask & whichField))
        _mfSurface.syncWith(pFrom->_mfSurface,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (LeftFieldMask & whichField))
        _sfLeft.syncWith(pFrom->_sfLeft);

    if(FieldBits::NoField != (BottomFieldMask & whichField))
        _sfBottom.syncWith(pFrom->_sfBottom);

    if(FieldBits::NoField != (NormalFieldMask & whichField))
        _sfNormal.syncWith(pFrom->_sfNormal);

    if(FieldBits::NoField != (WidthFieldMask & whichField))
        _sfWidth.syncWith(pFrom->_sfWidth);

    if(FieldBits::NoField != (HeightFieldMask & whichField))
        _sfHeight.syncWith(pFrom->_sfHeight);
}
#endif


inline
Char8 *ProjectionCameraDecoratorBase::getClassname(void)
{
    return "ProjectionCameraDecorator";
}
OSG_GEN_CONTAINERPTR(ProjectionCameraDecorator);

OSG_END_NAMESPACE

