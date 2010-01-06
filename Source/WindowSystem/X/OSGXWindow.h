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

#ifndef _OSGXWINDOW_H_
#define _OSGXWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGXWindowBase.h"
#include "OSGThreadManager.h"

OSG_BEGIN_NAMESPACE

/*! \brief X Window class. See \ref PageWindowX for a description. 
    \ingroup GrpWindowXObj
    \ingroup GrpLibOSGWindowX
    \includebasedoc
 */

class OSG_WINDOWX_DLLMAPPING XWindow : public XWindowBase
{
  public:

    typedef XWindowBase                           Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      Window system implementation functions                  */
    /*! \{                                                                 */

    virtual void init     (GLInitFunctor oFunc = GLInitFunctor());
    virtual void terminate(void               );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Redefined                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
	virtual WindowPtr initWindow(void);

    virtual bool attachWindow(void);

    virtual void openWindow(const Pnt2f& ScreenPosition,
                       const Vec2f& Size,
                       const std::string& WindowName);
    
    virtual void closeWindow(void);
	
    virtual void mainLoop(void);

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

    virtual void setShowCursor(bool showCursor);

    virtual bool getShowCursor(void) const;
	
    virtual void setAttachMouseToCursor(bool attach);
    
    virtual bool getAttachMouseToCursor(void) const;

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
    
	 virtual UInt32 getKeyModifiers(void) const;
     
	virtual KeyEvent::KeyState getKeyState(KeyEvent::Key TheKey) const;
    
	 virtual Pnt2f getMousePosition(void) const;
    
	 virtual std::string getClipboard(void) const;

	 virtual void putClipboard(const std::string Value);
    
    void handleEvent(XEvent& Event);
    
    
    virtual void draw(void);
    virtual void update(void);
    
    virtual Vec2f getDesktopSize(void) const;

	virtual std::vector<Path> openFileDialog(const std::string& WindowTitle,
		const std::vector<FileDialogFilter>& Filters,
		const Path& InitialDir,
		bool AllowMultiSelect);

    virtual Path saveFileDialog(const std::string& DialogTitle,
                    const std::vector<FileDialogFilter>& Filters,
                    const std::string& InitialFile,
                    const Path& InitialDirectory,
                    bool PromptForOverwrite
                    );
    /*=========================  PROTECTED  ===============================*/

  protected:

    static int wait_for_map_notify(Display *, XEvent *event, char *arg);
    static KeyEvent::Key determineKey(const KeySym& XKeySym);
    
    static UInt32 determineKeyModifiers(const unsigned int state);

    // Variables should all be in XWindowBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    XWindow(void);
    XWindow(const XWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~XWindow(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    virtual void onDestroy(UInt32 uiContainerId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void classicInit(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

           void onCreate       (const XWindow *source = NULL);

           void onDestroy      (      UInt32  uiContainerId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      Window system implementation functions                  */
    /*! \{                                                                 */

    virtual void doActivate  (void);
    virtual void doDeactivate(void);
    virtual bool doSwap      (void);

    virtual bool hasContext  (void);

    /*! \}                                                                 */
	virtual void setCursor(void);
    
    unsigned int _LastKeyboardMouseButtonMask;
    Pnt2f _LastMousePosition;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class XWindowBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const XWindow &source);
};

OSG_END_NAMESPACE

#include "OSGXWindow.inl"
#include "OSGXWindowBase.inl"

#endif /* _OSGXWINDOW_H_ */
