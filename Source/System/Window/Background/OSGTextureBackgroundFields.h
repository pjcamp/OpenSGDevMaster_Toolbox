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


#ifndef _OSGTEXTUREBACKGROUNDFIELDS_H_
#define _OSGTEXTUREBACKGROUNDFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGWindowDef.h"

#include "OSGBackgroundFields.h"

#include "OSGSFieldAdaptor.h"
#include "OSGMFieldAdaptor.h"


OSG_BEGIN_NAMESPACE

class TextureBackground;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! TextureBackgroundPtr

typedef PointerFwdBuilder<BackgroundPtr, 
                          BackgroundConstPtr,
                          TextureBackground>::ObjPtr         TextureBackgroundPtr;
typedef PointerFwdBuilder<BackgroundPtr, 
                          BackgroundConstPtr,
                          TextureBackground>::ObjPtrConst    TextureBackgroundPtrConst;
typedef PointerFwdBuilder<BackgroundPtr, 
                          BackgroundConstPtr,
                          TextureBackground>::ObjConstPtr    TextureBackgroundConstPtr;
typedef PointerFwdBuilder<BackgroundPtr, 
                          BackgroundConstPtr,
                          TextureBackground>::ObjPtrArg      TextureBackgroundPtrArg;
typedef PointerFwdBuilder<BackgroundPtr, 
                          BackgroundConstPtr,
                          TextureBackground>::ObjConstPtrArg TextureBackgroundConstPtrArg;
typedef PointerFwdBuilder<BackgroundPtr, 
                          BackgroundConstPtr,
                          TextureBackground>::ObjPtrConstArg TextureBackgroundPtrConstArg;

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpWindowFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<TextureBackgroundPtr> : 
    public FieldTraitsTemplateBase<TextureBackgroundPtr>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<TextureBackgroundPtr>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_WINDOW_DLLMAPPING 
                     DataType &getType (void);

    static const char *getSName(void) { return "SFTextureBackgroundPtr"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<TextureBackgroundPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpWindowFieldSingle */

typedef SFieldAdaptor<TextureBackgroundPtr, SFFieldContainerPtr> SFTextureBackgroundPtr;
#endif

#ifndef OSG_COMPILETEXTUREBACKGROUNDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, TextureBackgroundPtr, OSG_WINDOW_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGTEXTUREBACKGROUNDFIELDS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGTEXTUREBACKGROUNDFIELDS_H_ */
