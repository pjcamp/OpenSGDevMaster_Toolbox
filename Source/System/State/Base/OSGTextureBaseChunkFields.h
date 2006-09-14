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


#ifndef _OSGTEXTUREBASECHUNKFIELDS_H_
#define _OSGTEXTUREBASECHUNKFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGStateChunkFields.h"

#include "OSGSFieldAdaptor.h"
#include "OSGMFieldAdaptor.h"


OSG_BEGIN_NAMESPACE

class TextureBaseChunk;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! TextureBaseChunkPtr

typedef PointerFwdBuilder<StateChunkPtr, 
                          StateChunkConstPtr,
                          TextureBaseChunk>::ObjPtr         TextureBaseChunkPtr;
typedef PointerFwdBuilder<StateChunkPtr, 
                          StateChunkConstPtr,
                          TextureBaseChunk>::ObjPtrConst    TextureBaseChunkPtrConst;
typedef PointerFwdBuilder<StateChunkPtr, 
                          StateChunkConstPtr,
                          TextureBaseChunk>::ObjConstPtr    TextureBaseChunkConstPtr;
typedef PointerFwdBuilder<StateChunkPtr, 
                          StateChunkConstPtr,
                          TextureBaseChunk>::ObjPtrArg      TextureBaseChunkPtrArg;
typedef PointerFwdBuilder<StateChunkPtr, 
                          StateChunkConstPtr,
                          TextureBaseChunk>::ObjConstPtrArg TextureBaseChunkConstPtrArg;
typedef PointerFwdBuilder<StateChunkPtr, 
                          StateChunkConstPtr,
                          TextureBaseChunk>::ObjPtrConstArg TextureBaseChunkPtrConstArg;

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<TextureBaseChunkPtr> : 
    public FieldTraitsTemplateBase<TextureBaseChunkPtr>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<TextureBaseChunkPtr>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_SYSTEM_DLLMAPPING 
                     DataType &getType (void);

    static const char *getSName(void) { return "SFTextureBaseChunkPtr"; }
    static const char *getMName(void) { return "MFTextureBaseChunkPtr"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<TextureBaseChunkPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpSystemFieldSingle */

typedef SFieldAdaptor<TextureBaseChunkPtr, SFFieldContainerPtr> SFTextureBaseChunkPtr;
#endif

#ifndef OSG_COMPILETEXTUREBASECHUNKINST
OSG_FIELD_DLLEXPORT_DECL1(SField, TextureBaseChunkPtr, OSG_SYSTEM_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpSystemFieldMulti */

typedef MFieldAdaptor<TextureBaseChunkPtr, MFFieldContainerPtr> MFTextureBaseChunkPtr;
#endif

#ifndef OSG_COMPILETEXTUREBASECHUNKINST
OSG_FIELD_DLLEXPORT_DECL1(MField, TextureBaseChunkPtr, OSG_SYSTEM_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGTEXTUREBASECHUNKFIELDS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGTEXTUREBASECHUNKFIELDS_H_ */
