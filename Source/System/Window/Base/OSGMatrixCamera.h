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


#ifndef _OSGMATRIXCAMERA_H_
#define _OSGMATRIXCAMERA_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGMatrixCameraBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief Matrix Camera class. See \ref PageSystemWindowCameraMatrix for 
    a description.

  \ingroup GrpSystemWindowCamera
  \ingroup GrpLibOSGSystem
  \includebasedoc
*/

class OSG_SYSTEM_DLLMAPPING MatrixCamera : public MatrixCameraBase
{

    /*==========================  PUBLIC  =================================*/

  public:
    
    typedef MatrixCameraBase                          Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                    transformation                            */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */



    virtual void getProjection(      Matrix     &result, 
                                     UInt32      width, 
                                     UInt32      height);

    virtual void getViewing   (      Matrix     &result, 
                                     UInt32      width, 
                                     UInt32      height); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    dump                                      */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
 
    /*---------------------------------------------------------------------*/
    /*! \name                    Constructors                              */
    /*! \{                                                                 */

    MatrixCamera(void);
    MatrixCamera(const MatrixCamera &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructors                               */
    /*! \{                                                                 */

    virtual ~MatrixCamera(void); 
     
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/  
   
  private:

    friend class FieldContainer;
    friend class MatrixCameraBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MatrixCamera &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef MatrixCamera *MatrixCameraP;

OSG_END_NAMESPACE

#include "OSGMatrixCameraBase.inl"
#include "OSGMatrixCamera.inl"

#endif /* _OSGMATRIXCAMERA_H_ */
