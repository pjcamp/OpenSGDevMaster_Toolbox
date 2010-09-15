
#include "OSGColladaAnimation.h"
#include "OSGBaseFunctions.h"
#include "OSGTransformAnimator.h"
#include "OSGColladaGlobal.h"

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaAnimation::_regHelper(
    &ColladaAnimation::create, "animation");

ColladaElementTransitPtr
ColladaAnimation::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaAnimation(elem, global));
}

void  ColladaAnimation::read(void)
{ // parsing the data for the animation.
	domAnimationRef anim = getDOMElementAs<domAnimation>();
	
	readSamplers(anim);
	
	domChannel_Array channel = anim->getChannel_array();
	for(UInt32 i(0); i < channel.getCount(); i++)
	{
		_animationTarget = channel[i]->getTarget();
	}

	daeSidRef sidRef(_animationTarget,channel[0]);
	_animTarget = sidRef.resolve().elt;

	// if we can't find the animation target, we can't make an animation.
	if(_animTarget == NULL) return;

	 /*	
		Here we are checking to see if this animation target is an attribute of a 
		transform (e.g., a rotation, translation, etc.).  If this is the case
		the parent of the attribute is saved so that we can combine all animations
		on a transform into a single TransformAnimator
	 */
	if(isTransformAttribute(_animTarget))
	{
		_animTarget = _animTarget->getParent();
	}

	buildKeyframeSequence(anim);

	// this is where the animator/animation should be set up
	buildAnimator(anim);

	if(_animation != NULL) 
	{
		std::string name = _animTarget->getID();
		getGlobal()->addFieldContainer(_animation);

		getGlobal()->editAnimationMap()[_animTarget] = _animation;
	}

	return;
}

FieldContainer *
ColladaAnimation::createInstance(ColladaInstanceElement *colInstElem)
{
	// NIY - Collada doesn't support it yet 
	return NULL;
}

/*
*	Assembles an animator/animation 
*/
void ColladaAnimation::buildAnimator(domAnimationRef anim)
{ 
	_reusingAnimator  = false;
	// check and see if this target aleady has an animation.
	ColladaGlobal::AnimMapIt amIt = getGlobal()->editAnimationMap().find(_animTarget);
	ColladaGlobal::AnimMapIt amEnd = getGlobal()->editAnimationMap().end();
	if(amIt != amEnd)
	{
		_animation = dynamic_cast<FieldAnimation *>(amIt->second);

		_animator = _animation->getAnimator();
		if(_animator != NULL)
		{
			_reusingAnimator = true;
		}
	}

	//TODO: work out how to handle non-transform animations.
	switch(_seqTy)
	{
	case REAL:
		{
			break;
		}
	case QUATX:
		{
			OSG::TransformAnimator * xfAnim = getTransformAnimator();
			xfAnim->setXRotationSequence(dynamic_pointer_cast<KeyframeNumberSequenceReal32>(_keyframeSequence));
			buildAnimation(xfAnim);
			break;
		} 
	case QUATY:
		{
			OSG::TransformAnimator * xfAnim = getTransformAnimator();
			xfAnim->setYRotationSequence(dynamic_pointer_cast<KeyframeNumberSequenceReal32>(_keyframeSequence));
			buildAnimation(xfAnim);
			break;
		} 
	case QUATZ:
		{
			OSG::TransformAnimator * xfAnim = getTransformAnimator();
			xfAnim->setZRotationSequence(dynamic_pointer_cast<KeyframeNumberSequenceReal32>(_keyframeSequence));
			buildAnimation(xfAnim);
			break;
		} 
	case TRANSX:
		{
			OSG::TransformAnimator * xfAnim = getTransformAnimator();
			xfAnim->setXTranslationSequence(dynamic_pointer_cast<KeyframeNumberSequenceReal32>(_keyframeSequence));
			buildAnimation(xfAnim);
			break;
		}
	case TRANSY:
		{
			OSG::TransformAnimator * xfAnim = getTransformAnimator();
			xfAnim->setYTranslationSequence(dynamic_pointer_cast<KeyframeNumberSequenceReal32>(_keyframeSequence));
			buildAnimation(xfAnim);
			break;
		}
	case TRANSZ:
		{
			OSG::TransformAnimator * xfAnim = getTransformAnimator();
			xfAnim->setZTranslationSequence(dynamic_pointer_cast<KeyframeNumberSequenceReal32>(_keyframeSequence));
			buildAnimation(xfAnim);
			break;
		}
	case SCALEX:
		{
			OSG::TransformAnimator * xfAnim = getTransformAnimator();
			xfAnim->setXScaleSequence(dynamic_pointer_cast<KeyframeNumberSequenceReal32>(_keyframeSequence));
			buildAnimation(xfAnim);
			break;
		}
	case SCALEY:
		{
			OSG::TransformAnimator * xfAnim = getTransformAnimator();
			xfAnim->setYScaleSequence(dynamic_pointer_cast<KeyframeNumberSequenceReal32>(_keyframeSequence));
			buildAnimation(xfAnim);
			break;
		}
	case SCALEZ:
		{
			OSG::TransformAnimator * xfAnim = getTransformAnimator();
			xfAnim->setZScaleSequence(dynamic_pointer_cast<KeyframeNumberSequenceReal32>(_keyframeSequence));
			buildAnimation(xfAnim);
			break;
		}
	case REAL2:
		{
			break;
		}
	case REAL3:
		{
			break;
		} 
	case SCALE:
		{
			OSG::TransformAnimator * xfAnim = getTransformAnimator();
			xfAnim->setScaleSequence(dynamic_pointer_cast<KeyframeVectorSequenceVec3f>(_keyframeSequence));
			buildAnimation(xfAnim);
			break;
		} 
	case TRANSLATE:
		{
			OSG::TransformAnimator * xfAnim = getTransformAnimator();
			xfAnim->setTranslationSequence(dynamic_pointer_cast<KeyframeVectorSequenceVec3f>(_keyframeSequence));
			buildAnimation(xfAnim);
			break;
		}
	case REAL4:
		{
			break;
		}
	case COLOR3:
		{	
			break;
		}
	case COLOR4:
		{
			break;
		}

	case INVALID:
	default:
		{

			break;
		}
	} // end switch(seqTy)
}

