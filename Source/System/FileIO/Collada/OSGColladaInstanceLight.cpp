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

#include "OSGColladaInstanceLight.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"

#include <dom/domInstance_light.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaInstanceLight::_regHelper(
    &ColladaInstanceLight::create, "instance_light");

ColladaElementTransitPtr
ColladaInstanceLight::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaInstanceLight(elem, global));
}

void
ColladaInstanceLight::read(void)
{
    OSG_COLLADA_LOG(("ColladaInstanceLight::read\n"));

    ColladaLightRefPtr colLight = getTargetElem();

    if(colLight == NULL)
    {
        colLight = dynamic_pointer_cast<ColladaLight>(
            ColladaElementFactory::the()->create(
                getTargetDOMElem(), getGlobal()));

        colLight->read();
    }

    domInstance_lightRef instLight = getDOMElementAs<domInstance_light>();

    //const domInstance_light::domTechnique_hint_Array &techHints =
    //    instLight->getTechnique_hint_array();

    //if(techHints.getCount() > 0)
    //{
    //    SWARNING << "ColladaInstanceLight::read: Ignoring ["
    //             << techHints.getCount() << "] <technique_hint> elements."
    //             << std::endl;
    //}

    //const domInstance_light::domSetparam_Array &setParams =
    //    instLight->getSetparam_array();

    //if(setParams.getCount() > 0)
    //{
    //    SWARNING << "ColladaInstanceLight::read: Ignoring ["
    //             << setParams.getCount() << "] <setparam> elements."
    //             << std::endl;
    //}
}

Light *
ColladaInstanceLight::process(ColladaElement *parent)
{
    OSG_COLLADA_LOG(("ColaldaInstanceLight::process\n"));

    ColladaLightRefPtr colLight = getTargetElem();

    return colLight->createInstance(this);
}

ColladaLight *
ColladaInstanceLight::getTargetElem(void) const
{
    ColladaLight *retVal     = NULL;
    domLightRef   targetElem = getTargetDOMElem();

    if(targetElem != NULL)
    {
        retVal = getUserDataAs<ColladaLight>(targetElem);
    }

    return retVal;
}

domLight *
ColladaInstanceLight::getTargetDOMElem(void) const
{
    domLightRef          retVal     = NULL;
    domInstance_lightRef instLight = getDOMElementAs<domInstance_light>();

    if(instLight->getUrl().getElement() != NULL)
    {
        retVal = daeSafeCast<domLight>(instLight->getUrl().getElement());
    }
    else
    {
        SWARNING << "ColladaInstanceEffet::getTargetDOMElem: "
                 << "can not resolve URL [" << instLight->getUrl().str()
                 << "]." << std::endl;
    }

    return retVal;
}

const ColladaInstanceLight::TCSymbolToSlotMap &
ColladaInstanceLight::getTCMap(void) const
{
    return _tcMap;
}

ColladaInstanceLight::TCSymbolToSlotMap &
ColladaInstanceLight::editTCMap(void)
{
    return _tcMap;
}

bool
ColladaInstanceLight::findTC(
    const std::string &tcSymbol, UInt32 &texSlot) const
{
    bool                     retVal = false;
    TCSymbolToSlotMapConstIt tcIt   = _tcMap.find(tcSymbol);

    if(tcIt != _tcMap.end())
    {
        texSlot = tcIt->second;
        retVal  = true;
    }

    return retVal;
}

ColladaInstanceLight::ColladaInstanceLight(
    daeElement *elem, ColladaGlobal *global)

    : Inherited(elem, global)
{
}

ColladaInstanceLight::~ColladaInstanceLight(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
