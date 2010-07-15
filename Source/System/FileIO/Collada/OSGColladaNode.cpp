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

#include "OSGColladaNode.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGColladaGlobal.h"
#include "OSGColladaInstanceNode.h"
#include "OSGColladaInstanceGeometry.h"
#include "OSGColladaInstanceLight.h"
#include "OSGColladaVisualScene.h"
#include "OSGTransform.h"
#include "OSGNameAttachment.h"
#include "OSGFileIOUtils.h"

// skeleton drawable material includes...
#include "OSGLineChunk.h"
#include "OSGBlendChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"

#include "OSGSkeletonBlendedGeometry.h"
#include "OSGSkeletonDrawable.h"

#include <dom/domLookat.h>
#include <dom/domMatrix.h>
#include <dom/domRotate.h>
#include <dom/domScale.h>
#include <dom/domSkew.h>
#include <dom/domTranslate.h>
#include <dom/domInstance_node.h>
#include <dom/domNode.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaNode::_regHelper(
    &ColladaNode::create, "node");


ColladaElementTransitPtr
ColladaNode::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaNode(elem, global));
}

void
ColladaNode::setVisualScene(ColladaVisualScene     *visualScene)
{
    _visualScene = visualScene;
}

void
ColladaNode::read(void)
{
    OSG_COLLADA_LOG(("ColladaNode::read\n"));

    domNodeRef                node     = getDOMElementAs<domNode>();
    const daeElementRefArray &contents = node->getContents();

    // handle "transform" child elements in the order
    // they occur in the document

    for(UInt32 i = 0; i < contents.getCount(); ++i)
    {
        switch(contents[i]->getElementType())
        {
        case COLLADA_TYPE::LOOKAT:
            handleLookAt(daeSafeCast<domLookat>(contents[i]));
            break;
            
        case COLLADA_TYPE::MATRIX:
            handleMatrix(daeSafeCast<domMatrix>(contents[i]));
        break;
        
        case COLLADA_TYPE::ROTATE:
            handleRotate(daeSafeCast<domRotate>(contents[i]));
        break;
        
        case COLLADA_TYPE::SCALE:
            handleScale(daeSafeCast<domScale>(contents[i]));
        break;
        
        case COLLADA_TYPE::SKEW:
            handleSkew(daeSafeCast<domSkew>(contents[i]));
        break;
        
        case COLLADA_TYPE::TRANSLATE:
            handleTranslate(daeSafeCast<domTranslate>(contents[i]));
        break;
        }
    }

    // handle <node> child elements
    const domNode_Array &nodes = node->getNode_array();
    
    for(UInt32 i = 0; i < nodes.getCount(); ++i)
    {
        handleNode(nodes[i]);
    }

    // handle <instance_node> child elements
    const domInstance_node_Array &instNodes = node->getInstance_node_array();
    
    for(UInt32 i = 0; i < instNodes.getCount(); ++i)
    {
        handleInstanceNode(instNodes[i]);
    }

    // handle <instance_light> child elements
    const domInstance_light_Array &instLights = node->getInstance_light_array();
    for(UInt32 i = 0; i < instLights.getCount(); ++i)
    {
        handleInstanceLight(instLights[i]);
    }

    // handle <instance_geometry> child elements
    const domInstance_geometry_Array &instGeos =
        node->getInstance_geometry_array();

    for(UInt32 i = 0; i < instGeos.getCount(); ++i)
    {
        handleInstanceGeometry(instGeos[i]);
    }

    // handle <instance_controller> child elemnts
    const domInstance_controller_Array &instControllers =
        node->getInstance_controller_array();

    for(UInt32 i = 0; i < instControllers.getCount(); ++i)
    {
        handleInstanceController(instControllers[i]);
    }

    // nothing created? build a dummy node
    if(_topN == NULL)
    {
        _topN = makeCoredNode<Group>();

        if(getGlobal()->getOptions()->getCreateNameAttachments() == true &&
           node->getName()                                       != NULL   )
        {
            setName(_topN, node->getName());
        }
    }

    if(_bottomN == NULL)
    {
        _bottomN = _topN;
    }
}

Node *
ColladaNode::createInstance(ColladaInstanceElement *colInstElem)
{
    OSG_COLLADA_LOG(("ColladaNode::createInstance\n"));

    NodeUnrecPtr retVal = NULL;

    if(_topN->getParent() != NULL)
    {
        retVal = cloneTree(_topN);
    }
    else
    {
        retVal = cloneTree(_topN);
     }

    editInstStore().push_back(retVal);

    return retVal;
}

