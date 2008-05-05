/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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
 **     class TestMultiPartitionStage!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &TestMultiPartitionStageBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 TestMultiPartitionStageBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 TestMultiPartitionStageBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the TestMultiPartitionStage::_sfMessage field.

inline
std::string &TestMultiPartitionStageBase::editMessage(void)
{
    editSField(MessageFieldMask);

    return _sfMessage.getValue();
}

//! Get the value of the TestMultiPartitionStage::_sfMessage field.
inline
const std::string TestMultiPartitionStageBase::getMessage(void) const
{
    return _sfMessage.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
std::string         &TestMultiPartitionStageBase::getMessage        (void)
{
    return this->editMessage        ();
}
#endif

//! Set the value of the TestMultiPartitionStage::_sfMessage field.
inline
void TestMultiPartitionStageBase::setMessage(const std::string &value)
{
    editSField(MessageFieldMask);

    _sfMessage.setValue(value);
}
//! Get the value of the TestMultiPartitionStage::_sfNumPartitions field.

inline
Int32 &TestMultiPartitionStageBase::editNumPartitions(void)
{
    editSField(NumPartitionsFieldMask);

    return _sfNumPartitions.getValue();
}

//! Get the value of the TestMultiPartitionStage::_sfNumPartitions field.
inline
const Int32 TestMultiPartitionStageBase::getNumPartitions(void) const
{
    return _sfNumPartitions.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Int32               &TestMultiPartitionStageBase::getNumPartitions  (void)
{
    return this->editNumPartitions  ();
}
#endif

//! Set the value of the TestMultiPartitionStage::_sfNumPartitions field.
inline
void TestMultiPartitionStageBase::setNumPartitions(const Int32 &value)
{
    editSField(NumPartitionsFieldMask);

    _sfNumPartitions.setValue(value);
}
//! Get the value of the TestMultiPartitionStage::_sfUseGroup field.

inline
bool &TestMultiPartitionStageBase::editUseGroup(void)
{
    editSField(UseGroupFieldMask);

    return _sfUseGroup.getValue();
}

//! Get the value of the TestMultiPartitionStage::_sfUseGroup field.
inline
const bool TestMultiPartitionStageBase::getUseGroup(void) const
{
    return _sfUseGroup.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
bool                &TestMultiPartitionStageBase::getUseGroup       (void)
{
    return this->editUseGroup       ();
}
#endif

//! Set the value of the TestMultiPartitionStage::_sfUseGroup field.
inline
void TestMultiPartitionStageBase::setUseGroup(const bool &value)
{
    editSField(UseGroupFieldMask);

    _sfUseGroup.setValue(value);
}

//! Get the value of the \a index element the TestMultiPartitionStage::_mfOrder field.
inline
const Int32 TestMultiPartitionStageBase::getOrder(const UInt32 index) const
{
    return _mfOrder[index];
}

inline
Int32 &TestMultiPartitionStageBase::editOrder(const UInt32 index)
{
    editMField(OrderFieldMask, _mfOrder);

    return _mfOrder[index];
}

#ifdef OSG_1_GET_COMPAT
inline
Int32               &TestMultiPartitionStageBase::getOrder          (const UInt32 index)
{
    return this->editOrder          (index);
}

inline
MFInt32             &TestMultiPartitionStageBase::getOrder          (void)
{
    return this->editOrder          ();
}

#endif



#ifdef OSG_MT_CPTR_ASPECT
inline
void TestMultiPartitionStageBase::execSync (      TestMultiPartitionStageBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (MessageFieldMask & whichField))
        _sfMessage.syncWith(pFrom->_sfMessage);

    if(FieldBits::NoField != (NumPartitionsFieldMask & whichField))
        _sfNumPartitions.syncWith(pFrom->_sfNumPartitions);

    if(FieldBits::NoField != (OrderFieldMask & whichField))
        _mfOrder.syncWith(pFrom->_mfOrder,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (UseGroupFieldMask & whichField))
        _sfUseGroup.syncWith(pFrom->_sfUseGroup);
}
#endif


inline
Char8 *TestMultiPartitionStageBase::getClassname(void)
{
    return "TestMultiPartitionStage";
}
OSG_GEN_CONTAINERPTR(TestMultiPartitionStage);

OSG_END_NAMESPACE

