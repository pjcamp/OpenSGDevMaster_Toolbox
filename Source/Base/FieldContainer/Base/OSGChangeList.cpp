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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGChangeList.h"
#include "OSGContainerPtrFuncs.h"

#include "OSGFieldContainer.h"
#include "OSGFieldContainerType.h"

#include "OSGStatCollector.h"

#ifdef OSG_ENABLE_VALGRIND_CHECKS
#include <valgrind/memcheck.h>
#endif

OSG_BEGIN_NAMESPACE

#define SILENT
#define SILENT_CPTR

#if 1
void ChangeList::addAddRefd(const UInt32 uiContainerId)
{
#ifdef OSG_ENABLE_VALGRIND_CHECKS
    VALGRIND_CHECK_VALUE_IS_DEFINED(uiContainerId);
#endif

#ifndef SILENT
    fprintf(stderr, "Add AddRef %u\n",
            uiContainerId);
#endif

    if(_bReadOnly == true)
        return;

    ContainerChangeEntry *pEntry = getNewEntry();

    pEntry->uiEntryDesc   = ContainerChangeEntry::AddReference;
    pEntry->uiContainerId = uiContainerId;
    pEntry->pList         = this;
}

void ChangeList::addSubRefd(const UInt32 uiContainerId,
                                  bool   ignoreLevel  )
{
#ifdef OSG_ENABLE_VALGRIND_CHECKS
    VALGRIND_CHECK_VALUE_IS_DEFINED(uiContainerId);
#endif

#ifndef SILENT
    fprintf(stderr, "Add SubRef %u\n", uiContainerId);
#endif

    if(_bReadOnly == true)
        return;

    ContainerChangeEntry *pEntry = getNewEntry();

    if(_iSubRefLevel == 0 || ignoreLevel == true)
    {
        pEntry->uiEntryDesc   = ContainerChangeEntry::SubReference;
    }
    else
    {
        pEntry->uiEntryDesc   = ContainerChangeEntry::DepSubReference;
    }

    pEntry->uiContainerId = uiContainerId;
    pEntry->pList         = this;
}

void ChangeList::addCreated(const UInt32 uiContainerId, 
                                  BitVector bFlags    )
{
#ifdef OSG_ENABLE_VALGRIND_CHECKS
    VALGRIND_CHECK_VALUE_IS_DEFINED(uiContainerId);
#endif

#ifndef SILENT
    FieldContainer *fcPtr =  
        FieldContainerFactory::the()->getContainer(uiContainerId);

    fprintf(stderr, "Add Create %u : %d : %s\n",
            uiContainerId,
            fcPtr != NULL ? fcPtr->getTypeId() : -1,
            fcPtr != NULL ? fcPtr->getType  ().getCName() : "Unknow");
#endif
    if(_bReadOnly == true)
        return;

    ContainerChangeEntry *pEntry = getNewCreatedEntry();

    pEntry->uiEntryDesc   = ContainerChangeEntry::Create;
    pEntry->uiContainerId = uiContainerId;
    pEntry->whichField    = bFlags;
}

void ChangeList::addUncommited(ContainerChangeEntry *pEntry)
{
#ifndef SILENT
    fprintf(stderr, "Added changed %d\n", pEntry->uiContainerId);
#endif
    OSG_ASSERT(NULL != pEntry);
    _uncommitedChanges.push_back(pEntry);
}
#endif



//BitVector ContainerChangeEntry::defaultVec = TypeTraits<BitVector>::BitsClear;

void ContainerChangeEntry::commitChanges(UInt32 AdditionalChangeOrigin)
{
#ifdef OSG_ENABLE_VALGRIND_CHECKS
    VALGRIND_CHECK_VALUE_IS_DEFINED(uiContainerId);
#endif
    FieldContainer *pTmp =
        FieldContainerFactory::the()->getContainer(uiContainerId);

    if(pTmp != NULL)
    {
#ifndef SILENT
        fprintf(stderr, "Commit for %u %s\n",
                uiContainerId, pTmp->getType().getCName());
#endif
        
        BitVector tmpChanges;
        //OSG_ASSERT(NULL !=  bvUncommittedChanges);

        if (NULL != bvUncommittedChanges)
        { 
#ifdef OSG_ENABLE_MEMORY_DEBUGGING
           OSG_ASSERT(*bvUncommittedChanges != 0xDEADBEEF);
#endif
           tmpChanges             = *bvUncommittedChanges; 
           whichField            |= *bvUncommittedChanges;
           *bvUncommittedChanges  = TypeTraits<BitVector>::BitsClear;

           pTmp->changed      (tmpChanges, ChangedOrigin::Commit | AdditionalChangeOrigin, 0);
        }
    }
}

