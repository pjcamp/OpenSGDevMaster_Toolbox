/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                       Copyright 2008 by OpenSG Forum                      *
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

#ifndef _OSGREFCOUNTPOINTER_H_
#define _OSGREFCOUNTPOINTER_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGBaseFunctions.h"

#include <boost/mpl/if.hpp>

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGReferenceCountPointerDecl.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainer
 */

template <class ObjectT>
class TransitPtr;

template <class ObjectT, 
          class RefCountPolicyT>
class RefCountPtr
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
  
    typedef ObjectT                                          Object;
    typedef RefCountPolicyT                                  RefCountPolicy;
    typedef RefCountPtr<Object, 
                        RefCountPolicy>                      Self;
    typedef TransitPtr<ObjectT>                              ObjectTransitPtr;
                                           
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
  
    RefCountPtr(void                          );
    RefCountPtr(Self              const &other);
   
    RefCountPtr(ObjectTransitPtr  const &other);

    template <class OtherObjectT>
    RefCountPtr(TransitPtr<OtherObjectT> const &other);

    explicit
    RefCountPtr(ObjectTransitPtr         &other);

    RefCountPtr(Object           * const  pObj );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Desctructor                                                  */
    /*! \{                                                                 */

    ~RefCountPtr(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Assignment                                                   */
    /*! \{                                                                 */
    
    Self &operator =(const Self             &       other    );
    Self &operator =(      Object           * const objectPtr);
    Self &operator =(const ObjectTransitPtr &       other    );

    template <class OtherObjectT, class OtherRefCountPolicyT>
    Self &operator =(const RefCountPtr<OtherObjectT,
                                OtherRefCountPolicyT> &refPtr);
   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Conversion                                                   */
    /*! \{                                                                 */
    
    operator Object *(void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */
    
    Object *operator->(void) const;
    Object &operator *(void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    Object *get (void                    ) const;
    void    set (Object * const objectPtr);
    
    void    swap(Self   &       other    );
       
#ifdef REFPTR_UNITTEST
    inline
    Object *getRaw(void) const
    {
        return _pObj;
    }
#endif

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

    /*---------------------------------------------------------------------*/
    /*! \name Member                                                       */
    /*! \{                                                                 */
    
    Object *_pObj;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name Internal Helpers                                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
  
};
       
template <class TargetObjectT, class SourceObjectT, class RP> inline
RefCountPtr<TargetObjectT, RP> dynamic_pointer_cast(
    RefCountPtr<SourceObjectT, RP> const &source);
 
template <class TargetObjectT, class SourceObjectT, class RP> inline
RefCountPtr<TargetObjectT, RP> static_pointer_cast(
    RefCountPtr<SourceObjectT, RP> const &source);
  
OSG_END_NAMESPACE

#include "OSGRefCountPtr.inl"

#endif // _OSGREFCOUNTPOINTER_H_
