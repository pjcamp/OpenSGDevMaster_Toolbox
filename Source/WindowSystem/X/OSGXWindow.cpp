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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#define OSG_COMPILEWINDOWXINST

#include "OSGGLU.h"
#include "OSGGLEXT.h"

#include "OSGXWindow.h"

#include "OSGGLFuncProtos.h"

#include "GL/glx.h"

#include <X11/cursorfont.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGXWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGXWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

int XWindow::wait_for_map_notify(Display *, XEvent *event, char *arg)
{
    return( event->type == MapNotify && event->xmap.window == (::Window)arg );
}

void XWindow::mainLoop(void)
{

    XEvent event;
    while (event.type != DestroyNotify ) 
    //while (_WIN32HWNDToProducerMap.size() != 0) 
    {
        while ( XPending(this->getDisplay()) )
        {
            XNextEvent(this->getDisplay(), &event);
            handleEvent(event);
        }  
        
        update();
        draw();
    }
    
}

UInt32 XWindow::determineKeyModifiers(const unsigned int state)
{
   UInt32 Modifiers = 0;

   if(state & ShiftMask)
   {
      Modifiers |= KeyEventDetails::KEY_MODIFIER_SHIFT;
   }
   if(state & ControlMask)
   {
      Modifiers |= KeyEventDetails::KEY_MODIFIER_CONTROL;
   }
   if(state & Mod1Mask)
   {
      Modifiers |= KeyEventDetails::KEY_MODIFIER_ALT;
   }
   if(state & LockMask)
   {
      Modifiers |= KeyEventDetails::KEY_MODIFIER_CAPS_LOCK;
   }
   if(state & Mod2Mask)
   {
      Modifiers |= KeyEventDetails::KEY_MODIFIER_NUM_LOCK;
   }
   //if(state & )
   //{
   //   Modifiers |= KeyEventDetails::KEY_MODIFIER_SCROLL_LOCK;
   //}
   return Modifiers;
}

