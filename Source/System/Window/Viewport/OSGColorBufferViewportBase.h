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
 **     class ColorBufferViewport
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGCOLORBUFFERVIEWPORTBASE_H_
#define _OSGCOLORBUFFERVIEWPORTBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGWindowDef.h"

#include "OSGBaseTypes.h"

#include "OSGViewport.h" // Parent

#include "OSGBoolFields.h" // Red type
#include "OSGBoolFields.h" // Blue type
#include "OSGBoolFields.h" // Green type
#include "OSGBoolFields.h" // Alpha type

#include "OSGColorBufferViewportFields.h"

OSG_BEGIN_NAMESPACE

class ColorBufferViewport;

//! \brief ColorBufferViewport Base Class.

class OSG_WINDOW_DLLMAPPING ColorBufferViewportBase : public Viewport
{
  public:

    typedef Viewport Inherited;
    typedef Viewport ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    typedef PointerFwdBuilder<ViewportPtr, 
                              ViewportConstPtr, 
                              ColorBufferViewport>::ObjPtr         ObjPtr;
    typedef PointerFwdBuilder<ViewportPtr, 
                              ViewportConstPtr, 
                              ColorBufferViewport>::ObjPtrConst    ObjPtrConst;
    typedef PointerFwdBuilder<ViewportPtr, 
                              ViewportConstPtr,
                              ColorBufferViewport>::ObjConstPtr    ObjConstPtr;
    typedef PointerFwdBuilder<ViewportPtr, 
                              ViewportConstPtr,
                              ColorBufferViewport>::ObjPtrArg      ObjPtrArg;
    typedef PointerFwdBuilder<ViewportPtr, 
                              ViewportConstPtr,
                              ColorBufferViewport>::ObjConstPtrArg ObjConstPtrArg;
    typedef PointerFwdBuilder<ViewportPtr, 
                              ViewportConstPtr,
                              ColorBufferViewport>::ObjPtrConstArg ObjPtrConstArg;

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        RedFieldId = Inherited::NextFieldId,
        BlueFieldId = RedFieldId + 1,
        GreenFieldId = BlueFieldId + 1,
        AlphaFieldId = GreenFieldId + 1,
        NextFieldId = AlphaFieldId + 1
    };

    static const OSG::BitVector RedFieldMask = 
        (TypeTraits<BitVector>::One << RedFieldId);
    static const OSG::BitVector BlueFieldMask = 
        (TypeTraits<BitVector>::One << BlueFieldId);
    static const OSG::BitVector GreenFieldMask = 
        (TypeTraits<BitVector>::One << GreenFieldId);
    static const OSG::BitVector AlphaFieldMask = 
        (TypeTraits<BitVector>::One << AlphaFieldId);
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
           SFBool *getSFRed(void);
#endif
           SFBool *editSFRed(void);
     const SFBool *getSFRed (void) const;

#ifdef OSG_1_COMPAT
           SFBool *getSFBlue(void);
#endif
           SFBool *editSFBlue(void);
     const SFBool *getSFBlue (void) const;

#ifdef OSG_1_COMPAT
           SFBool *getSFGreen(void);
#endif
           SFBool *editSFGreen(void);
     const SFBool *getSFGreen (void) const;

#ifdef OSG_1_COMPAT
           SFBool *getSFAlpha(void);
#endif
           SFBool *editSFAlpha(void);
     const SFBool *getSFAlpha (void) const;


#ifdef OSG_1_COMPAT
           bool &getRed(void);
#endif
           bool &editRed(void);
     const bool &getRed (void) const;

#ifdef OSG_1_COMPAT
           bool &getBlue(void);
#endif
           bool &editBlue(void);
     const bool &getBlue (void) const;

#ifdef OSG_1_COMPAT
           bool &getGreen(void);
#endif
           bool &editGreen(void);
     const bool &getGreen (void) const;

#ifdef OSG_1_COMPAT
           bool &getAlpha(void);
#endif
           bool &editAlpha(void);
     const bool &getAlpha (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setRed(const bool &value);
     void setBlue(const bool &value);
     void setGreen(const bool &value);
     void setAlpha(const bool &value);

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

    static  ColorBufferViewportPtr create     (void); 
    static  ColorBufferViewportPtr createEmpty(void); 

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

    SFBool _sfRed;
    SFBool _sfBlue;
    SFBool _sfGreen;
    SFBool _sfAlpha;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ColorBufferViewportBase(void);
    ColorBufferViewportBase(const ColorBufferViewportBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ColorBufferViewportBase(void); 

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

            void execSync (      ColorBufferViewportBase *pFrom,
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

            void execSync (      ColorBufferViewportBase *pFrom,
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
    void operator =(const ColorBufferViewportBase &source);
};

typedef ColorBufferViewportBase *ColorBufferViewportBaseP;

/** Type specific RefPtr type for ColorBufferViewport. */
typedef RefPtr<ColorBufferViewportPtr> ColorBufferViewportRefPtr;

typedef osgIF<
    ColorBufferViewportBase::isNodeCore,

    CoredNodePtr<ColorBufferViewport>,
    FieldContainer::attempt_to_create_CoredNodePtr_on_non_NodeCore_FC>::_IRet

        ColorBufferViewportNodePtr;

OSG_END_NAMESPACE

#define OSGCOLORBUFFERVIEWPORTBASE_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGCOLORBUFFERVIEWPORTBASE_H_ */
