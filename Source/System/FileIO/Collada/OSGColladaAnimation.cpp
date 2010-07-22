
#include "OSGColladaAnimation.h"
#include "OSGBaseFunctions.h"

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

	buildKeyframeSequence(anim);

	// this is where the animator/animation should be set up
	// TODO: figure out how to link up the animation target from collada to openSG

	if(_animation != NULL) 
	{
		getGlobal()->addFieldContainer(_animation);
	}

	return;
}

FieldContainer *
ColladaAnimation::createInstance(ColladaInstanceElement *colInstElem)
{
	// NIY
	return NULL;
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
				UInt32 numKeys = OSG::osgMin<UInt32>(inputAccessor->getCount(),outputAccessor->getCount());
				domListOfFloats & arr = _inputSource->getFloat_array()->getValue();
				if(arr.getCount() > 0 && inputAccessor->getStride() == 1)
				{
					std::vector<Real32> inputKeys;
					for(UInt32 i(0); i < numKeys; i++)
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

void 
ColladaAnimation::buildFloatSequence(domAnimationRef	 animation, 
									 domAccessorRef		 accessor, 
									 std::vector<Real32> timeKeys)
{
	SequenceType seqTy = INVALID;
	domParam_Array & params = accessor->getParam_array();
	
	UInt32 stride = accessor->getStride();
	
	std::string pName(params[0]->getName());
	
	if(stride == 1)
	{
		if(pName.compare("ANGLE") == 0)
		{ // we have a quaternion, need to determine which axis is it around
			if(_animationTarget.find("rotateZ") != std::string::npos) 
				seqTy = QUATZ;
			else if(_animationTarget.find("rotateY") != std::string::npos)
				seqTy = QUATY;
			else if(_animationTarget.find("rotateX") != std::string::npos)
				seqTy = QUATX;
		} else 
			seqTy = REAL;
	} 
	else if(stride == 2)
		seqTy = REAL2;
	else if(stride == 3)
	{
		if( pName.compare("X") == 0 ||
			pName.compare("Y") == 0 ||
			pName.compare("Z") == 0	)
		{
			seqTy = REAL3;
		}
		else if (	pName.compare("R") == 0 ||
					pName.compare("G") == 0 ||
					pName.compare("B") == 0 ||
					pName.compare("H") == 0 ||
					pName.compare("S") == 0 ||
					pName.compare("V") == 0 )
		{
			seqTy = COLOR3;
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
			seqTy = COLOR4;
		}
	}

	domListOfFloats & floats = _outputSource->getFloat_array()->getValue( );
	UInt32 maxArrIdx = floats.getCount();
	// we want to match up the most appropriate keyframe sequence for this source
	switch(seqTy)
	{
	case REAL:
		{
			KeyframeNumberSequenceReal32UnrecPtr seq = KeyframeNumberSequenceReal32::create();
			for(UInt32 i(0); i < timeKeys.size() && i < maxArrIdx;i++)
			{
				seq->addKeyframe(floats[i],timeKeys[i]);
			}
			_keyframeSequence = seq;
			break;
		} 
	case REAL2:
		{
			KeyframeVectorSequenceVec2fUnrecPtr seq = KeyframeVectorSequenceVec2f::create();

			for(UInt32 i(0),j(0); i < timeKeys.size() && j < maxArrIdx ; i++)
			{
				Vec2f temp(floats[j++],floats[j++]);
				seq->editFieldPtr()->push_back(temp);
				seq->editKeys()    ->push_back(timeKeys[i]);
			}
			_keyframeSequence = seq;
			break;
		}
	case REAL3:
		{
			KeyframeVectorSequenceVec3fUnrecPtr seq = KeyframeVectorSequenceVec3f::create();

			for(UInt32 i(0),j(0); i < timeKeys.size() && j < maxArrIdx ;i++)
			{
				seq->addKeyframe(Vec3f(floats[j++],floats[j++],floats[j++]),timeKeys[i]);
			}
			_keyframeSequence = seq;
			break;
		}
	case REAL4:
		{
			KeyframeVectorSequenceVec4fUnrecPtr seq = KeyframeVectorSequenceVec4f::create();

			for(UInt32 i(0),j(0); i < timeKeys.size() && j < maxArrIdx ;i++)
			{
				Vec4f temp(floats[j++],floats[j++],floats[j++],floats[j++]);
				seq->editFieldPtr()->push_back(temp);
				seq->editKeys()    ->push_back(timeKeys[i]);
			}
			_keyframeSequence = seq;
			break;
		}
	case COLOR3:
		{	
			KeyframeColorSequenceColor3fUnrecPtr seq = KeyframeColorSequenceColor3f::create();

			for(UInt32 i(0),j(0); i < timeKeys.size() && j < maxArrIdx ;i++)
			{
				Color3f temp(floats[j++],floats[j++],floats[j++]);
				seq->editFieldPtr()->push_back(temp);
				seq->editKeys()    ->push_back(timeKeys[i]);
				
			}
			_keyframeSequence = seq;
			break;
		}
	case COLOR4:
		{
			KeyframeColorSequenceColor4fUnrecPtr seq = KeyframeColorSequenceColor4f::create();

			for(UInt32 i(0),j(0); i < timeKeys.size() && j < maxArrIdx ;i++)
			{
				seq->addKeyframe(Color4f(floats[j++],floats[j++],floats[j++],floats[j++]),timeKeys[i]);
			}
			_keyframeSequence = seq;
			break;
		}
	case QUATX:
	case QUATY:
	case QUATZ:
		{
			Vec3f axis = (seqTy == QUATX)?(Vec3f(1,0,0)):((seqTy == QUATY)?(Vec3f(0,1,0)):(Vec3f(0,0,1)));
			KeyframeRotationSequenceQuaternionUnrecPtr seq = KeyframeRotationSequenceQuaternion::create();
			for(UInt32 i(0); i < timeKeys.size() && i < maxArrIdx;i++)
			{
				seq->addKeyframe(Quaternion(axis, floats[i]),timeKeys[i]);
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

void ColladaAnimation::buildIntSequence(domAnimationRef		animation,  
										domAccessorRef		accessor, 
										std::vector<Real32> timeKeys)
{
	domListOfInts & ints = _outputSource->getInt_array()->getValue();
	SequenceType seqTy = INVALID;
	if(accessor->getStride() == 1)
	{
		seqTy = INT;
	} 
	else if(accessor->getStride() == 2)
	{
		seqTy = INT2;
	} 
	else if(accessor->getStride() == 3)
	{
		seqTy = INT3;
	} 
	else if(accessor->getStride() == 4)
	{
		seqTy = INT4;
	}

	if(seqTy == INT)
	{
		KeyframeNumberSequenceInt32UnrecPtr seq = KeyframeNumberSequenceInt32::create();
		for(UInt32 i(0); i < timeKeys.size();i++)
		{
			seq->addKeyframe(ints[0],timeKeys[0]);
		}
		_keyframeSequence = seq;
	}
	/*  ---- No integer vector types or keyframe sequences for them -----
	
	else if(seqTy == INT2)
	{
		KeyframeVectorSequenceVec2iUnrecPtr seq = KeyframeVectorSequenceVec2i::create();
		for(UInt32 i(0),j(0); i < timeKeys.size();i++)
		{
			seq->addKeyframe(Vec2f(floats[j++],floats[j++]),timeKeys[i]);
		}
		_keyframeSequence = seq;
	}
	else if(seqTy == INT3)
	{
		
	}
	else if(seqTy == INT4)
	{
		
	} */
	
}

void ColladaAnimation::buildBoolSequence(domAnimationRef	 animation, 
										 domAccessorRef		 accessor, 
										 std::vector<Real32> timeKeys)
{
	domBool_arrayRef bools	= _outputSource->getBool_array();
	SequenceType seqTy = INVALID;
	if(accessor->getStride() == 1)
	{
		seqTy = BOOL;
	} 
	else if(accessor->getStride() == 2)
	{
		seqTy = BOOL2;
	} 
	else if(accessor->getStride() == 3)
	{
		seqTy = BOOL3;
	} 
	else if(accessor->getStride() == 4)
	{
		seqTy = BOOL4;
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
				if(type.compare("BEZIER") == 0)
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
	// default to cubic interpolation
	_interpolationType = Animator::CUBIC_INTERPOLATION;
} // end getInterpolationType()


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