KeyEventDetails::Key XWindow::determineKey(const KeySym& XKeySym)
{
    switch(XKeySym)
    {
        //Alphabet
        case XK_a:
            return KeyEventDetails::KEY_A;
        case XK_b:
            return KeyEventDetails::KEY_B;
        case XK_c:
            return KeyEventDetails::KEY_C;
        case XK_d:
            return KeyEventDetails::KEY_D;
        case XK_e:
            return KeyEventDetails::KEY_E;
        case XK_f:
            return KeyEventDetails::KEY_F;
        case XK_g:
            return KeyEventDetails::KEY_G;
        case XK_h:
            return KeyEventDetails::KEY_H;
        case XK_i:
            return KeyEventDetails::KEY_I;
        case XK_j:
            return KeyEventDetails::KEY_J;
        case XK_k:
            return KeyEventDetails::KEY_K;
        case XK_l:
            return KeyEventDetails::KEY_L;
        case XK_m:
            return KeyEventDetails::KEY_M;
        case XK_n:
            return KeyEventDetails::KEY_N;
        case XK_o:
            return KeyEventDetails::KEY_O;
        case XK_p:
            return KeyEventDetails::KEY_P;
        case XK_q:
            return KeyEventDetails::KEY_Q;
        case XK_r:
            return KeyEventDetails::KEY_R;
        case XK_s:
            return KeyEventDetails::KEY_S;
        case XK_t:
            return KeyEventDetails::KEY_T;
        case XK_u:
            return KeyEventDetails::KEY_U;
        case XK_v:
            return KeyEventDetails::KEY_V;
        case XK_w:
            return KeyEventDetails::KEY_W;
        case XK_x:
            return KeyEventDetails::KEY_X;
        case XK_y:
            return KeyEventDetails::KEY_Y;
        case XK_z:
            return KeyEventDetails::KEY_Z;
        //Numbers
        case XK_0:
            return KeyEventDetails::KEY_0;
        case XK_1:
            return KeyEventDetails::KEY_1;
        case XK_2:
            return KeyEventDetails::KEY_2;
        case XK_3:
            return KeyEventDetails::KEY_3;
        case XK_4:
            return KeyEventDetails::KEY_4;
        case XK_5:
            return KeyEventDetails::KEY_5;
        case XK_6:
            return KeyEventDetails::KEY_6;
        case XK_7:
            return KeyEventDetails::KEY_7;
        case XK_8:
            return KeyEventDetails::KEY_8;
        case XK_9:
            return KeyEventDetails::KEY_9;

        //Other
        case XK_minus:
            return KeyEventDetails::KEY_MINUS;
        case XK_equal:
            return KeyEventDetails::KEY_EQUALS;
        case XK_grave:
            return KeyEventDetails::KEY_BACK_QUOTE;
        case XK_Tab:
            return KeyEventDetails::KEY_TAB;
        case XK_space:
            return KeyEventDetails::KEY_SPACE;
        case XK_bracketleft:
            return KeyEventDetails::KEY_OPEN_BRACKET;
        case XK_bracketright:
            return KeyEventDetails::KEY_CLOSE_BRACKET;
        case XK_semicolon:
            return KeyEventDetails::KEY_SEMICOLON;
        case XK_comma:
            return KeyEventDetails::KEY_COMMA;
        case XK_period:
            return KeyEventDetails::KEY_PERIOD;
        case XK_backslash:
            return KeyEventDetails::KEY_BACK_SLASH;
        case XK_apostrophe:
            return KeyEventDetails::KEY_APOSTROPHE;
        case XK_slash:
            return KeyEventDetails::KEY_SLASH;

        //Non-visible
        case XK_Escape:
            return KeyEventDetails::KEY_ESCAPE;
        case XK_Shift_L:
        case XK_Shift_R:
            return KeyEventDetails::KEY_SHIFT;
        case XK_Control_L:
        case XK_Control_R:
            return KeyEventDetails::KEY_CONTROL;
        case XK_Super_L:
        case XK_Super_R:
            return KeyEventDetails::KEY_META;
        case XK_Alt_L:
        case XK_Alt_R:
            return KeyEventDetails::KEY_ALT;
        case XK_Return:
            return KeyEventDetails::KEY_ENTER;
        case XK_Cancel:
            return KeyEventDetails::KEY_CANCEL;
        case XK_Clear:
            return KeyEventDetails::KEY_CLEAR;
        case XK_Pause:
            return KeyEventDetails::KEY_PAUSE;
        case XK_Caps_Lock:
            return KeyEventDetails::KEY_CAPS_LOCK;
        case XK_End:
            return KeyEventDetails::KEY_END;
        case XK_Menu:
            return KeyEventDetails::KEY_MENU;
        case XK_Home:
            return KeyEventDetails::KEY_HOME;
        case XK_Up:
            return KeyEventDetails::KEY_UP;
        case XK_Down:
            return KeyEventDetails::KEY_DOWN;
        case XK_Left:
            return KeyEventDetails::KEY_LEFT;
        case XK_Right:
            return KeyEventDetails::KEY_RIGHT;
        case XK_Print:
            return KeyEventDetails::KEY_PRINTSCREEN;
        case XK_Insert:
            return KeyEventDetails::KEY_INSERT;
        case XK_Delete:
            return KeyEventDetails::KEY_DELETE;
        case XK_Help:
            return KeyEventDetails::KEY_HELP;
        case XK_Num_Lock:
            return KeyEventDetails::KEY_NUM_LOCK;
        case XK_Scroll_Lock:
            return KeyEventDetails::KEY_SCROLL_LOCK;
        case XK_BackSpace:
            return KeyEventDetails::KEY_BACK_SPACE;
        case XK_Page_Up:
            return KeyEventDetails::KEY_PAGE_UP;
        case XK_Page_Down:
            return KeyEventDetails::KEY_PAGE_DOWN;

        //Function Keys
        case XK_F1:
            return KeyEventDetails::KEY_F1;
        case XK_F2:
            return KeyEventDetails::KEY_F2;
        case XK_F3:
            return KeyEventDetails::KEY_F3;
        case XK_F4:
            return KeyEventDetails::KEY_F4;
        case XK_F5:
            return KeyEventDetails::KEY_F5;
        case XK_F6:
            return KeyEventDetails::KEY_F6;
        case XK_F7:
            return KeyEventDetails::KEY_F7;
        case XK_F8:
            return KeyEventDetails::KEY_F8;
        case XK_F9:
            return KeyEventDetails::KEY_F9;
        case XK_F10:
            return KeyEventDetails::KEY_F10;
        case XK_F11:
            return KeyEventDetails::KEY_F11;
        case XK_F12:
            return KeyEventDetails::KEY_F12;
        case XK_F13:
            return KeyEventDetails::KEY_F13;
        case XK_F14:
            return KeyEventDetails::KEY_F14;
        case XK_F15:
            return KeyEventDetails::KEY_F15;
        case XK_F16:
            return KeyEventDetails::KEY_F16;
        case XK_F17:
            return KeyEventDetails::KEY_F17;
        case XK_F18:
            return KeyEventDetails::KEY_F18;
        case XK_F19:
            return KeyEventDetails::KEY_F19;
        case XK_F20:
            return KeyEventDetails::KEY_F20;
        case XK_F21:
            return KeyEventDetails::KEY_F21;
        case XK_F22:
            return KeyEventDetails::KEY_F22;
        case XK_F23:
            return KeyEventDetails::KEY_F23;
        case XK_F24:
            return KeyEventDetails::KEY_F24;

        //Numpad 
        case XK_KP_Enter:
            return KeyEventDetails::KEY_ENTER;
        case XK_KP_Add:
            return KeyEventDetails::KEY_ADD;
        case XK_KP_Subtract:
            return KeyEventDetails::KEY_MINUS;
        case XK_KP_Multiply:
            return KeyEventDetails::KEY_MULTIPLY;
        case XK_KP_Divide:
            return KeyEventDetails::KEY_DIVIDE;
        case XK_KP_Delete:
            return KeyEventDetails::KEY_DECIMAL;
        case XK_KP_Insert:
            return KeyEventDetails::KEY_NUMPAD_0;
        case XK_KP_End:
            return KeyEventDetails::KEY_NUMPAD_1;
        case XK_KP_Down:
            return KeyEventDetails::KEY_NUMPAD_2;
        case XK_KP_Next:
            return KeyEventDetails::KEY_NUMPAD_3;
        case XK_KP_Left:
            return KeyEventDetails::KEY_NUMPAD_4;
        case XK_KP_Begin:
            return KeyEventDetails::KEY_NUMPAD_5;
        case XK_KP_Right:
            return KeyEventDetails::KEY_NUMPAD_6;
        case XK_KP_Home:
            return KeyEventDetails::KEY_NUMPAD_7;
        case XK_KP_Up:
            return KeyEventDetails::KEY_NUMPAD_8;
        case XK_KP_Prior:
            return KeyEventDetails::KEY_NUMPAD_9;

        default:
            return KeyEventDetails::KEY_UNKNOWN;
    }
    return KeyEventDetails::KEY_UNKNOWN;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

::OSG::Window* XWindow::initWindow(void)
{
    Inherited::initWindow();

    DisplayP      dpy;
    X11Window     hwin;

    XVisualInfo   *vi;
    Colormap      cmap;
    XSetWindowAttributes swa;

    int dummy;

    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) 
    {
        SFATAL << "Error: Could not open display!" << std::endl;
    }

    if( ! glXQueryExtension( dpy, &dummy, &dummy ) )
    {
        SFATAL << "Error: X server has no OpenGL GLX extension" << std::endl;
    }

    //int VisualAttributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 32, GLX_DOUBLEBUFFER, None};
    int VisualAttributes[] = {GLX_RGBA, 
                              GLX_DEPTH_SIZE, 16,
                              GLX_DOUBLEBUFFER,
                              GLX_STENCIL_SIZE, 8,
                              None};
    
    vi = glXChooseVisual( dpy, DefaultScreen(dpy), VisualAttributes );
    if ( vi == NULL ) 
    {
        FFATAL(("Could not set Visual Attributes"));
    }
    if (vi->c_class != TrueColor)
    {
        FFATAL(("TrueColor visual required for this program"));
    }

    cmap = XCreateColormap( dpy, 
                            RootWindow(dpy, vi->screen), 
                            vi->visual, 
                            AllocNone );
    swa.colormap = cmap;
    swa.border_pixel = 0;
    swa.event_mask = ExposureMask | 
                     ButtonPressMask | 
                     ButtonReleaseMask |
                     KeyPressMask |
                     KeyReleaseMask |
                     PointerMotionMask |
                     StructureNotifyMask |
                     EnterWindowMask |
                     LeaveWindowMask |
                     FocusChangeMask |
                     SubstructureNotifyMask;

    // Create Window

    // Create a Window and connect it to the main display dpy
    hwin = XCreateWindow( dpy, 
                          RootWindow(dpy, vi->screen), 
                          0, 
                          0, 
                          10, 
                          10,
                          0, 
                          vi->depth,
                          InputOutput, 
                          vi->visual, 
                          CWBorderPixel | CWColormap | CWEventMask, 
                          &swa );
                          
    XFree(vi);

   setDisplay ( dpy );
   setWindow ( hwin );
    
    return this;
}