void ContainerChangeEntry::release(void)
{
    if(pList == NULL)
        return;

    if(pList->_bReadOnly == false)
        return;

    ChangeList::ChangedStoreIt cIt = std::find(pList->_changedStore.begin(),
                                               pList->_changedStore.end  (),
                                               this                        );

    if(cIt != pList->_changedStore.end())
    {
        pList->_qFreeElements.push_back(this);

        pList->_changedStore.erase(cIt);
    }

    cIt = std::find(pList->_uncommitedChanges.begin(),
                    pList->_uncommitedChanges.end  (),
                    this                             );

    if(cIt != pList->_uncommitedChanges.end())
    {
        pList->_uncommitedChanges.erase(cIt);
    }

}

StatElemDesc<StatIntElem> ChangeList::statNChangedStoreSize(
    "changedStoreSize",
    "number of elements in the changed store",
    StatElemDescBase::RESET_NEVER);

StatElemDesc<StatIntElem> ChangeList::statNCreatedStoreSize(
    "createdStoreSize",
    "number of elements in the created store",
    StatElemDescBase::RESET_NEVER);

StatElemDesc<StatIntElem> ChangeList::statNUnCommittedStoreSize(
    "uncommittedStoreSize",
    "number of elements in the uncommitted store",
    StatElemDescBase::RESET_NEVER);

StatElemDesc<StatIntElem> ChangeList::statNPoolSize(
    "poolSize",
    "number of elements in the entry pool",
    StatElemDescBase::RESET_NEVER);

#ifdef OSG_ENABLE_DEFAULT_READONLY_CHANGELIST
bool ChangeList::_bReadWriteDefault = false;
#else
bool ChangeList::_bReadWriteDefault = true;
#endif

