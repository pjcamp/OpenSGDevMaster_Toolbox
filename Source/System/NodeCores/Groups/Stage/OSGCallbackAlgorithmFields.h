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


#ifndef _OSGCALLBACKALGORITHMFIELDS_H_
#define _OSGCALLBACKALGORITHMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGGroupDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class CallbackAlgorithm;

OSG_GEN_CONTAINERPTR(CallbackAlgorithm);

/*! \ingroup GrpGroupStageFieldTraits
    \ingroup GrpLibOSGGroup
 */
template <>
struct FieldTraits<CallbackAlgorithm *> :
    public FieldTraitsFCPtrBase<CallbackAlgorithm *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<CallbackAlgorithm *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_GROUP_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFCallbackAlgorithmPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFCallbackAlgorithmPtr"; }
};

template<> inline
const Char8 *FieldTraits<CallbackAlgorithm *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecCallbackAlgorithmPtr"; 
}

template<> inline
const Char8 *FieldTraits<CallbackAlgorithm *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecCallbackAlgorithmPtr"; 
}

template<> inline
const Char8 *FieldTraits<CallbackAlgorithm *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakCallbackAlgorithmPtr"; 
}

template<> inline
const Char8 *FieldTraits<CallbackAlgorithm *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdCallbackAlgorithmPtr"; 
}

template<> inline
const Char8 *FieldTraits<CallbackAlgorithm *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecCallbackAlgorithmPtr"; 
}

template<> inline
const Char8 *FieldTraits<CallbackAlgorithm *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecCallbackAlgorithmPtr"; 
}

template<> inline
const Char8 *FieldTraits<CallbackAlgorithm *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakCallbackAlgorithmPtr"; 
}

template<> inline
const Char8 *FieldTraits<CallbackAlgorithm *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdCallbackAlgorithmPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpGroupStageFieldSFields */
typedef PointerSField<CallbackAlgorithm *,
                      RecordedRefCountPolicy  > SFRecCallbackAlgorithmPtr;
/*! \ingroup GrpGroupStageFieldSFields */
typedef PointerSField<CallbackAlgorithm *,
                      UnrecordedRefCountPolicy> SFUnrecCallbackAlgorithmPtr;
/*! \ingroup GrpGroupStageFieldSFields */
typedef PointerSField<CallbackAlgorithm *,
                      WeakRefCountPolicy      > SFWeakCallbackAlgorithmPtr;
/*! \ingroup GrpGroupStageFieldSFields */
typedef PointerSField<CallbackAlgorithm *,
                      NoRefCountPolicy        > SFUncountedCallbackAlgorithmPtr;


/*! \ingroup GrpGroupStageFieldMFields */
typedef PointerMField<CallbackAlgorithm *,
                      RecordedRefCountPolicy  > MFRecCallbackAlgorithmPtr;
/*! \ingroup GrpGroupStageFieldMFields */
typedef PointerMField<CallbackAlgorithm *,
                      UnrecordedRefCountPolicy> MFUnrecCallbackAlgorithmPtr;
/*! \ingroup GrpGroupStageFieldMFields */
typedef PointerMField<CallbackAlgorithm *,
                      WeakRefCountPolicy      > MFWeakCallbackAlgorithmPtr;
/*! \ingroup GrpGroupStageFieldMFields */
typedef PointerMField<CallbackAlgorithm *,
                      NoRefCountPolicy        > MFUncountedCallbackAlgorithmPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpGroupStageFieldSFields \ingroup GrpLibOSGGroup */
struct SFRecCallbackAlgorithmPtr : 
    public PointerSField<CallbackAlgorithm *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpGroupStageFieldSFields \ingroup GrpLibOSGGroup */
struct SFUnrecCallbackAlgorithmPtr : 
    public PointerSField<CallbackAlgorithm *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpGroupStageFieldSFields \ingroup GrpLibOSGGroup */
struct SFWeakCallbackAlgorithmPtr :
    public PointerSField<CallbackAlgorithm *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpGroupStageFieldSFields \ingroup GrpLibOSGGroup */
struct SFUncountedCallbackAlgorithmPtr :
    public PointerSField<CallbackAlgorithm *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpGroupStageFieldMFields \ingroup GrpLibOSGGroup */
struct MFRecCallbackAlgorithmPtr :
    public PointerMField<CallbackAlgorithm *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpGroupStageFieldMFields \ingroup GrpLibOSGGroup */
struct MFUnrecCallbackAlgorithmPtr :
    public PointerMField<CallbackAlgorithm *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpGroupStageFieldMFields \ingroup GrpLibOSGGroup */
struct MFWeakCallbackAlgorithmPtr :
    public PointerMField<CallbackAlgorithm *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpGroupStageFieldMFields \ingroup GrpLibOSGGroup */
struct MFUncountedCallbackAlgorithmPtr :
    public PointerMField<CallbackAlgorithm *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGCALLBACKALGORITHMFIELDS_H_ */