void XWindow::setPosition(Pnt2f Pos)
{
    XMoveWindow(this->getDisplay(),this->getWindow(),Pos.x(), Pos.y());
}

Pnt2f XWindow::getPosition(void) const
{
    ::Window *RootWindow;
    int x,y;
    unsigned int Width,Height,Depth,BorderWidth;
    
    XGetGeometry(this->getDisplay(),this->getWindow(),RootWindow,
            &x,&y,
            &Width,&Height,
            &BorderWidth,
            &Depth);
    
   return Pnt2f(x,y);
}

void XWindow::setSize(Vec2us Size)
{
    XResizeWindow(this->getDisplay(),this->getWindow(),Size.x(), Size.y());
}

Vec2f XWindow::getSize(void) const
{
    ::Window *RootWindow;
    int x,y;
    unsigned int Width,Height,Depth,BorderWidth;
    
    XGetGeometry(this->getDisplay(),this->getWindow(),RootWindow,
            &x,&y,
            &Width,&Height,
            &BorderWidth,
            &Depth);
    
   return Vec2f(Width,Height);
}

void XWindow::setFocused(bool Focused)
{
   if(Focused)
   {
       XSetInputFocus(this->getDisplay(),this->getWindow(),RevertToParent, getSystemTime());
   }
   else
   {
       XSetInputFocus(this->getDisplay(),None,RevertToParent, getSystemTime());
   }
}

