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

#include "OSGReflexiveContainer.h"
#include "OSGActivity.h"
#include <boost/bind.hpp>

OSG_USING_NAMESPACE

ReflexiveContainer::TypeObject ReflexiveContainer::_type(
    "ReflexiveContainer",
    NULL,
    "ReflexiveContainer",
    0,
    NULL,
    false,
    0);

EventProducerType ReflexiveContainer::_producerType(
    "Invalid");

ReflexiveContainer::TypeObject &ReflexiveContainer::getType(void)
{
    return _type;
}

const ReflexiveContainer::TypeObject &ReflexiveContainer::getType(void) const
{
    return _type;
}

UInt32 ReflexiveContainer::getBinSize(ConstFieldMaskArg)
{
    return 0;
}


void ReflexiveContainer::copyToBin(BinaryDataHandler  &, 
                                   ConstFieldMaskArg   )
{
}

void ReflexiveContainer::copyFromBin(BinaryDataHandler  &, 
                                     ConstFieldMaskArg   )
{
}

EditFieldHandlePtr ReflexiveContainer::invalidEditField(void)
{
    return EditFieldHandlePtr();
}

GetFieldHandlePtr ReflexiveContainer::invalidGetField(void) const
{
    return GetFieldHandlePtr();
}

GetEventHandlePtr ReflexiveContainer::invalidGetEvent (void) const
{
    return GetEventHandlePtr();
}

void   ReflexiveContainer::disconnectAll(void)
{
    for(UInt32 i(0) ; i<getNumEvents() ; ++i)
    {
        disconnectAllSlotsEvent(i+1);
    }
}

inline
boost::signals2::connection ReflexiveContainer::attachActivity(UInt32 eventId,
                                                               Activity* TheActivity)
{
    return connectEvent(eventId, boost::bind(&Activity::eventProduced, TheActivity, _1, _2) );
}


#ifdef OSG_ENABLE_MEMORY_DEBUGGING
bool ReflexiveContainer::_check_is_deleted()
{
   return ((_bvChanged == 0xDEADBEEF) &&
           (_pContainerChanges == (ContainerChangeEntry*)(0xDEADBEEF)));
}
#endif
