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


#ifndef _OSGRESOLUTIONDISPLAYFILTERFIELDS_H_
#define _OSGRESOLUTIONDISPLAYFILTERFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGEffectGroupsDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class ResolutionDisplayFilter;

OSG_GEN_CONTAINERPTR(ResolutionDisplayFilter);

/*! \ingroup GrpEffectsGroupsDisplayFilterFieldTraits
    \ingroup GrpLibOSGEffectGroups
 */
template <>
struct FieldTraits<ResolutionDisplayFilter *> :
    public FieldTraitsFCPtrBase<ResolutionDisplayFilter *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ResolutionDisplayFilter *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_EFFECTGROUPS_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFResolutionDisplayFilterPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFResolutionDisplayFilterPtr"; }
};

template<> inline
const Char8 *FieldTraits<ResolutionDisplayFilter *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecResolutionDisplayFilterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ResolutionDisplayFilter *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecResolutionDisplayFilterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ResolutionDisplayFilter *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakResolutionDisplayFilterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ResolutionDisplayFilter *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdResolutionDisplayFilterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ResolutionDisplayFilter *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecResolutionDisplayFilterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ResolutionDisplayFilter *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecResolutionDisplayFilterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ResolutionDisplayFilter *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakResolutionDisplayFilterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ResolutionDisplayFilter *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdResolutionDisplayFilterPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields */
typedef PointerSField<ResolutionDisplayFilter *,
                      RecordedRefCountPolicy  > SFRecResolutionDisplayFilterPtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields */
typedef PointerSField<ResolutionDisplayFilter *,
                      UnrecordedRefCountPolicy> SFUnrecResolutionDisplayFilterPtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields */
typedef PointerSField<ResolutionDisplayFilter *,
                      WeakRefCountPolicy      > SFWeakResolutionDisplayFilterPtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields */
typedef PointerSField<ResolutionDisplayFilter *,
                      NoRefCountPolicy        > SFUncountedResolutionDisplayFilterPtr;


/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields */
typedef PointerMField<ResolutionDisplayFilter *,
                      RecordedRefCountPolicy  > MFRecResolutionDisplayFilterPtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields */
typedef PointerMField<ResolutionDisplayFilter *,
                      UnrecordedRefCountPolicy> MFUnrecResolutionDisplayFilterPtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields */
typedef PointerMField<ResolutionDisplayFilter *,
                      WeakRefCountPolicy      > MFWeakResolutionDisplayFilterPtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields */
typedef PointerMField<ResolutionDisplayFilter *,
                      NoRefCountPolicy        > MFUncountedResolutionDisplayFilterPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields \ingroup GrpLibOSGEffectGroups */
struct SFRecResolutionDisplayFilterPtr : 
    public PointerSField<ResolutionDisplayFilter *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields \ingroup GrpLibOSGEffectGroups */
struct SFUnrecResolutionDisplayFilterPtr : 
    public PointerSField<ResolutionDisplayFilter *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields \ingroup GrpLibOSGEffectGroups */
struct SFWeakResolutionDisplayFilterPtr :
    public PointerSField<ResolutionDisplayFilter *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields \ingroup GrpLibOSGEffectGroups */
struct SFUncountedResolutionDisplayFilterPtr :
    public PointerSField<ResolutionDisplayFilter *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields \ingroup GrpLibOSGEffectGroups */
struct MFRecResolutionDisplayFilterPtr :
    public PointerMField<ResolutionDisplayFilter *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields \ingroup GrpLibOSGEffectGroups */
struct MFUnrecResolutionDisplayFilterPtr :
    public PointerMField<ResolutionDisplayFilter *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields \ingroup GrpLibOSGEffectGroups */
struct MFWeakResolutionDisplayFilterPtr :
    public PointerMField<ResolutionDisplayFilter *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields \ingroup GrpLibOSGEffectGroups */
struct MFUncountedResolutionDisplayFilterPtr :
    public PointerMField<ResolutionDisplayFilter *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGRESOLUTIONDISPLAYFILTERFIELDS_H_ */
