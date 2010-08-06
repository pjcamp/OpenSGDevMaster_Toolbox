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

#include "OSGColladaController.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"
#include "OSGColladaGlobal.h"
#include "OSGColladaSource.h"
#include "OSGColladaInstanceController.h"
#include "OSGColladaGeometry.h"
#include "OSGColladaInstanceGeometry.h"
#include "OSGColladaInstanceEffect.h"

#include "OSGGroup.h"
#include "OSGTransform.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGNameAttachment.h"

#include <dom/domGeometry.h>
#include <dom/domMesh.h>
#include <dom/domSource.h>
#include <dom/domLines.h>
#include <dom/domLinestrips.h>
#include <dom/domPolygons.h>
#include <dom/domPolylist.h>
#include <dom/domTriangles.h>
#include <dom/domTrifans.h>
#include <dom/domTristrips.h>


// skeleton drawable material includes...
#include "OSGLineChunk.h"
#include "OSGBlendChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"

#include "OSGSkeletonBlendedGeometry.h"
#include "OSGSkeletonDrawable.h"


OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaController::_regHelper(
    &ColladaController::create, "controller");


ColladaElementTransitPtr
ColladaController::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaController(elem, global));
}

void
ColladaController::read(void)
{
    OSG_COLLADA_LOG(("ColladaController::read\n"));

    domControllerRef cont  = getDOMElementAs<domController>();

    domSkinRef     skin = cont->getSkin();
	domMorphRef    morph = cont->getMorph();

    if(skin != NULL )
    {
		readSkin(skin);
    } 
	else if (morph != NULL)
	{
		readMorph(morph);
	}
	else
	{
		SWARNING << "ColladaController::read: No <skin>" << std::endl;
	}

    return;
}

