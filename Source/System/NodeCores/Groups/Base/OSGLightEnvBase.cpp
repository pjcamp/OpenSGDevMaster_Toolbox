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
 **     class LightEnv!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILELIGHTENVINST

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>




#include "OSGLightEnvBase.h"
#include "OSGLightEnv.h"

OSG_USING_NAMESPACE


LightEnvBase::TypeObject LightEnvBase::_type(true,
    LightEnvBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    (PrototypeCreateF) &LightEnvBase::createEmpty,
    LightEnv::initMethod,
    NULL,
    false);

/*------------------------------ get -----------------------------------*/

FieldContainerType &LightEnvBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &LightEnvBase::getType(void) const 
{
    return _type;
} 

UInt32 LightEnvBase::getContainerSize(void) const 
{ 
    return sizeof(LightEnv); 
}

/*------------------------- decorator get ------------------------------*/




/*------------------------------ access -----------------------------------*/

UInt32 LightEnvBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void LightEnvBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void LightEnvBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create an empty new instance of the class, do not copy the prototype
LightEnvPtr LightEnvBase::createEmpty(void) 
{ 
    LightEnvPtr returnValue; 
    
    newPtr<LightEnv>(returnValue); 

    return returnValue; 
}

FieldContainerPtr LightEnvBase::shallowCopy(void) const 
{ 
    LightEnvPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const LightEnv *>(this)); 

    return returnValue; 
}



/*------------------------- constructors ----------------------------------*/

LightEnvBase::LightEnvBase(void) :
    Inherited()
{
}

LightEnvBase::LightEnvBase(const LightEnvBase &source) :
    Inherited(source)
{
}

/*-------------------------- destructors ----------------------------------*/

LightEnvBase::~LightEnvBase(void)
{
}


#ifdef OSG_MT_FIELDCONTAINERPTR
void LightEnvBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo,
                                        UInt32             uiCopyOffset)
{
    this->execSync(static_cast<LightEnvBase *>(&oFrom),
                   whichField, 
                   syncMode, 
                   uiSyncInfo,
                   uiCopyOffset);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
void LightEnvBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<LightEnvBase *>(&oFrom), 
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

#if 0
void LightEnvBase::execBeginEditV(ConstFieldMaskArg whichField,
                                       UInt32            uiAspect,
                                       UInt32            uiContainerSize)
{
    this->execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
FieldContainerPtr LightEnvBase::createAspectCopy(void) const
{
    LightEnvPtr returnValue; 

    newAspectCopy(returnValue, 
                  dynamic_cast<const LightEnv *>(this)); 

    return returnValue; 
}
#endif

void LightEnvBase::resolveLinks(void)
{
    Inherited::resolveLinks();
}


OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<LightEnvPtr>::_type("LightEnvPtr", "NodeCorePtr");
#endif


OSG_END_NAMESPACE


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGLIGHTENVBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGLIGHTENVBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGLIGHTENVFIELDS_HEADER_CVSID;
}
