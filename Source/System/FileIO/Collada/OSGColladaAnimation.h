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

	// used to determine which type of keyframe sequence we need
	enum SequenceType {	REAL,REAL2,REAL3,REAL4,INT,INT2,INT3,INT4,BOOL,BOOL2,
						BOOL3,BOOL4,COLOR3,COLOR4,QUATX,QUATY,QUATZ,INVALID};

	void buildKeyframeSequence(domAnimationRef anim);
	void buildFloatSequence(domAnimationRef animation, domAccessorRef accessor, std::vector<Real32> timeKeys);
	void buildIntSequence(domAnimationRef animation, domAccessorRef accessor, std::vector<Real32> timeKeys);
	void buildBoolSequence(domAnimationRef animation, domAccessorRef accessor, std::vector<Real32> timeKeys);
	void readSamplers(domAnimationRef anim);
	void getInterpolationType();

	
	//  map from a <source> name to its corresponding OpenSG keyframe sequence
	//  typedef std::map<std::string, KeyframeInfoPtr>	SourceMap;
	//  typedef SourceMap::iterator								SourceMapIt;
	//	typedef SourceMap::const_iterator						SourceMapConstIt;

	//SourceMap _sourceMap;
	//SourceMap _samplerMap;
	std::string _animationTarget;
	KeyframeSequenceUnrecPtr _keyframeSequence;
	AnimatorUnrecPtr _animator;
	AnimationUnrecPtr _animation;
	Animator::InterpolationType _interpolationType;
	domSourceRef _inputSource;
	domSourceRef _outputSource;
	domSourceRef _interpolationSource;
	
};

OSG_GEN_MEMOBJPTR(ColladaAnimation);

OSG_END_NAMESPACE

// #include "OSGColladaGeometry.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADANIMATION_H_

