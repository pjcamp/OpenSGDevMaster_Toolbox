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

#ifndef _OSGSCALEMANIPULATOR_H_
#define _OSGSCALEMANIPULATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGScaleManipulatorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ScaleManipulator class. See \ref
           PageManipulatorsScaleManipulator for a description.
*/

class OSG_CONTRIBGUI_DLLMAPPING ScaleManipulator : public ScaleManipulatorBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

    virtual void mouseMove(Int16        x,
                           Int16        y);

    virtual void mouseButtonPress(UInt16        button,
                                   Int16        x,
                                   Int16        y     );

    virtual void mouseButtonRelease(UInt16      button,
                                     Int16      x,
                                     Int16      y     );
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ScaleManipulatorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ScaleManipulator(void);
    ScaleManipulator(const ScaleManipulator &source);
    void onCreate(const ScaleManipulator* source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ScaleManipulator(void);
    void    onDestroy();

    /*! \}                                                                 */
    virtual void addHandleGeo(Node *n);
    virtual void subHandleGeo(Node *n);

    virtual NodeTransitPtr makeHandleGeo(Real32 radius, UInt16 axis);
    virtual void updateLength(void);
    virtual UInt32 getAxisCollisionTravMask(UInt16 Axis) const;
    virtual Material* getAxisMaterial(UInt16 Axis) const;
    virtual MFUnrecGeometryPtr* editAxisGeometries(UInt16 Axis);


    Pnt3f _TargetInitialOrigin;
    Pnt3f _StartManipInitialPosition;
    Vec3f _InitialScale;

    
    bool  _StartUniformManip;
    Vec2f _InitialMouseDirection;
    /*==========================  PRIVATE  ================================*/
  private:

    typedef ScaleManipulatorBase Inherited;

    friend class FieldContainer;
    friend class ScaleManipulatorBase;

    static void initMethod(InitPhase ePhase);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ScaleManipulator &source);
};

typedef ScaleManipulator *ScaleManipulatorP;

OSG_END_NAMESPACE

#include "OSGScaleManipulatorBase.inl"
#include "OSGScaleManipulator.inl"

#endif /* _OSGSCALEMANIPULATOR_H_ */
