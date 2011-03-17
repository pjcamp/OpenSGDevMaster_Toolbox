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

#ifndef _OSGPASSIVEWINDOW_H_
#define _OSGPASSIVEWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGPassiveWindowBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PassiveWindow class. See \ref 
           PageSystemPassiveWindow for a description.
    \ingroup GrpWindowPassiveObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
 */

class OSG_WINDOW_DLLMAPPING PassiveWindow : public PassiveWindowBase
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
    /*---------------------------------------------------------------------*/
    /*! \name                      Redefined                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Redefined                               */
    /*! \{                                                                 */

    virtual void init     (GLInitFunctor oFunc = GLInitFunctor());
    virtual void terminate(void                                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Redefined                               */
    /*! \{                                                                 */

    /*! \}                                                                 */  
	virtual void setShowCursor(bool show);
	virtual bool getShowCursor() const;
    virtual void setAttachMouseToCursor(bool attach);
    virtual bool getAttachMouseToCursor(void) const;
	virtual Vec2f getDesktopSize() const;

	virtual std::vector<BoostPath, std::allocator<BoostPath> >
        openFileDialog(const std::string&,
                       const std::vector<WindowEventProducer::FileDialogFilter,
                       std::allocator<WindowEventProducer::FileDialogFilter> >&,
                       const BoostPath&, bool);
	virtual BoostPath
        saveFileDialog(const std::string&,
                       const std::vector<WindowEventProducer::FileDialogFilter,
                       std::allocator<WindowEventProducer::FileDialogFilter> >&,
                       const std::string&, const BoostPath&, bool);

	virtual KeyEventDetails::KeyState getKeyState(KeyEventDetails::Key) const;
	
    virtual void openWindow(const Pnt2f& ScreenPosition,
                            const Vec2f& Size,
                            const std::string& WindowName);
    
    virtual void closeWindow(void);
    
    virtual void mainLoop(void);
	
	virtual Window* initWindow(void);
	
    //Set the Window Position
    virtual void setPosition(Pnt2f Pos);

    //Set the Window Position
    virtual Pnt2f getPosition(void) const;

    //Set the Window size
    virtual void setSize(Vec2us Size);

    //Get the Window size
    virtual Vec2f getSize(void) const;

    //Focused
    //Set the Window Focus
    virtual void setFocused(bool Focused);

    //Get the Window Focus
    virtual bool getFocused(void) const;

    //Visible / Iconify / Normal
    //Set the Window Visible
    virtual void setVisible(bool Visible);

    //Get the Window Visible
    virtual bool getVisible(void) const;

    //Set the Window Iconify
    virtual void setIconify(bool Iconify);

    //Get the Window Iconify
    virtual bool getIconify(void) const;

    //Fullscreen
    virtual void setFullscreen(bool Fullscreen);

    //Get the Window Fullscreen
    virtual bool getFullscreen(void) const;

    //Set the text on the Title bar of the window
    virtual void setTitle(const std::string& TitleText);

    //Get the text of the Title bar of the window
    virtual std::string getTitle(void);

    //Set the window to allow or not allow Resizing
    virtual void setRisizable(bool IsResizable);

    //Get whether or not the window allows resizing
    virtual bool getRisizable(void);

    //Set the window to draw or not draw it's border
    virtual void setDrawBorder(bool DrawBorder);

    //Get wether or not the window is drawing a border
    virtual bool getDrawBorder(void);
	
    virtual void draw(void);

    virtual void update(void);

    virtual bool attachWindow(void);

	virtual UInt32 getKeyModifiers(void) const;
    
	virtual Pnt2f getMousePosition(void) const;
	
	virtual std::string getClipboard(void) const;

	virtual void putClipboard(const std::string Value);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PassiveWindowBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PassiveWindow(void);
    PassiveWindow(const PassiveWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PassiveWindow(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      Window system implementation functions                  */
    /*! \{                                                                 */

   /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef PassiveWindowBase Inherited;
    
    friend class FieldContainer;
    friend class PassiveWindowBase;
    friend class PassiveViewport;

    static void initMethod(InitPhase ePhase);
    
    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PassiveWindow &source);
};

typedef PassiveWindow *PassiveWindowP;

OSG_END_NAMESPACE

#include "OSGPassiveWindowBase.inl"
#include "OSGPassiveWindow.inl"

#endif /* _OSGPASSIVEWINDOW_H_ */