bool XWindow::getFocused(void) const
{
    ::Window *FocusWindow;
    int revert_to;
    XGetInputFocus(this->getDisplay(), FocusWindow, &revert_to);
    
   return FocusWindow == &this->getWindow();
}

void XWindow::setVisible(bool Visible)
{
   //TODO:Implement
}

bool XWindow::getVisible(void) const
{
   //TODO:Implement
   return true;
}

void XWindow::setIconify(bool Iconify)
{
    if(Iconify)
    {
        XIconifyWindow(this->getDisplay(),this->getWindow(),0);
    }
    else
    {
        XMapWindow(this->getDisplay(), this->getWindow());
    }
}

bool XWindow::getIconify(void) const
{
   //TODO:Implement
   return false;
}

void XWindow::setFullscreen(bool Fullscreen)
{
   //TODO:Implement
}

bool XWindow::getFullscreen(void) const
{
   //TODO:Implement
   return false;
}

UInt32 XWindow::getKeyModifiers(void) const
{
    
    return determineKeyModifiers(_LastKeyboardMouseButtonMask);
}

Pnt2f XWindow::getMousePosition(void) const
{   
    return _LastMousePosition;
}

std::string XWindow::getClipboard(void) const
{
   //TODO:Implement
   return std::string("");
}

void XWindow::putClipboard(const std::string Value)
{
   //TODO:Implement
}

void XWindow::closeWindow(void)
{
    XDestroyWindow(this->getDisplay(),this->getWindow());
}

void XWindow::draw(void)
{
    internalDraw();
}


void XWindow::setTitle(const std::string& TitleText)
{
   //TODO:Implement
}


std::string XWindow::getTitle(void)
{
   //TODO:Implement
    return std::string("");
}

void XWindow::setRisizable(bool IsResizable)
{
   //TODO:Implement
}

bool XWindow::getRisizable(void)
{
   //TODO:Implement
    return true;
}

void XWindow::setDrawBorder(bool DrawBorder)
{
   //TODO:Implement
}

bool XWindow::getDrawBorder(void)
{
   //TODO:Implement
    return true;
}

void XWindow::setShowCursor(bool showCursor)
{
   //TODO:Implement
}

bool XWindow::getShowCursor(void) const
{
   //TODO:Implement
    return true;
}

void XWindow::setAttachMouseToCursor(bool showCursor)
{
   //TODO:Implement
}

bool XWindow::getAttachMouseToCursor(void) const
{
   //TODO:Implement
    return true;
}

void XWindow::update(void)
{
    //Updating
    Time Now(getSystemTime());
    Time ElapsedTime(Now - getLastUpdateTime());
    if(ElapsedTime > 0.0 && ElapsedTime < 10.0)
    {
        produceUpdate(ElapsedTime);
    }
    setLastUpdateTime(Now);
}

void XWindow::openWindow(const Pnt2f& ScreenPosition,
                    const Vec2f& Size,
                    const std::string& WindowName)
{

    int argc(1);
    char **argv = new char*[1];
    (*argv)= "Bla";
     XSetStandardProperties(this->getDisplay(), this->getWindow(), WindowName.c_str(), WindowName.c_str(), None, argv, argc, NULL);
    attachWindow();
    

    this->init();
    
    XMapWindow(this->getDisplay(),
               this->getWindow());
    XEvent event;
    XIfEvent(this->getDisplay(), &event, wait_for_map_notify, (char *)(this->getWindow()));
    produceWindowOpened();
    
    this->activate();
    
    setPosition(ScreenPosition);
    setSize(Vec2us(Size[0], Size[1]));
    
    //Set things up to capture the delete window event
    Atom wm_delete_window=XInternAtom(this->getDisplay(), "WM_DELETE_WINDOW", False);
    XSetWMProtocols(this->getDisplay(), this->getWindow(), &wm_delete_window, 1);
    Atom wm_protocols=XInternAtom(this->getDisplay(), "WM_PROTOCOLS", False); 
}

