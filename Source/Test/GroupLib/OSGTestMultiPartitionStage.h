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

#ifndef _OSGTESTMULTIPARTITIONSTAGE_H_
#define _OSGTESTMULTIPARTITIONSTAGE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTestMultiPartitionStageBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TestMultiPartitionStage class. See \ref
           PageGroupTestMultiPartitionStage for a description.
*/

class OSG_GROUP_DLLMAPPING TestMultiPartitionStage : public TestMultiPartitionStageBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TestMultiPartitionStageBase Inherited;
    typedef TestMultiPartitionStage     Self;

    typedef PointerBuilder<TestMultiPartitionStage>::ObjPtr           ObjPtr;
    typedef PointerBuilder<TestMultiPartitionStage>::ObjPtrConst      ObjPtrConst;

    typedef PointerBuilder<TestMultiPartitionStage>::ObjConstPtr      ObjConstPtr;
    typedef PointerBuilder<TestMultiPartitionStage>::ObjConstPtrConst ObjConstPtrConst;

    typedef PointerBuilder<TestMultiPartitionStage>::ObjPtrArg        ObjPtrArg;
    typedef PointerBuilder<TestMultiPartitionStage>::ObjPtrConstArg   ObjPtrConstArg;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TestMultiPartitionStageBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TestMultiPartitionStage(void);
    TestMultiPartitionStage(const TestMultiPartitionStage &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TestMultiPartitionStage(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class TestMultiPartitionStageBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TestMultiPartitionStage &source);
};

typedef TestMultiPartitionStage *TestMultiPartitionStageP;

typedef TestMultiPartitionStage::ObjPtr           TestMultiPartitionStagePtr;
typedef TestMultiPartitionStage::ObjPtrConst      TestMultiPartitionStagePtrConst;

typedef TestMultiPartitionStage::ObjConstPtr      TestMultiPartitionStageConstPtr;
typedef TestMultiPartitionStage::ObjConstPtrConst TestMultiPartitionStageConstPtrConst;

typedef TestMultiPartitionStage::ObjPtrArg        TestMultiPartitionStagePtrArg;
typedef TestMultiPartitionStage::ObjPtrConstArg   TestMultiPartitionStagePtrConstArg;

OSG_END_NAMESPACE

#include "OSGTestMultiPartitionStageBase.inl"
#include "OSGTestMultiPartitionStage.inl"

#endif /* _OSGTESTMULTIPARTITIONSTAGE_H_ */