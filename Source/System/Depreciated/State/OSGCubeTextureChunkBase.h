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
 **     class CubeTextureChunk
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGCUBETEXTURECHUNKBASE_H_
#define _OSGCUBETEXTURECHUNKBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGStateDef.h"

#include "OSGBaseTypes.h"

#include "OSGTextureChunk.h" // Parent

#include "OSGImageFields.h" // PosZImage type
#include "OSGImageFields.h" // PosXImage type
#include "OSGImageFields.h" // NegXImage type
#include "OSGImageFields.h" // PosYImage type
#include "OSGImageFields.h" // NegYImage type
#include "OSGBoolFields.h" // IsReflectionMap type

#include "OSGCubeTextureChunkFields.h"

OSG_BEGIN_NAMESPACE

class CubeTextureChunk;

//! \brief CubeTextureChunk Base Class.

class OSG_STATE_DLLMAPPING CubeTextureChunkBase : public TextureChunk
{
  public:

    typedef TextureChunk Inherited;
    typedef TextureChunk ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    typedef PointerFwdBuilder<TextureChunkPtr, 
                              TextureChunkConstPtr, 
                              CubeTextureChunk>::ObjPtr         ObjPtr;
    typedef PointerFwdBuilder<TextureChunkPtr, 
                              TextureChunkConstPtr, 
                              CubeTextureChunk>::ObjPtrConst    ObjPtrConst;
    typedef PointerFwdBuilder<TextureChunkPtr, 
                              TextureChunkConstPtr,
                              CubeTextureChunk>::ObjConstPtr    ObjConstPtr;
    typedef PointerFwdBuilder<TextureChunkPtr, 
                              TextureChunkConstPtr,
                              CubeTextureChunk>::ObjPtrArg      ObjPtrArg;
    typedef PointerFwdBuilder<TextureChunkPtr, 
                              TextureChunkConstPtr,
                              CubeTextureChunk>::ObjConstPtrArg ObjConstPtrArg;
    typedef PointerFwdBuilder<TextureChunkPtr, 
                              TextureChunkConstPtr,
                              CubeTextureChunk>::ObjPtrConstArg ObjPtrConstArg;

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        PosZImageFieldId = Inherited::NextFieldId,
        PosXImageFieldId = PosZImageFieldId + 1,
        NegXImageFieldId = PosXImageFieldId + 1,
        PosYImageFieldId = NegXImageFieldId + 1,
        NegYImageFieldId = PosYImageFieldId + 1,
        IsReflectionMapFieldId = NegYImageFieldId + 1,
        NextFieldId = IsReflectionMapFieldId + 1
    };

    static const OSG::BitVector PosZImageFieldMask = 
        (TypeTraits<BitVector>::One << PosZImageFieldId);
    static const OSG::BitVector PosXImageFieldMask = 
        (TypeTraits<BitVector>::One << PosXImageFieldId);
    static const OSG::BitVector NegXImageFieldMask = 
        (TypeTraits<BitVector>::One << NegXImageFieldId);
    static const OSG::BitVector PosYImageFieldMask = 
        (TypeTraits<BitVector>::One << PosYImageFieldId);
    static const OSG::BitVector NegYImageFieldMask = 
        (TypeTraits<BitVector>::One << NegYImageFieldId);
    static const OSG::BitVector IsReflectionMapFieldMask = 
        (TypeTraits<BitVector>::One << IsReflectionMapFieldId);
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

     const SFImagePtr *getSFPosZImage (void) const;
     const SFImagePtr *getSFPosXImage (void) const;
     const SFImagePtr *getSFNegXImage (void) const;
     const SFImagePtr *getSFPosYImage (void) const;
     const SFImagePtr *getSFNegYImage (void) const;

#ifdef OSG_1_COMPAT
           SFBool *getSFIsReflectionMap(void);
#endif
           SFBool *editSFIsReflectionMap(void);
     const SFBool *getSFIsReflectionMap (void) const;


           ImagePtrConst getPosZImage(void) const;

           ImagePtrConst getPosXImage(void) const;

           ImagePtrConst getNegXImage(void) const;

           ImagePtrConst getPosYImage(void) const;

           ImagePtrConst getNegYImage(void) const;

#ifdef OSG_1_COMPAT
           bool &getIsReflectionMap(void);
#endif
           bool &editIsReflectionMap(void);
     const bool &getIsReflectionMap (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setPosZImage(ImagePtrConstArg value);
     void setPosXImage(ImagePtrConstArg value);
     void setNegXImage(ImagePtrConstArg value);
     void setPosYImage(ImagePtrConstArg value);
     void setNegYImage(ImagePtrConstArg value);
     void setIsReflectionMap(const bool &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr Field Set                                 */
    /*! \{                                                                 */

    virtual void pushToField     (      FieldContainerPtrConstArg pNewElement, 
                                  const UInt32                    uiFieldId  );

    virtual void insertIntoMField(const UInt32                    uiIndex, 
                                        FieldContainerPtrConstArg pNewElement, 
                                  const UInt32                    uiFieldId  );

    virtual void replaceInMField (const UInt32                    uiIndex,
                                        FieldContainerPtrConstArg pNewElement, 
                                  const UInt32                    uiFieldId  );

    virtual void replaceInMField (      FieldContainerPtrConstArg pOldElement,
                                        FieldContainerPtrConstArg pNewElement, 
                                  const UInt32                    uiFieldId  );

    virtual void removeFromMField(const UInt32                    uiIndex, 
                                  const UInt32                    uiFieldId  );
    
    virtual void removeFromMField(      FieldContainerPtrConstArg pElement, 
                                  const UInt32                    uiFieldId  );

    virtual void clearField      (const UInt32                    uiFieldId  );

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
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  CubeTextureChunkPtr create     (void); 
    static  CubeTextureChunkPtr createEmpty(void); 

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

    SFImagePtr _sfPosZImage;
    SFImagePtr _sfPosXImage;
    SFImagePtr _sfNegXImage;
    SFImagePtr _sfPosYImage;
    SFImagePtr _sfNegYImage;
    SFBool _sfIsReflectionMap;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    CubeTextureChunkBase(void);
    CubeTextureChunkBase(const CubeTextureChunkBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CubeTextureChunkBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const CubeTextureChunk *source = NULL);

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

            void execSync (      CubeTextureChunkBase *pFrom,
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

            void execSync (      CubeTextureChunkBase *pFrom,
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
    void operator =(const CubeTextureChunkBase &source);
};

typedef CubeTextureChunkBase *CubeTextureChunkBaseP;

/** Type specific RefPtr type for CubeTextureChunk. */
typedef RefPtr<CubeTextureChunkPtr> CubeTextureChunkRefPtr;

typedef osgIF<
    CubeTextureChunkBase::isNodeCore,

    CoredNodePtr<CubeTextureChunk>,
    FieldContainer::attempt_to_create_CoredNodePtr_on_non_NodeCore_FC>::_IRet

        CubeTextureChunkNodePtr;

OSG_END_NAMESPACE

#define OSGCUBETEXTURECHUNKBASE_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGCUBETEXTURECHUNKBASE_H_ */