Node *
ColladaNode::getTopNode(void) const
{
    return _topN;
}

Node *
ColladaNode::getBottomNode(void) const
{
    return _bottomN;
}

ColladaNode::ColladaNode(daeElement *elem, ColladaGlobal *global)
    : Inherited(elem, global)
    , _topN    (NULL)
    , _bottomN (NULL)
{
}

ColladaNode::~ColladaNode(void)
{
}

void
ColladaNode::handleLookAt(domLookat *lookat)
{
    if(lookat == NULL)
        return;

    SWARNING << "ColladaNode::handleLookAt: NIY" << std::endl;
}

void
ColladaNode::handleMatrix(domMatrix *matrix)
{
    if(matrix == NULL)
        return;

    domNodeRef        node   = getDOMElementAs<domNode>();

    TransformUnrecPtr xform  = Transform::create();
    NodeUnrecPtr      xformN = makeNodeFor(xform);

    Matrix m(matrix->getValue()[0],      // rVal00
             matrix->getValue()[1],      // rVal10
             matrix->getValue()[2],      // rVal20
             matrix->getValue()[3],      // rVal30
             matrix->getValue()[4],      // rVal01
             matrix->getValue()[5],      // rVal11
             matrix->getValue()[6],      // rVal21
             matrix->getValue()[7],      // rVal31
             matrix->getValue()[8],      // rVal02
             matrix->getValue()[9],      // rVal12
             matrix->getValue()[10],     // rVal22
             matrix->getValue()[11],     // rVal32
             matrix->getValue()[12],     // rVal03
             matrix->getValue()[13],     // rVal13
             matrix->getValue()[14],     // rVal23
             matrix->getValue()[15] );   // rVal33
    
    xform->setMatrix(m);

    if(getGlobal()->getOptions()->getCreateNameAttachments() == true && 
       node->getName()                                       != NULL   )
    {
        std::string nodeName = node->getName();

        if(matrix->getSid() != NULL&& 
			getGlobal()->getOptions()->getFlattenNodeXForms() == false)
        {
            nodeName.append("."             );
            nodeName.append(matrix->getSid());
        }

        setName(xformN, nodeName);
    }

    appendXForm(xformN);
}

void
ColladaNode::handleRotate(domRotate *rotate)
{
    if(rotate == NULL)
        return;

    domNodeRef        node   = getDOMElementAs<domNode>();

    TransformUnrecPtr xform  = Transform::create();
    NodeUnrecPtr      xformN = makeNodeFor(xform);

    Quaternion q;
    q.setValueAsAxisDeg(rotate->getValue()[0],
                        rotate->getValue()[1],
                        rotate->getValue()[2],
                        rotate->getValue()[3] );
    
    xform->editMatrix().setRotate(q);

    if(getGlobal()->getOptions()->getCreateNameAttachments() == true && 
       node->getName()                                       != NULL   )
    {
        std::string nodeName = node->getName();

        if(rotate->getSid() != NULL&& 
			getGlobal()->getOptions()->getFlattenNodeXForms() == false)
        {
            nodeName.append("."             );
            nodeName.append(rotate->getSid());
        }

        setName(xformN, nodeName);
    }

    appendXForm(xformN);
}

void
ColladaNode::handleScale(domScale *scale)
{
    if(scale == NULL)
        return;

    domNodeRef        node   = getDOMElementAs<domNode>();

    TransformUnrecPtr xform  = Transform::create();
    NodeUnrecPtr      xformN = makeNodeFor(xform);

    xform->editMatrix().setScale(scale->getValue()[0],
                                 scale->getValue()[1],
                                 scale->getValue()[2] );

    if(getGlobal()->getOptions()->getCreateNameAttachments() == true && 
       node->getName()                                       != NULL   )
    {
        std::string nodeName = node->getName();

        if(scale->getSid() != NULL&& 
			getGlobal()->getOptions()->getFlattenNodeXForms() == false)
        {
            nodeName.append("."            );
            nodeName.append(scale->getSid());
        }

        setName(xformN, nodeName);
    }

    appendXForm(xformN);
}

void
ColladaNode::handleSkew(domSkew *skew)
{
    if(skew == NULL)
        return;

    SWARNING << "ColladaNode::handleSkew: NIY" << std::endl;
}