bool XWindow::attachWindow(void)
{   
    return true;
}

void XWindow::handleEvent(XEvent& Event)
{
    switch (Event.type) 
    {
        case KeyPress:
            //produceKeyPressed(determineKey(wParam),getKeyModifiers());
            _LastKeyboardMouseButtonMask = Event.xkey.state;
            produceKeyPressed(determineKey(XLookupKeysym(&(Event.xkey), 0)),determineKeyModifiers(Event.xkey.state));
            break;
        case KeyRelease:
            //produceKeyReleased(determineKey(wParam),getKeyModifiers());
            _LastKeyboardMouseButtonMask = Event.xkey.state;
            produceKeyReleased(determineKey(XLookupKeysym(&(Event.xkey),0)),determineKeyModifiers(Event.xkey.state));
            break;
        case MotionNotify:
            {
                _LastKeyboardMouseButtonMask = Event.xmotion.state;
                _LastMousePosition.setValues(Event.xbutton.x, Event.xbutton.y);
                if(Event.xmotion.state & Button1MotionMask)
                {
                    produceMouseDragged(MouseEventDetails::BUTTON1,Pnt2f(Event.xmotion.x, Event.xmotion.y), Vec2f(0.0f,0.0f));
                }
                if(Event.xmotion.state & Button2MotionMask)
                {
                    produceMouseDragged(MouseEventDetails::BUTTON2,Pnt2f(Event.xmotion.x, Event.xmotion.y), Vec2f(0.0f,0.0f));
                }
                if(Event.xmotion.state & Button3MotionMask)
                {
                    produceMouseDragged(MouseEventDetails::BUTTON3,Pnt2f(Event.xmotion.x, Event.xmotion.y), Vec2f(0.0f,0.0f));
                }
                if(Event.xmotion.state & Button4MotionMask)
                {
                    produceMouseDragged(MouseEventDetails::BUTTON4,Pnt2f(Event.xmotion.x, Event.xmotion.y), Vec2f(0.0f,0.0f));
                }
                if(Event.xmotion.state & Button5MotionMask)
                {
                    produceMouseDragged(MouseEventDetails::BUTTON5,Pnt2f(Event.xmotion.x, Event.xmotion.y), Vec2f(0.0f,0.0f));
                }
                
                produceMouseMoved(Pnt2f(Event.xmotion.x, Event.xmotion.y), Vec2f(0.0f,0.0f));
                break;
            }
         case ButtonPress:
            {
                _LastKeyboardMouseButtonMask = Event.xbutton.state;
               _LastMousePosition.setValues(Event.xbutton.x, Event.xbutton.y);
               MouseEventDetails::MouseButton OSGButton(MouseEventDetails::NO_BUTTON);
               switch(Event.xbutton.button)
               {
               case  1:
                  OSGButton = MouseEventDetails::BUTTON1;
                  break;
               case  2:
                  OSGButton = MouseEventDetails::BUTTON2;
                  break;
               case  3:
                  OSGButton = MouseEventDetails::BUTTON3;
                  break;
               case   4:
				  produceMouseWheelMoved(1, Pnt2f(Event.xbutton.x, Event.xbutton.y));
                  break;
               case   5:
				  produceMouseWheelMoved(-1, Pnt2f(Event.xbutton.x, Event.xbutton.y));
                  break;
               case   6:
                  OSGButton = MouseEventDetails::BUTTON6;
                  break;
               case   7:
                  OSGButton = MouseEventDetails::BUTTON7;
                  break;
               case   8:
                  OSGButton = MouseEventDetails::BUTTON8;
                  break;
               case   9:
                  OSGButton = MouseEventDetails::BUTTON9;
                  break;
               case   10:
                  OSGButton = MouseEventDetails::BUTTON10;
                  break;
               default:
                  OSGButton = MouseEventDetails::NO_BUTTON;
                  break;
               }
               if(OSGButton != MouseEventDetails::NO_BUTTON)
               {
                   produceMousePressed(OSGButton, Pnt2f(Event.xbutton.x, Event.xbutton.y));
               }
               break;
            }

         case ButtonRelease:
            {
               _LastKeyboardMouseButtonMask = Event.xbutton.state;
               _LastMousePosition.setValues(Event.xbutton.x, Event.xbutton.y);
               MouseEventDetails::MouseButton OSGButton(MouseEventDetails::NO_BUTTON);
              switch(Event.xbutton.button)
              {
              case  1:
                 OSGButton = MouseEventDetails::BUTTON1;
                 break;
              case  2:
                 OSGButton = MouseEventDetails::BUTTON2;
                 break;
               case  3:
                  OSGButton = MouseEventDetails::BUTTON3;
                  break;
               case   6:
                  OSGButton = MouseEventDetails::BUTTON6;
                  break;
               case   7:
                  OSGButton = MouseEventDetails::BUTTON7;
                  break;
               case   8:
                  OSGButton = MouseEventDetails::BUTTON8;
                  break;
               case   9:
                  OSGButton = MouseEventDetails::BUTTON9;
                  break;
               case   10:
                  OSGButton = MouseEventDetails::BUTTON10;
                  break;
              default:
                 break;
              }
               if(OSGButton != MouseEventDetails::NO_BUTTON)
               {
                   produceMouseReleased(OSGButton, Pnt2f(Event.xbutton.x, Event.xbutton.y));
               }
              break;
            }
         case ConfigureNotify:
               this->resize( Event.xconfigure.width,
                            Event.xconfigure.height );

               internalReshape(Vec2f(Event.xconfigure.width, Event.xconfigure.height));
            break;
            
         case DestroyNotify:
            produceWindowClosing();
            produceWindowClosed();
            break;
         case EnterNotify:
            produceWindowEntered();
            break;
         case LeaveNotify:
            produceWindowExited();
            break;
         case UnmapNotify:
            produceWindowIconified();
            break;
         case MapNotify:
            produceWindowDeiconified();
            break;
         case FocusIn:
            produceWindowActivated();
            break;
         case FocusOut:
            produceWindowDeactivated();
            break;
         case Expose:
            internalDraw();
            break;
        case ClientMessage:
        {
            Atom wm_delete_window=XInternAtom(this->getDisplay(), "WM_DELETE_WINDOW", False);
            Atom wm_protocols=XInternAtom(this->getDisplay(), "WM_PROTOCOLS", False);
            if (Event.xclient.message_type == wm_protocols &&
                Event.xclient.data.l[0] == (long)wm_delete_window)
            {
                XDestroyWindow(this->getDisplay(),this->getWindow());
            }
            break;
        }
        default:
            //std::cout << "Event Type: " << Event.type << std::endl;
            break;
      }
}