void 
ColladaController::readSkin(domSkin *skin)
{
	_hasSkin = true;
	// save the bind shape matrix
	domFloat4x4 bsm = skin->getBind_shape_matrix()->getValue();

	_mSkin.bindShapeMatrix = Matrix(bsm[0],bsm[1],bsm[2],bsm[3],
									bsm[4],bsm[5],bsm[6],bsm[7],
									bsm[8],bsm[9],bsm[10],bsm[11],
									bsm[12],bsm[13],bsm[14],bsm[15]);

	// get the joint source
	domSkin::domJointsRef dJoints = skin->getJoints();
	domInputLocal_Array inputs = dJoints->getInput_array();

	// these two arrays correspond one to one, from the joint name to its inverse bind matrix
	domName_arrayRef jointNamesArr;
	domFloat_arrayRef IBPMArr;
	UInt32 i(0),j(0),nameCount(0),matrixCount(0),stride(0);
	for(i = 0; i < inputs.getCount(); i++)
	{
		std::string sem = inputs[i]->getSemantic();
		if(sem.compare("JOINT") == 0) 
		{
			domSourceRef src = daeSafeCast<domSource>(inputs[i]->getSource().getElement());
			nameCount = src->getTechnique_common()->getAccessor()->getCount();
			jointNamesArr = src->getName_array();
		}
		else if(sem.compare("INV_BIND_MATRIX") == 0) 
		{
			domSourceRef src = daeSafeCast<domSource>(inputs[i]->getSource().getElement());
			IBPMArr = src->getFloat_array();
			matrixCount = src->getTechnique_common()->getAccessor()->getCount();
			stride = src->getTechnique_common()->getAccessor()->getStride();
		}
	}

	// extracting the actual inverse bind matrices and joint sids from the arrays.
	// this is done after finding the sources in order to ensure joints and their
	// inverse bind pose matrices have the same index.
	if(stride == 16 && nameCount == matrixCount)
	{ // if the stride isn't 16, then we can't get the matrices!
		domListOfFloats vals = IBPMArr->getValue();
		for(i = 0; i < vals.getCount(); i+=16)
		{

			Matrix newMatrix(vals[i],vals[i+1],vals[i+2],vals[i+3],
							 vals[i+4],vals[i+5],vals[i+6],vals[i+7],
							 vals[i+8],vals[i+9],vals[i+10],vals[i+11],
							 vals[i+12],vals[i+13],vals[i+14],vals[i+15]);

			_mSkin.inverseBindPoseMatrices.push_back(newMatrix);
		}
		// grabbing the actual SIDs of the joints
		domListOfNames names = jointNamesArr->getValue();
		for(i = 0; i < names.getCount(); i++)
		{
			_mSkin.jointSIDs.push_back(names[i]);
		}
	}

	// getting the vertex weights
	domSkin::domVertex_weightsRef vertWts = skin->getVertex_weights();
	domInputLocalOffset_Array VWInputs = vertWts->getInput_array();

	for(i = 0; i < VWInputs.getCount(); i++)
	{
		std::string sem = VWInputs[i]->getSemantic();
		if(sem.compare("WEIGHT") == 0)
		{
			domSourceRef src = daeSafeCast<domSource>(VWInputs[i]->getSource().getElement());
			domListOfFloats wts = src->getFloat_array()->getValue();
			
			for(j = 0; j < wts.getCount(); j++)
			{
				_mSkin.weights->push_back(Vec1f(wts[j]));
			}
		}
	}

	// get v and vcount values
	if(vertWts->getV() != NULL)
	{
		domListOfInts vList =  vertWts->getV()->getValue();
		for(i = 0; i < vList.getCount(); i++)
		{
			_mSkin.v.push_back(vList[i]);
		}
	}

	if(vertWts->getVcount() != NULL)
	{
		domListOfUInts vCountList = vertWts->getVcount()->getValue();

		for(i = 0; i < vCountList.getCount(); i++)
		{
			_mSkin.vCount.push_back(vCountList[i]);
		}
	}

	domGeometryRef  geometry = daeSafeCast<domGeometry>(skin->getSource().getElement());

	_sourceColGeo = dynamic_pointer_cast<ColladaGeometry>(
            ColladaElementFactory::the()->create(
                geometry, getGlobal()));

	_sourceColGeo->read();
}

void ColladaController::readMorph(domMorph *morph)
{
	_hasMorph = true;

	return; // for now
}

