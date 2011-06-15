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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaLight.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"
#include "OSGColladaGlobal.h"
#include "OSGColladaInstanceLight.h"


#include "OSGDirectionalLight.h"
#include "OSGPointLight.h"
#include "OSGSpotLight.h"
#include "OSGLightEnv.h"

#include <dom/domLight.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaLight::_regHelper(
    &ColladaLight::create, "light");


ColladaElementTransitPtr
ColladaLight::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaLight(elem, global));
}

void
ColladaLight::read(void)
{
    OSG_COLLADA_LOG(("ColladaLight::read\n"));

    domLightRef          light = getDOMElementAs<domLight>();

    domLight::domTechnique_commonRef technique = light->getTechnique_common();

    if(technique)
    {
        if(technique->getAmbient())
        {
            readTechniqueAmbient(technique->getAmbient());
        }
        else if(technique->getDirectional())
        {
            readTechniqueDirectional(technique->getDirectional());
        }
        else if(technique->getPoint())
        {
            readTechniquePoint(technique->getPoint());
        }
        else if(technique->getSpot())
        {
            readTechniqueSpot(technique->getSpot());
        }
    }
}

Light *
ColladaLight::createInstance(ColladaInstanceElement *colInstElem)
{
    OSG_COLLADA_LOG(("ColladaLight::createInstance\n"));

    LightUnrecPtr              retVal        = NULL;
    domLightRef                light        = getDOMElementAs<domLight>();
    ColladaInstanceLightRefPtr colInstLight =
        dynamic_cast<ColladaInstanceLight *>(colInstElem);
    domInstance_lightRef       instLight    =
        colInstElem->getDOMElementAs<domInstance_light>();

    domLight::domTechnique_commonRef technique = light->getTechnique_common();

    if(technique)
    {
        if(technique->getAmbient())
        {
            retVal = createTechniqueAmbient(technique->getAmbient(),
                light, instLight);
        }
        else if(technique->getDirectional())
        {
            retVal = createTechniqueDirectional(technique->getDirectional(),
                light, instLight);
        }
        else if(technique->getPoint())
        {
            retVal = createTechniquePoint(technique->getPoint(),
                light, instLight);
        }
        else if(technique->getSpot())
        {
            retVal = createTechniqueSpot(technique->getSpot(),
                light, instLight);
        }
    }

    editInstStore().push_back(retVal);

    return retVal;
}

void
ColladaLight::readTechniqueAmbient(domLight::domTechnique_common::domAmbient *tec)
{
    if(tec == NULL)
    {
        SWARNING << "ColladaLight::readTechniqueAmbient: No DOM element or "
                 << "incorrect type." << std::endl;
        return;
    }
}

void
ColladaLight::readTechniqueDirectional(domLight::domTechnique_common::domDirectional *tec)
{
    if(tec == NULL)
    {
        SWARNING << "ColladaLight::readTechniqueDirectional: No DOM element or "
                 << "incorrect type." << std::endl;
        return;
    }
}

void
ColladaLight::readTechniquePoint(domLight::domTechnique_common::domPoint *tec)
{
    if(tec == NULL)
    {
        SWARNING << "ColladaLight::readTechniquePoint: No DOM element or "
                 << "incorrect type." << std::endl;
        return;
    }
}

void
ColladaLight::readTechniqueSpot(domLight::domTechnique_common::domSpot *tec)
{
    if(tec == NULL)
    {
        SWARNING << "ColladaLight::readTechniqueSpot: No DOM element or "
                 << "incorrect type." << std::endl;
        return;
    }
}

LightTransitPtr
ColladaLight::createTechniqueAmbient(
    domLight::domTechnique_common::domAmbient *tec,
    domLight *light,
    domInstance_light *instLight                      )
{
    SWARNING << "ColladaLight::createTechniqueAmbient: NIY." << std::endl;

    return LightTransitPtr(NULL);
}

LightTransitPtr
ColladaLight::createTechniqueDirectional(
    domLight::domTechnique_common::domDirectional *tec,
    domLight *light,
    domInstance_light *instLight                      )
{
    OSG_COLLADA_LOG(("ColladaLight::createTechniqueDirectional\n"));

    ColladaInstanceLightRefPtr colInstLight =
        getUserDataAs<ColladaInstanceLight>(instLight);

    domTargetableFloat3Ref color = tec->getColor    ();

    getGlobal()->getStatCollector()->getElem(ColladaGlobal::statNLightCreated)->inc();
    DirectionalLightUnrecPtr osgLight        = DirectionalLight::create();
    osgLight->setAmbient(Color4f(0.0f,0.0f,0.0f,1.0f));
    osgLight->setDirection(Vec3f(0.0f,0.0f,-1.0f));

    if(color != NULL)
    {
        Color4f osgColor(color->getValue().get(0),color->getValue().get(1),color->getValue().get(2),1.0f);
        osgLight->setDiffuse(osgColor);
        osgLight->setSpecular(osgColor);
    }

    return LightTransitPtr(osgLight);
}

