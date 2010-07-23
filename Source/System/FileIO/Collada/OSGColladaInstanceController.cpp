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

#include "OSGColladaInstanceController.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"

#include <dom/domInstance_controller.h>
#include <dom/domInstance_material.h>
#include <dom/domBind_material.h>
#include <dom/domParam.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaInstanceController::_regHelper(
    &ColladaInstanceController::create, "instance_controller");


ColladaElementTransitPtr
ColladaInstanceController::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaInstanceController(elem, global));
}

void
ColladaInstanceController::read(void)
{
    OSG_COLLADA_LOG(("ColladaInstanceController::read\n"));

    ColladaControllerRefPtr colCont = getTargetElem();

    if(colCont == NULL)
    {
        colCont = dynamic_pointer_cast<ColladaController>(
            ColladaElementFactory::the()->create(
                getTargetDOMElem(), getGlobal()));

        colCont->read();
    }

	domInstance_controllerRef instCont = getDOMElementAs<domInstance_controller>();
	
	_joints = instCont->getSkeleton_array();

    domBind_materialRef     bindMat = instCont->getBind_material            ();

    if(bindMat == NULL)
    {
        SWARNING << "ColladaInstanceController::read: No <bind_material> found."
                 << std::endl;
        return;
    }

    domBind_material::domTechnique_commonRef  techCom      =
        bindMat->getTechnique_common();
    const domInstance_material_Array         &instMatArray =
        techCom->getInstance_material_array();

    for(UInt32 i = 0; i < instMatArray.getCount(); ++i)
    {
        ColladaInstanceMaterialRefPtr colInstMat =
            getUserDataAs<ColladaInstanceMaterial>(instMatArray[i]);

        if(colInstMat == NULL)
        {
            colInstMat = dynamic_pointer_cast<ColladaInstanceMaterial>(
                ColladaElementFactory::the()->create(
                    instMatArray[i], getGlobal()));

            colInstMat->read();
        }

        _matMap[colInstMat->getSymbol()] = colInstMat;

        OSG_COLLADA_LOG(("ColladaInstanceController::read: binding symbol [%s] "
                         "to target [%s]\n",
                         colInstMat->getSymbol().c_str(),
                         instMatArray[i]->getTarget().getURI()));
    }
}

Node *
ColladaInstanceController::process(ColladaElement *parent)
{
    OSG_COLLADA_LOG(("ColladaInstanceController::process\n"));

    ColladaControllerRefPtr colCont = getTargetElem();

	getGlobal()->addInstanceController(this);

    return colCont->createInstance(this);
}

ColladaController *
ColladaInstanceController::getTargetElem(void) const
{
    ColladaController *retVal     = NULL;
    daeElementRef    targetElem = getTargetDOMElem();

    if(targetElem != NULL)
    {
        retVal = getUserDataAs<ColladaController>(targetElem);
    }

    return retVal;
}

daeElement *
ColladaInstanceController::getTargetDOMElem(void) const
{
    domControllerRef          retVal  = NULL;
    domInstance_controllerRef instCont = getDOMElementAs<domInstance_controller>();

    if(instCont->getUrl().getElement() != NULL)
    {
        retVal = daeSafeCast<domController>(instCont->getUrl().getElement());
    }

    return retVal;
}

SkeletonBlendedGeometry *
ColladaInstanceController::getSkeleton	 (void) const
{
	return _skeleton;
}

void
ColladaInstanceController::setSkeleton	 (SkeletonBlendedGeometry * skeleton)
{
	_skeleton = skeleton;
}


const ColladaInstanceController::Joints& 
ColladaInstanceController::getJoints		 (void) const
{
	return _joints;
}

const ColladaInstanceController::MaterialMap &
ColladaInstanceController::getMaterialMap(void) const
{
    return _matMap;
}


ColladaInstanceController::ColladaInstanceController(
    daeElement *elem, ColladaGlobal *global)

    : Inherited(elem, global)
{
}

ColladaInstanceController::~ColladaInstanceController(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
