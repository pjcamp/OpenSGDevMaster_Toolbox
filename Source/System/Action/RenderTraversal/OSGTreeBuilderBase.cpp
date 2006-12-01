/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_CLEANED_RENDERACTION

#include "OSGRenderTreeNodePool.h"
#include "OSGTreeBuilderBase.h"
#include "OSGBaseFunctions.h"
#include "OSGRenderPartition.h"

//#define OSG_DUMP_SORTING

OSG_USING_NAMESPACE

/*! \class OSG::TreeBuilderBase
    \ingroup 
 */

const TreeBuilderBase TreeBuilderBase::Proto;

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */


TreeBuilderBase::TreeBuilderBase(void) :
    _pNodePool      (NULL    ),
    _pRoot          (NULL    )
{
}

TreeBuilderBase::~TreeBuilderBase(void)
{
}


void TreeBuilderBase::reset(void)
{
    _pRoot = NULL;
    _uiMatrixId = 0;
}


void TreeBuilderBase::add(DrawEnv &denv, 
                          RenderPartition *part,
                          RenderTreeNode *pNode,
                          State          *pState,
                          StateOverride  *pStateOverride,
                          UInt32          uiKeyGen      )
{
    if(_pRoot == NULL)
    {
        _pRoot = _pNodePool->create();
    }
    
    _pRoot->addChild(pNode);
}


void TreeBuilderBase::draw(DrawEnv &denv, RenderPartition *part)
{
    _uiActiveMatrix = 0;
    
    drawNode(_pRoot, denv, part);
}

void TreeBuilderBase::drawNode(RenderTreeNode *pNode, DrawEnv &denv, RenderPartition *part)
{
    while (pNode != NULL)
    {
        UInt32 uiNextMatrix = pNode->getMatrixStore().first;

        if(uiNextMatrix != 0 && uiNextMatrix != _uiActiveMatrix)
        {
            glLoadMatrixf(pNode->getMatrixStore().second.getValues());

            _uiActiveMatrix = uiNextMatrix;

            _currMatrix.second = pNode->getMatrixStore().second;

            updateTopMatrix(denv);

            denv.setObjectToWorld(_accMatrix);

            ++part->_uiNumMatrixChanges;

            // Negative scaled matrices in conjunction with double sided 
            // lighting
            // gives wrong render results cause the lighting itselfs gets 
            // inverted. This corrects this behavior.

            if(part->_bCorrectTwoSidedLighting)
            {
                const Matrix &m = _currMatrix.second;

                // test for a "flipped" matrix
                // glFrontFace can give conflicts with the polygon chunk ...

                if(m[0].cross(m[1]).dot(m[2]) < 0.0)
                {
                    glFrontFace(GL_CW);
                }
                else
                {
                    glFrontFace(GL_CCW);
                }
            }
        }

        State         *pNewState         = pNode->getState();
        StateOverride *pNewStateOverride = pNode->getStateOverride();

        denv.activateState(pNewState, pNewStateOverride);

        if(pNode->hasFunctor() == true)
            pNode->getFunctor()(&denv);

        if(pNode->getFirstChild() != NULL)
        {
            drawNode(pNode->getFirstChild(), denv, part);
        }
        
        pNode = pNode->getBrother();
    }
}

void TreeBuilderBase::updateTopMatrix(DrawEnv &denv)
{
    _accMatrix = denv.getCameraToWorld();
    _accMatrix.mult(_currMatrix.second);
}

const Matrix &TreeBuilderBase::topMatrix(void)
{
    return _accMatrix;
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGTreeBuilderBase.cpp 142 2006-09-18 08:49:39Z vossg $";
    static Char8 cvsid_hpp[] = OSGTREEBUILDERBASE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGTREEBUILDERBASE_INLINE_CVSID;
}

#endif