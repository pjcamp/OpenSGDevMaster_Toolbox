/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#ifndef _OSGREFLEXIVECONTAINER_H_
#define _OSGREFLEXIVECONTAINER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGReflexiveContainerType.h"
#include "OSGContainerBase.h"
#include "OSGContainerDefines.h"
#include "OSGField.h"
#include "OSGFieldType.h"
#include "OSGBinaryDataHandler.h"
#include "OSGThread.h"
#include "OSGChangeList.h"
#include "OSGFieldHandle.h"
#include "OSGEventHandle.h"
#include "OSGEventProducerType.h"
#include <boost/signals2.hpp>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Class         
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFieldContainerBase
    \ingroup GrpLibOSGBase
 */

class ReflexiveContainer 
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Type definitions                          */
    /*! \{                                                                 */
    
    typedef ReflexiveContainerType TypeObject;
    typedef TypeObject::InitPhase  InitPhase;

    typedef       Field *(ReflexiveContainer::*FieldEditMethod)(void);

    typedef const Field *(ReflexiveContainer::*FieldGetMethod )(void) const;

    typedef std::pair<std::string, const TypeBase*> EventDescPair;
    typedef std::vector<EventDescPair> EventDescVector;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Constants                               */
    /*! \{                                                                 */

    static const UInt32    NextFieldId        =    1;
    static const BitVector NextFieldMask      = 0x01;

    static const UInt32    SpinLockBit        =  0x80000000;
    static const UInt32    SpinLockClearMask  = ~0x80000000;

    static const UInt32    DeadContainerBit   =  0x40000000;
    static const UInt32    DeadContainerMask  = ~0x40000000;

    static const UInt32    ContainerIdMask    = ~(SpinLockBit     | 
                                                  DeadContainerBit);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Get Class Type Information                       */
    /*! \{                                                                 */
     
    static OSG_BASE_DLLMAPPING TypeObject &getClassType   (void); 
    static OSG_BASE_DLLMAPPING UInt32      getClassTypeId (void);
    static OSG_BASE_DLLMAPPING UInt16      getClassGroupId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    virtual       TypeObject &getType    (void);

    OSG_BASE_DLLMAPPING 
    virtual const TypeObject &getType    (void) const;

    OSG_BASE_DLLMAPPING 
                  UInt32      getTypeId  (void) const;

    OSG_BASE_DLLMAPPING
                  UInt16      getGroupId (void) const;

    OSG_BASE_DLLMAPPING 
            const Char8      *getTypeName(void) const;

    OSG_BASE_DLLMAPPING 
    virtual const EventProducerType &getProducerType(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    virtual UInt32 getContainerSize(void) const = 0;

    OSG_BASE_DLLMAPPING       
            UInt32 getId           (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         details) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Field                                   */
    /*! \{                                                                 */


    OSG_BASE_DLLMAPPING
    virtual UInt32             getNumFields(      void            ) const;

    OSG_BASE_DLLMAPPING 
    virtual EditFieldHandlePtr editField   (      UInt32 fieldId  );
    
    OSG_BASE_DLLMAPPING 
    virtual EditFieldHandlePtr editField   (const Char8 *fieldName);

    OSG_BASE_DLLMAPPING 
    virtual GetFieldHandlePtr  getField    (      UInt32 fieldId  ) const;
    
    OSG_BASE_DLLMAPPING 
    virtual GetFieldHandlePtr  getField    (const Char8 *fieldName) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Events                                 */
    /*! \{                                                                 */


    OSG_BASE_DLLMAPPING
    virtual UInt32            getNumEvents(      void            ) const;

    OSG_BASE_DLLMAPPING 
    virtual GetEventHandlePtr getEvent    (      UInt32 eventId  ) const;
    
    OSG_BASE_DLLMAPPING 
    virtual GetEventHandlePtr getEvent    (const Char8 *eventName) const;

    OSG_BASE_DLLMAPPING 
    bool isEventProducer(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Manage Events                                 */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    virtual boost::signals2::connection attachActivity(UInt32 eventId,
                                                       Activity* TheActivity);

    OSG_BASE_DLLMAPPING
    virtual boost::signals2::connection connectEvent(UInt32 eventId, 
                                                      const BaseEventType::slot_type &listener,
                                                      boost::signals2::connect_position at= boost::signals2::at_back);
                                              
    OSG_BASE_DLLMAPPING
    virtual boost::signals2::connection connectEvent(UInt32 eventId, 
                                                      const BaseEventType::group_type &group,
                                                      const BaseEventType::slot_type &listener,
                                                      boost::signals2::connect_position at= boost::signals2::at_back);
    
    OSG_BASE_DLLMAPPING
    virtual void   disconnectEvent        (UInt32 eventId, const BaseEventType::group_type &group);

    OSG_BASE_DLLMAPPING
    virtual void   disconnectAllSlotsEvent(UInt32 eventId);

    OSG_BASE_DLLMAPPING
    virtual bool   isEmptyEvent           (UInt32 eventId) const;

    OSG_BASE_DLLMAPPING
    virtual UInt32 numSlotsEvent          (UInt32 eventId) const;

    OSG_BASE_DLLMAPPING
    virtual void   disconnectAll(void);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Field                                   */
    /*! \{                                                                 */

#if 0
    OSG_BASE_DLLMAPPING 
    EditFieldHandle editHandledField(      UInt32 fieldId  );
    
    OSG_BASE_DLLMAPPING 
    EditFieldHandle editHandledField(const Char8 *fieldName);

    OSG_BASE_DLLMAPPING 
    FieldHandle     getHandledField (      UInt32 fieldId  ) const;
    
    OSG_BASE_DLLMAPPING 
    FieldHandle     getHandledField (const Char8 *fieldName) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Get Field Description                        */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    virtual FieldDescriptionBase *
                           getFieldDescription(      UInt32 fieldId  ) const;
    
    OSG_BASE_DLLMAPPING 
    virtual FieldDescriptionBase *
                           getFieldDescription(const Char8 *fieldName) const;


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Get Event Description                       */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    virtual EventDescription const *
                           getEventDescription(      UInt32 eventId  ) const;
    
    OSG_BASE_DLLMAPPING 
    virtual EventDescription const *
                           getEventDescription(const Char8 *eventName) const;


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Get Connectable Events                        */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    bool isEventConnectable(void) const;

    OSG_BASE_DLLMAPPING 
    virtual bool
    isConnectableEvent(EventDescription const * eventDesc) const;

    OSG_BASE_DLLMAPPING 
    virtual EventDescVector getConnectableEvents(void) const;

    OSG_BASE_DLLMAPPING 
    virtual boost::signals2::connection 
        connectToEvent(EventDescription const * eventDesc,
                       ReflexiveContainer* const eventProducer) const;

    OSG_BASE_DLLMAPPING 
    virtual bool
        isConnected(EventDescription const * eventDesc) const;

    OSG_BASE_DLLMAPPING 
    virtual bool
        disconnectFromEvent(EventDescription const * eventDesc) const;

    OSG_BASE_DLLMAPPING 
    bool validateConnectable(EventDescription const * eventDesc,
                             ReflexiveContainer* const eventProducer) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    virtual UInt32  getBinSize (ConstFieldMaskArg   whichField);

    OSG_BASE_DLLMAPPING 
    virtual void    copyToBin  (BinaryDataHandler  &pMem, 
                                ConstFieldMaskArg   whichField);

    OSG_BASE_DLLMAPPING 
    virtual void    copyFromBin(BinaryDataHandler  &pMem, 
                                ConstFieldMaskArg   whichField);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_operators                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    EditFieldHandlePtr invalidEditField(void);

    OSG_BASE_DLLMAPPING 
    GetFieldHandlePtr invalidGetField (void) const;

    OSG_BASE_DLLMAPPING 
    GetEventHandlePtr invalidGetEvent (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

#ifdef OSG_ENABLE_MEMORY_DEBUGGING
    bool _check_is_deleted();
#endif

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static TypeObject _type;
    static EventProducerType _producerType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    ReflexiveContainer(void);

    OSG_BASE_DLLMAPPING 
    ReflexiveContainer(const ReflexiveContainer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

  public:

    OSG_BASE_DLLMAPPING 
    virtual ~ReflexiveContainer(void);

  protected:

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */
    
    BitVector             _bvChanged;
    ContainerChangeEntry *_pContainerChanges;
    UInt32                _uiContainerId;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
            void onCreate       (const ReflexiveContainer *source = NULL);

    OSG_BASE_DLLMAPPING
    virtual void onDestroy      (      UInt32              uiContainerId);

    OSG_BASE_DLLMAPPING
    virtual void onDestroyAspect(      UInt32              uiContainerId,
                                       UInt32              uiAspect     );

    OSG_BASE_DLLMAPPING       
    virtual bool deregister     (      UInt32              uiContainerId) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    virtual void registerChangedContainerV(void) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    void                  execEndEdit   (ConstFieldMaskArg whichField);

//    ContainerChangeEntry *getChangeEntry(void                        );
    void                  clearChangeEntry(ContainerChangeEntry *pRef);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING       
    void   setId(UInt32 uiContainerId);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/

  private:

    friend class  ChangeList;
    friend struct ContainerChangeEntry;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ReflexiveContainer &source);

    std::list<std::pair<boost::signals2::connection, Activity*> > _ConnectedActivities;
};

#define OSG_RC_FIRST_FIELD_DECL(OSG_ELEMNAME)                                 \
    static const OSG::UInt32                                                  \
        OSG_ELEMNAME##FieldId   = Inherited::NextFieldId;                     \
    static const OSG::BitVector                                               \
        OSG_ELEMNAME##FieldMask =                                             \
                        (TypeTraits<BitVector>::One << OSG_ELEMNAME##FieldId)

#define OSG_RC_FIELD_DECL(OSG_ELEMNAME, OSG_PREV_ELEMNAME)                    \
    static const OSG::UInt32    OSG_ELEMNAME##FieldId   =                     \
        OSG_PREV_ELEMNAME##FieldId + 1;                                       \
    static const OSG::BitVector                                               \
        OSG_ELEMNAME##FieldMask =                                             \
                        (TypeTraits<BitVector>::One << OSG_ELEMNAME##FieldId)

#define OSG_RC_LAST_FIELD_DECL(OSG_PREV_ELEMNAME)                             \
  static const OSG::UInt32    NextFieldId   = OSG_PREV_ELEMNAME##FieldId + 1; \
  static const OSG::BitVector NextFieldMask =                                 \
                         (TypeTraits<BitVector>::One << NextFieldId)

#define OSG_RC_NO_FIELD_DECL                                                  \
  static const OSG::UInt32    NextFieldId   = Inherited::NextFieldId;         \
  static const OSG::BitVector NextFieldMask = Inherited::NextFieldMask

#define OSG_RC_FIELD_DESC(OSG_FIELDNAME)                                      \
    OSG_FIELDNAME##FieldId, OSG_FIELDNAME##FieldMask

OSG_END_NAMESPACE

#include "OSGFieldDescriptionBase.h"
#include "OSGReflexiveContainer.inl"

#endif /* _OSGREFLEXIVECONTAINER_H_ */
