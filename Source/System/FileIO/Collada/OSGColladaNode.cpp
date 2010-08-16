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
#include "OSGColladaInstanceController.h"
#include "OSGColladaVisualScene.h"
#include "OSGTransform.h"
#include "OSGNameAttachment.h"

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
	if(node->getType() ==  NODETYPE_JOINT)
	{
		handleJointNode(node);
	}
	else
	{
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

    TransformUnrecPtr xform = Transform::create();

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

    TransformUnrecPtr xform = Transform::create();
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

    TransformUnrecPtr xform = Transform::create();
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
	/* 
	 * Implemented in accordance with the RenderMan specification.
	 * See http://www.koders.com/cpp/fidA08C276050F880D11C2E49280DD9997478DC5BA1.aspx for
	 * the implementation that this was copied from.
	 * (If the url is invalid, this implementation was copied from the GNU GMAN project,
	 * in the gmanmatrix4.cpp file.)
	 *
	 */
    if(skew == NULL)
        return;
	
   // SWARNING << "ColladaNode::handleSkew: NIY" << std::endl;
	Real32 angle,an1,an2,rx,ry,alpha;
	Matrix m;
	Vec3f a1,a2,n1,n2;

	domFloat7 elems = skew->getValue();
	angle = elems[0];
	Vec3f a(elems[1],elems[2],elems[3]), b(elems[4],elems[5],elems[6]);
	b.normalize();
	a1 = b * a.dot(b);
	a2 = a - a1;
	a2.normalize();

	an1 = a.dot(a2);
	an2 = a.dot(b);

	angle = osgDegree2Rad(angle);
	rx = an1*osgCos(angle) - an2*osgSin(angle);
	ry = an1*osgSin(angle) + an2*osgCos(angle);

	if(rx <= 0.0f)
	{  // skew angle too large, and we can't calculate the skew matrix
		SWARNING << "ColladaNode::handleSkew: Skew Angle too large! ( rx = " 
				 << rx << " )" << std::endl;
		return; 
	}

	// are A and B parallel?
	if(OSG::osgAbs(an1) < 0.000001) 
		alpha = 0.0f;
	else 
		alpha = ry/rx - an2/an1;
	
	m[0][0] = a2.x() * b.x() * alpha + 1.0f;
	m[1][0] = a2.y() * b.x() * alpha;
	m[2][0] = a2.z() * b.x() * alpha;

	m[0][1] = a2.x() * b.y() * alpha;
	m[1][1] = a2.y() * b.y() * alpha + 1.0f;
	m[2][1] = a2.z() * b.y() * alpha;

	m[0][2] = a2.x() * b.z() * alpha;
	m[1][2] = a2.y() * b.z() * alpha;
	m[2][2] = a2.z() * b.z() * alpha + 1.0f;

	domNodeRef        node   = getDOMElementAs<domNode>();

    TransformUnrecPtr xform = Transform::create();
	NodeUnrecPtr      xformN = makeNodeFor(xform);

	xform->setMatrix(m);

	 if(getGlobal()->getOptions()->getCreateNameAttachments() == true && 
       node->getName()                                       != NULL   )
    {
        std::string nodeName = node->getName();

        if(skew->getSid() != NULL && 
			getGlobal()->getOptions()->getFlattenNodeXForms() == false)
        {
            nodeName.append("."                );
            nodeName.append(skew->getSid());
        }

        setName(xformN, nodeName);
    }

    appendXForm(xformN);

}

void
ColladaNode::handleTranslate(domTranslate *translate)
{
    if(translate == NULL)
        return;

    domNodeRef        node   = getDOMElementAs<domNode>();

    TransformUnrecPtr xform = Transform::create();
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
    
    //push the Light onto the root
    LightUnrecPtr light = colInstLight->process(this);
    if(light != NULL)
    {

        //Append the lights beacon node
        GroupUnrecPtr lightBeacon = Group::create();
        NodeRecPtr lightBeaconN = Node::create();
        lightBeaconN->setCore(lightBeacon);
        /*std::string BeaconNodeName(instLight->getName());
        BeaconNodeName += "_beacon";
        setName(lightBeaconN, BeaconNodeName);*/

        //TODO: set beacon name
        appendChild(lightBeaconN);

        light->setBeacon(lightBeaconN);

        NodeRecPtr lightN = Node::create();
        lightN->setCore(light);
        //setName(lightN,instLight->getName());
        //TODO: set light name

        _visualScene->pushNodeToRoot(lightN);
    }

}

void
ColladaNode::handleInstanceController(domInstance_controller *instController)
{
    ColladaInstanceControllerRefPtr colInstCont =
		getUserDataAs<ColladaInstanceController>(instController);

    if(colInstCont == NULL)
    {
        colInstCont = dynamic_pointer_cast<ColladaInstanceController>(
            ColladaElementFactory::the()->create(instController, getGlobal()));

        colInstCont->read();
    }

    NodeUnrecPtr contN = colInstCont->process(this);

    appendChild(contN);

}

/*! Creates a joint, and sets its transformations based on the transformation
	of the domNode.
*/
void ColladaNode::handleJointNode(domNode *node)
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

    NodeRecPtr      jointN = makeNodeFor(newJoint);

	_bottomN = jointN;

	if(_topN == NULL)
    {
        _topN = _bottomN;
    }

	setName(_bottomN, node->getID());

	getGlobal()->editNodeToNodeMap()[node] = jointN;

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
            if(_bottomN->getCore()->getType().isDerivedFrom(Transform::getClassType()))
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
