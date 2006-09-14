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
 **     class TileCameraDecorator
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGTILECAMERADECORATORBASE_H_
#define _OSGTILECAMERADECORATORBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGWindowDef.h"

#include "OSGBaseTypes.h"

#include "OSGCameraDecorator.h" // Parent

#include "OSGReal32Fields.h" // Left type
#include "OSGReal32Fields.h" // Right type
#include "OSGReal32Fields.h" // Bottom type
#include "OSGReal32Fields.h" // Top type
#include "OSGUInt32Fields.h" // FullWidth type
#include "OSGUInt32Fields.h" // FullHeight type

#include "OSGTileCameraDecoratorFields.h"

OSG_BEGIN_NAMESPACE

class TileCameraDecorator;

//! \brief TileCameraDecorator Base Class.

class OSG_WINDOW_DLLMAPPING TileCameraDecoratorBase : public CameraDecorator
{
  public:

    typedef CameraDecorator Inherited;
    typedef CameraDecorator ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    typedef PointerFwdBuilder<CameraDecoratorPtr, 
                              CameraDecoratorConstPtr, 
                              TileCameraDecorator>::ObjPtr         ObjPtr;
    typedef PointerFwdBuilder<CameraDecoratorPtr, 
                              CameraDecoratorConstPtr, 
                              TileCameraDecorator>::ObjPtrConst    ObjPtrConst;
    typedef PointerFwdBuilder<CameraDecoratorPtr, 
                              CameraDecoratorConstPtr,
                              TileCameraDecorator>::ObjConstPtr    ObjConstPtr;
    typedef PointerFwdBuilder<CameraDecoratorPtr, 
                              CameraDecoratorConstPtr,
                              TileCameraDecorator>::ObjPtrArg      ObjPtrArg;
    typedef PointerFwdBuilder<CameraDecoratorPtr, 
                              CameraDecoratorConstPtr,
                              TileCameraDecorator>::ObjConstPtrArg ObjConstPtrArg;
    typedef PointerFwdBuilder<CameraDecoratorPtr, 
                              CameraDecoratorConstPtr,
                              TileCameraDecorator>::ObjPtrConstArg ObjPtrConstArg;

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        LeftFieldId = Inherited::NextFieldId,
        RightFieldId = LeftFieldId + 1,
        BottomFieldId = RightFieldId + 1,
        TopFieldId = BottomFieldId + 1,
        FullWidthFieldId = TopFieldId + 1,
        FullHeightFieldId = FullWidthFieldId + 1,
        NextFieldId = FullHeightFieldId + 1
    };

    static const OSG::BitVector LeftFieldMask = 
        (TypeTraits<BitVector>::One << LeftFieldId);
    static const OSG::BitVector RightFieldMask = 
        (TypeTraits<BitVector>::One << RightFieldId);
    static const OSG::BitVector BottomFieldMask = 
        (TypeTraits<BitVector>::One << BottomFieldId);
    static const OSG::BitVector TopFieldMask = 
        (TypeTraits<BitVector>::One << TopFieldId);
    static const OSG::BitVector FullWidthFieldMask = 
        (TypeTraits<BitVector>::One << FullWidthFieldId);
    static const OSG::BitVector FullHeightFieldMask = 
        (TypeTraits<BitVector>::One << FullHeightFieldId);
    static const OSG::BitVector NextFieldMask = 
        (TypeTraits<BitVector>::One << NextFieldId);


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


#ifdef OSG_1_COMPAT
           SFReal32 *getSFLeft(void);
#endif
           SFReal32 *editSFLeft(void);
     const SFReal32 *getSFLeft (void) const;

#ifdef OSG_1_COMPAT
           SFReal32 *getSFRight(void);
#endif
           SFReal32 *editSFRight(void);
     const SFReal32 *getSFRight (void) const;

#ifdef OSG_1_COMPAT
           SFReal32 *getSFBottom(void);
#endif
           SFReal32 *editSFBottom(void);
     const SFReal32 *getSFBottom (void) const;

#ifdef OSG_1_COMPAT
           SFReal32 *getSFTop(void);