/*! Reads the input and output sources for an <animation>, and 
	builds the appropriate keyframe sequence from it
*/
void ColladaAnimation::buildKeyframeSequence(domAnimationRef anim)
{
	
    // get interpolation type
	getInterpolationType();

	// now we make sure that the quantity input and output values is the same for the input and output
	if(_inputSource != NULL && _outputSource != NULL)
	{
		domSource::domTechnique_commonRef inputTech = _inputSource->getTechnique_common();
		domSource::domTechnique_commonRef outputTech = _outputSource->getTechnique_common();

		if(inputTech != NULL && outputTech != NULL)
		{
			domAccessorRef inputAccessor = inputTech->getAccessor();
			domAccessorRef outputAccessor = outputTech->getAccessor();
			if(inputAccessor != NULL && outputAccessor != NULL)
			{	
				// the counts should be the same, but if the number of 
				// one is less than the other, we will
				// still make an animation out of what we can
				_animLength = OSG::osgMin<UInt32>(inputAccessor->getCount(),outputAccessor->getCount());
				domListOfFloats & arr = _inputSource->getFloat_array()->getValue();
				if(arr.getCount() > 0 && inputAccessor->getStride() == 1)
				{
					std::vector<Real32> inputKeys;
					for(UInt32 i(0); i < _animLength; i++)
					{
						inputKeys.push_back(arr[i]);
					}
					
					if(_outputSource->getFloat_array() != NULL)
					{
						buildFloatSequence(anim,outputAccessor,inputKeys);
					}
					else if(_outputSource->getInt_array() != NULL)
					{
						buildIntSequence(anim,outputAccessor,inputKeys);
					}
					else if(_outputSource->getBool_array() != NULL)
					{
						buildBoolSequence(anim,outputAccessor,inputKeys);
					}
					
				} else
				{
					SWARNING << "Unable to get input keys for animation "<< anim->getID() 
							 << "! (Probably not keyed by TIME)" << std::endl;
				}
				
			}
		}
	}
}

