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

#include "OSGStatTimeElem.h"
#include "OSGBaseFieldTraits.h"

#include <boost/format.hpp>

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::StatTimeElem

    The StatIntElem keeps a OSG::Time value for time measurements, 
    see \ref PageSystemStatistics for details. 
*/

/***************************************************************************\
 *                         Instance methods                                *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

StatTimeElem::StatTimeElem(StatElemDescBase *desc) :
     StatElem(desc),
    _lastStartTime(   0),
    _accumTime    (   0)
{
}

StatElem *StatTimeElem::create(StatElemDescBase *desc)
{
    return new StatTimeElem(desc);
}


StatTimeElem::~StatTimeElem(void)
{
}

/*------------------------------ access -----------------------------------*/

void StatTimeElem::putToString(
    std::string &str, const std::string &format) const
{
    if(format.empty())
    {
        // Confusing if %e is used.

        Char8 temp[64];

        sprintf(temp, "%f", _accumTime);

        str.assign(temp);
    }
    else
    {
        std::string            formatCopy = format;
        std::string::size_type pos        = formatCopy.find("%");
        Time                   val        = _accumTime;
        
        if(pos != std::string::npos)
        {
            if((pos = formatCopy.find("%ms")) != std::string::npos)
            {
                formatCopy.replace(pos, 3, "%.2f");
                val *= 1000.f;
            }
            else if((pos = formatCopy.find("%r")) != std::string::npos)
            {
                formatCopy.replace(pos, 2, "%");
                if(val <= TypeTraits<Time>::ZeroEps())
                {
                    val = 0.;
                }
                else
                {
                    val = 1. / val;
                }
            }
        }
        
        boost::format fmt(formatCopy);
        
        fmt % val;
        
        str = fmt.str();
    }

#if 0
        const Char8 *proc = strchr(format,'%');        
              Char8 *temp = new Char8[strlen(format) + 60];

        if(proc)
        {
            if(! strncmp(proc, "%ms", 3))
            {
                std::string fcopy(format);
                fcopy.erase((proc - format) + 1, 2);
                fcopy.insert((proc - format) + 1,".2f");
                sprintf(temp, fcopy.c_str(), (double(_accumTime))*1000.);
            }
            else if(! strncmp(proc, "%r", 2))
            {
                std::string fcopy(format);
                fcopy.erase((proc - format) + 1, 1);
                sprintf(temp, fcopy.c_str(), 1./double(_accumTime));
            }
            else
            {
                sprintf(temp, format, double(_accumTime));
            }
           
        }
        else
        {
            sprintf(temp, format, double(_accumTime));
        }
        
        str = temp;
        delete [] temp;
    }
#endif
}

bool StatTimeElem::getFromCString(const Char8 *&inVal)
{
    return FieldTraits<Time, 1>::getFromCString(_accumTime, inVal);
}

Real64 StatTimeElem::getValue(void) const
{
    return static_cast<Real64>(getTime());
}

void StatTimeElem::reset(void) 
{ 
    _accumTime = 0;
}

/*-------------------------- assignment -----------------------------------*/

StatTimeElem& StatTimeElem::operator = (const StatTimeElem &source)
{
    if (this == &source)
        return *this;

    _lastStartTime = source._lastStartTime;
    _accumTime = source._accumTime;
    
    return *this;
}

/*-------------------------- comparison -----------------------------------*/

bool StatTimeElem::operator < (const StatTimeElem &other) const
{
    return _accumTime < other._accumTime;
}

/*--------------------------- creation ------------------------------------*/

StatElem *StatTimeElem::clone(void) const
{
    StatTimeElem *e = new StatTimeElem(getDesc());
    
    *e = *this;
    
    return e;
}

/*--------------------------- operators ------------------------------------*/

StatElem &StatTimeElem::operator += (const StatElem &other)
{
    const StatTimeElem *o = dynamic_cast<const StatTimeElem *>(&other);
    
    _accumTime += o->_accumTime;
    
    return *this;
}