#endif
           SFReal32 *editSFTop(void);
     const SFReal32 *getSFTop (void) const;

#ifdef OSG_1_COMPAT
           SFUInt32 *getSFFullWidth(void);
#endif
           SFUInt32 *editSFFullWidth(void);
     const SFUInt32 *getSFFullWidth (void) const;

#ifdef OSG_1_COMPAT
           SFUInt32 *getSFFullHeight(void);
#endif
           SFUInt32 *editSFFullHeight(void);
     const SFUInt32 *getSFFullHeight (void) const;


#ifdef OSG_1_COMPAT
           Real32 &getLeft(void);
#endif
           Real32 &editLeft(void);
     const Real32 &getLeft (void) const;

#ifdef OSG_1_COMPAT
           Real32 &getRight(void);
#endif
           Real32 &editRight(void);
     const Real32 &getRight (void) const;

#ifdef OSG_1_COMPAT
           Real32 &getBottom(void);
#endif
           Real32 &editBottom(void);
     const Real32 &getBottom (void) const;

#ifdef OSG_1_COMPAT
           Real32 &getTop(void);
#endif
           Real32 &editTop(void);
     const Real32 &getTop (void) const;

#ifdef OSG_1_COMPAT
           UInt32 &getFullWidth(void);
#endif
           UInt32 &editFullWidth(void);
     const UInt32 &getFullWidth (void) const;

#ifdef OSG_1_COMPAT
           UInt32 &getFullHeight(void);
#endif
           UInt32 &editFullHeight(void);
     const UInt32 &getFullHeight (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setLeft(const Real32 &value);
     void setRight(const Real32 &value);
     void setBottom(const Real32 &value);
     void setTop(const Real32 &value);
     void setFullWidth(const UInt32 &value);
     void setFullHeight(const UInt32 &value);

    /*! \}                                                                 */
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
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  TileCameraDecoratorPtr create     (void); 
    static  TileCameraDecoratorPtr createEmpty(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Copy                                   */
    /*! \{                                                                 */

    virtual FieldContainerPtr shallowCopy(void) const; 

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static TypeObject _type;

    static void   classDescInserter(TypeObject &oType);
    static Char8 *getClassname     (void             );

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFReal32 _sfLeft;
    SFReal32 _sfRight;
    SFReal32 _sfBottom;
    SFReal32 _sfTop;
    SFUInt32 _sfFullWidth;
    SFUInt32 _sfFullHeight;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TileCameraDecoratorBase(void);
    TileCameraDecoratorBase(const TileCameraDecoratorBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TileCameraDecoratorBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#ifdef OSG_MT_FIELDCONTAINERPTR
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo,
                                 UInt32             uiCopyOffset);

            void execSync (      TileCameraDecoratorBase *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo,
                                 UInt32             uiCopyOffset);
#endif
#ifdef OSG_MT_CPTR_ASPECT
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);

            void execSync (      TileCameraDecoratorBase *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

#if 0
    virtual void execBeginEditV(ConstFieldMaskArg whichField, 
                                UInt32            uiAspect,
                                UInt32            uiContainerSize);

            void execBeginEdit (ConstFieldMaskArg whichField, 
                                UInt32            uiAspect,
                                UInt32            uiContainerSize);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Aspect Create                            */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual FieldContainerPtr createAspectCopy(void) const;
#endif

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

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TileCameraDecoratorBase &source);
};

typedef TileCameraDecoratorBase *TileCameraDecoratorBaseP;

/** Type specific RefPtr type for TileCameraDecorator. */
typedef RefPtr<TileCameraDecoratorPtr> TileCameraDecoratorRefPtr;

typedef osgIF<
    TileCameraDecoratorBase::isNodeCore,

    CoredNodePtr<TileCameraDecorator>,
    FieldContainer::attempt_to_create_CoredNodePtr_on_non_NodeCore_FC>::_IRet

        TileCameraDecoratorNodePtr;

OSG_END_NAMESPACE

#define OSGTILECAMERADECORATORBASE_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGTILECAMERADECORATORBASE_H_ */
