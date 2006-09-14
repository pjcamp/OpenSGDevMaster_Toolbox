/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGGL.h>
#include <OSGGLEXT.h>

#include "OSGLog.h"

#include "OSGFieldContainerPtr.h"
#include "OSGGeometry.h"
#include "OSGDrawEnv.h"

#include "OSGMaterial.h"

#include "OSGGeoPumpGroup.h"
#include "OSGGeoImmediatePumpGroup.h"
#include "OSGGeoVertexArrayPumpGroup.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/* \class OSG::GeoPumpGroup
   \ingroup GrpSystemNodeCoresDrawablesGeometry
    
The PumpGroup is responsible for selecting the most appropriate pump
function to send the geometry's data to OpenGL in the most efficient manner.

The pump is selected inside the rendering function and should not be accessed
from the outside.

\dev The pump factory chooses the pump based on the used properties. For
non- and single-indexed geometry OpenGL VertexArrays are used, for
multi-indexed geometry an immediate mode pump has to be used. Specialized Pumps
for all combinations of properties are created to optimizie this case as much
as possible.
*/


std::vector<GeoPumpGroup*> *GeoPumpGroup::_activeGroups;

/*! Initialize the _activeGroups at startup.
*/
InitFuncWrapper GeoPumpGroup::actInit(GeoPumpGroup::initActiveGroups);

bool GeoPumpGroup::initActiveGroups(void)
{
    _activeGroups = new std::vector<GeoPumpGroup*>;
    
    _activeGroups->push_back(new GeoVertexArrayPumpGroup);
    _activeGroups->push_back(new GeoImmediatePumpGroup);
    
    addPostFactoryExitFunction(&GeoPumpGroup::terminateActiveGroups);

    return true;
}

bool GeoPumpGroup::terminateActiveGroups(void)
{
    for(UInt32 i = 0; i < _activeGroups->size(); ++i)
    {
        delete (*_activeGroups)[i];
    }
    
    delete _activeGroups;

    return true;
}

/*! PropertyCharacteristics handling.
*/

std::string GeoPumpGroup::describePropertyCharacteristics(
                                        PropertyCharacteristics ac)
{
    std::string result;
    
    if(ac & GeoPumpGroup::NonIndexed)    result += "NonIndexed,";
    if(ac & GeoPumpGroup::SingleIndexed) result += "SingleIndexed,";
    if(ac & GeoPumpGroup::MultiIndexed)  result += "MultiIndexed,";
    if(ac & GeoPumpGroup::NonTraditionalProperties) 
        result += "NonTraditionalProperties,";

    result.resize(result.length()-1);
    
    return result;
}

GeoPumpGroup::PropertyCharacteristics 
    GeoPumpGroup::characterizeGeometry(
    Geometry* geo)
{
    PropertyCharacteristics val = 0;
    
    Int16 natt = geo->getProperties().size();
    Int16 nind = geo->getPropIndices().size();
    
    // Check for single- and multi-indexed
    GeoIntegralPropertyPtr ind = NullFC;
    
    bool single = true;
    bool multi  = true;
    bool nonind = true;

    for(Int16 i = 0; i < natt; ++i)
    {
        // Only count actual attributes
        if(geo->getProperty(i) != NullFC)
        {
            if(i < nind)
            {
                if(geo->getIndex(i) == NullFC)
                {
                    single = false;
                    multi = false;
                }
                else
                {
                    nonind = false;
                    
                    if(ind == NullFC)
                        ind = geo->getIndex(i);
                    
                    if(geo->getIndex(i) != ind)
                        single = false;
                }
            }
            else
            {
               single = false;
               multi = false; 
            }
        }
    }
    
         if(nonind)  val |= GeoPumpGroup::NonIndexed;
    else if(single)  val |= GeoPumpGroup::SingleIndexed;
    else if(multi)   val |= GeoPumpGroup::MultiIndexed;
    
    // Check for non-traditional properties.
    // Right now just check existence of attribs 6&7
    // To be complete this would also have to check 
    // type compatibility! *DR*
    
    if(natt > 6 && geo->getProperty(6) != NullFC)
        val |= GeoPumpGroup::NonTraditionalProperties;
    if(natt > 7 && geo->getProperty(7) != NullFC)
        val |= GeoPumpGroup::NonTraditionalProperties;
        
    return val;
}

/*! Find the actual pumps for the given Window/Geometry.
*/
 
GeoPumpGroup::GeoPump GeoPumpGroup::findGeoPump(DrawEnv                 *pEnv, 
                                                PropertyCharacteristics  acset)
{
    GeoPump pump = NULL;
    
    Window *win = pEnv->getWindow();
    
    for(std::vector<GeoPumpGroup*>::iterator it = _activeGroups->begin();
        it != _activeGroups->end() && pump == NULL;
        ++it)
    {
        pump = (*it)->getGeoPump(pEnv,acset);
    }
    
    if(pump == NULL)
    {
        FWARNING(("GeoPumpGroup::findGeoPump: Couldn't find pump for"
                "Window %p and characteristics %s!\n", win, 
                describePropertyCharacteristics(acset).c_str() ));
    }
    return pump;
}

GeoPumpGroup::PartialGeoPump GeoPumpGroup::findPartialGeoPump(
    DrawEnv                 *pEnv, 
    PropertyCharacteristics  acset)
{
    return NULL;
}

GeoPumpGroup::ExtIndexGeoPump GeoPumpGroup::findExtIndexGeoPump(
    DrawEnv                 *pEnv, 
    PropertyCharacteristics  acset)
{
    return NULL;
}

GeoPumpGroup::~GeoPumpGroup()
{
}

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
    static Char8 cvsid_hpp       [] = OSGGEOPUMPGROUP_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGGEOPUMPGROUP_INLINE_CVSID;
}