void ColladaAnimation::readSamplers(domAnimationRef anim)
{
	domSampler_Array &samplers = anim->getSampler_array();

	for(UInt32 i(0); i < samplers.getCount(); i++)
	{
		// reading in the samplers consists of finding the 
		// corresponging source for each sampler input
		domInputLocal_Array inputs = samplers[i]->getInput_array();
		for(UInt32 j(0); j < inputs.getCount();j++)
		{
			std::string inputSemantic = inputs[j]->getSemantic();
			if(inputSemantic.compare("INPUT") == 0)
			{	
				domURIFragmentType & source = inputs[j]->getSource();
				_inputSource = daeSafeCast<domSource>(source.getElement());
			} 
			else if(inputSemantic.compare("OUTPUT") == 0)
			{
				domURIFragmentType & source = inputs[j]->getSource();
				_outputSource = daeSafeCast<domSource>(source.getElement());
			}
			else if(inputSemantic.compare("INTERPOLATION") == 0)
			{
				domURIFragmentType & source = inputs[j]->getSource();
				_interpolationSource = daeSafeCast<domSource>(source.getElement());
			}
		}
	}
}

/*
*	Builds the keyframe sequences on floating point
*	fields.  This includes matrix and color animations.
*/
void 
ColladaAnimation::buildFloatSequence(domAnimationRef	 animation, 
									 domAccessorRef		 accessor, 
									 std::vector<Real32> timeKeys)
{
	_seqTy = INVALID;
	
	
	UInt32 stride = accessor->getStride();
	
	std::string pName;
	domParam_Array & params = accessor->getParam_array();
	if(params.getCount() > 0 && (params[0]->getName() != NULL))
	{
		pName = params[0]->getName();
	} 
	else 
	{
		pName = "";
	}

	if(stride == 1)
	{
		if(pName.compare("ANGLE") == 0)
		{ // we have a quaternion, need to determine which axis is it around
			if(_animationTarget.find("/rotateZ") != std::string::npos) 
				_seqTy = QUATZ;
			else if(_animationTarget.find("/rotateY") != std::string::npos)
				_seqTy = QUATY;
			else if(_animationTarget.find("/rotateX") != std::string::npos)
				_seqTy = QUATX;
		} 
		else if(	pName.compare("X") == 0 ||
					pName.compare("Y") == 0 ||
					pName.compare("Z") == 0	)
		{
			if(_animationTarget.find("/scale.X") != std::string::npos) 
				_seqTy = SCALEX;
			else if(_animationTarget.find("/scale.Y") != std::string::npos)
				_seqTy = SCALEY;
			else if(_animationTarget.find("/scale.Z") != std::string::npos)
				_seqTy = SCALEZ;
			else if(_animationTarget.find("/translate.X") != std::string::npos)
				_seqTy = TRANSX;
			else if(_animationTarget.find("/translate.Y") != std::string::npos)
				_seqTy = TRANSY;
			else if(_animationTarget.find("/translate.Z") != std::string::npos)
				_seqTy = TRANSZ;
		} 
		else
			_seqTy = REAL;
	} 
	else if(stride == 2)
		_seqTy = REAL2;
	else if(stride == 3)
	{
		// check to see if it might be a scale or translations animation
		if( pName.compare("X") == 0 ||
			pName.compare("Y") == 0 ||
			pName.compare("Z") == 0	)
		{
			if(_animationTarget.find("/scale") != std::string::npos)
			{
				_seqTy = SCALE;
			}
			else if(_animationTarget.find("/translate") != std::string::npos)
			{
				_seqTy = TRANSLATE;
			}
			else
			{
				_seqTy = REAL3;
			}
			
		}
		else if (	pName.compare("R") == 0 ||
					pName.compare("G") == 0 ||
					pName.compare("B") == 0 ||
					pName.compare("H") == 0 ||
					pName.compare("S") == 0 ||
					pName.compare("V") == 0 )
		{
			_seqTy = COLOR3;
		}	
		else
		{
			_seqTy = REAL3;
		}
	}
	else if(stride == 4)
	{
		if (	pName.compare("R") == 0 ||
				pName.compare("G") == 0 ||
				pName.compare("B") == 0 ||
				pName.compare("H") == 0 ||
				pName.compare("S") == 0 ||
				pName.compare("V") == 0 ||
				pName.compare("A") == 0 )
		{
			_seqTy = COLOR4;
		}
		else
			_seqTy = REAL4;
	}

	domListOfFloats & floats = _outputSource->getFloat_array()->getValue();
	UInt32 arrSize = floats.getCount();
	// we want to match up the most appropriate keyframe sequence for this source
	switch(_seqTy)
	{
	case REAL:
		{   //NIY
			break;
		}
	case QUATX:
	case QUATY:
	case QUATZ:
	case TRANSX:
	case TRANSY:
	case TRANSZ:
	case SCALEX:
	case SCALEY:
	case SCALEZ:
		{
			KeyframeNumberSequenceReal32UnrecPtr seq = KeyframeNumberSequenceReal32::create();
			for(UInt32 i(0); i < timeKeys.size() && i < arrSize;i++)
			{	
				seq->addKeyframe(floats[i],timeKeys[i]);
			}
			_keyframeSequence = seq;
			break;
		} 
	case REAL2:
		{
			KeyframeVectorSequenceVec2fUnrecPtr seq = KeyframeVectorSequenceVec2f::create();

			for(UInt32 i(0),j(0); i < timeKeys.size() && j < arrSize ; i++, j+=2)
			{
				seq->editFieldPtr()->push_back(Vec2f(floats[j],floats[j+1]));
				seq->editKeys()->push_back(timeKeys[i]);
			}
			_keyframeSequence = seq;
			break;
		}
	case REAL3:
	case SCALE:
	case TRANSLATE:
		{
			KeyframeVectorSequenceVec3fUnrecPtr seq = KeyframeVectorSequenceVec3f::create();

			for(UInt32 i(0),j(0); i < timeKeys.size() && j < arrSize ;i++, j+=3)
			{
				seq->addKeyframe(Vec3f(floats[j],floats[j+1],floats[j+2]),timeKeys[i]);
			}
			_keyframeSequence = seq;
			break;
		}
	case REAL4:
		{
			KeyframeVectorSequenceVec4fUnrecPtr seq = KeyframeVectorSequenceVec4f::create();

			for(UInt32 i(0),j(0); i < timeKeys.size() && j < arrSize ;i++, j+=4)
			{
				seq->editFieldPtr()->push_back(Vec4f(floats[j],floats[j+1],floats[j+2],floats[j+3]));
				seq->editKeys()->push_back(timeKeys[i]);
			}
			_keyframeSequence = seq;
			break;
		}
	case COLOR3:
		{	
			KeyframeColorSequenceColor3fUnrecPtr seq = KeyframeColorSequenceColor3f::create();

			for(UInt32 i(0),j(0); i < timeKeys.size() && j < arrSize ;i++, j+=3)
			{
				seq->editFieldPtr()->push_back(Color3f(floats[j],floats[j+1],floats[j+2]));
				seq->editKeys()    ->push_back(timeKeys[i]);
			}
			_keyframeSequence = seq;
			break;
		}
	case COLOR4:
		{
			KeyframeColorSequenceColor4fUnrecPtr seq = KeyframeColorSequenceColor4f::create();

			for(UInt32 i(0),j(0); i < timeKeys.size() && j < arrSize ;i++, j+=4)
			{
				seq->addKeyframe(Color4f(floats[j],floats[j+1],floats[j+2],floats[j+3]),timeKeys[i]);
			}
			_keyframeSequence = seq;
			break;
		}

	case INVALID:
	default:
		{
			_keyframeSequence = NULL;
			break;
		}
	} // end switch(seqTy)
}

