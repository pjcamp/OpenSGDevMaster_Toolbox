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
 **     class ConnectorAttachment!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILECONNECTORATTACHMENTINST

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>




#include "OSGConnectorAttachmentBase.h"
#include "OSGConnectorAttachment.h"

#include "boost/bind.hpp"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ConnectorAttachment
    
 */


ConnectorAttachmentBase::TypeObject ConnectorAttachmentBase::_type(
    ConnectorAttachmentBase::getClassname(),
    Inherited::getClassname(),
    "ConnectorAttachment",
    0,
    reinterpret_cast<PrototypeCreateF>(&ConnectorAttachmentBase::createEmptyLocal),
    ConnectorAttachment::initMethod,
    ConnectorAttachment::exitMethod,
    NULL,
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"ConnectorAttachment\"\n"
    "    parent=\"Attachment\"\n"
    "    library=\"System\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    isBundle=\"true\"\n"
    ">\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ConnectorAttachmentBase::getType(void)
{
    return _type;
}

const FieldContainerType &ConnectorAttachmentBase::getType(void) const
{
    return _type;
}

UInt32 ConnectorAttachmentBase::getContainerSize(void) const
{
    return sizeof(ConnectorAttachment);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 ConnectorAttachmentBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void ConnectorAttachmentBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void ConnectorAttachmentBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
ConnectorAttachmentTransitPtr ConnectorAttachmentBase::createLocal(BitVector bFlags)
{
    ConnectorAttachmentTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<ConnectorAttachment>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ConnectorAttachmentTransitPtr ConnectorAttachmentBase::create(void)
{
    return createLocal();
}

ConnectorAttachment *ConnectorAttachmentBase::createEmptyLocal(BitVector bFlags)
{
    ConnectorAttachment *returnValue;

    newPtr<ConnectorAttachment>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
ConnectorAttachment *ConnectorAttachmentBase::createEmpty(void)
{
    return createEmptyLocal();
}


FieldContainerTransitPtr ConnectorAttachmentBase::shallowCopyLocal(
    BitVector bFlags) const
{
    ConnectorAttachment *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ConnectorAttachment *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ConnectorAttachmentBase::shallowCopy(void) const
{
    return shallowCopyLocal();
}




/*------------------------- constructors ----------------------------------*/

ConnectorAttachmentBase::ConnectorAttachmentBase(void) :
    Inherited()
{
}

ConnectorAttachmentBase::ConnectorAttachmentBase(const ConnectorAttachmentBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

ConnectorAttachmentBase::~ConnectorAttachmentBase(void)
{
}



#ifdef OSG_MT_CPTR_ASPECT
void ConnectorAttachmentBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<ConnectorAttachmentBase *>(&oFrom),
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *ConnectorAttachmentBase::createAspectCopy(void) const
{
    ConnectorAttachment *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const ConnectorAttachment *>(this));

    return returnValue;
}
#endif

void ConnectorAttachmentBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<ConnectorAttachment *>::_type("ConnectorAttachmentPtr", "AttachmentPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(ConnectorAttachment *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           ConnectorAttachment *, 
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           ConnectorAttachment *, 
                           0);

OSG_END_NAMESPACE
