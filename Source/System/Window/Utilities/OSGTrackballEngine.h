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

#ifndef _OSG_TRACKBALLENGINE_H_
#define _OSG_TRACKBALLENGINE_H_

#include "OSGNavigatorEngine.h"

OSG_BEGIN_NAMESPACE

class Navigator;

/*! \brief TrackballEngine provides the trackball navigator functionality.
    \ingroup GrpUtilNavigation
    \ingroup GrpLibOSGUtil
 */

class OSG_UTIL_DLLMAPPING TrackballEngine : public NavigatorEngine
{
    typedef NavigatorEngine Inherited;
    typedef TrackballEngine Self;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    OSG_GEN_INTERNAL_MEMOBJPTR(TrackballEngine);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Construction                              */
    /*! \{                                                                 */

    static ObjTransitPtr create(Real32 rSize = 0.8f);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    const char *getClassname(void) { return "TrackballEngine"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Get                                   */
    /*! \{                                                                 */

    virtual const Pnt3f  &getFrom(void);
    virtual const Pnt3f  &getAt(void);
    virtual const Vec3f  &getUp(void);
    virtual const Matrix &getMatrix(void);
    virtual Real32 getDistance(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Set                                   */
    /*! \{                                                                 */

    virtual void setFrom(Pnt3f new_from);
    virtual void setAt(Pnt3f new_at);
    virtual void setUp(Vec3f new_up);
    virtual void set(Pnt3f new_from, Pnt3f new_at, Vec3f new_up);
    virtual void set(const Matrix & new_matrix);
    virtual void setDistance(Real32 new_distance);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             navigator engine callbacks                       */
    /*! \{                                                                 */

    virtual void buttonPress(Int16 button,   Int16 x, Int16 y, Navigator* nav);
    virtual void buttonRelease(Int16 button, Int16 x, Int16 y, Navigator* nav);
    virtual void keyPress(Int16 key,         Int16 x, Int16 y, Navigator* nav);
    virtual void moveTo(                     Int16 x, Int16 y, Navigator* nav);
    virtual void idle(Int16 buttons,         Int16 x, Int16 y, Navigator* nav);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Trackball Transformations                       */
    /*! \{                                                                 */

    void rotate     (Real32 fromX, Real32 fromY, Real32 toX, Real32 toY);
    void translateXY(Real32 distanceX, Real32 distanceY);
    void translateZ (Real32 distance);


    /*! \}                                                                 */
    /*==========================  PROTECTED  ==============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name            Constructors/Destructor                           */
    /*! \{                                                                 */

             TrackballEngine(Real32 rSize = 0.8f);
    virtual ~TrackballEngine(void               );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Members                                  */
    /*! \{                                                                 */

    Real32 _rRadius;
    Real32 _rDistance;
    Matrix _tMatrix;
    Matrix _finalMatrix;
    Pnt3f  _pFrom;
    Pnt3f  _pAt;
    Vec3f  _vUp;

    /* temporary values */
    Pnt3f  _ip;
    Vec3f  _dir;

    /*! \}                                                                 */

    void updateFinalMatrix();

    Real32 projectToSphere(Real32 rRadius, Real32 rX, Real32 rY);
    void getIntersectionPoint(Int16 x, Int16 y, Navigator* nav);
    void calcDeltas(Int16 , Int16 , Int16 toX, Int16 toY,
                    Real32 &distanceX, Real32 &distanceY, Navigator* nav);


  private:

    /* Not implemented */
    TrackballEngine(const TrackballEngine &other);
    TrackballEngine &operator =(const TrackballEngine &other);
};

OSG_GEN_MEMOBJPTR(TrackballEngine);

OSG_END_NAMESPACE

#endif
