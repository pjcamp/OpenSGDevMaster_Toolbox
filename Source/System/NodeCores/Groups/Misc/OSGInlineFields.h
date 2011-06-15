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


#ifndef _OSGINLINEFIELDS_H_
#define _OSGINLINEFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGGroupDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class Inline;

OSG_GEN_CONTAINERPTR(Inline);

/*! \ingroup GrpGroupMiscFieldTraits
    \ingroup GrpLibOSGGroup
 */
template <>
struct FieldTraits<Inline *> :
    public FieldTraitsFCPtrBase<Inline *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<Inline *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_GROUP_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFInlinePtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFInlinePtr"; }
};

template<> inline
const Char8 *FieldTraits<Inline *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecInlinePtr"; 
}

template<> inline
const Char8 *FieldTraits<Inline *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecInlinePtr"; 
}

template<> inline
const Char8 *FieldTraits<Inline *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakInlinePtr"; 
}

template<> inline
const Char8 *FieldTraits<Inline *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdInlinePtr"; 
}

template<> inline
const Char8 *FieldTraits<Inline *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecInlinePtr"; 
}

template<> inline
const Char8 *FieldTraits<Inline *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecInlinePtr"; 
}

template<> inline
const Char8 *FieldTraits<Inline *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakInlinePtr"; 
}

template<> inline
const Char8 *FieldTraits<Inline *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdInlinePtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpGroupMiscFieldSFields */
typedef PointerSField<Inline *,
                      RecordedRefCountPolicy  > SFRecInlinePtr;
/*! \ingroup GrpGroupMiscFieldSFields */
typedef PointerSField<Inline *,
                      UnrecordedRefCountPolicy> SFUnrecInlinePtr;
/*! \ingroup GrpGroupMiscFieldSFields */
typedef PointerSField<Inline *,
                      WeakRefCountPolicy      > SFWeakInlinePtr;
/*! \ingroup GrpGroupMiscFieldSFields */
typedef PointerSField<Inline *,
                      NoRefCountPolicy        > SFUncountedInlinePtr;


/*! \ingroup GrpGroupMiscFieldMFields */
typedef PointerMField<Inline *,
                      RecordedRefCountPolicy  > MFRecInlinePtr;
/*! \ingroup GrpGroupMiscFieldMFields */
typedef PointerMField<Inline *,
                      UnrecordedRefCountPolicy> MFUnrecInlinePtr;
/*! \ingroup GrpGroupMiscFieldMFields */
typedef PointerMField<Inline *,
                      WeakRefCountPolicy      > MFWeakInlinePtr;
/*! \ingroup GrpGroupMiscFieldMFields */
typedef PointerMField<Inline *,
                      NoRefCountPolicy        > MFUncountedInlinePtr;




#else // these are the doxygen hacks

/*! \ingroup GrpGroupMiscFieldSFields \ingroup GrpLibOSGGroup */
struct SFRecInlinePtr : 
    public PointerSField<Inline *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpGroupMiscFieldSFields \ingroup GrpLibOSGGroup */
struct SFUnrecInlinePtr : 
    public PointerSField<Inline *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpGroupMiscFieldSFields \ingroup GrpLibOSGGroup */
struct SFWeakInlinePtr :
    public PointerSField<Inline *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpGroupMiscFieldSFields \ingroup GrpLibOSGGroup */
struct SFUncountedInlinePtr :
    public PointerSField<Inline *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpGroupMiscFieldMFields \ingroup GrpLibOSGGroup */
struct MFRecInlinePtr :
    public PointerMField<Inline *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpGroupMiscFieldMFields \ingroup GrpLibOSGGroup */
struct MFUnrecInlinePtr :
    public PointerMField<Inline *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpGroupMiscFieldMFields \ingroup GrpLibOSGGroup */
struct MFWeakInlinePtr :
    public PointerMField<Inline *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpGroupMiscFieldMFields \ingroup GrpLibOSGGroup */
struct MFUncountedInlinePtr :
    public PointerMField<Inline *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGINLINEFIELDS_H_ */