LightTransitPtr
ColladaLight::createTechniquePoint(
    domLight::domTechnique_common::domPoint *tec,
    domLight *light,
    domInstance_light *instLight                      )
{
    OSG_COLLADA_LOG(("ColladaLight::createTechniquePoint\n"));

    ColladaInstanceLightRefPtr colInstLight =
        getUserDataAs<ColladaInstanceLight>(instLight);

    domTargetableFloat3Ref color = tec->getColor    ();
    domTargetableFloatRef constAtten = tec->getConstant_attenuation    ();
    domTargetableFloatRef linAtten = tec->getLinear_attenuation    ();
    domTargetableFloatRef quadAtten = tec->getQuadratic_attenuation    ();

    getGlobal()->getStatCollector()->getElem(ColladaGlobal::statNLightCreated)->inc();
    PointLightUnrecPtr osgLight        = PointLight::create();
    osgLight->setAmbient(Color4f(0.0f,0.0f,0.0f,1.0f));
    osgLight->setPosition(Vec3f(0.0f,0.0f,0.0f));

    if(color != NULL)
    {
        Color4f osgColor(color->getValue().get(0),color->getValue().get(1),color->getValue().get(2),1.0f);
        osgLight->setDiffuse(osgColor);
        osgLight->setSpecular(osgColor);
    }
    if(constAtten != NULL)
    {
        osgLight->setConstantAttenuation(constAtten->getValue());
    }
    if(linAtten != NULL)
    {
        osgLight->setLinearAttenuation(linAtten->getValue());
    }
    if(quadAtten != NULL)
    {
        osgLight->setQuadraticAttenuation(quadAtten->getValue());
    }

    return LightTransitPtr(osgLight);
}

LightTransitPtr
ColladaLight::createTechniqueSpot(
    domLight::domTechnique_common::domSpot *tec,
    domLight *light,
    domInstance_light *instLight                      )
{
    OSG_COLLADA_LOG(("ColladaLight::createTechniqueSpot\n"));

    ColladaInstanceLightRefPtr colInstLight =
        getUserDataAs<ColladaInstanceLight>(instLight);

    domTargetableFloat3Ref color = tec->getColor    ();
    domTargetableFloatRef constAtten = tec->getConstant_attenuation    ();
    domTargetableFloatRef linAtten = tec->getLinear_attenuation    ();
    domTargetableFloatRef quadAtten = tec->getQuadratic_attenuation    ();
    domTargetableFloatRef falloffAngle = tec->getFalloff_angle    ();
    domTargetableFloatRef falloffExp = tec->getFalloff_exponent    ();

    getGlobal()->getStatCollector()->getElem(ColladaGlobal::statNLightCreated)->inc();
    SpotLightUnrecPtr osgLight        = SpotLight::create();
    osgLight->setAmbient(Color4f(0.0f,0.0f,0.0f,1.0f));
    osgLight->setDirection(Vec3f(0.0f,0.0f,-1.0f));

    if(color != NULL)
    {
        Color4f osgColor(color->getValue().get(0),color->getValue().get(1),color->getValue().get(2),1.0f);
        osgLight->setDiffuse(osgColor);
        osgLight->setSpecular(osgColor);
    }
    if(constAtten != NULL)
    {
        osgLight->setConstantAttenuation(constAtten->getValue());
    }
    if(linAtten != NULL)
    {
        osgLight->setLinearAttenuation(linAtten->getValue());
    }
    if(quadAtten != NULL)
    {
        osgLight->setQuadraticAttenuation(quadAtten->getValue());
    }
    if(falloffAngle != NULL)
    {
        osgLight->setSpotCutOff(osgDegree2Rad(falloffAngle->getValue()));
    }
    if(falloffExp != NULL)
    {
        osgLight->setSpotExponent(falloffExp->getValue());
    }

    return LightTransitPtr(osgLight);
}

/*! Return parameter of the light (\c <newparam> tags) with the given \a name.
 */
daeElement *
ColladaLight::findDOMParam(const std::string &name) const
{
    //ParamSampler2DMapConstIt sampler2DIt = _sampler2DParams.find(name);

    //if(sampler2DIt != _sampler2DParams.end())
    //{
    //    return sampler2DIt->second.sampler2D;
    //}

    //ParamSurfaceMapConstIt surfaceIt = _surfaceParams.find(name);

    //if(surfaceIt != _surfaceParams.end())
    //{
    //    return surfaceIt->second.surface;
    //}

    return NULL;
}

/*! Return the loader element for the parameter of the light (\c <newparam>
    tags) with the given \a name.
 */
ColladaElement *
ColladaLight::findParam(const std::string &name) const
{
    /*ParamSampler2DMapConstIt sampler2DIt = _sampler2DParams.find(name);

    if(sampler2DIt != _sampler2DParams.end())
    {
        return sampler2DIt->second.colSampler2D;
    }

    ParamSurfaceMapConstIt surfaceIt = _surfaceParams.find(name);

    if(surfaceIt != _surfaceParams.end())
    {
        return surfaceIt->second.colSurface;
    }*/

    return NULL;
}

ColladaLight::ColladaLight(daeElement *elem, ColladaGlobal *global)
    : Inherited(elem, global)
{
}

ColladaLight::~ColladaLight(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
