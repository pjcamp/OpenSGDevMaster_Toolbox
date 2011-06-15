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

OSG_BEGIN_NAMESPACE


inline
void ChangeList::clearPool(void)
{
    _currentPoolElement = _entryPool          .begin();
    _currentEntry       = _currentPoolElement->begin();

    _changedStore     .clear();
    _createdStore     .clear();
    _uncommitedChanges.clear();

    _qFreeElements.clear();
}

#if 0
inline
void ChangeList::addAddRefd(const UInt32 uiContainerId)
{
    FieldContainerPtr pTmp = 
        FieldContainerFactory::the()->getContainer(uiContainerId);

    fprintf(stderr, "Add AddRef %u %s\n", 
            uiContainerId, pTmp->getType().getCName());

    ContainerChangeEntry *pEntry = getNewEntry();

    pEntry->uiEntryDesc   = ContainerChangeEntry::AddReference;
    pEntry->uiContainerId = uiContainerId;
}

inline
void ChangeList::addSubRefd(const UInt32 uiContainerId)
{
    fprintf(stderr, "Add SubRef %u\n", uiContainerId);

    ContainerChangeEntry *pEntry = getNewEntry();

    pEntry->uiEntryDesc   = ContainerChangeEntry::SubReference;
    pEntry->uiContainerId = uiContainerId;
}

inline
void ChangeList::addCreated(const UInt32    uiContainerId,
                                  BitVector bFlags       )
{
    FieldContainerPtr pTmp = 
        FieldContainerFactory::the()->getContainer(uiContainerId);

    fprintf(stderr, "Add Create %u %s\n", 
            uiContainerId, pTmp->getType().getCName());

    ContainerChangeEntry *pEntry = getNewEntry();

    pEntry->uiEntryDesc   = ContainerChangeEntry::Create;
    pEntry->uiContainerId = uiContainerId;
    pEntry->whichField    = bFlags;
}

inline
void ChangeList::addUncommited(ContainerChangeEntry *pEntry)
{
    fprintf(stderr, "Added changed %d\n", pEntry->uiContainerId);

    _uncommitedChanges.push_back(pEntry);
}
#endif

inline
void ChangeList::applyAndClear(void)
{
    doApply  (true);
    clearPool(    );
}

inline
void ChangeList::applyNoClear (void)
{
    doApply(false);
}

inline
void ChangeList::clear(void)
{
#ifdef OSG_MT_CPTR_ASPECT
    if(_uiAspect != Thread::getCurrentAspect())
    {
        fprintf(stderr, "ChangeList::clear aspects don't match %d %d\n",
                _uiAspect, Thread::getCurrentAspect());
        
        return;
    }
#endif

    doClear  ();
    clearPool();
}

inline
void ChangeList::setAspect(UInt32 uiAspectId)
{
    _uiAspect = uiAspectId;
}

inline
ChangeList::ChangedStoreConstIt ChangeList::begin(void) const
{
    return _changedStore.begin();
}

inline
ChangeList::ChangedStoreConstIt ChangeList::end(void) const
{
    return _changedStore.end();
}

inline
ChangeList::ChangedStoreConstIt ChangeList::beginCreated(void) const
{
    return _createdStore.begin();
}

inline
ChangeList::ChangedStoreConstIt ChangeList::endCreated(void) const
{
    return _createdStore.end();
}

inline
UInt32 ChangeList::getNumCreated(void) const
{
    return _createdStore.size();
}

inline
UInt32 ChangeList::getNumChanged(void) const
{
    return _changedStore.size();
}

inline
void ChangeList::incSubRefLevel(void)
{
    ++_iSubRefLevel;
}

inline
void ChangeList::decSubRefLevel(void)
{
    --_iSubRefLevel;
}

inline
void ChangeList::setReadWriteDefault(bool bReadWrite)
{
    _bReadWriteDefault = bReadWrite;
}

inline 
void commitChanges(UInt32 AdditionalChangeOrigin)
{
    Thread::getCurrentChangeList()->commitChanges(AdditionalChangeOrigin);
}

inline 
void commitChangesAndClear(UInt32 AdditionalChangeOrigin)
{
    Thread::getCurrentChangeList()->commitChangesAndClear(AdditionalChangeOrigin);
}

inline 
void clearChangeList(void)
{
    Thread::getCurrentChangeList()->clear();
}


OSG_END_NAMESPACE

