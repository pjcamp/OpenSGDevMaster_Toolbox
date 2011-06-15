/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#ifndef _OSGCOLLADAGLOBAL_H_
#define _OSGCOLLADAGLOBAL_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaGlobal.h
    \ingroup GrpLoader
 */
#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGFileIODef.h"
#include "OSGMemoryObject.h"
#include "OSGPathHandler.h"
#include "OSGNode.h"
#include "OSGColladaElement.h"
#include "OSGColladaOptions.h"
#include "OSGStatElemTypes.h"
#include "OSGStatCollector.h"
#include "OSGFCFileType.h"

// collada dom includes
#include <dae.h>
#include <dom/domCOLLADA.h>

#include <string>
#include <vector>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */
class ColladaInstanceController;
class FieldAnimation;
class ColladaAnimation;

class OSG_FILEIO_DLLMAPPING ColladaGlobal : public MemoryObject
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
	typedef FCFileType::FCPtrStore FCPtrStore;
    /*! \{                                                                 */

    typedef MemoryObject   Inherited;
    typedef ColladaGlobal  Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaGlobal);

    typedef std::vector<ColladaElementRefPtr> ElementStore;
    typedef ElementStore::iterator            ElementStoreIt;
    typedef ElementStore::const_iterator      ElementStoreConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Statistics                                                   */
    /*! \{                                                                 */

    static StatElemDesc<StatIntElem> statNGeometryCreated;
    static StatElemDesc<StatIntElem> statNGeometryUsed;
    static StatElemDesc<StatIntElem> statNMaterialCreated;
    static StatElemDesc<StatIntElem> statNMaterialUsed;
    static StatElemDesc<StatIntElem> statNLightCreated;
    static StatElemDesc<StatIntElem> statNLightUsed;
    static StatElemDesc<StatIntElem> statNTextureCreated;
    static StatElemDesc<StatIntElem> statNTextureUsed;

    StatCollector *getStatCollector(void                   );
    void           setStatCollector(StatCollector *statColl);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Create                                                       */
    /*! \{                                                                 */

    static ObjTransitPtr create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Read                                                         */
    /*! \{                                                                 */

    NodeTransitPtr read(      std::istream &is,
                        const std::string  &fileName);

    NodeTransitPtr read(      DAE          *dae,
                        const std::string  &fileName);

	FCPtrStore readAll( std::istream &is,
						const std::string &fileName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    inline const DAE          *getDAE       (void                      ) const;
    inline DAE                *editDAE      (void                      );

    inline const std::string  &getDocPath   (void                      ) const;
    inline void                setDocPath   (const std::string &docPath);

    inline ColladaOptions     *getOptions   (void                      ) const;
    inline void                setOptions   (ColladaOptions    *options);

    inline Node               *getRoot      (void                      ) const;
    inline void                setRoot      (Node              *rootN  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name ElementStore                                                 */
    /*! \{                                                                 */

    inline const ElementStore &getElemStore (void                      ) const;
    inline ElementStore       &editElemStore(void                      );

           void                addElement   (ColladaElement    *elem   );

           ColladaElement     *getElement   (const daeURI      &elemURI) const;
           ColladaElement     *getElement   (const std::string &elemId ) const;

	inline 
	bool				addFieldContainer		(FieldContainer * fc);

	inline 
	const FCPtrStore	getFieldContainerStore	( void ) const;

	inline			
	FCPtrStore			editFieldContainerStore	( void );

	void	addInstanceController		( ColladaInstanceController * const contr );

	typedef std::map<domNode* ,Node*>	NodeToNodeMap;
	typedef NodeToNodeMap::iterator		NTNMapIt;

	typedef std::map<daeElement *, ColladaAnimation *> AnimationMap;
	typedef AnimationMap::iterator AnimMapIt;

	NodeToNodeMap			&editNodeToNodeMap			(void);
	AnimationMap			&editAnimationMap			(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             ColladaGlobal(void);
    virtual ~ColladaGlobal(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Read                                                         */
    /*! \{                                                                 */

    NodeTransitPtr	doRead				(void);
	FCPtrStore		readAnimations		(void);
	void			resolveControllers	(void);
	void parseJointNodes(domNodeRef colDomNode, 
						 std::vector<domNodeRef> &domNodes,
						 std::map<std::string, NodeRecPtr> &joints);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    ElementStore          _elemStore;

    ColladaOptionsRefPtr  _options;
    StatCollectorRefPtr   _statColl;

    PathHandler           _pathHandler;
    std::string           _docPath;

    DAE                  *_dae;

    NodeUnrecPtr          _rootN;
	FCPtrStore			  _FCStore;

	std::vector<ColladaInstanceController *> _instControllers;
	AnimationMap _animMap;

	NodeToNodeMap		  _nodeMap;

};


OSG_GEN_MEMOBJPTR(ColladaGlobal);

OSG_END_NAMESPACE

#include "OSGColladaGlobal.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAGLOBAL_H_