Vec2f XWindow::getDesktopSize(void) const
{
    //TODO: Implement
    return Vec2f(XDisplayWidth(this->getDisplay(), 0), XDisplayHeight(this->getDisplay(), 0));
}

std::vector<BoostPath> XWindow::openFileDialog(const std::string& WindowTitle,
		const std::vector<FileDialogFilter>& Filters,
		const BoostPath& InitialDir,
		bool AllowMultiSelect)
{
    //TODO: Implement
    std::vector<BoostPath> Result;
    return Result;
}

BoostPath XWindow::saveFileDialog(const std::string& DialogTitle,
                const std::vector<FileDialogFilter>& Filters,
                const std::string& InitialFile,
                const BoostPath& InitialDirectory,
                bool PromptForOverwrite
                )
{
    //TODO: Implement
    BoostPath Result;
    return Result;
}

KeyEventDetails::KeyState XWindow::getKeyState(KeyEventDetails::Key TheKey) const
{
    //TODO: Implement
    return KeyEventDetails::KEY_STATE_UP;
}

/*----------------------- constructors & destructors ----------------------*/

//! Constructor
XWindow::XWindow(void) :
    Inherited(),
        _LastKeyboardMouseButtonMask(0),
        _LastMousePosition(0,0)
{
}

//! Copy Constructor
XWindow::XWindow(const XWindow &source) :
    Inherited(source),
        _LastKeyboardMouseButtonMask(0),
        _LastMousePosition(0,0)
{
}

