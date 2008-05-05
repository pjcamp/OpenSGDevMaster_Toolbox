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
 **     class EGLWindow!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &EGLWindowBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 EGLWindowBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 EGLWindowBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the EGLWindow::_sfDisplay field.

inline
EGLDisplay &EGLWindowBase::editDisplay(void)
{
    editSField(DisplayFieldMask);

    return _sfDisplay.getValue();
}

//! Get the value of the EGLWindow::_sfDisplay field.
inline
const EGLDisplay EGLWindowBase::getDisplay(void) const
{
    return _sfDisplay.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
EGLDisplay          &EGLWindowBase::getDisplay        (void)
{
    return this->editDisplay        ();
}
#endif

//! Set the value of the EGLWindow::_sfDisplay field.
inline
void EGLWindowBase::setDisplay(const EGLDisplay &value)
{
    editSField(DisplayFieldMask);

    _sfDisplay.setValue(value);
}
//! Get the value of the EGLWindow::_sfWindow field.

inline
EGLSurface &EGLWindowBase::editWindow(void)
{
    editSField(WindowFieldMask);

    return _sfWindow.getValue();
}

//! Get the value of the EGLWindow::_sfWindow field.
inline
const EGLSurface EGLWindowBase::getWindow(void) const
{
    return _sfWindow.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
EGLSurface          &EGLWindowBase::getWindow         (void)
{
    return this->editWindow         ();
}
#endif

//! Set the value of the EGLWindow::_sfWindow field.
inline
void EGLWindowBase::setWindow(const EGLSurface &value)
{
    editSField(WindowFieldMask);

    _sfWindow.setValue(value);
}
//! Get the value of the EGLWindow::_sfContext field.

inline
EGLContext &EGLWindowBase::editContext(void)
{
    editSField(ContextFieldMask);

    return _sfContext.getValue();
}

//! Get the value of the EGLWindow::_sfContext field.
inline
const EGLContext EGLWindowBase::getContext(void) const
{
    return _sfContext.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
EGLContext          &EGLWindowBase::getContext        (void)
{
    return this->editContext        ();
}
#endif

//! Set the value of the EGLWindow::_sfContext field.
inline
void EGLWindowBase::setContext(const EGLContext &value)
{
    editSField(ContextFieldMask);

    _sfContext.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void EGLWindowBase::execSync (      EGLWindowBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (DisplayFieldMask & whichField))
        _sfDisplay.syncWith(pFrom->_sfDisplay);

    if(FieldBits::NoField != (WindowFieldMask & whichField))
        _sfWindow.syncWith(pFrom->_sfWindow);

    if(FieldBits::NoField != (ContextFieldMask & whichField))
        _sfContext.syncWith(pFrom->_sfContext);
}
#endif


inline
Char8 *EGLWindowBase::getClassname(void)
{
    return "EGLWindow";
}
OSG_GEN_CONTAINERPTR(EGLWindow);

OSG_END_NAMESPACE