void
ColladaNode::handleTranslate(domTranslate *translate)
{
    if(translate == NULL)
        return;

    domNodeRef        node   = getDOMElementAs<domNode>();

    TransformUnrecPtr xform  = Transform::create();
    NodeUnrecPtr      xformN = makeNodeFor(xform);

    xform->editMatrix().setTranslate(translate->getValue()[0],
                                     translate->getValue()[1],
                                     translate->getValue()[2] );

    if(getGlobal()->getOptions()->getCreateNameAttachments() == true && 
       node->getName()                                       != NULL   )
    {
        std::string nodeName = node->getName();

        if(translate->getSid() != NULL && 
			getGlobal()->getOptions()->getFlattenNodeXForms() == false)
        {
            nodeName.append("."                );
            nodeName.append(translate->getSid());
        }

        setName(xformN, nodeName);
    }

    appendXForm(xformN);
}

void
ColladaNode::handleNode(domNode *node)
{
    ColladaNodeRefPtr colNode = getUserDataAs<ColladaNode>(node);

    if(colNode == NULL)
    {
        colNode = dynamic_pointer_cast<ColladaNode>(
            ColladaElementFactory::the()->create(node, getGlobal()));

        colNode->setVisualScene(_visualScene);
        colNode->read();
    }

    Node *childN = colNode->getTopNode();

    if(childN->getParent() != NULL)
    {
        SWARNING << "ColladaNode::handleNode: Node already has a parent."
                 << std::endl;
    }

    appendChild(childN);
}

void
ColladaNode::handleInstanceNode(domInstance_node *instNode)
{
    ColladaInstanceNodeRefPtr colInstNode =
        getUserDataAs<ColladaInstanceNode>(instNode);

    if(colInstNode == NULL)
    {
        colInstNode = dynamic_pointer_cast<ColladaInstanceNode>(
            ColladaElementFactory::the()->create(instNode, getGlobal()));

        colInstNode->read();
    }

    NodeUnrecPtr childN = colInstNode->process(this);

    appendChild(childN);
}

void
ColladaNode::handleInstanceGeometry(domInstance_geometry *instGeo)
{
    ColladaInstanceGeometryRefPtr colInstGeo =
        getUserDataAs<ColladaInstanceGeometry>(instGeo);

    if(colInstGeo == NULL)
    {
        colInstGeo = dynamic_pointer_cast<ColladaInstanceGeometry>(
            ColladaElementFactory::the()->create(instGeo, getGlobal()));

        colInstGeo->read();
    }

    NodeUnrecPtr geoN = colInstGeo->process(this);

    appendChild(geoN);
}

void
ColladaNode::handleInstanceLight(domInstance_light *instLight)
{
    ColladaInstanceLightRefPtr colInstLight =
        getUserDataAs<ColladaInstanceLight>(instLight);

    if(colInstLight == NULL)
    {
        colInstLight = dynamic_pointer_cast<ColladaInstanceLight>(
            ColladaElementFactory::the()->create(instLight, getGlobal()));

        colInstLight->read();
    }

    //Append the lights beacon node
    GroupUnrecPtr lightBeacon = Group::create();
    NodeRecPtr lightBeaconN = Node::create();
    lightBeaconN->setCore(lightBeacon);
    /*std::string BeaconNodeName(instLight->getName());
    BeaconNodeName += "_beacon";
    setName(lightBeaconN, BeaconNodeName);*/

    //TODO: set beacon name
    appendChild(lightBeaconN);
    
    //push the Light onto the root
    LightUnrecPtr light = colInstLight->process(this);
    light->setBeacon(lightBeaconN);

    NodeRecPtr lightN = Node::create();
    lightN->setCore(light);
    //setName(lightN,instLight->getName());
    //TODO: set light noame

    _visualScene->pushNodeToRoot(lightN);

}