Node *
ColladaController::createInstance(ColladaInstanceElement *colInstElem)
{
	ColladaInstanceControllerRefPtr colInstCont =
			dynamic_cast<ColladaInstanceController *>(colInstElem);

	domControllerRef controller  = getDOMElementAs<domController>();

    typedef ColladaInstanceController::MaterialMap        MaterialMap;
    typedef ColladaInstanceController::MaterialMapConstIt MaterialMapConstIt;

	
    domGeometryRef  geometry; 
	if(_hasSkin)
	{
		geometry = daeSafeCast<domGeometry>(controller->getSkin()->getSource().getElement());
	}
	else if(_hasMorph)
	{
		geometry = daeSafeCast<domGeometry>(controller->getMorph()->getSource().getElement());
	}

    const MaterialMap &matMap = colInstCont->getMaterialMap();

    // iterate over all parts of geometry
	ColladaGeometry::GeoStoreIt         gsIt   = _sourceColGeo->_geoStore.begin();
    ColladaGeometry::GeoStoreIt         gsEnd  = _sourceColGeo->_geoStore.end  ();

	GeometryRefPtr   geo      = NULL;

    for(; gsIt != gsEnd; ++gsIt)
    {
        OSG_ASSERT(gsIt->_propStore.size() == gsIt->_indexStore.size());

        // find the material associated with the geometry's material symbol
        MaterialMapConstIt mmIt       = matMap.find(gsIt->_matSymbol);
        std::string        matTarget;

        if(mmIt != matMap.end())
        {
            matTarget = mmIt->second->getTarget();
        }

        // check if the geometry was already used with that material

        
        ColladaGeometry::InstanceMapConstIt instIt   = gsIt->_instMap.find(matTarget);

        if(instIt != gsIt->_instMap.end())
        {
            // reuse geometry

            geo = dynamic_pointer_cast<Geometry>(
                getInstStore()[instIt->second]);

            getGlobal()->getStatCollector()->getElem(
                ColladaGlobal::statNGeometryUsed)->inc();
        }
        else
        {
            // create new geometry

            geo = Geometry::create();

            getGlobal()->getStatCollector()->getElem(
                ColladaGlobal::statNGeometryCreated)->inc();

            geo->setLengths(gsIt->_lengths);
            geo->setTypes  (gsIt->_types  );

            handleBindMaterial(*gsIt, geo, colInstCont);

            // record the instantiation of the geometry with the
            // material for reuse
            gsIt->_instMap.insert(
                ColladaGeometry::InstanceMap::value_type(matTarget, getInstStore().size()));

            editInstStore().push_back(geo);
        }
        
        if(geo != NULL) break;
    }

	if(++gsIt != gsEnd) SWARNING << "ColladaController::createInstance: Geometry parially ignored!" << std::endl;
	if(geo == NULL) return NULL; // can't do anything without the geometry!

	// create the skeleton.  Joints won't be fully resolved until later (see ColladaGlobal)
	SkeletonBlendedGeometryRecPtr skeleton = SkeletonBlendedGeometry::create();	
	skeleton->setBaseGeometry(geo);
	skeleton->setBindTransformation(_mSkin.bindShapeMatrix);

	NodeRecPtr skelNode = makeNodeFor(skeleton);

	skeleton->setWeights(_mSkin.weights);
	// get skeleton joints
	domInstance_controller::domSkeleton_Array skelArr = colInstCont->getJoints();
    std::map<std::string, NodeRecPtr> joints;
	std::vector<NodeRecPtr> osgNodes;
	std::vector<domNodeRef> domNodes;
	// create the joints/nodes and fetch the nodes
	UInt32 i(0),j(0);
	for(i = 0; i < skelArr.getCount(); i++)
	{
		domNodeRef colDomNode = daeSafeCast<domNode>(skelArr[i]->getValue().getElement());

		std::string nodeName = colDomNode->getSid();
		domNodes.push_back(colDomNode);

		NodeRecPtr jointNode = createJointFromNode(colDomNode);
		joints[nodeName] = jointNode;

		setName(jointNode,colDomNode->getSid());
		osgNodes.push_back(jointNode);
	}

	/* 
		The heirarchy of the skeleton structure must be created from the 
		visual scene node heirarchy.  But, since we don't want to have two
		instances of the heirarchy, we just save the IDs of the nodes to a map, and 
		link up the joints after the visual scene is finished reading.
	*/

	/*
	for(i = 0; i < domNodes.size(); i++)
	{
		domNodeRef parent = daeSafeCast<domNode>(domNodes[i]->getParent());
		if(parent != NULL && parent->getType() == NODETYPE_JOINT)
		{
			for(j = 0; j < domNodes.size(); j++)
			{
				std::string parentSID(parent->getSid());
				std::string childSID(domNodes[j]->getSid());
				if(parentSID.compare(childSID) == 0)
				{	
					osgNodes[j]->addChild(osgNodes[i]);
				}
			}
		} else
		{
			skelNode->addChild(osgNodes[i]);
		}
	}

	

    for(j = 0; j < _mSkin.jointSIDs.size() && j < _mSkin.inverseBindPoseMatrices.size(); j++)
    {
        // now we need to match up the SID of this domNode to the joint
        for(i = 0; i < domNodes.size(); i++)
        {
			if(_mSkin.jointSIDs[j].compare(domNodes[i]->getSid()) == 0)
			{	// this is a match, so push it to the skeleton
                
				skeleton->pushToJoints(joints[_mSkin.jointSIDs[j]],_mSkin.inverseBindPoseMatrices[j]);
			    break;
			}
		}
	}
	
	int k(0);
	for(i = 0; i < _mSkin.vCount.size(); i++)
	{
		for(j = 0; j < _mSkin.vCount[i]; j++, k += 2)
		{
			skeleton->addJointBlending(i,_mSkin.v[k],_mSkin.v[k+1]);
		}
	}
	
	colInstCont->setSkeleton(skeleton);
	editInstStore().push_back(skelNode);

	return skelNode; 
	*/
	
	// the code below is added to draw the bones of the skeletons

	 //SkeletonDrawer System Material
    LineChunkRecPtr ExampleLineChunk = LineChunk::create();
    ExampleLineChunk->setWidth(2.0f);
    ExampleLineChunk->setSmooth(true);

    BlendChunkRecPtr ExampleBlendChunk = BlendChunk::create();
    ExampleBlendChunk->setSrcFactor(GL_SRC_ALPHA);
    ExampleBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

    ChunkMaterialRecPtr ExampleMaterial = ChunkMaterial::create();
    ExampleMaterial->addChunk(ExampleLineChunk);
    ExampleMaterial->addChunk(ExampleBlendChunk);

	SkeletonDrawableRecPtr skelDraw = SkeletonDrawable::create();
	skelDraw->setSkeleton(skeleton);
	skelDraw->setMaterial(ExampleMaterial);
	skelDraw->setDrawBindPose(true);
	skelDraw->setDrawPose(true);   
    skelDraw->setBindPoseColor(Color4f(0.0, 1.0, 0.0, 1.0));  //When the skeleton's bind pose is rendered, it will be green
    skelDraw->setPoseColor(Color4f(0.0, 0.0, 1.0, 1.0));  //The skeleton's current pose is rendered in blue

	NodeRecPtr skelDrawNode = makeNodeFor(skelDraw);

	NodeRecPtr theNode = makeNodeFor(OSG::Group::create());

	colInstCont->setSkeleton(skeleton);
	theNode->addChild(skelDrawNode);
	theNode->addChild(skelNode);
    editInstStore().push_back(skelNode);
    editInstStore().push_back(skelDrawNode);
    editInstStore().push_back(theNode);
	return theNode;
	
}

