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


#ifndef _OSGHARDWARECONTEXTFIELDS_H_
#define _OSGHARDWARECONTEXTFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGBaseDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class HardwareContext;

OSG_GEN_CONTAINERPTR(HardwareContext);

/*! \ingroup GrpBaseHardwareContextFieldTraits
    \ingroup GrpLibOSGBase
 */
template <>
struct FieldTraits<HardwareContext *> :
    public FieldTraitsFCPtrBase<HardwareContext *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<HardwareContext *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_BASE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFHardwareContextPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFHardwareContextPtr"; }
};

template<> inline
const Char8 *FieldTraits<HardwareContext *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecHardwareContextPtr"; 
}

template<> inline
const Char8 *FieldTraits<HardwareContext *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecHardwareContextPtr"; 
}

template<> inline
const Char8 *FieldTraits<HardwareContext *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakHardwareContextPtr"; 
}

template<> inline
const Char8 *FieldTraits<HardwareContext *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdHardwareContextPtr"; 
}

template<> inline
const Char8 *FieldTraits<HardwareContext *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecHardwareContextPtr"; 
}

template<> inline
const Char8 *FieldTraits<HardwareContext *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecHardwareContextPtr"; 
}

template<> inline
const Char8 *FieldTraits<HardwareContext *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakHardwareContextPtr"; 
}

template<> inline
const Char8 *FieldTraits<HardwareContext *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdHardwareContextPtr"; 
}


/*! \ingroup GrpBaseHardwareContextFieldTraits
 */
template <>
struct FieldTraits<HardwareContext *, 1> :
    public FieldTraitsFCPtrBase<HardwareContext *, 1>
{
  private:

  public:
    typedef FieldTraits<HardwareContext *, 1>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_BASE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);
};

template<> inline
const Char8 *FieldTraits<HardwareContext *, 1>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecChildHardwareContextPtr"; 
}

template<> inline
const Char8 *FieldTraits<HardwareContext *, 1>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecChildHardwareContextPtr"; 
}

template<> inline
const Char8 *FieldTraits<HardwareContext *, 1>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakChildHardwareContextPtr"; 
}

template<> inline
const Char8 *FieldTraits<HardwareContext *, 1>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdChildHardwareContextPtr"; 
}

template<> inline
const Char8 *FieldTraits<HardwareContext *, 1>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecChildHardwareContextPtr"; 
}

template<> inline
const Char8 *FieldTraits<HardwareContext *, 1>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecChildHardwareContextPtr"; 
}

template<> inline
const Char8 *FieldTraits<HardwareContext *, 1>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakChildHardwareContextPtr"; 
}

template<> inline
const Char8 *FieldTraits<HardwareContext *, 1>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdChildHardwareContextPtr"; 
}


/*! \ingroup GrpBaseHardwareContextFieldTraits
 */
