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


#ifndef _OSGNODECOREFIELDS_H_
#define _OSGNODECOREFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGBaseDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class NodeCore;

OSG_GEN_CONTAINERPTR(NodeCore);

/*! \ingroup GrpBaseFieldContainerFieldTraits
    \ingroup GrpLibOSGBase
 */
template <>
struct FieldTraits<NodeCore *> :
    public FieldTraitsFCPtrBase<NodeCore *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<NodeCore *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_BASE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFNodeCorePtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFNodeCorePtr"; }
};

template<> inline
const Char8 *FieldTraits<NodeCore *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCore *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCore *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCore *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCore *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCore *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCore *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCore *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdNodeCorePtr"; 
}


/*! \ingroup GrpBaseFieldContainerFieldTraits
 */
template <>
struct FieldTraits<NodeCore *, 1> :
    public FieldTraitsFCPtrBase<NodeCore *, 1>
{
  private:

  public:
    typedef FieldTraits<NodeCore *, 1>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_BASE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);
};

template<> inline
const Char8 *FieldTraits<NodeCore *, 1>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecChildNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCore *, 1>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecChildNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCore *, 1>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakChildNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCore *, 1>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdChildNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCore *, 1>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecChildNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCore *, 1>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecChildNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCore *, 1>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakChildNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCore *, 1>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdChildNodeCorePtr"; 
}


/*! \ingroup GrpBaseFieldContainerFieldTraits
 */
template <>
struct FieldTraits<NodeCore *, 2> : 
    public FieldTraitsFCPtrBase<NodeCore *, 2>
{
  private:

    static  DataType                                _type;

  public:

    static const bool bIsPointerField = true;

    typedef FieldTraits<NodeCore *, 2>        Self;


    enum             { Convertible = Self::NotConvertible };
    
    static OSG_BASE_DLLMAPPING
                 DataType &getType (void);

    static const Char8    *getSName(void) 
    {
        return "SFParentNodeCorePtr"; 
    }

    static const Char8    *getMName(void) 
    { 
        return "MFParentNodeCorePtr"; 
    }
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField<NodeCore *,
                      RecordedRefCountPolicy  > SFRecNodeCorePtr;
/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField<NodeCore *,
                      UnrecordedRefCountPolicy> SFUnrecNodeCorePtr;
/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField<NodeCore *,
                      WeakRefCountPolicy      > SFWeakNodeCorePtr;
/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField<NodeCore *,
                      NoRefCountPolicy        > SFUncountedNodeCorePtr;


/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<NodeCore *,
                      RecordedRefCountPolicy  > MFRecNodeCorePtr;
/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<NodeCore *,
                      UnrecordedRefCountPolicy> MFUnrecNodeCorePtr;
/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<NodeCore *,
                      WeakRefCountPolicy      > MFWeakNodeCorePtr;
/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<NodeCore *,
                      NoRefCountPolicy        > MFUncountedNodeCorePtr;



/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef ChildPointerSField<
          NodeCore *, 
          UnrecordedRefCountPolicy,
          1             > SFUnrecChildNodeCorePtr;


/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef ChildPointerMField<
          NodeCore *, 
          UnrecordedRefCountPolicy,
          1             > MFUnrecChildNodeCorePtr;


/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef ParentPointerSField<
          NodeCore *, 
          NoRefCountPolicy,
          2    > SFParentNodeCorePtr;

/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef ParentPointerMField<
          NodeCore *, 
          NoRefCountPolicy,
          2    > MFParentNodeCorePtr;



#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldContainerFieldSFields \ingroup GrpLibOSGBase */
struct SFRecNodeCorePtr : 
    public PointerSField<NodeCore *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerFieldSFields \ingroup GrpLibOSGBase */
struct SFUnrecNodeCorePtr : 
    public PointerSField<NodeCore *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerFieldSFields \ingroup GrpLibOSGBase */
struct SFWeakNodeCorePtr :
    public PointerSField<NodeCore *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerFieldSFields \ingroup GrpLibOSGBase */
struct SFUncountedNodeCorePtr :
    public PointerSField<NodeCore *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFRecNodeCorePtr :
    public PointerMField<NodeCore *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFUnrecNodeCorePtr :
    public PointerMField<NodeCore *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFWeakNodeCorePtr :
    public PointerMField<NodeCore *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFUncountedNodeCorePtr :
    public PointerMField<NodeCore *,
                         NoRefCountPolicy        > {};



/*! \ingroup GrpBaseFieldContainerFieldSFields \ingroup GrpLibOSGBase */
struct SFUnrecChildNodeCorePtr :
    public ChildPointerSField<
        NodeCore *, 
        UnrecordedRefCountPolicy,
        1             > {};


/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFUnrecChildNodeCorePtr :
    public ChildPointerMField<
        NodeCore *, 
        UnrecordedRefCountPolicy,
        1             > {};


/*! \ingroup GrpBaseFieldContainerFieldSFields \ingroup GrpLibOSGBase */
struct SFParentNodeCorePtr :
    public ParentPointerSField<
        NodeCore *, 
        NoRefCountPolicy,
        2    > {};

/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFParentNodeCorePtr :
    public  ParentPointerMField<
        NodeCore *, 
        NoRefCountPolicy,
        2    > {};


#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGNODECOREFIELDS_H_ */