/*! Creates a joint, and sets its transformations based on the transformation
	of the domNode.
*/
NodeTransitPtr ColladaController::createJointFromNode(domNode *node)
{
	TransformRecPtr newJoint = Transform::create();
	Matrix baseXform,jointXform,tmp;

	domTranslate_Array translations = node->getTranslate_array();
	domRotate_Array rotations = node->getRotate_array();
	domScale_Array scalings = node->getScale_array();

	UInt32 i(0);
	for(i = 0; i < translations.getCount(); i++)
	{	
		Vec3f translate(translations[i]->getValue()[0],
						translations[i]->getValue()[1],
						translations[i]->getValue()[2]);
		tmp.setTranslate(translate);

		newJoint->editMatrix().mult(tmp);
		
	}
	tmp.setIdentity(); // reset tmp matrix
	for(i = 0; i < rotations.getCount(); i++)
	{	
		
		Quaternion quat;
		
		quat.setValueAsAxisDeg( rotations[i]->getValue()[0],
								rotations[i]->getValue()[1],
								rotations[i]->getValue()[2],
								rotations[i]->getValue()[3]);
		tmp.setRotate(quat);

		newJoint->editMatrix().mult(tmp);
		
	}
	tmp.setIdentity(); // reset tmp matrix
	for(i = 0; i < scalings.getCount(); i++)
	{	
		Vec3f scale(scalings[i]->getValue()[0],
					scalings[i]->getValue()[1],
					scalings[i]->getValue()[2]);
		tmp.setScale(scale);
		
		newJoint->editMatrix().mult(tmp);

	}

    NodeUnrecPtr      jointNode = makeNodeFor(newJoint);
	return NodeTransitPtr(jointNode);
}

