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

#ifndef _OSGCOLLADACONTROLLER_H_
#define _OSGCOLLADACONTROLLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaInstantiableElement.h"
#include "OSGColladaElementFactoryHelper.h"
#include "OSGColladaGeometry.h"
#include "OSGNodeFields.h"

#include <vector>

OSG_BEGIN_NAMESPACE

// forward decl
class domInstanceController;
class ColladaInstanceController;
class ColladaAnimation;
class daeGeometry;

OSG_GEN_MEMOBJPTR(ColladaInstanceController);

class OSG_FILEIO_DLLMAPPING ColladaController : public ColladaInstantiableElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaInstantiableElement             Inherited;
    typedef ColladaController Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaController);


	static ColladaElementTransitPtr
        create(daeElement *elem, ColladaGlobal *global);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void read(void);

    virtual Node *
        createInstance(ColladaInstanceElement *instElem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

	struct SkinInfo {
		GeoVec1fPropertyRecPtr weights;
		Matrix bindShapeMatrix;

		std::vector<Matrix> inverseBindPoseMatrices;
		std::vector<std::string> jointSIDs;
		std::vector<UInt32> v;
		std::vector<UInt32> vCount;

	};

	const	SkinInfo &getSkinInfo	(void);

	bool	hasSkin					(void);

	struct MorphInfo {
		std::vector<Real32> weights;
		std::vector<domGeometry *> targets;
		domGeometry * source;
	};
	bool	hasMorph				(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaController(daeElement    *elem,
                                        ColladaGlobal *global);
    virtual ~ColladaController(void                 );

	void readSkin(domSkin *skin);
	void readMorph(domMorph *morph);

	// function to help with material binding
	void handleBindMaterial( Geometry *geo, 
							 ColladaInstanceController *colInstCont);

	GeometryTransitPtr handleGeometry(	domGeometryRef geometry, 
										ColladaInstanceElement *colInstElem );

	const ColladaGeometry::BindInfo       
		*findBind      (const ColladaGeometry::BindStore       &store,
					    const std::string     &semantic,
					    UInt32                &offset     );
    const ColladaGeometry::BindVertexInfo 
		*findBindVertex(const ColladaGeometry::BindVertexStore &store,
						const std::string     &inSemantic,
					    UInt32                 inSet,
					    UInt32                &offset     );

    NodeTransitPtr createJointFromNode(domNode *node);

	bool _hasSkin;
	bool _hasMorph;

	SkinInfo _mSkin;
	MorphInfo _mMorph;
    GeometryRefPtr _sourceMesh;
	ColladaGeometryRefPtr _sourceColGeo;

    ColladaAnimation *_animation;

	static ColladaElementRegistrationHelper _regHelper;

};

OSG_GEN_MEMOBJPTR(ColladaController);

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADACONTROLLER_H_