/*
*	Builds the keyframes for integer sequences. (only sequences of 
*	integers, no sequences of integer vectors)
*/
void ColladaAnimation::buildIntSequence(domAnimationRef		animation,  
										domAccessorRef		accessor, 
										std::vector<Real32> timeKeys)
{
	domListOfInts & ints = _outputSource->getInt_array()->getValue();
	_seqTy = INVALID;
	if(accessor->getStride() == 1)
	{
		_seqTy = INT;
	} 
	else if(accessor->getStride() == 2)
	{
		_seqTy = INT2;
	} 
	else if(accessor->getStride() == 3)
	{
		_seqTy = INT3;
	} 
	else if(accessor->getStride() == 4)
	{
		_seqTy = INT4;
	}

	if(_seqTy == INT)
	{
		KeyframeNumberSequenceInt32UnrecPtr seq = KeyframeNumberSequenceInt32::create();
		for(UInt32 i(0); i < timeKeys.size();i++)
		{
			seq->addKeyframe(ints[0],timeKeys[0]);
		}
		_keyframeSequence = seq;
	}
	/*  ---- No integer vector types or keyframe sequences for them ----- */

}

// probably won't be needed....
void ColladaAnimation::buildBoolSequence(domAnimationRef	 animation, 
										 domAccessorRef		 accessor, 
										 std::vector<Real32> timeKeys)
{
	domBool_arrayRef bools	= _outputSource->getBool_array();
	_seqTy = INVALID;
	if(accessor->getStride() == 1)
	{
		_seqTy = BOOL;
	} 
	else if(accessor->getStride() == 2)
	{
		_seqTy = BOOL2;
	} 
	else if(accessor->getStride() == 3)
	{
		_seqTy = BOOL3;
	} 
	else if(accessor->getStride() == 4)
	{
		_seqTy = BOOL4;
	}
}

