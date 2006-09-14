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


#ifndef _OSGSTEREOBUFFERVIEWPORTFIELDS_H_
#define _OSGSTEREOBUFFERVIEWPORTFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGWindowDef.h"

#include "OSGViewportFields.h"

#include "OSGSFieldAdaptor.h"
#include "OSGMFieldAdaptor.h"


OSG_BEGIN_NAMESPACE

class StereoBufferViewport;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! StereoBufferViewportPtr

typedef PointerFwdBuilder<ViewportPtr, 
                          ViewportConstPtr,
                          StereoBufferViewport>::ObjPtr         StereoBufferViewportPtr;
typedef PointerFwdBuilder<ViewportPtr, 
                          ViewportConstPtr,
                          StereoBufferViewport>::ObjPtrConst    StereoBufferViewportPtrConst;
typedef PointerFwdBuilder<ViewportPtr, 
                          ViewportConstPtr,
                          StereoBufferViewport>::ObjConstPtr    StereoBufferViewportConstPtr;
typedef PointerFwdBuilder<ViewportPtr, 
                          ViewportConstPtr,
                          StereoBufferViewport>::ObjPtrArg      StereoBufferViewportPtrArg;
typedef PointerFwdBuilder<ViewportPtr, 
                          ViewportConstPtr,
                          StereoBufferViewport>::ObjConstPtrArg StereoBufferViewportConstPtrArg;
typedef PointerFwdBuilder<ViewportPtr, 
                          ViewportConstPtr,
                          StereoBufferViewport>::ObjPtrConstArg StereoBufferViewportPtrConstArg;

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpWindowFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<StereoBufferViewportPtr> : 
    public FieldTraitsTemplateBase<StereoBufferViewportPtr>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<StereoBufferViewportPtr>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_WINDOW_DLLMAPPING 
                     DataType &getType (void);

    static const char *getSName(void) { return "SFStereoBufferViewportPtr"; }
    static const char *getMName(void) { return "MFStereoBufferViewportPtr"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<StereoBufferViewportPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpWindowFieldSingle */

typedef SFieldAdaptor<StereoBufferViewportPtr, SFFieldContainerPtr> SFStereoBufferViewportPtr;
#endif

#ifndef OSG_COMPILESTEREOBUFFERVIEWPORTINST
OSG_FIELD_DLLEXPORT_DECL1(SField, StereoBufferViewportPtr, OSG_WINDOW_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpWindowFieldMulti */

typedef MFieldAdaptor<StereoBufferViewportPtr, MFFieldContainerPtr> MFStereoBufferViewportPtr;
#endif

#ifndef OSG_COMPILESTEREOBUFFERVIEWPORTINST
OSG_FIELD_DLLEXPORT_DECL1(MField, StereoBufferViewportPtr, OSG_WINDOW_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGSTEREOBUFFERVIEWPORTFIELDS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGSTEREOBUFFERVIEWPORTFIELDS_H_ */