//! Destructor
XWindow::~XWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void XWindow::setCursor(void)
{
	int cursor_shape;
	switch(getCursorType())
	{
	case CURSOR_POINTER:
		cursor_shape = XC_top_left_arrow;
		break;
	case CURSOR_HAND:
		cursor_shape = XC_hand1;
		break;
	case CURSOR_I_BEAM:
		cursor_shape = XC_xterm;
		break;
	case CURSOR_WAIT:
		cursor_shape = XC_watch;
		break;
	case CURSOR_RESIZE_W_TO_E:
		cursor_shape = XC_sb_h_double_arrow;
		break;
	case CURSOR_RESIZE_N_TO_S:
		cursor_shape = XC_sb_v_double_arrow;
		break;
	case CURSOR_RESIZE_NW_TO_SE:
		cursor_shape = XC_sizing;
		break;
	case CURSOR_RESIZE_SW_TO_NE:
		cursor_shape = XC_sizing;
		break;
	case CURSOR_RESIZE_ALL:
		cursor_shape = XC_fleur;
		break;
	case CURSOR_NONE:
		cursor_shape = XC_X_cursor;
		break;
	default:
		cursor_shape = XC_arrow;
		break;
	}
    XDefineCursor(this->getDisplay(),this->getWindow(),
            XCreateFontCursor(this->getDisplay(),cursor_shape));
}
//! initialize the static features of the class, e.g. action callbacks
void XWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

