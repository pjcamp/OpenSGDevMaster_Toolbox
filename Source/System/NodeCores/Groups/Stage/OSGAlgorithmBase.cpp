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
 **     class Algorithm!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILEALGORITHMINST

#include <stdlib.h>
#include <stdio.h>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>




#include "OSGAlgorithmBase.h"
#include "OSGAlgorithm.h"

OSG_USING_NAMESPACE


AlgorithmBase::TypeObject AlgorithmBase::_type(true,
    AlgorithmBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    NULL, 
    Algorithm::initMethod,
    NULL,
    false,
    "<?xml version=\"1.0\"?>\n"
"\n"
"<FieldContainer\n"
"	name=\"Algorithm\"\n"
"	parent=\"FieldContainer\"\n"
"	library=\"Group\"\n"
"	pointerfieldtypes=\"both\"\n"
"	structure=\"abstract\"\n"
"	systemcomponent=\"true\"\n"
"	parentsystemcomponent=\"true\"\n"
"	decoratable=\"false\"\n"
"	useLocalIncludes=\"false\"\n"
"    isNodeCore=\"true\"\n"
">\n"
"</FieldContainer>\n"
,
    "" 
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &AlgorithmBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &AlgorithmBase::getType(void) const 
{
    return _type;
} 

UInt32 AlgorithmBase::getContainerSize(void) const 
{ 
    return sizeof(Algorithm); 
}

/*------------------------- decorator get ------------------------------*/




/*------------------------------ access -----------------------------------*/

UInt32 AlgorithmBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void AlgorithmBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void AlgorithmBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}



/*------------------------- constructors ----------------------------------*/

AlgorithmBase::AlgorithmBase(void) :
    Inherited()
{
}

AlgorithmBase::AlgorithmBase(const AlgorithmBase &source) :
    Inherited(source)
{
}

/*-------------------------- destructors ----------------------------------*/

AlgorithmBase::~AlgorithmBase(void)
{
}


#ifdef OSG_MT_FIELDCONTAINERPTR
void AlgorithmBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo,
                                        UInt32             uiCopyOffset)
{
    this->execSync(static_cast<AlgorithmBase *>(&oFrom),
                   whichField, 
                   syncMode, 
                   uiSyncInfo,
                   uiCopyOffset);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
void AlgorithmBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<AlgorithmBase *>(&oFrom), 
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

#if 0
void AlgorithmBase::execBeginEditV(ConstFieldMaskArg whichField,
                                       UInt32            uiAspect,
                                       UInt32            uiContainerSize)
{
    this->execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif


void AlgorithmBase::resolveLinks(void)
{
    Inherited::resolveLinks();
}


#include "OSGSField.ins"
#include "OSGMField.ins"

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_FUNCTION_INSTANTIATION) || \
    defined(OSG_TMPL_STATIC_MEMBER_NEEDS_CLASS_INSTANTIATION   )

#include "OSGSFieldFuncs.ins"
#include "OSGMFieldFuncs.ins"
#endif

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<AlgorithmPtr>::_type("AlgorithmPtr", "FieldContainerPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(AlgorithmPtr)

OSG_FIELD_DLLEXPORT_DEF1(SField, AlgorithmPtr);
OSG_FIELD_DLLEXPORT_DEF1(MField, AlgorithmPtr);

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCBaseTemplate_cpp.h 219 2006-10-03 03:22:32Z allenb $";
    static Char8 cvsid_hpp       [] = OSGALGORITHMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGALGORITHMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGALGORITHMFIELDS_HEADER_CVSID;
}