void
ColladaController::handleBindMaterial(  const ColladaGeometry::GeoInfo &geoInfo, 
										Geometry *geo, 
										ColladaInstanceController *colInstCont)
{
    typedef ColladaInstanceGeometry::MaterialMap        MaterialMap;
    typedef ColladaInstanceGeometry::MaterialMapConstIt MaterialMapConstIt;

    const MaterialMap       &matMap        = colInstCont->getMaterialMap();
    MaterialMapConstIt       mmIt          = matMap.find(geoInfo._matSymbol);
    Material                *material      = NULL;
    ColladaInstanceMaterial *colInstMat    = NULL;
    ColladaInstanceEffect   *colInstEffect = NULL;

    if(mmIt != matMap.end())
    {
        colInstMat    = mmIt      ->second;
        material      = colInstMat->process          (NULL);
        colInstEffect = colInstMat->getInstanceEffect(    );
    }
    else
    {
        SWARNING << "ColladaController::handleBindMaterial: No material found "
                 << "for symbol [" << geoInfo._matSymbol << "]."
                 << std::endl;
        return;
    }

    const ColladaGeometry::BindStore       &bindStore       = colInstMat->getBindStore      ();
    const ColladaGeometry::BindVertexStore &bindVertexStore = colInstMat->getBindVertexStore();

    ColladaGeometry::PropStoreConstIt       psIt     = geoInfo._propStore .begin();
    ColladaGeometry::PropStoreConstIt       psEnd    = geoInfo._propStore .end  ();
    ColladaGeometry::IndexStoreConstIt      isIt     = geoInfo._indexStore.begin();
    ColladaGeometry::IndexStoreConstIt      isEnd    = geoInfo._indexStore.end  ();

    // for every property in geoInfo we need to check if it gets remapped by a
    // <bind> or <bind_vertex_input>

    for(UInt32 i = 0; psIt != psEnd && isIt != isEnd; ++psIt, ++isIt, ++i)
    {
        if(psIt->_prop == NULL || *isIt == NULL)
            continue;

        bool   handledProperty  = false;
        UInt32 bindOffset       = 0;
        UInt32 bindVertexOffset = 0;

        const ColladaGeometry::BindInfo       *bi  = findBind      (bindStore,
                                                   psIt->_semantic, bindOffset );
        const ColladaGeometry::BindVertexInfo *bvi = findBindVertex(bindVertexStore,
                                                   psIt->_semantic, psIt->_set,
                                                   bindVertexOffset            );

        // there may be multiple consumers for a property, keep looping
        // until no more consumers are found
        while(bi != NULL || bvi != NULL)
        {
            UInt32 mappedProp = i;

            if(bi != NULL)
            {
                if(colInstEffect->findTC(bi->target, mappedProp) == true)
                {
                    OSG_COLLADA_LOG(("ColladaController::handleBindMaterial: "
                                     "Resolved <bind> semantic [%s] "
                                     "target [%s] to property [%d]\n",
                                     bi->semantic.c_str(), bi->target.c_str(),
                                     mappedProp));

                    geo->setProperty( psIt->_prop, mappedProp);
                    geo->setIndex   (*isIt,        mappedProp);

                    handledProperty = true;
                }
                else
                {
                    SWARNING << "ColladaController::handleBindMaterial: "
                             << "Failed to resolve <bind> semantic ["
                             << bi->semantic << "] target [" << bi->target
                             << "]." << std::endl;
                }
            }
            else if(bvi != NULL)
            {
                if(colInstEffect->findTC(bvi->semantic, mappedProp) == true)
                {
                    OSG_COLLADA_LOG(("ColladaController::handleBindMaterial: "
                                     "Resolved <bind_vertex_input> "
                                     "inSemantic [%s] inSet [%d] semantic [%s] "
                                     "to property [%d]\n",
                                     bvi->inSemantic.c_str(), bvi->inSet,
                                     bvi->semantic.c_str(), mappedProp));

                    geo->setProperty( psIt->_prop, mappedProp);
                    geo->setIndex   (*isIt,        mappedProp);
                    
                    handledProperty = true;
                }
                else
                {
                    SWARNING << "ColladaController::handleBindMaterial: "
                             << "Failed to resolve <bind_vertex_input> "
                             << "inSemantic ["
                             << bvi->inSemantic << "] inSet [" << bvi->inSet
                             << "] semantic [" << bvi->semantic
                             << "]." << std::endl;
                }
            }

            // find next consumers if any
            ++bindOffset;
            ++bindVertexOffset;

            bi  = findBind      (bindStore,       psIt->_semantic,
                                 bindOffset                       );
            bvi = findBindVertex(bindVertexStore, psIt->_semantic,
                                 psIt->_set,      bindVertexOffset);
        }

        // if the property is not remapped by <bind> or <bind_vertex_input>
        // we just put it at the location it received at read time
        // this is for properties that are not of interest to the material
        // directly (e.g. positions, normals)
        if(handledProperty == false)
        {
            OSG_COLLADA_LOG(("ColladaController::handleBindMaterial: "
                             "Setting property [%d] without "
                             "<bind>/<bind_vertex_input> mapping.\n", i));

            geo->setProperty( psIt->_prop, i);
            geo->setIndex   (*isIt,        i);
        }
    }

    if(material != NULL)
    {
        geo->setMaterial(material);
    }
    else
    {
        SWARNING << "ColladaController::handleBindMaterial: No material created "
                 << "for symbol [" << geoInfo._matSymbol << "]."
                 << std::endl;
    }
}

