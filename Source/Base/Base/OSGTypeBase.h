/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2003 by the OpenSG Forum                    *
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

#ifndef _OSGTYPEBASE_HPP_
#define _OSGTYPEBASE_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class TypeFactoryBase;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBaseTypeSystem
    \ingroup GrpBaseBase
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING TypeBase
{
  public:

    //-----------------------------------------------------------------------
    //   constants
    //-----------------------------------------------------------------------

    static const UInt32 GlobalNamespace = 0;

    //-----------------------------------------------------------------------
    //   enums
    //-----------------------------------------------------------------------

    enum InitPhase
    {
        Static      = 0x0000,
        SystemPre   = 0x0001,
        SystemPost  = 0x0002,
        FactoryPost = 0x0004
    };

    //-----------------------------------------------------------------------
    //   types
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes
    //-----------------------------------------------------------------------

    friend class TypeFactoryBase;
    friend class EventProducerFactoryBase;

    //-----------------------------------------------------------------------
    //   friend functions
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions
    //-----------------------------------------------------------------------

    //! prohibit default function (move to 'public' if needed)
    void operator =(const TypeBase &source);

  protected:

    //-----------------------------------------------------------------------
    //   enums
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables
    //-----------------------------------------------------------------------

    UInt32       _uiTypeId;     /*!< Unique id of type in global type system. */
    //UInt32     _uiTypeRootId;
    UInt32       _uiNameSpace;  /*!< Namespace that the id belongs to. */

    TypeBase    *_pParentType;  /*!< The type of the parent, if one exists. */

    std::string  _szName;       /*!< The name of this type. */
    std::string  _szParentName; /*!< The name of the parent type. */

    bool         _bInitialized; /*!< Set true once type has been initialized. */

    //-----------------------------------------------------------------------
    //   instance functions
    //-----------------------------------------------------------------------

    TypeBase(const TypeBase &source);

    virtual bool initialize(void);
    virtual void terminate (void);

  public :

    //-----------------------------------------------------------------------
    //   class functions
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions
    //-----------------------------------------------------------------------

    TypeBase(const std::string             &szName, 
             const std::string             &szParentName,
             const UInt32  uiNamespace = GlobalNamespace);

    virtual ~TypeBase(void);

    /*----------------------------- id --------------------------------------*/

          UInt32       getId         (void) const;

    const std::string &getName       (void) const;
    const Char8       *getCName      (void) const;

    const TypeBase    &getParent     (void) const;
    const std::string &getParentName (void) const;
    const Char8       *getCParentName(void) const;

          UInt32       getNameSpace  (void) const;

    /*------------------------- your_operators ------------------------------*/

            bool isInitialized(      void           ) const;

    virtual bool isDerivedFrom(const TypeBase &other) const;


    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    bool operator ==(const TypeBase &other) const;
    bool operator !=(const TypeBase &other) const;


    /*------------------------- comparison ----------------------------------*/

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;
};

OSG_END_NAMESPACE

#endif /* _OSGTYPEBASE_HPP_ */