void
ColladaNode::handleInstanceController(domInstance_controller *instController)
{
   // SWARNING << "ColladaNode::handleInstanceController: NIY"
   //          << std::endl;

	// For now, we just push these instance_controllers to a store, and finish creating
	// them later. This is because the instance controllers might need information from nodes
	// that haven't been created in OpenSG yet. 
	domControllerRef ctrlr = daeSafeCast<domController>(instController->getUrl().getElement());
	domSkinRef theSkin = ctrlr->getSkin();
	if(theSkin != NULL)
	{	// it's a skeleton controller 
		// create a drawable skeleton for now
		
		// get skeleton joints
		domInstance_controller::domSkeleton_Array skelArr = instController->getSkeleton_array();
		
		// get the joint source
		domSkin::domJointsRef dJoints = theSkin->getJoints();
		domInputLocal_Array inputs = dJoints->getInput_array();

		// these two arrays correspond one to one, from the joint name to its inverse bind matrix
		domName_arrayRef jointNamesArr;
		domFloat_arrayRef IBPMArr;
		UInt32 i(0),nameCount(0),matrixCount(0),stride(0);
		for(i = 0; inputs.getCount(); i++)
		{
			if(inputs[i]->getSemantic() == "JOINT") 
			{
				domSourceRef src = daeSafeCast<domSource>(inputs[i]);
				nameCount = src->getTechnique_common()->getAccessor()->getCount();
				jointNamesArr = src->getName_array();

			}
			else if(inputs[i]->getSemantic() == "INV_BIND_MATRIX") 
			{
				domSourceRef src = daeSafeCast<domSource>(inputs[i]);
				
				IBPMArr = src->getFloat_array();
				matrixCount = src->getTechnique_common()->getAccessor()->getCount();
				stride = src->getTechnique_common()->getAccessor()->getStride();
			}
		}

		// extracting the actual inverse bind matrices  and joint sids from the arrays
		std::vector<Matrix> invBPMatrices;
		std::vector<std::string> jointSIDs;
		if(stride == 16 && nameCount == matrixCount)
		{ // if the stride isn't 16, then we can't get the matrices!
			domListOfFloats vals = IBPMArr->getValue();
			for(i = 0; i < vals.getCount(); i++)
			{
				Matrix newMatrix(vals[i++],vals[i++],vals[i++],vals[i++],
								 vals[i++],vals[i++],vals[i++],vals[i++],
								 vals[i++],vals[i++],vals[i++],vals[i++],
								 vals[i++],vals[i++],vals[i++],vals[i++]);

				invBPMatrices.push_back(newMatrix);
			}

			//TODO: get matrices for each joint node, build the joints, push to the skeleton.
			domListOfNames names = jointNamesArr->getValue();
			for(i = 0; i < names.getCount(); i++)
			{
				jointSIDs.push_back(names[i]);
			}
		}

		std::vector<Joint *> joints;
		
		for(i = 0; i < skelArr.getCount(); i++)
		{
			domNodeRef node = daeSafeCast<domNode>(skelArr[i]->getValue().getElement());
		}

		SkeletonBlendedGeometryUnrecPtr skeleton = SkeletonBlendedGeometry::create();
		SkeletonDrawableUnrecPtr ExampleSkeletonDrawable = SkeletonDrawable::create();
		ExampleSkeletonDrawable->setSkeleton(skeleton);
		
		//ExampleSkeletonDrawable->setMaterial(ExampleMaterial); // make a material??
	
	}

}

/*! Add a transform node to the OpenSG tree representing
    this &lt;node&gt;.
 */
void
ColladaNode::appendXForm(Node *xformN)
{
    if(_topN == NULL)
    {
        _topN = xformN;
    }
    
    if(getGlobal()->getOptions()->getFlattenNodeXForms())
    {
        if(_bottomN != NULL)
        {
            if(_bottomN->getCore()->getType() == Transform::getClassType())
            {
                Transform* _bottomTrans = dynamic_cast<Transform*>(_bottomN->getCore());

                _bottomTrans->editMatrix().mult(dynamic_cast<Transform*>(xformN->getCore())->getMatrix());
            }
            else
            {
                _bottomN->addChild(xformN);
            }
        }
        else
        {
            _bottomN = xformN;
        }
    }
    else
    {
        if(_bottomN != NULL)
        {
            _bottomN->addChild(xformN);
        }

        _bottomN = xformN;
    }
}

/*! Add a child node to the OpenSG tree representing
    this &lt;node&gt;.
 */
void
ColladaNode::appendChild(Node *childN)
{
    if(_bottomN == NULL)
    {
        _bottomN = makeCoredNode<Group>();

        domNodeRef node = getDOMElementAs<domNode>();

        if(getGlobal()->getOptions()->getCreateNameAttachments() == true &&
           node->getName()                                       != NULL   )
        {
            setName(_bottomN, node->getName());
        }
    }

    if(_topN == NULL)
    {
        _topN = _bottomN;
    }

    _bottomN->addChild(childN);
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
