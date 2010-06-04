/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: David Kabala djkabala@gmail.com                                *
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

#ifndef _OSGCOLLADALIGHT_H_
#define _OSGCOLLADALIGHT_H_

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaInstantiableElement.h"
#include "OSGColladaElementFactoryHelper.h"
#include "OSGLight.h"

#include <dom/domCommon_transparent_type.h>

// forward decl
class domLight;


OSG_BEGIN_NAMESPACE

// forward decl
class ColladaInstanceLight;


class OSG_FILEIO_DLLMAPPING ColladaLight : public ColladaInstantiableElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaInstantiableElement Inherited;
    typedef ColladaLight              Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaLight);

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

    virtual void      read          (void                            );
    virtual Light    *createInstance(ColladaInstanceElement *instElem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    daeElement     *findDOMParam(const std::string &name) const;
    ColladaElement *findParam   (const std::string &name) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
 protected:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             ColladaLight(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaLight(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Profile Handlers                                             */
    /*! \{                                                                 */

    /*virtual void      readProfileCommon(domProfile_COMMON *prof);

    virtual MaterialTransitPtr createInstanceProfileCommon(
        domProfile_COMMON  *prof,       domLight *light,
        domInstance_light *instLight                    );*/

    /*! \}                                                                 */
    void readTechniqueAmbient(domLight::domTechnique_common::domAmbient *tec);

    void readTechniqueDirectional(domLight::domTechnique_common::domDirectional *tec);

    void readTechniquePoint(domLight::domTechnique_common::domPoint *tec);

    void readTechniqueSpot(domLight::domTechnique_common::domSpot *tec);

    LightTransitPtr createTechniqueAmbient(
        domLight::domTechnique_common::domAmbient *tec,
        domLight *light,
        domInstance_light *instLight                      );

    LightTransitPtr createTechniqueDirectional(
        domLight::domTechnique_common::domDirectional *tec,
        domLight *light,
        domInstance_light *instLight                      );

    LightTransitPtr createTechniquePoint(
        domLight::domTechnique_common::domPoint *tec,
        domLight *light,
        domInstance_light *instLight                      );

    LightTransitPtr createTechniqueSpot(
        domLight::domTechnique_common::domSpot *tec,
        domLight *light,
        domInstance_light *instLight                      );

    /*---------------------------------------------------------------------*/

    static ColladaElementRegistrationHelper _regHelper;
};

OSG_GEN_MEMOBJPTR(ColladaLight);

OSG_END_NAMESPACE

// #include "OSGColladaLight.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADALIGHT_H_
