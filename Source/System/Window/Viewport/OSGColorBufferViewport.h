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

#ifndef _OSGCOLORBUFFERVIEWPORT_H_
#define _OSGCOLORBUFFERVIEWPORT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGColorBufferViewportBase.h"

OSG_BEGIN_NAMESPACE

class RenderActionBase;

/*! \brief Viewport class for color channel selection. See \ref 
           PageSystemWindowViewports for a description.
    \ingroup GrpWindowViewportObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
 */

class OSG_WINDOW_DLLMAPPING ColorBufferViewport : 
    public ColorBufferViewportBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ColorBufferViewportBase                           Inherited;

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
    /*---------------------------------------------------------------------*/
    /*! \name                    your_category                             */
    /*! \{                                                                 */

#if 0 // Have to check GV
    virtual void activate    (void                             );
    virtual void deactivate  (void                             );
#endif

#ifdef OSG_OLD_RENDER_ACTION
    virtual void render(DrawActionBase   *action);
#endif

    virtual void render(RenderActionBase *action);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ColorBufferViewportBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ColorBufferViewport(void);
    ColorBufferViewport(const ColorBufferViewport &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ColorBufferViewport(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ColorBufferViewportBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ColorBufferViewport &source);
};

typedef ColorBufferViewport *ColorBufferViewportP;

OSG_END_NAMESPACE

#include "OSGColorBufferViewportBase.inl"
#include "OSGColorBufferViewport.inl"

#endif /* _OSGCOLORBUFFERVIEWPORT_H_ */
