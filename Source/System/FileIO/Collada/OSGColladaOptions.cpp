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

#include "OSGColladaOptions.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGIOFileTypeBase.h"

OSG_BEGIN_NAMESPACE

void
ColladaOptions::parseOptions(const OptionSet &optSet)
{
    OSG_COLLADA_LOG(("ColladaOptions::parseOptions\n"));

    IOFileTypeBase::getOptionAs<bool>(
        optSet, "invertTransparency", _invertTransparency);
    IOFileTypeBase::getOptionAs<bool>(
        optSet, "createNameAttachments", _createNameAttachments);
    IOFileTypeBase::getOptionAs<bool>(
        optSet, "flattenNodeXForms", _flattenNodeXForms);
	IOFileTypeBase::getOptionAs<bool>(
		optSet, "readAnimations", _readAnimations);
}

/*! Return \c true if transparency values should be inverted, \c false
    otherwise. Option name: "invertTransparency".
    Some tools store transparency values inverted, use this to ensure correct
    display.
 */
bool
ColladaOptions::getInvertTransparency(void) const
{
    return _invertTransparency;
}

/*! Set transparency value inversion. Option name: "invertTransparency".
    Some tools store transparency values inverted, use this to ensure correct
    display.
 */
void
ColladaOptions::setInvertTransparency(bool value)
{
    _invertTransparency = value;
}

/*! Return \c true if NameAttachments should be created, \c false otherwise.
    Option name: "createNameAttachments".
 */
bool
ColladaOptions::getCreateNameAttachments(void) const
{
    return _createNameAttachments;
}

/*! Set if NameAttachments should be created.
    Option name: "createNameAttachments".
 */
void
ColladaOptions::setCreateNameAttachments(bool value)
{
    _createNameAttachments = value;
}


/*! Set if Node transforms should be flattened into a single xform.
    Option name: "flattenNodeXForms".
 */
bool ColladaOptions::getFlattenNodeXForms    (void      ) const
{
    return _flattenNodeXForms;
}

/*! Return \c true if Node transforms should be flattened into a single xform, \c false otherwise.
    Option name: "flattenNodeXForms".
 */
void ColladaOptions::setFlattenNodeXForms    (bool value)
{
    _flattenNodeXForms = value;
}

bool ColladaOptions::getReadAnimations    (void      ) const
{
	return _readAnimations;
}

void ColladaOptions::setReadAnimations    (bool value)
{
	_readAnimations = value;
}

ColladaOptions::ColladaOptions(void)
    : Inherited             ()
    , _invertTransparency   (false)
    , _createNameAttachments(true)
    , _flattenNodeXForms    (true)
	, _readAnimations		(true)
{
}

ColladaOptions::~ColladaOptions(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
