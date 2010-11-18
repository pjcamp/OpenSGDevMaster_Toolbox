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

#ifndef _OSGMANIPULATOR_H_
#define _OSGMANIPULATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGManipulatorBase.h"
#include "OSGExternalUpdateHandler.h"

#include "OSGComponentTransform.h"

OSG_BEGIN_NAMESPACE

/*! \brief Manipulator class. See \ref
           PageManipulatorsManipulator for a description.
*/

class OSG_CONTRIBGUI_DLLMAPPING Manipulator : public ManipulatorBase
{
    /*==========================  PUBLIC  =================================*/
  public:
    enum ManipHandle
    {
        X_AXIS_HANDLE   = 0,
        Y_AXIS_HANDLE   = 1,
        Z_AXIS_HANDLE   = 2,
        ALL_AXES_HANDLE = 3,
        XY_AXES_HANDLE  = 4,
        XZ_AXES_HANDLE  = 5,
        YZ_AXES_HANDLE  = 6,
        NO_AXES_HANDLE  = 7
    };

    enum ManipCollideTravmask
    {
        NONE_TRAV_MASK   = 0,
        NONCOLLIDE_RENDERED_TRAV_MASK   = 1,
        X_AXIS_TRAV_MASK   = 2,
        Y_AXIS_TRAV_MASK   = 4,
        Z_AXIS_TRAV_MASK   = 8,
        XY_AXES_TRAV_MASK  = 6,
        XZ_AXES_TRAV_MASK  = 10,
        YZ_AXES_TRAV_MASK  = 12,
        ALL_AXIS_TRAV_MASK   = 14
    };

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

    virtual void mouseMove(Int16        x,
                           Int16        y);

    virtual void mouseButtonPress(UInt16        button,
                                   Int16        x,
                                   Int16        y     );

    virtual void mouseButtonRelease(UInt16      button,
                                     Int16      x,
                                     Int16      y     );

    void setExternalUpdateHandler(ExternalUpdateHandler* h);

    void callExternalUpdateHandler();

    virtual void startManip    (Node *subHandle);
    virtual void cancelManip   (void);
    virtual void endManip      (void);
            bool isManipulating(void) const;
    const Matrix& getInitialXForm(void) const;

    virtual void rolloverHandle(Node *subHandle);
    virtual void exitHandle(void);
            bool isRolledOver(void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef ManipulatorBase Inherited;

    // Variables should all be in ManipulatorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Manipulator(void);
    Manipulator(const Manipulator &source);

    void onCreate(const Manipulator* source = NULL);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Manipulator(void);

    void    onDestroy();

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Init                                  */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    virtual NodeTransitPtr makeHandleGeo(Real32 radius, UInt16 Axis) = 0;
    virtual void           addHandleGeo(Node * n);
    virtual void           subHandleGeo(Node * n);
    void                   reverseTransform();
    virtual void           updateLength(void);
    virtual void           updateWidth (void);
    void                   updateParent(void);

    Pnt2f calcScreenProjection(const Pnt3f    &,
                                     Viewport * const port);

    void getTransformation(Vec3f        &translation,
                           Quaternion   &rotation,
                           Vec3f        &scaleFactor,
                           Quaternion   &scaleOrientation) const;

    void getTransformation(Matrix        &mat) const;

    void setTransformation(const Vec3f        &translation,
                           const Quaternion   &rotation,
                           const Vec3f        &scaleFactor,
                           const Quaternion   &scaleOrientation);

    void setTransformation(const Matrix   &mat);

    UInt16 getNodeHandle(Node* const HandleNode) const;

    virtual NodeTransitPtr createXAxisManipulator(void);
    virtual NodeTransitPtr createYAxisManipulator(void);
    virtual NodeTransitPtr createZAxisManipulator(void);
    virtual NodeTransitPtr createAxisManipulator(UInt16 Axis);

    NodeUnrecPtr            _activeParent;
    NodeUnrecPtr            _root;
    ExternalUpdateHandler*  _externalUpdateHandler;
    Matrix                  _initialXForm;

    virtual UInt32 getAxisCollisionTravMask(UInt16 Axis) const;
    virtual Material* getAxisMaterial(UInt16 Axis) const;
    virtual MFUnrecGeometryPtr* editAxisGeometries(UInt16 Axis);
    virtual void createMaterials(void);
    
    void applyStateMaterial(UInt16 Axis);
    virtual Material* getCurStateAxisMaterial(UInt16 Axis) const;

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ManipulatorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Manipulator &source);
};

typedef Manipulator *ManipulatorP;

OSG_END_NAMESPACE

#include "OSGManipulatorBase.inl"
#include "OSGManipulator.inl"

#endif /* _OSGMANIPULATOR_H_ */