ChangeList *ChangeList::create(void)
{
    ChangeList *returnValue = new ChangeList;

    returnValue->_uiAspect  = Thread::getCurrentAspect();

    returnValue->_bExternal = true;

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ChangeList::ChangeList(void) :
     Inherited           (                   ),
    _entryPool           (                   ),
    _currentPoolElement  (                   ),
    _currentEntry        (                   ),
    _changedStore        (                   ),
    _createdStore        (                   ),
    _uncommitedChanges   (                   ),
    _workStore           (                   ),
    _uiAspect            (                  0),
    _iSubRefLevel        (                  0),
    _bExternal           (false              ),
    _bReadOnly           (!_bReadWriteDefault),
    _vDelayedUnrecSubRefs(                   ),
    _vDelayedRecSubRefs  (                   ),
    _vDelayedWeakSubRefs (                   ),
    _qFreeElements       (                   )
{
    _entryPool.push_back(ChangeEntryStore());

    _currentPoolElement = _entryPool.begin();

    _currentPoolElement->resize(32);

    _currentEntry = _currentPoolElement->begin();
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ChangeList::~ChangeList(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

ContainerChangeEntry *ChangeList::createNewEntry(void)
{
    if(_qFreeElements.empty() == false)
    {
        ContainerChangeEntry *returnValue = _qFreeElements.back();

        _qFreeElements.pop_back();

        return returnValue;
    }

    if(_currentEntry == _currentPoolElement->end())
    {
        ++_currentPoolElement;

        if(_currentPoolElement == _entryPool.end())
        {
            _entryPool.push_back(ChangeEntryStore());

              _currentPoolElement = _entryPool.end();
            --_currentPoolElement;

              _currentPoolElement->resize(32);
        }

        _currentEntry = _currentPoolElement->begin();
    }

    ContainerChangeEntry *returnValue = &(*_currentEntry);

    ++_currentEntry;

    return returnValue;
}




ContainerChangeEntry *ChangeList::getNewEntry(void)
{
    ContainerChangeEntry *returnValue = createNewEntry();
    returnValue->clear(this);

    _changedStore.push_back(returnValue);

    return returnValue;
}


ContainerChangeEntry *ChangeList::getNewCreatedEntry(void)
{
    ContainerChangeEntry *returnValue = createNewEntry();
    returnValue->clear(this);

    _createdStore.push_back(returnValue);

    return returnValue;
}

template<> OSG_DLL_EXPORT 
void ChangeList::addDelayedSubRef<NoRefCountPolicy>(FieldContainer *)
{
}

template<> OSG_DLL_EXPORT 
void ChangeList::addDelayedSubRef<RecordedRefCountPolicy>(FieldContainer *pFC)
{
    _vDelayedRecSubRefs.push_back(pFC);
}

template<> OSG_DLL_EXPORT 
void ChangeList::addDelayedSubRef<UnrecordedRefCountPolicy>(
    FieldContainer *pFC)
{
    _vDelayedUnrecSubRefs.push_back(pFC);
}

template<> OSG_DLL_EXPORT 
void ChangeList::addDelayedSubRef<WeakRefCountPolicy>(FieldContainer *pFC)
{
    _vDelayedWeakSubRefs.push_back(pFC);
}

template<ChangeList::CommitFunction func> inline
void ChangeList::doCommitChanges(UInt32 AdditionalChangeOrigin)
{
    if(_workStore.empty() == false)
    {
        fprintf(stderr, "warning non empty workstore found\n");
        return;
    }


    const unsigned loop_detection_limit(25);
    unsigned loop_count(0);
    bool  detected_loop(false);
    
    _workStore.clear();

#if 0
    std::cerr << "----------- DETECTED LOOP START -------------" << std::endl;
    dump();
#endif

    while((_uncommitedChanges.empty() == false) && !detected_loop)
    {
        _workStore.swap(_uncommitedChanges);
        _uncommitedChanges.clear();

        ChangedStore::iterator       changesIt  = _workStore.begin();
        ChangedStore::const_iterator changesEnd = _workStore.end  ();

#if 0
        std::cerr << "--------- DETECTED LOOP1 START ----------" << std::endl;
        dump();
#endif

        while(changesIt != changesEnd )
        {
            OSG_ASSERT(NULL != (*changesIt));
            
            if((*changesIt)->uiEntryDesc == ContainerChangeEntry::Change)
            {
                ((*changesIt)->*func)(AdditionalChangeOrigin);
            }
            
            ++changesIt;
        }

#if 0
        std::cerr << "-------- DETECTED LOOP2 START ----------" << std::endl;
        dump();
#endif

        _workStore.clear();
        if(loop_count++ > loop_detection_limit)
        {
           detected_loop = true;
           std::cerr << "----------- DETECTED LOOP ------------" << std::endl;
           dump();
        }        
    }
}

void ChangeList::commitChanges(UInt32 AdditionalChangeOrigin)
{
    doCommitChanges<&ContainerChangeEntry::commitChanges>(AdditionalChangeOrigin);
}

void ChangeList::commitChangesAndClear(UInt32 AdditionalChangeOrigin)
{
    doCommitChanges<&ContainerChangeEntry::commitChanges>(AdditionalChangeOrigin);
    clear();
}


void ChangeList::doApply(bool bClear)
{
    if(_bReadOnly == true)
    {
        FWARNING(("Read-only changelist, can not apply\n"));
        return;
    }

#ifdef OSG_MT_CPTR_ASPECT
    FieldContainer      *pSrc  = NULL;
    FieldContainer      *pDst  = NULL;

    ChangedStoreConstIt  ccIt  = _createdStore.begin();
    ChangedStoreConstIt  ccEnd = _createdStore.end  ();


    while(ccIt != ccEnd)
    {
        AspectStoreP pHandler =
            FieldContainerFactory::the()->getContainerHandler(
                (*ccIt)->uiContainerId);

        if(pHandler == NULL)
        {
#ifndef SILENT_CPTR
            fprintf(stderr, "Strange handler nil %d %p\n", 
                    (*ccIt)->uiContainerId, 
                    pHandler);

#endif
            ++ccIt;
            continue;
        }

        pSrc = pHandler->getPtr(_uiAspect                 );
        pDst = pHandler->getPtr(Thread::getCurrentAspect());

        if(pSrc == NULL)
        {
#ifndef SILENT_CPTR
            fprintf(stderr, "Strange src nil %d %p\n", 
                    (*ccIt)->uiContainerId, 
                    pSrc);
            
#endif
            ++ccIt;
            continue;
        }

        if(pDst == NULL)
        {
            if(0x0000 == ((*ccIt)->whichField & FCLocal::MTMask))
            {
                pDst = pSrc->getType().createAspectCopy(pSrc,
                                                        (*ccIt)->uiContainerId);

                Thread::getCurrentChangeList()->addCreated(
                    (*ccIt)->uiContainerId, 
                    TypeTraits<BitVector>::BitsClear);

#ifndef SILENT_CPTR
                fprintf(stderr, "Setup store for %d %p \n",
                        (*ccIt)->uiContainerId,
                        pDst);
#endif

                if(pDst != NULL)
                    pDst->setupAspectStore(pHandler);
                
#ifndef SILENT_CPTR
                pHandler->dump();
#endif
            }
        }

        ++ccIt;
    }


    ChangedStoreIt      cIt  = _changedStore.begin();
    ChangedStoreConstIt cEnd = _changedStore.end  ();

#ifndef SILENT_CPTR
    fprintf(stderr, "CL apply %u -> %u\n",
            _uiAspect,
            Thread::getCurrentAspect());
#endif

    BitVector         syncMode = 0;

    AspectOffsetStore oOffsets;

    while(cIt != cEnd)
    {
        AspectStoreP pHandler =
            FieldContainerFactory::the()->getContainerHandler(
                (*cIt)->uiContainerId);

        if(pHandler == NULL)
        {
            ++cIt;
            continue;
        }

        pSrc = pHandler->getPtr(_uiAspect                 );
        pDst = pHandler->getPtr(Thread::getCurrentAspect());


#ifndef SILENT_CPTR
        fprintf(stderr, "process changes for %d %p %s %p %s\n",
                (*cIt)->uiContainerId,
                pSrc,
                pSrc != NULL ? pSrc->getType().getCName() : "null",
                pDst,
                pDst != NULL ? pDst->getType().getCName() : "null");
#endif

        if(pDst == NULL && 
           pSrc != NULL)
        {
            if((pSrc->getFieldFlags()->_bNamespaceMask & FCLocal::MTMask) != 
               TypeTraits<BitVector>::BitsClear             )
            {
                pDst = pSrc->getType().createAspectCopy(pSrc,
                                                        (*cIt)->uiContainerId);
            
                if(pDst != NULL) 
                {
                    Thread::getCurrentChangeList()->addCreated(
                        (*cIt)->uiContainerId, 
                        TypeTraits<BitVector>::BitsClear);

                    pDst->setupAspectStore(pHandler);
                }

#ifndef SILENT_CPTR
                pHandler->dump();
#endif
            }
            else
            {
                ++cIt;
                continue;
            }
        }

#ifndef SILENT_CPTR
        fprintf(stderr, "Xprocess changes for %d %p %s %p %s | %d %d %p\n",
                (*cIt)->uiContainerId,
                pSrc,
                pSrc != NULL ? pSrc->getType().getCName() : "null",
                pDst,
                pDst != NULL ? pDst->getType().getCName() : "null",
                _uiAspect,
                Thread::getCurrentAspect(),
                pHandler);
#endif

        if((*cIt)->uiEntryDesc == ContainerChangeEntry::Change)
        {
            if(pSrc != NULL && pDst != NULL) // be safe for now
            {
                BitVector mask = ((*cIt)->whichField & 
                                  pSrc->getFieldFlags()->_bThreadLocalFlags);

                if(mask != 0x0000)
                {
                    pHandler->fillOffsetArray(oOffsets, pDst);
                   
#ifndef SILENT_CPTR
                    for(UInt32 i = 0; i < ThreadManager::getNumAspects(); ++i)
                    {
                        fprintf(stderr, "offset %d %d\n", i, oOffsets[i]);
                    }
#endif
                    
                    UInt32 uiSInfo =
                        /*uiSyncInfo*/ 0 |
                        (_uiAspect << 24) |
                        (Thread::getCurrentAspect() << 16);
                    
                    pDst->execSyncV(*pSrc,
                                    mask,
                                    oOffsets,
                                    syncMode,
                                    uiSInfo);
                }
                
                if(bClear == true)
                {
                    pSrc->clearChangeEntry(*cIt);
                }
            }
        }
        else if((*cIt)->uiEntryDesc == ContainerChangeEntry::AddReference)
        {
#ifndef SILENT_CPTR
            fprintf(stderr, "Execute add Ref for %d %s\n",
                    (*cIt)->uiContainerId, pDst->getType().getCName());
#endif

            if(pDst != NULL)
                pDst->addReferenceRecorded();
        }
        else if((*cIt)->uiEntryDesc == ContainerChangeEntry::SubReference)// ||
//            (*cIt)->uiEntryDesc == ContainerChangeEntry::DepSubReference)
        {
#ifndef SILENT_CPTR
            fprintf(stderr, "Execute sub Ref for %d %s\n",
                    (*cIt)->uiContainerId, pDst->getType().getCName());
#endif
            
            if(pDst != NULL)
            {
                //pDst->subReferenceRecorded();
                this->addDelayedSubRef<RecordedRefCountPolicy>(pDst);
            }
        }

        ++cIt;
    }

    commitDelayedSubRefs();

    Thread::getCurrentChangeList()->commitDelayedSubRefs();
#endif
}

void ChangeList::doClear(void)
{
#ifdef OSG_MT_CPTR_ASPECT
    if(_uiAspect != Thread::getCurrentAspect())
    {
        fprintf(stderr, "ChangeList::doClear aspects don't match %d %d\n",
                _uiAspect, Thread::getCurrentAspect());
        
        return;
    }

    ChangedStoreIt       cIt  = _changedStore.begin();
    ChangedStoreConstIt  cEnd = _changedStore.end  ();

    FieldContainer      *pDst = NULL;

    while(cIt != cEnd)
    {
        AspectStoreP pHandler =
            FieldContainerFactory::the()->getContainerHandler(
                (*cIt)->uiContainerId);

        if(pHandler == NULL)
        {
            ++cIt;
            continue;
        }

        pDst = pHandler->getPtr(Thread::getCurrentAspect());

        if(pDst != NULL)
        {
            pDst->clearChangeEntry(*cIt);
        }

        ++cIt;
    }
#endif
}


void ChangeList::merge(ChangeList &other)
{
    ChangedStoreConstIt cIt  = other._createdStore.begin();
    ChangedStoreConstIt cEnd = other._createdStore.end  ();

    while(cIt != cEnd)
    {
        ContainerChangeEntry *pEntry = getNewCreatedEntry();

        pEntry->uiEntryDesc   = ContainerChangeEntry::Create;
        pEntry->uiContainerId = (*cIt)->uiContainerId;

        ++cIt;
    }

    cIt  = other._changedStore.begin();
    cEnd = other._changedStore.end  ();

    while(cIt != cEnd)
    {
        if((*cIt)->uiEntryDesc == ContainerChangeEntry::AddReference   ||
           (*cIt)->uiEntryDesc == ContainerChangeEntry::SubReference   ||
           (*cIt)->uiEntryDesc == ContainerChangeEntry::DepSubReference )
        {
            ContainerChangeEntry *pEntry = getNewEntry();
     
            pEntry->uiEntryDesc   = (*cIt)->uiEntryDesc;
            pEntry->uiContainerId = (*cIt)->uiContainerId;
            pEntry->pList         = this;
        }
        else if((*cIt)->uiEntryDesc == ContainerChangeEntry::Change)
        {
            ContainerChangeEntry *pEntry = getNewEntry();
            
            pEntry->uiEntryDesc   = ContainerChangeEntry::Change;
            pEntry->pFieldFlags   = (*cIt)->pFieldFlags;
            pEntry->uiContainerId = (*cIt)->uiContainerId;
            pEntry->whichField    = (*cIt)->whichField;
            pEntry->pList         = this;
        }

        ++cIt;
    }
}

/*! Fills this changelist with entries that represent the current state of
    the system starting at the container with the given id.
    Prototypes are skipped unless skipPrototypes is false.

    For every container a 'Create' entry and a 'Change' entry (marking all fields
    as modified) is added and as many 'AddReference' entries as the ref count
    of the container.
 */
void ChangeList::fillFromCurrentState(UInt32 uiFieldContainerId,
                                      bool   skipPrototypes     )
{
    this->clear();

    UInt32 uiNumContainers = 
        FieldContainerFactory::the()->getNumContainers();

    if(uiNumContainers <= uiFieldContainerId)
    {
        return;
    }

    for(UInt32 i = uiFieldContainerId; i < uiNumContainers; ++i)
    {
        FieldContainer *pContainer = 
            FieldContainerFactory::the()->getContainer(i);

        // skip destroyed FC
        if(pContainer == NULL)
          continue;

        // skip prototypes - unless requested
        if(skipPrototypes == true &&
           (pContainer->getType().getPrototype() == pContainer ||
            pContainer->getType().getPrototype() == NULL         ))
        {
            continue;
        }

        this->addCreated(i, TypeTraits<BitVector>::BitsClear);

        for(Int32 j = 0; j < pContainer->getRefCount(); ++j)
            this->addAddRefd(i);

        ContainerChangeEntry *pEntry = this->getNewEntry();

        pEntry->uiEntryDesc   = ContainerChangeEntry::Change;
        pEntry->pFieldFlags   = pContainer->getFieldFlags();
        pEntry->uiContainerId = i;
        pEntry->whichField    = FieldBits::AllFields;
        pEntry->pList         = this;
    }
}

#ifdef OSG_THREAD_DEBUG_SETASPECTTO
void ChangeList::setAspectTo(UInt32 uiNewAspect)
{
    _uiAspect = uiNewAspect;
}
#endif


void ChangeList::commitDelayedSubRefs(void)
{
    // Unrec
    std::vector<FieldContainer *>::      iterator vIt  = 
        _vDelayedUnrecSubRefs.begin();

    std::vector<FieldContainer *>::const_iterator vEnd = 
        _vDelayedUnrecSubRefs.end  ();

    while(vIt != vEnd)
    {
        (*vIt)->subReferenceUnrecorded();

        ++vIt;
    }

    _vDelayedUnrecSubRefs.clear();

    // Rec
    vIt  = _vDelayedRecSubRefs.begin();
    vEnd = _vDelayedRecSubRefs.end  ();

    while(vIt != vEnd)
    {
        (*vIt)->subReferenceRecorded();

        ++vIt;
    }

    _vDelayedRecSubRefs.clear();

    
    // Weak
    vIt  = _vDelayedWeakSubRefs.begin();
    vEnd = _vDelayedWeakSubRefs.end  ();

    while(vIt != vEnd)
    {
        (*vIt)->subWeakReference();

        ++vIt;
    }

    _vDelayedWeakSubRefs.clear();
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

void ChangeList::dump(      UInt32    uiIndent,
                      const BitVector bvFlags ) const
{
    ChangedStoreConstIt cIt  = _createdStore.begin();
    ChangedStoreConstIt cEnd = _createdStore.end  ();

    fprintf(stderr, "CL created dump\n");

    while(cIt != cEnd)
    {
        for(UInt32 i = 0; i < uiIndent + 4; ++i)
        {
            fprintf(stderr, " ");
        }

        fprintf(stderr, "CE : %u %u\n",
                (*cIt)->uiEntryDesc,
                (*cIt)->uiContainerId);

        ++cIt;
    }

    cIt  = _changedStore.begin();
    cEnd = _changedStore.end  ();

    fprintf(stderr, "CL changed dump\n");

    while(cIt != cEnd)
    {
        for(UInt32 i = 0; i < uiIndent + 4; ++i)
        {
            fprintf(stderr, " ");
        }

        FieldContainer *pTmp =
            FieldContainerFactory::the()->getContainer((*cIt)->uiContainerId);

        std::string szTmp("Unknown");

        if(pTmp != NULL)
        {
            szTmp.assign(pTmp->getType().getCName());
        }

        BitVector tmpChanges = 0xDEADBEEF;

        if((*cIt)->bvUncommittedChanges != NULL && pTmp != NULL)
        { 
            tmpChanges = *((*cIt)->bvUncommittedChanges); 
        }

        fprintf(stderr, 
                "CE : %u %u 0x%016"PRIx64" 0x%016"PRIx64" (%p|%p) | %s\n",
                (*cIt)->uiEntryDesc,
                (*cIt)->uiContainerId,
                tmpChanges,
                (*cIt)->whichField,
                (*cIt),
                (*cIt)->bvUncommittedChanges,
                szTmp.c_str());

        ++cIt;
    }

    cIt  = _uncommitedChanges.begin();
    cEnd = _uncommitedChanges.end  ();

    fprintf(stderr, "CL uncommited dump\n");

    while(cIt != cEnd)
    {
        for(UInt32 i = 0; i < uiIndent + 4; ++i)
        {
            fprintf(stderr, " ");
        }

        FieldContainer *pTmp =
            FieldContainerFactory::the()->getContainer((*cIt)->uiContainerId);

        std::string szTmp("Unknown");

        if(pTmp != NULL)
        {
            szTmp.assign(pTmp->getType().getCName());
        }

        BitVector tmpChanges = 0xDEADBEEF;

        if((*cIt)->bvUncommittedChanges != NULL && pTmp != NULL)
        { 
            tmpChanges = *((*cIt)->bvUncommittedChanges); 
        }

        fprintf(stderr, 
                "CE : %u %u 0x%016"PRIx64" 0x%016"PRIx64" (%p|%p) | %s\n",
                (*cIt)->uiEntryDesc,
                (*cIt)->uiContainerId,
                tmpChanges,
                (*cIt)->whichField,
                (*cIt),
                (*cIt)->bvUncommittedChanges,
                szTmp.c_str());

        ++cIt;
    }

    cIt  = _workStore.begin();
    cEnd = _workStore.end  ();

    fprintf(stderr, "CL workstore dump\n");

    while(cIt != cEnd)
    {
        for(UInt32 i = 0; i < uiIndent + 4; ++i)
        {
            fprintf(stderr, " ");
        }

        FieldContainer *pTmp =
            FieldContainerFactory::the()->getContainer((*cIt)->uiContainerId);

        BitVector tmpChanges = 0xDEADBEEF;

        if((*cIt)->bvUncommittedChanges != NULL && pTmp != NULL)
        { 
            tmpChanges = *((*cIt)->bvUncommittedChanges); 
        }

        fprintf(stderr, "CE : %u %u 0x%016"PRIx64" 0x%016"PRIx64"\n",
                (*cIt)->uiEntryDesc,
                (*cIt)->uiContainerId,
                tmpChanges,
                (*cIt)->whichField);

        ++cIt;
    }
}

void ChangeList::dumpListSizes(void) const
{
    fprintf(stderr, "CL : CH_S : %"PRISize" | CR_S : %"PRISize" | UC_S : %"
            PRISize" | P_S %"PRISize"\n",
            _changedStore.size(),
            _createdStore.size(),
            _uncommitedChanges.size(),
            _entryPool.size() * 32 );
}

void ChangeList::fillStatistic(StatCollector *pColl) const
{
    if(pColl == NULL)
        return;

    pColl->getElem(statNChangedStoreSize    )->set(_changedStore     .size());
    pColl->getElem(statNCreatedStoreSize    )->set(_createdStore     .size());
    pColl->getElem(statNUnCommittedStoreSize)->set(_uncommitedChanges.size());
    pColl->getElem(statNPoolSize            )->set(_entryPool.size() * 32   );

}

OSG_END_NAMESPACE
