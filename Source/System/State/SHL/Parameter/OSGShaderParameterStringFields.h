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


#ifndef _OSGSHADERPARAMETERSTRINGFIELDS_H_
#define _OSGSHADERPARAMETERSTRINGFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGStateDef.h"

#include "OSGShaderParameterFields.h"

#include "OSGSFieldAdaptor.h"
#include "OSGMFieldAdaptor.h"


OSG_BEGIN_NAMESPACE

class ShaderParameterString;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! ShaderParameterStringPtr

typedef PointerFwdBuilder<ShaderParameterPtr, 
                          ShaderParameterConstPtr,
                          ShaderParameterString>::ObjPtr         ShaderParameterStringPtr;
typedef PointerFwdBuilder<ShaderParameterPtr, 
                          ShaderParameterConstPtr,
                          ShaderParameterString>::ObjPtrConst    ShaderParameterStringPtrConst;
typedef PointerFwdBuilder<ShaderParameterPtr, 
                          ShaderParameterConstPtr,
                          ShaderParameterString>::ObjConstPtr    ShaderParameterStringConstPtr;
typedef PointerFwdBuilder<ShaderParameterPtr, 
                          ShaderParameterConstPtr,
                          ShaderParameterString>::ObjPtrArg      ShaderParameterStringPtrArg;
typedef PointerFwdBuilder<ShaderParameterPtr, 
                          ShaderParameterConstPtr,
                          ShaderParameterString>::ObjConstPtrArg ShaderParameterStringConstPtrArg;
typedef PointerFwdBuilder<ShaderParameterPtr, 
                          ShaderParameterConstPtr,
                          ShaderParameterString>::ObjPtrConstArg ShaderParameterStringPtrConstArg;

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpStateFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<ShaderParameterStringPtr> : 
    public FieldTraitsTemplateBase<ShaderParameterStringPtr>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<ShaderParameterStringPtr>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_STATE_DLLMAPPING 
                     DataType &getType (void);

    static const char *getSName(void) { return "SFShaderParameterStringPtr"; }
    static const char *getMName(void) { return "MFShaderParameterStringPtr"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<ShaderParameterStringPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpStateFieldSingle */

typedef SFieldAdaptor<ShaderParameterStringPtr, SFFieldContainerPtr> SFShaderParameterStringPtr;
#endif

#ifndef OSG_COMPILESHADERPARAMETERSTRINGINST
OSG_FIELD_DLLEXPORT_DECL1(SField, ShaderParameterStringPtr, OSG_STATE_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpStateFieldMulti */

typedef MFieldAdaptor<ShaderParameterStringPtr, MFFieldContainerPtr> MFShaderParameterStringPtr;
#endif

#ifndef OSG_COMPILESHADERPARAMETERSTRINGINST
OSG_FIELD_DLLEXPORT_DECL1(MField, ShaderParameterStringPtr, OSG_STATE_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGSHADERPARAMETERSTRINGFIELDS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGSHADERPARAMETERSTRINGFIELDS_H_ */