/*! Returns a <bind> (actually a BindInfo built from a <bind>) that has
    the given \a semantic. The search starts at the given \a offset to
    allow multiple <bind> with the same semantic to be found.
 */
const ColladaGeometry::BindInfo *
	ColladaController::findBind( const ColladaGeometry::BindStore &store, 
								 const std::string &semantic, 
								 UInt32 &offset)
{
    const ColladaGeometry::BindInfo *retVal = NULL;

    for(UInt32 i = offset; i < store.size(); ++i)
    {
        if(store[i].semantic == semantic)
        {
            retVal = &store[i];
            offset = i;
            break;
        }
    }

    return retVal;
}

/*! Returns a <bind_vertex_input> (actually a BindVertexInfo built from
    a <bind_vertex_input>) that has the given \a inSemantic and \a inSet.
    The search starts at the given \a offset to allow
    multiple <bind_vertex_input> with the same inSemantic/inSet to be found.
 */
const ColladaGeometry::BindVertexInfo *
	ColladaController::findBindVertex(  const ColladaGeometry::BindVertexStore &store, 
										const std::string	  &inSemantic,
										UInt32                inSet, 
										UInt32				  &offset     )
{
    const ColladaGeometry::BindVertexInfo *retVal = NULL;

    for(UInt32 i = offset; i < store.size(); ++i)
    {
        if(store[i].inSemantic == inSemantic &&
           store[i].inSet      == inSet        )
        {
            retVal = &store[i];
            offset = i;
            break;
        }
    }

    return retVal;
}

const ColladaController::SkinInfo &ColladaController::getSkinInfo		(void)
{
	return _mSkin;
}

bool	
ColladaController::hasSkin (void)
{
	return _hasSkin;
}

bool	
ColladaController::hasMorph	(void)
{
	return _hasMorph;
}

ColladaController::ColladaController(daeElement *elem, ColladaGlobal *global)
    : Inherited (elem, global),
	_hasSkin(false),
	_hasMorph(false)
{
	_mSkin.weights = GeoVec1fProperty::create();
}


ColladaController::~ColladaController(void)
{
}


OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
