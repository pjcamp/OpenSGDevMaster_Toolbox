/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *                 contact: dan.guilliams@gmail.com			     *
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

#ifndef _OSGCOLLADANIMATION_H_
#define _OSGCOLLADANIMATION_H_

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaInstantiableElement.h"
#include "OSGColladaElementFactoryHelper.h"
#include "OSGColladaInstanceMaterial.h"
#include "OSGColladaSource.h"
#include "OSGNode.h"
//Animation
#include "OSGKeyframeSequences.h"
#include "OSGKeyframeAnimator.h"
#include "OSGFieldAnimation.h"
#include "OSGAnimation.h"


#include <dae/daeDomTypes.h>
#include <dom/domInputLocal.h>
#include <dom/domInputLocalOffset.h>

// forward decls



OSG_BEGIN_NAMESPACE

// forward decls
class TransformAnimator;
class ColladaInstanceAnimation;
OSG_GEN_MEMOBJPTR(ColladaInstanceAnimation);


class OSG_FILEIO_DLLMAPPING ColladaAnimation : public ColladaInstantiableElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaInstantiableElement Inherited;
    typedef ColladaAnimation            Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaAnimation);



    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Create                                                       */
    /*! \{                                                                 */

    static ColladaElementTransitPtr
        create(daeElement *elem, ColladaGlobal *global);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void		read(void);
   // virtual FieldContainer *process(void);

	virtual FieldContainer *createInstance(ColladaInstanceElement *colInstElem);

	// used to determine which type of keyframe sequence used
	enum SequenceType {	REAL,REAL2,REAL3,REAL4, // 
						INT,INT2,INT3,INT4, // not used?
						BOOL,BOOL2,BOOL3,BOOL4, // probably not used
						COLOR3,COLOR4, // definitely used
						QUATX,QUATY,QUATZ, // rotations
						TRANSX,TRANSY,TRANSZ, // translations in 1 axis
						SCALEX,SCALEY,SCALEZ, // scales in 1 axis
						TRANSLATE,SCALE, // translation/scaling in all 3 axis
						INVALID // unable to determine type
					  };
	// getters for this class.  These are used to get data from the ColladaAnimaiton
	// when finalizing animated fields when setting up a scene in ColladNode.cpp
	ColladaAnimation::SequenceType getSequenceType();
	FieldAnimation* getAnimation();

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             ColladaAnimation(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaAnimation(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Internal Types                                               */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
	static ColladaElementRegistrationHelper _regHelper;



	void buildKeyframeSequence(domAnimationRef anim);
	void buildAnimator(domAnimationRef anim);
	void buildAnimation(Animator * animator);
	void buildFloatSequence(domAnimationRef animation, domAccessorRef accessor, std::vector<Real32> timeKeys);
	void buildIntSequence(domAnimationRef animation, domAccessorRef accessor, std::vector<Real32> timeKeys);
	void buildBoolSequence(domAnimationRef animation, domAccessorRef accessor, std::vector<Real32> timeKeys);
	void readSamplers(domAnimationRef anim);
	void getInterpolationType();
	bool isTransformAttribute(daeElement * target);
	TransformAnimator* getTransformAnimator();
	KeyframeAnimator*   getKeyframeAnimator();

	
	//  map from a <source> name to its corresponding OpenSG keyframe sequence
	//  typedef std::map<std::string, KeyframeInfoPtr>	SourceMap;
	//  typedef SourceMap::iterator								SourceMapIt;
	//	typedef SourceMap::const_iterator						SourceMapConstIt;

	//SourceMap _sourceMap;
	//SourceMap _samplerMap;
	std::string _animationTarget;
	KeyframeSequenceUnrecPtr _keyframeSequence;
	SequenceType _seqTy;
	AnimatorUnrecPtr _animator;
	FieldAnimationUnrecPtr _animation;
	Animator::InterpolationType _interpolationType;
	daeElement * _animTarget;
	domSourceRef _inputSource;
	domSourceRef _outputSource;
	domSourceRef _interpolationSource;
	UInt32 _animLength;
	bool _reusingAnimator;
};

OSG_GEN_MEMOBJPTR(ColladaAnimation);

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADANIMATION_H_

