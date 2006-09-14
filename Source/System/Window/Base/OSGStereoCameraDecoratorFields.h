/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
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
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGSTEREOCAMERADECORATORFIELDS_H_
#define _OSGSTEREOCAMERADECORATORFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGCameraDecoratorFields.h"

#include "OSGSFieldAdaptor.h"
#include "OSGMFieldAdaptor.h"


OSG_BEGIN_NAMESPACE

class StereoCameraDecorator;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! StereoCameraDecoratorPtr

typedef PointerFwdBuilder<CameraDecoratorPtr, 
                          CameraDecoratorConstPtr,
                          StereoCameraDecorator>::ObjPtr         StereoCameraDecoratorPtr;
typedef PointerFwdBuilder<CameraDecoratorPtr, 
                          CameraDecoratorConstPtr,
                          StereoCameraDecorator>::ObjPtrConst    StereoCameraDecoratorPtrConst;
typedef PointerFwdBuilder<CameraDecoratorPtr, 
                          CameraDecoratorConstPtr,
                          StereoCameraDecorator>::ObjConstPtr    StereoCameraDecoratorConstPtr;
typedef PointerFwdBuilder<CameraDecoratorPtr, 
                          CameraDecoratorConstPtr,
                          StereoCameraDecorator>::ObjPtrArg      StereoCameraDecoratorPtrArg;
typedef PointerFwdBuilder<CameraDecoratorPtr, 
                          CameraDecoratorConstPtr,
                          StereoCameraDecorator>::ObjConstPtrArg StereoCameraDecoratorConstPtrArg;
typedef PointerFwdBuilder<CameraDecoratorPtr, 
                          CameraDecoratorConstPtr,
                          StereoCameraDecorator>::ObjPtrConstArg StereoCameraDecoratorPtrConstArg;

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<StereoCameraDecoratorPtr> : 
    public FieldTraitsTemplateBase<StereoCameraDecoratorPtr>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<StereoCameraDecoratorPtr>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_SYSTEM_DLLMAPPING 
                     DataType &getType (void);

    static const char *getSName(void) { return "SFStereoCameraDecoratorPtr"; }
    static const char *getMName(void) { return "MFStereoCameraDecoratorPtr"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<StereoCameraDecoratorPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpSystemFieldSingle */

typedef SFieldAdaptor<StereoCameraDecoratorPtr, SFFieldContainerPtr> SFStereoCameraDecoratorPtr;
#endif

#ifndef OSG_COMPILESTEREOCAMERADECORATORINST
OSG_FIELD_DLLEXPORT_DECL1(SField, StereoCameraDecoratorPtr, OSG_SYSTEM_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpSystemFieldMulti */

typedef MFieldAdaptor<StereoCameraDecoratorPtr, MFFieldContainerPtr> MFStereoCameraDecoratorPtr;
#endif

#ifndef OSG_COMPILESTEREOCAMERADECORATORINST
OSG_FIELD_DLLEXPORT_DECL1(MField, StereoCameraDecoratorPtr, OSG_SYSTEM_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGSTEREOCAMERADECORATORFIELDS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGSTEREOCAMERADECORATORFIELDS_H_ */