//! react to field changes
void XWindow::changed(ConstFieldMaskArg whichField, 
                      UInt32            origin,
                      BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

//! output the instance for debug purposes
void XWindow::dump(      UInt32    , 
                   const BitVector ) const
{
    SLOG << "Dump XWindow NI" << std::endl;
}

void XWindow::onCreate(const XWindow *source)
{
    Inherited::onCreate(source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;
   
    if(source != NULL)
    {
    }
}

/*! instance deletion
*/

void XWindow::onDestroy(UInt32 uiContainerId)
{

    Inherited::onDestroy(uiContainerId);
}


#ifdef OSG_DEBUG_OLD_C_CASTS
#ifdef DisplayString
#undef DisplayString
#endif
#define DisplayString(dpy)((reinterpret_cast<_XPrivDisplay>(dpy))->display_name)
#ifdef ScreenOfDisplay
#undef ScreenOfDisplay
#endif
#ifdef DefaultScreen
#undef DefaultScreen
#endif
#define ScreenOfDisplay(dpy, scr)(&(_XPrivDisplay(dpy))->screens[scr])
#define DefaultScreen(dpy) 	((_XPrivDisplay(dpy))->default_screen)
#endif

void XWindow::classicInit(void)
{
    XVisualInfo       *vi, visInfo;
    XWindowAttributes winAttr;

    XGetWindowAttributes(getDisplay(), getWindow(), &winAttr);

    // get the existing glWidget's visual-id
    memset(&visInfo, 0, sizeof(XVisualInfo));

    visInfo.visualid = XVisualIDFromVisual(winAttr.visual);

    // get new display-variable
    if(getDisplay() == NULL)
    {
        setDisplay(XOpenDisplay(DisplayString(getDisplay())));  
    }
        
    // get a visual for the glx context
    int nvis;
    
    vi = XGetVisualInfo(getDisplay(), VisualIDMask, &visInfo, &nvis);

    // is the visual GL-capable ?
    int useGL;
    glXGetConfig( getDisplay(), 
                  vi, 
                  GLX_USE_GL, 
                 &useGL );

    if (!useGL)
    {
        SFATAL << "Visual is not OpenGL-capable!" << std::endl;
        exit(0);
    }    
        
    // create the new context
    this->setContext(glXCreateContext(getDisplay(), vi, None, GL_TRUE));
        
    XFree(vi);
}

/*! Init the window: create the context and setup the OpenGL.
*/
void XWindow::init(GLInitFunctor oFunc)
{  
    if(_sfFbConfigId.getValue() == -1)
    {
        classicInit();
    }
    else
    {
        OSGGETGLFUNCBYNAME(OSGglxChooseFBConfigProc, 
                           osgGlxChooseFBConfig,
                           "glXChooseFBConfig",
                           this);

        OSG_ASSERT(osgGlxChooseFBConfig != NULL);

        int iMatching;

        int fbAttr[] =
        {
            GLX_FBCONFIG_ID, _sfFbConfigId.getValue(),
            None
        };

        GLXFBConfig *fbConfigs = 
            osgGlxChooseFBConfig( getDisplay(),
                                  DefaultScreen(getDisplay()),
                                  fbAttr,
                                 &iMatching);

        if(iMatching <= 0)
        {
            fprintf(stderr, "no valid fbconfig %d\n",
                    _sfFbConfigId.getValue());

            exit(0);
        }


        OSGGETGLFUNCBYNAME(OSGglxCreateContextAttribsARB, 
                           osgGlXCreateContextAttribsARB,
                           "glXCreateContextAttribsARB",
                           this);

        if(osgGlXCreateContextAttribsARB != NULL)
        {
            std::vector<int> ctxAttr;
        
            if(getRequestMajor() > 0)
            {
                ctxAttr.push_back(GLX_CONTEXT_MAJOR_VERSION_ARB);
                ctxAttr.push_back(getRequestMajor());
                ctxAttr.push_back(GLX_CONTEXT_MINOR_VERSION_ARB);
                ctxAttr.push_back(getRequestMinor());
            }
         
            if(getContextFlags() != 0)
            {
                ctxAttr.push_back(GLX_CONTEXT_FLAGS_ARB);
                ctxAttr.push_back(getContextFlags()    );
            }
            
            ctxAttr.push_back(None);
            
            this->setContext(osgGlXCreateContextAttribsARB( getDisplay(),
                                                            fbConfigs[0],
                                                            None,
                                                            GL_TRUE,
                                                           &(ctxAttr.front())));
            
            if(getContext() == NULL)
            {
                FWARNING(("Could not create context, requested version "
                          "%d.%d might not be supported (guessing)\n",
                          getRequestMajor(),
                          getRequestMinor()));
                
                exit(0);
            }

            XFree(fbConfigs);
        }
        else
        {
            classicInit();
        }
    }

    Inherited::init(oFunc);
}
    
void XWindow::terminate(void)
{
    Inherited::doTerminate();

    if(getDisplay() != NULL && getContext() != NULL)
    {
        this->doDeactivate();

        glXDestroyContext(getDisplay(), getContext());

        setContext(NULL);
    }
}

// activate the window: bind the OGL context    
void XWindow::doActivate(void)
{
    Bool res;

#ifdef OSG_DEBUG
    if(getDisplay() == NULL)
    {
        SWARNING << "XWindow::doActivate: Display is NULL, can not activate context."
                 << std::endl;
    }

    if(getWindow() == 0)
    {
        SWARNING << "XWindow::doActivate: Window is NULL, can not activate context."
                 << std::endl;
    }

    if(getContext() == NULL)
    {
        SWARNING << "XWindow::doActivate: Context is NULL, can not activate context."
                 << std::endl;
    }
#endif

    res = glXMakeCurrent(getDisplay(), getWindow(), getContext());
    
    if(res != True)
    {
        FWARNING(("XWindow::activate: makeCurrent failed!\n"));
        glErr("XWindow::activate");
        glErr("XWindow::activate");
        glErr("XWindow::activate");
    }
}
    
// activate the window: bind the OGL context    
void XWindow::doDeactivate(void)
{
    glXMakeCurrent(getDisplay(), None, NULL);
}
    
// swap front and back buffers  
bool XWindow::doSwap(void)
{
    glXSwapBuffers(getDisplay(), getWindow());
    return true;
}

bool XWindow::hasContext(void)
{
    return (this->getContext() != NULL);
}

#if 0
void XWindow::onDestroy(UInt32 uiContainerId)
{
    Inherited::onDestroy(uiContainerId);
}
#endif


#include "OSGSField.ins"
#include "OSGMField.ins"

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_FUNCTION_INSTANTIATION) || \
    defined(OSG_TMPL_STATIC_MEMBER_NEEDS_CLASS_INSTANTIATION   )

#include "OSGSFieldFuncs.ins"
#include "OSGMFieldFuncs.ins"
#endif

OSG_BEGIN_NAMESPACE

DataType FieldTraits<DisplayP,   2>::_type("DisplayP",   "");
#if ( !defined(__GNUC__) || !defined(__linux) || ( !defined(__ia64) && !defined(__x86_64) && !defined(_ARCH_PPC64)) ) && (!defined(_MIPS_SZPTR) || _MIPS_SZPTR != 64)
DataType FieldTraits<X11Window,  2>::_type("X11Window",  "");
#endif
DataType FieldTraits<GLXContext, 2>::_type("GLXContext", "");

OSG_FIELD_DLLEXPORT_DEF2(SField, DisplayP,   2);
OSG_FIELD_DLLEXPORT_DEF2(MField, DisplayP,   2);
#if ( !defined(__GNUC__) || !defined(__linux) || ( !defined(__ia64) && !defined(__x86_64) && !defined(_ARCH_PPC64)) ) && (!defined(_MIPS_SZPTR) || _MIPS_SZPTR != 64)
OSG_FIELD_DLLEXPORT_DEF2(SField, X11Window,  2);
OSG_FIELD_DLLEXPORT_DEF2(MField, X11Window,  2);
#endif
OSG_FIELD_DLLEXPORT_DEF2(SField, GLXContext, 2);
OSG_FIELD_DLLEXPORT_DEF2(MField, GLXContext, 2);

OSG_END_NAMESPACE
