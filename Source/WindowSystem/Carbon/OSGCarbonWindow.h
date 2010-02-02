/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSGCARBONWINDOW_H_
#define _OSGCARBONWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#if defined(__APPLE__) || defined(OSG_DO_DOC)

#include "OSGCarbonWindowBase.h"
#include <AGL/agl.h>
#include "OSGThreadManager.h"

#include <map>

OSG_BEGIN_NAMESPACE

/*! \brief CarbonWindow class. See \ref
           PageWindowCarbon for a description.
    \ingroup GrpWindowCarbonObj
    \ingroup GrpLibOSGWindowCarbon
    \includebasedoc
 */

class OSG_WINDOWCARBON_DLLMAPPING CarbonWindow : public CarbonWindowBase
{
  protected:
    
    /*==========================  PUBLIC  =================================*/

  public:

    typedef CarbonWindowBase Inherited;
    typedef CarbonWindow     Self;

    typedef std::map<UInt32, CarbonWindowUnrecPtr> CarbonWindowToProducerMap;    
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Window functions                              */
    /*! \{                                                                 */
    
    virtual void init     (GLInitFunctor oFunc = GLInitFunctor());
    virtual void terminate(void                                 );

    /*! \}                                                                 */
	virtual void setShowCursor(bool show);
	virtual bool getShowCursor() const;
    virtual void setAttachMouseToCursor(bool attach);
    virtual bool getAttachMouseToCursor(void) const;
	virtual Vec2f getDesktopSize() const;

	virtual std::vector<BoostPath, std::allocator<BoostPath> > openFileDialog(const std::string&, const std::vector<WindowEventProducer::FileDialogFilter, std::allocator<WindowEventProducer::FileDialogFilter> >&, const BoostPath&, bool);
	virtual BoostPath saveFileDialog(const std::string&, const std::vector<WindowEventProducer::FileDialogFilter, std::allocator<WindowEventProducer::FileDialogFilter> >&, const std::string&, const BoostPath&, bool);
	virtual KeyEvent::KeyState getKeyState(KeyEvent::Key) const;
	
	//Store state of modifier keys
	UInt32 _modifierKeyState;
	
    virtual void openWindow(const Pnt2f& ScreenPosition,
                       const Vec2f& Size,
                       const std::string& WindowName);
    
    virtual void closeWindow(void);
    
    virtual void mainLoop(void);
	
	virtual WindowUnrecPtr initWindow(void);
	
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

    // Variables should all be in CarbonWindowBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CarbonWindow(void);
    CarbonWindow(const CarbonWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CarbonWindow(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      Window system implementation functions                  */
    /*! \{                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

           void onCreate       (const CarbonWindow *source = NULL);

           void onDestroy      (      UInt32  uiContainerId);

    /*! \}                                                                 */

    virtual void doActivate  (void);
    virtual void doDeactivate(void);
    virtual bool doSwap      (void);
    virtual bool hasContext  (void);

    /*! \}                                                                 */
	virtual void setCursor(void);
	OSStatus handleMouseEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData);
	OSStatus handleWindowEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData);
	OSStatus handleAppEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData);
	OSStatus handleKeyEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData);
    void disposeWindow(void);
	
	static KeyEvent::Key determineKey(::UInt32 key);
	static UInt32 determineKeyModifiers(::UInt32 keyModifiers);

    static CGKeyCode getKeyCode(KeyEvent::Key TheKey);

	static CarbonWindowToProducerMap _CarbonWindowToProducerMap;
	
	
    static pascal OSStatus eventHandler(EventHandlerCallRef nextHandler, EventRef event, void *userData);
    
	OSStatus internalEventHandler(EventHandlerCallRef nextHandler, EventRef event, void *userData);
	
	UInt32 _WindowId;
	EventHandlerUPP _EventHandlerUPP;
    WindowRef _WindowRef;
	AGLContext _Context;
	static UInt32 getUndefinedWindowId(void);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CarbonWindowBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CarbonWindow &source);

    bool _AttachMouseToCursor;
};

typedef CarbonWindow *CarbonWindowP;

OSG_END_NAMESPACE

#include "OSGCarbonWindowBase.inl"
#include "OSGCarbonWindow.inl"

#endif /* __APPLE__ */

#endif /* _OSGCARBONWINDOW_H_ */
