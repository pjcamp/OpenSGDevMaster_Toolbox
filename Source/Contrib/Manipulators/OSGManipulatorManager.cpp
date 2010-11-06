/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"
#include "OSGManipulatorManager.h"

OSG_BEGIN_NAMESPACE

// TODO: der ManipulatorManager merkt sich den Core, nicht den Node des
// Manipulators. Damit besteht ein Problem mit Multi-Parents, das nicht waere,
// wenn der ManipulatorManager sich den Node merken wuerde!?!

ManipulatorManager::ManipulatorManager()
    : _maniN      (),
      _currentType(),
      _target     (),
      _viewport   ()
{
}

ManipulatorManager::~ManipulatorManager()
{
    _maniN    = NULL;
    _target   = NULL;
    _viewport = NULL;
}

Node* ManipulatorManager::createManipulator(const ManipulatorType type)
{
    ManipulatorUnrecPtr mani;
  
    switch (type)
    {
        case ROTATE:
            mani = RotateManipulator::create();
            break;
        case SCALE:
            mani = ScaleManipulator::create();
            break;
        case TRANSLATE:
            mani = MoveManipulator::create();    
            break;
    }
    
    _currentType = type;

    _maniN = makeNodeFor(mani);
    commitChanges();

    return _maniN;
}

Manipulator* ManipulatorManager::getManipulator(void) const
{
    return _maniC;
}

Node* ManipulatorManager::getTarget(void) const
{
    return _target;
}

bool ManipulatorManager::getUniformScale(void) const
{
    return _uniformScale;
}

void ManipulatorManager::setUniformScale(bool value)
{
    _uniformScale = value;
}

ManipulatorManager::ManipulatorType ManipulatorManager::getManipulatorType(void) const
{
    return _currentType;
}

// TODO: 
void ManipulatorManager::changeManipulator(const ManipulatorType type)
{
    if(type != _currentType)
    {
        ManipulatorUnrecPtr mani;
  
        switch (type)
        {
            Node *maniN = dynamic_cast<Node *>(_maniC->getParents()[0]);
            Vec3f len(1.0f,1.0f,1.0f);
            if(_maniC != NULL)
            {
                len = _maniC->getLength();
            }

            _maniC = NULL;

            switch (type)
            {
                case TRANSLATE:
                    _maniC = MoveManipulator::create();
                    _maniC->setLength(len);
                    break;
                case ROTATE:
                    _maniC = RotateManipulator::create();
                    _maniC->setLength(len);
                    break;
                case SCALE:
                    _maniC = ScaleManipulator::create();
                    _maniC->setLength(len);
                    dynamic_pointer_cast<ScaleManipulator>(_maniC)->setUniform(_uniformScale);
                    break;
            }
            
            _currentType = type;

            maniN->setCore(_maniC);

            // Calling commitChanges() here seems to be critical for making
            // this method behave at all.
            commitChanges();

            _maniC->setTarget  (_target  );
            _maniC->setViewport(_viewport);

            commitChanges();
        }

        _currentType = type;

        _maniN->setCore(mani);

        commitChanges();

        mani->setTarget  (_target  );
        mani->setViewport(_viewport);
    }
}

ManipulatorManager::ManipulatorType
ManipulatorManager::getCurrentType() const
{
    return _currentType;
}

void ManipulatorManager::setTarget(Node * const value)
{
    Manipulator* mani = _maniN->getCore<Manipulator>();

    if(mani != NULL)
    {
        mani->setTarget(value);
        _target = value;
    }
    else
    {
        SWARNING << "ManipulatorManager::setTarget: No active manipulator."
                 << std::endl;
    }
}

void ManipulatorManager::setViewport(Viewport * const value)
{
    Manipulator* mani = _maniN->getCore<Manipulator>();

    if(mani != NULL)
    {
        mani->setViewport(value);
        _viewport = value;
    }
    else
    {
        SWARNING << "ManipulatorManager::setViewport: No active manipulator."
                 << std::endl;
    }
}

bool ManipulatorManager::isActive()
{
    bool         retVal = false;
    Manipulator* mani   = _maniN->getCore<Manipulator>();

    if(mani != NULL)
        retVal = mani->getActive();

    return retVal;
}

void ManipulatorManager::mouseMove(const Int16 x,
                                   const Int16 y)
{
    Manipulator* mani = _maniN->getCore<Manipulator>();

    mani->mouseMove(x, y);
}

void ManipulatorManager::mouseButtonPress(const UInt16 uiButton,
                                          const Int16 x,
                                          const Int16 y      )
{
    Manipulator* mani = _maniN->getCore<Manipulator>();

    mani->mouseButtonPress(uiButton, x, y);
}

void ManipulatorManager::mouseButtonRelease(const UInt16 uiButton,
                                            const Int16 x,
                                            const Int16 y      )
{
    Manipulator* mani = _maniN->getCore<Manipulator>();

    mani->mouseButtonRelease(uiButton, x, y);
}

bool ManipulatorManager::startManip(Node *n)
{
    Manipulator* mani = _maniN->getCore<Manipulator>();

    if(mani->hasSubHandle(n) )
    {
        _maniC->startManip(n);
        return true;
    }
    else
    {
        return false;
    }
}

void ManipulatorManager::cancelManip(void)
{
    _maniC->cancelManip();
}

void ManipulatorManager::endManip(void)
{
    _maniC->endManip();
}

bool ManipulatorManager::isManipulating(void) const
{
    return _maniC->isManipulating();
}

void ManipulatorManager::setLength(const Vec3f& len)
{
    _maniC->setLength(len);
}


OSG_END_NAMESPACE
