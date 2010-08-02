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

#ifndef _OSGMANIPULATORMANAGER_H_
#define _OSGMANIPULATORMANAGER_H_

#include "OSGConfig.h"
#include "OSGBaseTypes.h"
#include "OSGNodeFields.h"

#include "OSGManipulator.h"
#include "OSGMoveManipulator.h"
#include "OSGRotateManipulator.h"
#include "OSGScaleManipulator.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBGUI_DLLMAPPING ManipulatorManager
{
 public:
    enum    ManipulatorType { ROTATE, SCALE, TRANSLATE };

    NodeTransitPtr createManipulator(const ManipulatorType  type);
    void           changeManipulator(const ManipulatorType  type);
    Manipulator*   getManipulator   (void                       ) const;
    
    void           setTarget        (      Node     * const value);
    Node*          getTarget        (void                        ) const;
    void           setViewport      (      Viewport * const value);
    bool           isActive         (      void                  );

    void           setLength         (const Vec3f& len);
    
    void           mouseMove         (const Int16  x,
                                      const Int16  y);
    void           mouseButtonPress  (const UInt16 button,
                                      const Int16  x,
                                      const Int16  y     );
    void           mouseButtonRelease(const UInt16 button,
                                      const Int16  x,
                                      const Int16  y     );

    void           setUniformScale    (bool value        );
    bool           getUniformScale    (void              ) const;

    bool startManip    (Node *n);
    void cancelManip   (void);
    void endManip      (void);
    bool isManipulating(void) const;
private:

    ManipulatorUnrecPtr  _maniC;
    ManipulatorType      _currentType;
    NodeUnrecPtr         _target;
    ViewportUnrecPtr     _viewport;
    bool                 _uniformScale;
};

OSG_END_NAMESPACE

#endif // _OSGMANIPULATORMANAGER_H_
