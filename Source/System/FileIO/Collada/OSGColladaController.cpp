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
#include "OSGColladaAnimation.h"

#include "OSGGroup.h"
#include "OSGTransform.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGNameAttachment.h"

#include "OSGSkeletonBlendedGeometry.h"
#include "OSGSkeletonDrawable.h"
#include "OSGMorphGeometry.h"

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
		SWARNING << "ColladaController::read: No <skin> or <morph>" << std::endl;
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
	// get the source mesh
	_mMorph.source = daeSafeCast<domGeometry>(morph->getSource().getElement());
	// get the target meshes and their weights
	domInputLocal_Array locals = morph->getTargets()->getInput_array();

	domSourceRef targets, weights;
	std::string targetToken("MORPH_TARGET"),weightToken("MORPH_WEIGHT");
	// match up targets and weights
	for(UInt32 i(0); i < locals.getCount(); i++)
	{	
		std::string semantic(locals[i]->getSemantic());
		if(targetToken.compare(semantic) == 0 )
			targets = daeSafeCast<domSource>(locals[i]->getSource().getElement());
		else if(weightToken.compare(semantic) == 0)
			weights = daeSafeCast<domSource>(locals[i]->getSource().getElement());
	}
	// check if this morph has an animation on it

	

	// extract values from the arrays
	if( targets != NULL && weights != NULL )
	{
		if(getGlobal()->editAnimationMap()[weights] != NULL)
		{
			_animation = getGlobal()->editAnimationMap()[weights];
		}
		else
		{
			_animation = NULL;
		}

		xsIDREFS ids = targets->getIDREF_array()->getValue();
		domListOfFloats wts = weights->getFloat_array()->getValue();

		for(UInt32 i(0); ( wts.getCount() == ids.getCount()) && i < ids.getCount(); i++)
		{
			domGeometry * targetGeom = daeSafeCast<domGeometry>(ids.get(i).getElement());
			if(targetGeom != NULL)
			{
				_mMorph.weights.push_back(wts.get(i));
				_mMorph.targets.push_back(targetGeom);
			}
		}
	}

	return;
}

Node *
ColladaController::createInstance(ColladaInstanceElement *colInstElem)
{
	ColladaInstanceControllerRefPtr colInstCont =
			dynamic_cast<ColladaInstanceController *>(colInstElem);

	domControllerRef controller  = getDOMElementAs<domController>();

    domGeometryRef  geometry; 
	if(_hasSkin)
	{
		geometry = daeSafeCast<domGeometry>(controller->getSkin()->getSource().getElement());
	}
	else if(_hasMorph)
	{
		geometry = daeSafeCast<domGeometry>(controller->getMorph()->getSource().getElement());
	}

	GeometryRefPtr geo;

	if(geometry != NULL)
	{	
		geo = handleGeometry(geometry,colInstCont);
	}

	if(geo == NULL) 
		return NULL; // can't do anything without the geometry!

	// bind the material associated with this controller
	handleBindMaterial(geo, colInstCont);
	
	// There are two types of controllers: Skeletons and Morphs.  Controllers can 
	// be one or the other, but not both.
	if(_hasSkin)
	{
		// create the skeleton.  Joints won't be fully resolved until later (see ColladaGlobal)
		SkeletonBlendedGeometryRecPtr skeleton = SkeletonBlendedGeometry::create();	
		skeleton->setBaseGeometry(geo);
		skeleton->setBindTransformation(_mSkin.bindShapeMatrix);

		NodeRecPtr skelNode = makeNodeFor(skeleton);

		skeleton->setWeights(_mSkin.weights);
	
		colInstCont->setSkeleton(skeleton);

		editInstStore().push_back(skelNode);

		return skelNode;
	} // end if(_hasSkin)
	else// if(_hasMorph) // it will either have a morph or a skin
	{ 
		MorphGeometryRefPtr newMorphGeo = MorphGeometry::create();
		newMorphGeo->setBaseGeometry(geo);
		for(UInt32 i(0); i < _mMorph.targets.size(); i++)
		{
			GeometryRefPtr target = handleGeometry(_mMorph.targets[i], colInstElem);
			if(target != NULL)
			{
				newMorphGeo->addMorphTarget(target,_mMorph.weights[i]);
			}
		}
		
		NodeRecPtr newNode = makeNodeFor(newMorphGeo);
		editInstStore().push_back(newNode);
		// finish the animation setup
		if(_animation != NULL )
		{
			// workaround for dealing with typing of the sequence required to animate blend weights
			// We are just converting the keyframe sequence from a Real32 to a Vec1f type
			KeyframeAnimator * animator = dynamic_cast<KeyframeAnimator *>(_animation->getAnimation()->getAnimator());
			if(animator != NULL)
			{
				KeyframeNumberSequenceReal32 * kfSeq = dynamic_cast<KeyframeNumberSequenceReal32 *>(animator->getKeyframeSequence());
				KeyframeVectorSequenceVec1fRecPtr newKfSeq = KeyframeVectorSequenceVec1f::create();

				MFReal32 keys = kfSeq->getKeys();
				MFReal32 values = kfSeq->editField();
				// fill in the new keyframe sequence
				for(UInt32 i(0); i < keys.size(); i++)
				{
					newKfSeq->addKeyframe(values[i],keys[i]);
				}

				animator->setKeyframeSequence(newKfSeq);
				_animation->getAnimation()->setAnimator(animator);

				// set the animated field.  Some animations will be on a particular index of a multi-field...
				if(_animation->isIndexed())
				{
					_animation->getAnimation()->setAnimatedMultiField(newMorphGeo->getWeights(),"values",_animation->getTargetIndex());
				}
				else if(_animation != NULL)
				{
					_animation->getAnimation()->setAnimatedMultiField(newMorphGeo->getWeights(),"values",0);
				}
			}
		}

		return newNode;
	}
	
}

GeometryTransitPtr ColladaController::handleGeometry(domGeometryRef geometry, ColladaInstanceElement *colInstElem )
{
	ColladaInstanceControllerRefPtr colInstCont =
			dynamic_cast<ColladaInstanceController *>(colInstElem);

	ColladaGeometryRefPtr colGeo = dynamic_pointer_cast<ColladaGeometry>(
												ColladaElementFactory::the()->create(
											    geometry, getGlobal()));

	colGeo->read();

	Geometry * geo = colGeo->createGeometryInstance(colInstElem);

	return GeometryTransitPtr(geo);
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
ColladaController::handleBindMaterial(  Geometry *geo, 
										ColladaInstanceController *colInstCont	)
{	
	domInstance_controllerRef instCont = colInstCont->getDOMElementAs<domInstance_controller>();
	
	if(instCont != NULL)
	{
		domInstance_material_Array &colInstMatArr 
			= instCont->getBind_material()->getTechnique_common()->getInstance_material_array();
		std::string matSymbol;
		// there may be more than one material, but we just use the first one
		if(colInstMatArr.getCount() > 0)
		{
			matSymbol = colInstMatArr.get(0)->getSymbol();
		}

		ColladaInstanceController::MaterialMap matMap = colInstCont->getMaterialMap();
		ColladaInstanceMaterialRefPtr instMat;

		instMat = matMap[matSymbol];

		if(instMat != NULL)
		{
			geo->setMaterial(instMat->process(colInstCont));
		}
		else
		{
			SWARNING << "ColladaController::handleBindMaterial: No material found. Material will be NULL!\n";
		}
	}
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