void ColladaAnimation::getInterpolationType()
{
	/*		Animator interpolation types:
			{LINEAR_INTERPOLATION=1, CUBIC_INTERPOLATION=2, 
			STEP_INTERPOLATION=4, LINEAR_NORMAL_INTERPOLATION=8, 
			SPHERICAL_LINEAR_INTERPOLATION=1, NORMALIZED_LINEAR_INTERPOLATION=1};
				use as OSG::Animator::<type>
	*/
	if( _interpolationSource != NULL)
	{
		if(	_interpolationSource->getName_array() != NULL )
		{
			std::string paramName = 
				_interpolationSource->getTechnique_common()->getAccessor()->getParam_array()[0]->getName();

			if( paramName == "INTERPOLATION")
			{
				std::string type;
				domListOfNames & names = _interpolationSource->getName_array()->getValue();
				
				if(names[0] != NULL) type = names[0];
				// we just pick the closest interpolation possible
				if(_animLength < 3) 
				{
					_interpolationType = Animator::LINEAR_INTERPOLATION;
				}
				else if(type.compare("BEZIER") == 0)
				{
					_interpolationType = Animator::CUBIC_INTERPOLATION;
				}
				else if(type.compare("LINEAR") == 0)
				{
					_interpolationType = Animator::LINEAR_INTERPOLATION;
				}
				else if(type.compare("BSPLINE") == 0)
				{
					_interpolationType = Animator::CUBIC_INTERPOLATION;
				}
				else if(type.compare("HERMITE") == 0)
				{
					_interpolationType = Animator::CUBIC_INTERPOLATION;
				} 
				else _interpolationType = Animator::CUBIC_INTERPOLATION;
			}
		}	
	}
	// default to linear interpolation
	_interpolationType = Animator::LINEAR_INTERPOLATION;
} // end getInterpolationType()

bool ColladaAnimation::isTransformAttribute(daeElement * target)
{
	if( daeSafeCast<domTranslate>(target) != NULL	||
		daeSafeCast<domRotate>(target) != NULL		||
		daeSafeCast<domScale>(target) != NULL		||
		daeSafeCast<domSkew>(target) != NULL)
	{
		return true;
	}
	return false;
}

TransformAnimator * ColladaAnimation::getTransformAnimator()
{
	if(!_reusingAnimator)
	{
		OSG::TransformAnimatorRecPtr anim = OSG::TransformAnimator::create();
		_animator = anim;
		return anim;
	} 
	else return dynamic_pointer_cast<TransformAnimator>(_animator); 
}

void ColladaAnimation::buildAnimation(Animator * animator)
{
	if(_animator != NULL)
	{
		if(_animation == NULL)
		{
			_animation = FieldAnimation::create();
		}
		// we attach everything to the animation except for the 
		// node core/etc that we are animating, because it hasn't
		// been created yet.  This will be done later, when the
		// scene is set up (in ColladaNode.cpp)
		_animation->setAnimator(_animator);
		_animation->setCycling(-1);
		_animation->setInterpolationType(_interpolationType);
	}
}

/***********************Ctors & Dtors*******************************/
ColladaAnimation::ColladaAnimation(daeElement *elem, ColladaGlobal *global)
    : Inherited (elem, global)
{
}

ColladaAnimation::~ColladaAnimation(void)
{ 
}

OSG_END_NAMESPACE
// EOF

