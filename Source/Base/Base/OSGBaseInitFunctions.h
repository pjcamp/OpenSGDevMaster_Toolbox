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

#ifndef _OSGBASEINITFUNCTIONS_H_
#define _OSGBASEINITFUNCTIONS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"

#include <vector>
#include <map>
#include <string>
#include <boost/function.hpp>

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*                           Initialization                            */

/*! \ingroup GrpBaseBaseInitExit
 */

enum SystemState
{
    Startup      = 0x01,
    Running      = 0x02,
    Shutdown     = 0x03,
    PostShutdown = 0x04
};

extern OSG_BASE_DLLMAPPING SystemState GlobalSystemState;

// Init sequence:
//
// * PreMP
// * MP              internal call
// * PreFactories
// * Factories       internal call
// * PostFactories

typedef boost::function<bool (void)> InitFuncF;

// Shutdown sequence:
//
// * PreFactories
// * Factories       internal call
// * PostFactories
// * MP              internal call
// * PostMP

typedef boost::function<bool (void)> ExitFuncF;

/*! \ingroup GrpBaseBaseInitExit
    \ingroup GrpBaseBase
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct OSG_BASE_DLLMAPPING InitFuncWrapper
{
    /*---------------------------------------------------------------------*/
    /*! \name                      Constructors                            */
    /*! \{                                                                 */

    InitFuncWrapper(const InitFuncF func);

    /*! \}                                                                 */
};

/*! \ingroup GrpBaseBaseInitExit
    \ingroup GrpBaseBase
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct OSG_BASE_DLLMAPPING StaticInitFuncWrapper
{
    /*---------------------------------------------------------------------*/
    /*! \name                      Constructors                            */
    /*! \{                                                                 */

    StaticInitFuncWrapper(const InitFuncF func);

    /*! \}                                                                 */
};


OSG_BASE_DLLMAPPING 
void addPreMPInitFunction      (OSG::InitFuncF initFunc);

OSG_BASE_DLLMAPPING 
void addPreFactoryInitFunction (OSG::InitFuncF initFunc);

OSG_BASE_DLLMAPPING 
void addPostFactoryInitFunction(OSG::InitFuncF initFunc);


OSG_BASE_DLLMAPPING 
void addPreFactoryExitFunction (OSG::ExitFuncF exitFunc);

OSG_BASE_DLLMAPPING 
void addPostFactoryExitFunction(OSG::ExitFuncF exitFunc);

OSG_BASE_DLLMAPPING 
void addPreMPExitFunction      (OSG::ExitFuncF exitFunc);

OSG_BASE_DLLMAPPING 
void addPostMPExitFunction     (OSG::ExitFuncF exitFunc);

/*---------------------------------------------------------------------*/
/*! \name init / exit                                                  */
/*! \{                                                                 */

OSG_BASE_DLLMAPPING
void preloadSharedObject       (const OSG::TChar *szName);

OSG_BASE_DLLMAPPING
void addLibraryVersion         (const std::string& szName,
                                const std::string& szVersion,
                                const std::string& szRevision);

OSG_BASE_DLLMAPPING
UInt32 getNumLibraries         (void);

OSG_BASE_DLLMAPPING
std::string getLibraryName     (UInt32 Index);

OSG_BASE_DLLMAPPING
std::string getLibraryVersion  (const std::string& szName);

OSG_BASE_DLLMAPPING
std::string getLibraryRevision (const std::string& szName);

#ifdef _DEBUG  
# define OSG_INIT_DEBUG true
#else
# define OSG_INIT_DEBUG false
#endif
#ifdef _DLL  
# define OSG_INIT_DLL   true
#else
# define OSG_INIT_DLL   false
#endif
#ifdef _MT  
#define OSG_INIT_MT     true
#else
#define OSG_INIT_MT     false
#endif

// osgInit needs to be inline (at least on windows),
// see OSGBaseInitFunctions.inl for an explanation.

inline
bool osgInit  (OSG::Int32    argc, 
               OSG::Char8  **argv,
               OSG::UInt16   major   = OSG_MAJOR_VERSION, 
               OSG::UInt16   minor   = OSG_MINOR_VERSION, 
               OSG::UInt16   release = OSG_RELEASE_VERSION,
               bool          debug   = OSG_INIT_DEBUG,
               bool          dll     = OSG_INIT_DLL,
               bool          mt      = OSG_INIT_MT        );

OSG_BASE_DLLMAPPING 
bool osgExit(void);

/*! \}                                                                 */

OSG_BASE_DLLMAPPING
bool osgDoInit(OSG::Int32    argc,
               OSG::Char8  **argv,
               OSG::UInt16   major   = OSG_MAJOR_VERSION, 
               OSG::UInt16   minor   = OSG_MINOR_VERSION, 
               OSG::UInt16   release = OSG_RELEASE_VERSION,
               bool          debug   = OSG_INIT_DEBUG,
               bool          dll     = OSG_INIT_DLL,
               bool          mt      = OSG_INIT_MT        );

OSG_BASE_DLLMAPPING
void osgExitWrapper(void);

OSG_END_NAMESPACE

#include "OSGBaseInitFunctions.inl"

#endif /* OSGBASEINITFUNCTIONS_H */
