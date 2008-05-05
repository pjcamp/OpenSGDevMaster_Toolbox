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
 **     Do not change this file, changes should be done in the derived      **
 **     class CameraDecorator
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGCAMERADECORATORBASE_H_
#define _OSGCAMERADECORATORBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGBaseTypes.h"

#include "OSGCamera.h" // Parent

#include "OSGCameraFields.h" // Decoratee type

#include "OSGCameraDecoratorFields.h"

OSG_BEGIN_NAMESPACE

class CameraDecorator;

//! \brief CameraDecorator Base Class.

class OSG_SYSTEM_DLLMAPPING CameraDecoratorBase : public Camera
{
  public:

    typedef Camera Inherited;
    typedef Camera ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(CameraDecorator);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        DecorateeFieldId        = Inherited::NextFieldId,
        NextFieldId             = DecorateeFieldId          + 1
    };

    static const OSG::BitVector DecorateeFieldMask =
        (TypeTraits<BitVector>::One << DecorateeFieldId);

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static FieldContainerType &getClassType   (void);
    static UInt32              getClassTypeId (void);
    static UInt16              getClassGroupId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                FieldContainer Get                            */
    /*! \{                                                                 */

    virtual       FieldContainerType &getType         (void);
    virtual const FieldContainerType &getType         (void) const;

    virtual       UInt32              getContainerSize(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

    virtual       const SFUnrecCameraPtr *getSFDecoratee(void) const;
    virtual const SFWeakNodePtr       *getSFBeacon         (void) const;
    virtual       SFWeakNodePtr       *editSFBeacon         (void);

#ifdef OSG_1_GET_COMPAT
    virtual       SFReal32            *getSFNear            (void);
#endif
    virtual       SFReal32            *editSFNear           (void);
    virtual const SFReal32            *getSFNear            (void) const;

#ifdef OSG_1_GET_COMPAT
    virtual       SFReal32            *getSFFar             (void);
#endif
    virtual       SFReal32            *editSFFar            (void);
    virtual const SFReal32            *getSFFar             (void) const;

    virtual             CameraPtr getDecoratee(void) const;

    virtual       NodePtr getBeacon         (void) const;

#ifdef OSG_1_GET_COMPAT
    virtual       Real32              &getNear            (void);
#endif
    virtual       Real32              &editNear           (void);
    virtual const Real32               getNear            (void) const;

#ifdef OSG_1_GET_COMPAT
    virtual       Real32              &getFar             (void);
#endif
    virtual       Real32              &editFar            (void);
    virtual const Real32               getFar             (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

    virtual       void setDecoratee      ( const CameraPtr &value );
    virtual void setBeacon         (const NodePtr value);
    virtual void setNear           (const Real32 &value);
    virtual void setFar            (const Real32 &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr Field Set                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    virtual UInt32 getBinSize (ConstFieldMaskArg  whichField);
    virtual void   copyToBin  (BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);
    virtual void   copyFromBin(BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);


    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static TypeObject _type;

    static void   classDescInserter(TypeObject &oType);
    static Char8 *getClassname     (void             );

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFUnrecCameraPtr _sfDecoratee;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    CameraDecoratorBase(void);
    CameraDecoratorBase(const CameraDecoratorBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CameraDecoratorBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const CameraDecorator *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleDecoratee (void) const;
    EditFieldHandlePtr editHandleDecoratee(void);

    GetFieldHandlePtr  getHandleBeacon          (void) const;
    EditFieldHandlePtr editHandleBeacon         (void);
    GetFieldHandlePtr  getHandleNear            (void) const;
    EditFieldHandlePtr editHandleNear           (void);
    GetFieldHandlePtr  getHandleFar             (void) const;
    EditFieldHandlePtr editHandleFar            (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);

            void execSync (      CameraDecoratorBase *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Aspect Create                            */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
    /*---------------------------------------------------------------------*/

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CameraDecoratorBase &source);
};

typedef CameraDecoratorBase *CameraDecoratorBaseP;

OSG_END_NAMESPACE

#endif /* _OSGCAMERADECORATORBASE_H_ */
