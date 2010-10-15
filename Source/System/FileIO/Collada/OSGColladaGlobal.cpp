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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaGlobal.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGColladaCOLLADA.h"
#include "OSGColladaElementFactory.h"
#include "OSGColladaOptions.h"
#include "OSGColladaAnimation.h"
#include "OSGColladaController.h"
#include "OSGColladaInstanceController.h"
#include "OSGNode.h"

#include "OSGSkeletonDrawable.h"

#include <dom/domInstance_controller.h>
#include <dom/domNode.h>

/*! \class OSG::ColladaGlobal
    This is the entry point for the Collada loader from which the loading
    process is started.
    You can think of it as representing the &lt;COLLADA&gt; tag in a document.
 */

OSG_BEGIN_NAMESPACE

StatElemDesc<StatIntElem> ColladaGlobal::statNGeometryCreated(
    "Collada::NGeometryCreated",
    "Number of OpenSG geometries created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);
StatElemDesc<StatIntElem> ColladaGlobal::statNGeometryUsed(
    "Collada::NGeometryUsed",
    "Number of OpenSG geometries in the scene created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);
StatElemDesc<StatIntElem> ColladaGlobal::statNMaterialCreated(
    "Collada::NMaterialCreated",
    "Number of OpenSG materials created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);
StatElemDesc<StatIntElem> ColladaGlobal::statNMaterialUsed(
    "Collada::NMaterialUsed",
    "Number of OpenSG materials in the scene created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);
StatElemDesc<StatIntElem> ColladaGlobal::statNLightCreated(
    "Collada::NLightCreated",
    "Number of OpenSG materials created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);
StatElemDesc<StatIntElem> ColladaGlobal::statNLightUsed(
    "Collada::NLightUsed",
    "Number of OpenSG materials in the scene created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);
StatElemDesc<StatIntElem> ColladaGlobal::statNTextureCreated(
    "Collada::NTextureCreated",
    "Number of OpenSG textures created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);
StatElemDesc<StatIntElem> ColladaGlobal::statNTextureUsed(
    "Collada::NTextureUsed",
    "Number of OpenSG textures in the scene created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);

StatCollector *
ColladaGlobal::getStatCollector(void)
{
    return _statColl;
}

void
ColladaGlobal::setStatCollector(StatCollector *statColl)
{
    _statColl = statColl;
}

ColladaGlobalTransitPtr
ColladaGlobal::create(void)
{
    return ColladaGlobalTransitPtr(new Self);
}

/*! Read the file \a fileName using a new DAE database.
 */
NodeTransitPtr
ColladaGlobal::read(std::istream &is, const std::string &fileName)
{
    NodeTransitPtr rootN;

    _pathHandler.clearPathList();
    _pathHandler.clearBaseFile();

    _pathHandler.push_frontCurrentDir(                );
    _pathHandler.setBaseFile         (fileName.c_str());

    _docPath = fileName;

    _dae = new DAE;
    _dae->open(fileName.c_str());

    rootN = doRead();

    _docPath. clear();
    _dae    ->clear();
    delete _dae;
    _dae = NULL;

    return rootN;
}

/*! Read the file \a fileName from the existing DAE database \a dae.
    The given \a fileName must already be loaded into the DAE.

    Useful if multiple documents are stored in one DAE database or
    if an application needs to access the DAE itself to extract
    data that is not processed by the loader.
 */
NodeTransitPtr
ColladaGlobal::read(DAE *dae, const std::string &fileName)
{
    NodeTransitPtr rootN(NULL);

    _pathHandler.clearPathList();
    _pathHandler.clearBaseFile();

    _pathHandler.push_frontCurrentDir(                );
    _pathHandler.setBaseFile         (fileName.c_str());

    _docPath = fileName;
    _dae     = dae;

    rootN = doRead();

    _docPath.clear();
    _dae = NULL;

    return rootN;
}

/*! Read the file \a fileName using a new DAE database. This
	method differs from the other read method in that it will 
	also read in other elements not directly associated with 
	the scene hierarchy (e.g. <library_animations>, etc.)
	if the options to do so are set.

    Useful if multiple documents are stored in one DAE database or
    if an application needs to access the DAE itself to extract
    data that is not processed by the loader.
 */
ColladaGlobal::FCPtrStore 
ColladaGlobal::readAll( std::istream &is, const std::string &fileName)
{
	NodeTransitPtr rootN;
	getOptions()->setCreateNameAttachments(true);
	getOptions()->setFlattenNodeXForms(true);
    _pathHandler.clearPathList();
    _pathHandler.clearBaseFile();

    _pathHandler.push_frontCurrentDir(                );
    _pathHandler.setBaseFile         (fileName.c_str());

    _docPath = fileName;

    _dae = new DAE;
    _dae->open(fileName.c_str());

	if(getOptions()->getReadAnimations())
	{ // read animations here
		FCPtrStore animations = readAnimations();
		_FCStore.insert(animations.begin(), animations.end());
	}

    rootN = doRead();
	_FCStore.insert(rootN);

    _docPath. clear();
    _dae    ->clear();
    delete _dae;
    _dae = NULL;

    return _FCStore;

}

void
ColladaGlobal::addElement(ColladaElement *elem)
{
    _elemStore.push_back(elem);
}

ColladaGlobal::ColladaGlobal(void)
    : Inherited   ()
    , _elemStore  ()
    , _options    ()
    , _statColl   (NULL)
    , _pathHandler()
    , _docPath    ()
    , _dae        (NULL)
    , _rootN      (NULL)
{
}

ColladaGlobal::~ColladaGlobal(void)
{
    delete _dae;
    _dae = NULL;
}

/*! Read the file stored in _docPath from the DAE _dae.
 */
NodeTransitPtr
ColladaGlobal::doRead(void)
{
    NodeTransitPtr rootN(NULL);

    if(_statColl == NULL)
        _statColl = new StatCollector;

    // force creation of the statistic elements
    _statColl->getElem(statNGeometryCreated, true);
    _statColl->getElem(statNGeometryUsed,    true);
    _statColl->getElem(statNMaterialCreated, true);
    _statColl->getElem(statNMaterialUsed,    true);
    _statColl->getElem(statNLightCreated, true);
    _statColl->getElem(statNLightUsed,    true);
    _statColl->getElem(statNTextureCreated,  true);
    _statColl->getElem(statNTextureUsed,     true);

    _statColl->reset  (StatElemDescBase::RESET_ALWAYS);

    domCOLLADARef docRoot = _dae->getRoot(_docPath);

    if(docRoot != NULL)
    {
        ColladaCOLLADARefPtr colCOL = dynamic_pointer_cast<ColladaCOLLADA>(
            ColladaElementFactory::the()->create(docRoot, this));

        colCOL->read();
    }
    else
    {
        SWARNING << "ColladaGlobal::read: collada-dom failed to obtain "
                 << "document root for file [" << _docPath << "]."
                 << std::endl;
    }
    
    rootN = _rootN;

	resolveControllers();

    _elemStore.clear();

#ifndef OSG_COLLADA_SILENT
    std::string statString;
    _statColl->putToString(statString);

    OSG_COLLADA_LOG(("ColladaGlobal:read: Statistics\n%s\n",
                     statString.c_str()));
#endif // OSG_COLLADA_SILENT

    return rootN;
}

ColladaGlobal::FCPtrStore ColladaGlobal::readAnimations(void)
{
	FCPtrStore animations;
	
	domCOLLADARef docRoot = _dae->getRoot(_docPath);

    if(docRoot != NULL)
    {
		domLibrary_animations_Array libAnims = docRoot->getLibrary_animations_array();
		for(UInt32 i(0); i < libAnims.getCount(); i++)
		{
			domAnimation_Array anims = libAnims[i]->getAnimation_array();
			for(UInt32 j(0); j < anims.getCount(); j++)
			{

				ColladaAnimationRefPtr colAnim = dynamic_pointer_cast<ColladaAnimation>(
								ColladaElementFactory::the()->create(anims[j], this));
				
				colAnim->read();
			}
		}
    }
	return animations;
}

void 
ColladaGlobal::resolveControllers(void)
{
	
	for(UInt32 i(0); i < _instControllers.size(); ++i)
	{
		ColladaController * cont = _instControllers[i]->getTargetElem();

		if(cont->hasSkin())
		{
			const ColladaController::SkinInfo &skin = cont->getSkinInfo();

			domInstance_controller::domSkeleton_Array skelArr = _instControllers[i]->getJoints();
			std::map<std::string, NodeRecPtr> joints;

			std::vector<domNodeRef> domNodes;
			// fetch the nodes

			for(UInt32 j = 0; j < skelArr.getCount(); j++)
			{
				domNodeRef colDomNode = daeSafeCast<domNode>(skelArr[j]->getValue().getElement());
				parseJointNodes(colDomNode,domNodes,joints);
			}

			UInt32 j(0);
			SkeletonBlendedGeometry *skeleton = _instControllers[i]->getSkeleton();
			for(j = 0; j < skin.jointSIDs.size() && j < skin.inverseBindPoseMatrices.size(); j++)
			{
				// now we need to match up the SID of this domNode to the joint
				for(UInt32 k = 0; k < domNodes.size(); k++)
				{
					if(skin.jointSIDs[j].compare(domNodes[k]->getSid()) == 0)
					{	// this is a match, so push it to the skeleton
		                
						skeleton->pushToJoints(joints[skin.jointSIDs[j]],skin.inverseBindPoseMatrices[j]);
						break;
					}
				}
			}

			// handle joint blending
			UInt32 k(0),m(0);
			for(j = 0; j < skin.vCount.size(); j++)
			{
				for(k = 0; k < skin.vCount[j]; k++, m += 2)
				{
					skeleton->addJointBlending(j,skin.v[m],skin.v[m+1]);
				}
			}

		} // end if(hasSkin())
		else if(cont->hasMorph()) 
		{
			// morphs NIY
		}
	}

	return;
}

void ColladaGlobal::parseJointNodes(domNodeRef colDomNode, 
					 std::vector<domNodeRef> &domNodes,
					 std::map<std::string, NodeRecPtr> &joints)
{
	// check the type of the node
	if(colDomNode->getType() == NODETYPE_JOINT)
	{	// add all joints found to the map
		if(colDomNode->getSid() != NULL)
		{
			std::string nodeName = colDomNode->getSid();
			domNodes.push_back(colDomNode);
			
			NodeRecPtr jointNode = _nodeMap[colDomNode];
			joints[nodeName] = jointNode;
			// recursively add child joints to the map.
			const domNode_Array &nodes = colDomNode->getNode_array();
			for(UInt32 i(0); i < nodes.getCount(); i++)
			{
				parseJointNodes(nodes[i], domNodes, joints);
			}
		}
	}
}

void ColladaGlobal::addInstanceController( ColladaInstanceController * const contr)
{
	_instControllers.push_back(contr);
}

ColladaGlobal::NodeToNodeMap & 
ColladaGlobal::editNodeToNodeMap(void)
{
	return _nodeMap;
}

ColladaGlobal::AnimationMap &
ColladaGlobal::editAnimationMap(void)
{
	return _animMap;
}



OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