template <>
struct FieldTraits<HardwareContext *, 2> : 
    public FieldTraitsFCPtrBase<HardwareContext *, 2>
{
  private:

    static  DataType                                _type;

  public:

    static const bool bIsPointerField = true;

    typedef FieldTraits<HardwareContext *, 2>        Self;


    enum             { Convertible = Self::NotConvertible };
    
    static OSG_BASE_DLLMAPPING
                 DataType &getType (void);

    static const Char8    *getSName(void) 
    {
        return "SFParentHardwareContextPtr"; 
    }

    static const Char8    *getMName(void) 
    { 
        return "MFParentHardwareContextPtr"; 
    }
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpBaseHardwareContextFieldSFields */
typedef PointerSField<HardwareContext *,
                      RecordedRefCountPolicy  > SFRecHardwareContextPtr;
/*! \ingroup GrpBaseHardwareContextFieldSFields */
typedef PointerSField<HardwareContext *,
                      UnrecordedRefCountPolicy> SFUnrecHardwareContextPtr;
/*! \ingroup GrpBaseHardwareContextFieldSFields */
typedef PointerSField<HardwareContext *,
                      WeakRefCountPolicy      > SFWeakHardwareContextPtr;
/*! \ingroup GrpBaseHardwareContextFieldSFields */
typedef PointerSField<HardwareContext *,
                      NoRefCountPolicy        > SFUncountedHardwareContextPtr;


/*! \ingroup GrpBaseHardwareContextFieldMFields */
typedef PointerMField<HardwareContext *,
                      RecordedRefCountPolicy  > MFRecHardwareContextPtr;
/*! \ingroup GrpBaseHardwareContextFieldMFields */
typedef PointerMField<HardwareContext *,
                      UnrecordedRefCountPolicy> MFUnrecHardwareContextPtr;
/*! \ingroup GrpBaseHardwareContextFieldMFields */
typedef PointerMField<HardwareContext *,
                      WeakRefCountPolicy      > MFWeakHardwareContextPtr;
/*! \ingroup GrpBaseHardwareContextFieldMFields */
typedef PointerMField<HardwareContext *,
                      NoRefCountPolicy        > MFUncountedHardwareContextPtr;



/*! \ingroup GrpBaseHardwareContextFieldSFields */
typedef ChildPointerSField<
          HardwareContext *, 
          UnrecordedRefCountPolicy,
          1             > SFUnrecChildHardwareContextPtr;


/*! \ingroup GrpBaseHardwareContextFieldMFields */
typedef ChildPointerMField<
          HardwareContext *, 
          UnrecordedRefCountPolicy,
          1             > MFUnrecChildHardwareContextPtr;


/*! \ingroup GrpBaseHardwareContextFieldSFields */
typedef ParentPointerSField<
          HardwareContext *, 
          NoRefCountPolicy,
          2    > SFParentHardwareContextPtr;

/*! \ingroup GrpBaseHardwareContextFieldMFields */
typedef ParentPointerMField<
          HardwareContext *, 
          NoRefCountPolicy,
          2    > MFParentHardwareContextPtr;



#else // these are the doxygen hacks

/*! \ingroup GrpBaseHardwareContextFieldSFields \ingroup GrpLibOSGBase */
struct SFRecHardwareContextPtr : 
    public PointerSField<HardwareContext *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpBaseHardwareContextFieldSFields \ingroup GrpLibOSGBase */
struct SFUnrecHardwareContextPtr : 
    public PointerSField<HardwareContext *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpBaseHardwareContextFieldSFields \ingroup GrpLibOSGBase */
struct SFWeakHardwareContextPtr :
    public PointerSField<HardwareContext *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpBaseHardwareContextFieldSFields \ingroup GrpLibOSGBase */
struct SFUncountedHardwareContextPtr :
    public PointerSField<HardwareContext *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpBaseHardwareContextFieldMFields \ingroup GrpLibOSGBase */
struct MFRecHardwareContextPtr :
    public PointerMField<HardwareContext *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpBaseHardwareContextFieldMFields \ingroup GrpLibOSGBase */
struct MFUnrecHardwareContextPtr :
    public PointerMField<HardwareContext *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpBaseHardwareContextFieldMFields \ingroup GrpLibOSGBase */
struct MFWeakHardwareContextPtr :
    public PointerMField<HardwareContext *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpBaseHardwareContextFieldMFields \ingroup GrpLibOSGBase */
struct MFUncountedHardwareContextPtr :
    public PointerMField<HardwareContext *,
                         NoRefCountPolicy        > {};



/*! \ingroup GrpBaseHardwareContextFieldSFields \ingroup GrpLibOSGBase */
struct SFUnrecChildHardwareContextPtr :
    public ChildPointerSField<
        HardwareContext *, 
        UnrecordedRefCountPolicy,
        1             > {};


/*! \ingroup GrpBaseHardwareContextFieldMFields \ingroup GrpLibOSGBase */
struct MFUnrecChildHardwareContextPtr :
    public ChildPointerMField<
        HardwareContext *, 
        UnrecordedRefCountPolicy,
        1             > {};


/*! \ingroup GrpBaseHardwareContextFieldSFields \ingroup GrpLibOSGBase */
struct SFParentHardwareContextPtr :
    public ParentPointerSField<
        HardwareContext *, 
        NoRefCountPolicy,
        2    > {};

/*! \ingroup GrpBaseHardwareContextFieldMFields \ingroup GrpLibOSGBase */
struct MFParentHardwareContextPtr :
    public  ParentPointerMField<
        HardwareContext *, 
        NoRefCountPolicy,
        2    > {};


#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGHARDWARECONTEXTFIELDS_H_ */
