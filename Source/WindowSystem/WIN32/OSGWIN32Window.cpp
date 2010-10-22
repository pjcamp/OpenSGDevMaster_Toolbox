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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGWIN32Window.h"

#include "Windowsx.h"
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <boost/bind.hpp>


OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGWIN32WindowBase.cpp file.
// To modify it, please change the .fcd file (OSGWIN32Window.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

WIN32Window::WIN32HWNDToProducerMap WIN32Window::_WIN32HWNDToProducerMap;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void WIN32Window::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

LRESULT WIN32Window::staticWndProc(HWND hwnd, UINT uMsg,
                                   WPARAM wParam, LPARAM lParam)
{
    if(_WIN32HWNDToProducerMap.find(hwnd) != _WIN32HWNDToProducerMap.end())
    {
        return _WIN32HWNDToProducerMap[hwnd]->WndProc(hwnd, uMsg,
                                                      wParam, lParam);
    }
    else
    {
        switch(uMsg)
        {
            case WM_CREATE:
                {
                    PIXELFORMATDESCRIPTOR   pfd;
                    HDC           hDC;
                    int iPixelFormat;

                    ZeroMemory( &pfd, sizeof( pfd ) );
                    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
                    pfd.nVersion = 1;
                    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                        PFD_DOUBLEBUFFER;
                    pfd.iPixelType = PFD_TYPE_RGBA;
                    pfd.cColorBits = 32;
                    pfd.cDepthBits = 32;
                    pfd.iLayerType = PFD_MAIN_PLANE;
                    pfd.cStencilBits = 8;
                    pfd.cAlphaBits = 8;


                    // init the OSG window  
                    hDC = GetDC(hwnd);

                    iPixelFormat = ChoosePixelFormat(hDC, &pfd);
                    if (! SetPixelFormat(hDC, iPixelFormat, &pfd) )
                    {
                        FWARNING(("Failed to set Pixel Format."));
                    }

                    break;
                }
            default:
                return DefWindowProc(hwnd, uMsg, wParam, lParam);
                break;
        }
    }
    return 0;

}

void  WIN32Window::mainLoop(void)
{
    // Main loop ( event dispatching )
    MSG msg;
    // main loop 
    WIN32HWNDToProducerMap::iterator MapItor;
    //while ( GetMessage(&msg, NULL, 0, 0) > 0 )
    _RunMainLoop = true;
    _Active = true;
    StatTimeStampElem *LoopTimeStatElem;
    while (_RunMainLoop)
    {
        /*if(!_Active)
        {
            WaitMessage();
            while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                DispatchMessage(&msg);
            }
        }
        else
        {*/
            LoopTimeStatElem = StatCollector::getGlobalElem(WindowEventProducer::statWindowLoopTime);
            if(LoopTimeStatElem)
            {
                LoopTimeStatElem->start();
            }

            for( MapItor = _WIN32HWNDToProducerMap.begin(); MapItor != _WIN32HWNDToProducerMap.end(); ++MapItor)
            {
                MapItor->second->update();
            }

            while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                DispatchMessage(&msg);
            }

            for( MapItor = _WIN32HWNDToProducerMap.begin(); MapItor != _WIN32HWNDToProducerMap.end(); ++MapItor)
            {
                MapItor->second->draw();
            }

            LoopTimeStatElem = StatCollector::getGlobalElem(WindowEventProducer::statWindowLoopTime);
            if(LoopTimeStatElem)
            {
                LoopTimeStatElem->stop();
            }
        //}
    }

    if (getFullscreen())								// Are We In Fullscreen Mode?
    {
        ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
        ShowCursor(TRUE);						// Show Mouse Pointer
    }
}

std::string WIN32Window::getClipboard(void) const
{
    if(OpenClipboard(getHwnd()))
    {
        // Try to open the clipboard
        std::string Content;
        if(IsClipboardFormatAvailable(CF_TEXT))
        {
            HANDLE h = GetClipboardData(CF_TEXT);
            if (h)
            {
                const char * buf = (const char *)::GlobalLock(h);
                Content = buf;
                if (!Content.empty())
                    ::GlobalUnlock(h);
            }
        }
        CloseClipboard();
        return Content;
    }
    else
    {
        return std::string("");
    }
}

void WIN32Window::putClipboard(const std::string Value)
{
    if(OpenClipboard(getHwnd()))
    {
        if(EmptyClipboard())
        {
            HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (Value.size() + 1) * sizeof(char));
            if(hglbCopy != NULL)
            {
                //LPTSTR  lptstrCopy;
                void * buf = ::GlobalLock(hglbCopy);
                ::memcpy(buf, (const void *)Value.c_str(), Value.length()+1);
                ::GlobalUnlock(hglbCopy);
                SetClipboardData(CF_TEXT, hglbCopy);
            }
        }
        CloseClipboard();
    }
}

void WIN32Window::setCursor(void)
{
    LPSTR c;
    switch(getCursorType())
    {
        case CURSOR_POINTER:
            c = IDC_ARROW;
            break;
        case CURSOR_HAND:
            c = IDC_HAND;
            break;
        case CURSOR_I_BEAM:
            c = IDC_IBEAM;
            break;
        case CURSOR_WAIT:
            c = IDC_WAIT;
            break;
        case CURSOR_RESIZE_W_TO_E:
            c = IDC_SIZEWE;
            break;
        case CURSOR_RESIZE_N_TO_S:
            c = IDC_SIZENS;
            break;
        case CURSOR_RESIZE_NW_TO_SE:
            c = IDC_SIZENWSE;
            break;
        case CURSOR_RESIZE_SW_TO_NE:
            c = IDC_SIZENESW;
            break;
        case CURSOR_RESIZE_ALL:
            c = IDC_SIZEALL;
            break;
        case CURSOR_NONE:
            c = IDC_NO;
            break;
        default:
            c = IDC_ARROW;
            break;
    }
    SetCursor(LoadCursor(NULL, c));
}

Pnt2f WIN32Window::getMousePosition(void) const
{
    DWORD MousePos = GetMessagePos();
    LPPOINT ClientPoint = new POINT;
    ClientPoint->x = LOWORD(MousePos);
    ClientPoint->y = HIWORD(MousePos);

    Pnt2f Result(0,0);
    if(ScreenToClient(getHwnd(), ClientPoint))
    {
        Result.setValues(ClientPoint->x, ClientPoint->y);
    }
    delete ClientPoint;
    return Result;

}

UInt32 WIN32Window::getKeyModifiers(void) const
{
    UInt32 Modifiers = 0;

    if(GetKeyState(VK_SHIFT)<0)
    {
        Modifiers |= KeyEventDetails::KEY_MODIFIER_SHIFT;
    }
    if(GetKeyState(VK_CONTROL)<0)
    {
        Modifiers |= KeyEventDetails::KEY_MODIFIER_CONTROL;
    }
    if(GetKeyState(VK_MENU)<0)
    {
        Modifiers |= KeyEventDetails::KEY_MODIFIER_ALT;
    }
    if(GetKeyState(VK_CAPITAL)>0)
    {
        Modifiers |= KeyEventDetails::KEY_MODIFIER_CAPS_LOCK;
    }
    if(GetKeyState(VK_NUMLOCK)>0)
    {
        Modifiers |= KeyEventDetails::KEY_MODIFIER_NUM_LOCK;
    }
    if(GetKeyState(VK_SCROLL)>0)
    {
        Modifiers |= KeyEventDetails::KEY_MODIFIER_SCROLL_LOCK;
    }
    return Modifiers;
}

KeyEventDetails::KeyState WIN32Window::getKeyState(KeyEventDetails::Key TheKey) const
{
    SHORT KeyState(0);
    switch(TheKey)
    {
        //Alphabet
        case KeyEventDetails::KEY_A:
            KeyState = GetAsyncKeyState('A');
            break;
        case KeyEventDetails::KEY_B:
            KeyState = GetAsyncKeyState('B');
            break;
        case KeyEventDetails::KEY_C:
            KeyState = GetAsyncKeyState('C');
            break;
        case KeyEventDetails::KEY_D:
            KeyState = GetAsyncKeyState('D');
            break;
        case KeyEventDetails::KEY_E:
            KeyState = GetAsyncKeyState('E');
            break;
        case KeyEventDetails::KEY_F:
            KeyState = GetAsyncKeyState('F');
            break;
        case KeyEventDetails::KEY_G:
            KeyState = GetAsyncKeyState('G');
            break;
        case KeyEventDetails::KEY_H:
            KeyState = GetAsyncKeyState('H');
            break;
        case KeyEventDetails::KEY_I:
            KeyState = GetAsyncKeyState('I');
            break;
        case KeyEventDetails::KEY_J:
            KeyState = GetAsyncKeyState('J');
            break;
        case KeyEventDetails::KEY_K:
            KeyState = GetAsyncKeyState('K');
            break;
        case KeyEventDetails::KEY_L:
            KeyState = GetAsyncKeyState('L');
            break;
        case KeyEventDetails::KEY_M:
            KeyState = GetAsyncKeyState('M');
            break;
        case KeyEventDetails::KEY_N:
            KeyState = GetAsyncKeyState('N');
            break;
        case KeyEventDetails::KEY_O:
            KeyState = GetAsyncKeyState('O');
            break;
        case KeyEventDetails::KEY_P:
            KeyState = GetAsyncKeyState('P');
            break;
        case KeyEventDetails::KEY_Q:
            KeyState = GetAsyncKeyState('Q');
            break;
        case KeyEventDetails::KEY_R:
            KeyState = GetAsyncKeyState('R');
            break;
        case KeyEventDetails::KEY_S:
            KeyState = GetAsyncKeyState('S');
            break;
        case KeyEventDetails::KEY_T:
            KeyState = GetAsyncKeyState('T');
            break;
        case KeyEventDetails::KEY_U:
            KeyState = GetAsyncKeyState('U');
            break;
        case KeyEventDetails::KEY_V:
            KeyState = GetAsyncKeyState('V');
            break;
        case KeyEventDetails::KEY_W:
            KeyState = GetAsyncKeyState('W');
            break;
        case KeyEventDetails::KEY_X:
            KeyState = GetAsyncKeyState('X');
            break;
        case KeyEventDetails::KEY_Y:
            KeyState = GetAsyncKeyState('Y');
            break;
        case KeyEventDetails::KEY_Z:
            KeyState = GetAsyncKeyState('Z');
            break;
            //Numbers
        case KeyEventDetails::KEY_0:
            KeyState = GetAsyncKeyState('0');
            break;
        case KeyEventDetails::KEY_1:
            KeyState = GetAsyncKeyState('1');
            break;
        case KeyEventDetails::KEY_2:
            KeyState = GetAsyncKeyState('2');
            break;
        case KeyEventDetails::KEY_3:
            KeyState = GetAsyncKeyState('3');
            break;
        case KeyEventDetails::KEY_4:
            KeyState = GetAsyncKeyState('4');
            break;
        case KeyEventDetails::KEY_5:
            KeyState = GetAsyncKeyState('5');
            break;
        case KeyEventDetails::KEY_6:
            KeyState = GetAsyncKeyState('6');
            break;
        case KeyEventDetails::KEY_7:
            KeyState = GetAsyncKeyState('7');
            break;
        case KeyEventDetails::KEY_8:
            KeyState = GetAsyncKeyState('8');
            break;
        case KeyEventDetails::KEY_9:
            KeyState = GetAsyncKeyState('9');
            break;

            //Other
        case KeyEventDetails::KEY_MINUS:
            KeyState = GetAsyncKeyState(VK_OEM_MINUS);
            break;
        case KeyEventDetails::KEY_EQUALS:
            KeyState = GetAsyncKeyState(VK_OEM_PLUS);
            break;
        case KeyEventDetails::KEY_BACK_QUOTE:
            KeyState = GetAsyncKeyState(VK_OEM_3);
            break;
        case KeyEventDetails::KEY_TAB:
            KeyState = GetAsyncKeyState(VK_TAB);
            break;
        case KeyEventDetails::KEY_SPACE:
            KeyState = GetAsyncKeyState(VK_SPACE);
            break;
        case KeyEventDetails::KEY_OPEN_BRACKET:
            KeyState = GetAsyncKeyState(VK_OEM_4);
            break;
        case KeyEventDetails::KEY_CLOSE_BRACKET:
            KeyState = GetAsyncKeyState(VK_OEM_6);
            break;
        case KeyEventDetails::KEY_SEMICOLON:
            KeyState = GetAsyncKeyState(VK_OEM_1);
            break;
        case KeyEventDetails::KEY_COMMA:
            KeyState = GetAsyncKeyState(VK_OEM_COMMA);
            break;
        case KeyEventDetails::KEY_PERIOD:
            KeyState = GetAsyncKeyState(VK_OEM_PERIOD);
            break;
        case KeyEventDetails::KEY_BACK_SLASH:
            KeyState = GetAsyncKeyState(VK_OEM_5);
            break;
        case KeyEventDetails::KEY_APOSTROPHE:
            KeyState = GetAsyncKeyState(VK_OEM_7);
            break;
        case KeyEventDetails::KEY_SLASH:
            KeyState = GetAsyncKeyState(VK_OEM_2);
            break;

            //Non-visible
        case KeyEventDetails::KEY_ESCAPE:
            KeyState = GetAsyncKeyState(VK_ESCAPE);
            break;
        case KeyEventDetails::KEY_SHIFT:
            KeyState = GetAsyncKeyState(VK_SHIFT);
            break;
        case KeyEventDetails::KEY_CONTROL:
            KeyState = GetAsyncKeyState(VK_CONTROL);
            break;
        case KeyEventDetails::KEY_ALT:
            KeyState = GetAsyncKeyState(VK_MENU);
            break;
        case KeyEventDetails::KEY_ENTER:
            KeyState = GetAsyncKeyState(VK_RETURN);
            break;
        case KeyEventDetails::KEY_CANCEL:
            KeyState = GetAsyncKeyState(VK_CANCEL);
            break;
        case KeyEventDetails::KEY_CLEAR:
            KeyState = GetAsyncKeyState(VK_CLEAR);
            break;
        case KeyEventDetails::KEY_PAUSE:
            KeyState = GetAsyncKeyState(VK_PAUSE);
            break;
        case KeyEventDetails::KEY_CAPS_LOCK:
            KeyState = GetAsyncKeyState(VK_CAPITAL);
            break;
        case KeyEventDetails::KEY_END:
            KeyState = GetAsyncKeyState(VK_END);
            break;
        case KeyEventDetails::KEY_PAGE_UP:
            KeyState = GetAsyncKeyState(VK_PRIOR);
            break;
        case KeyEventDetails::KEY_PAGE_DOWN:
            KeyState = GetAsyncKeyState(VK_NEXT);
            break;
        case KeyEventDetails::KEY_HOME:
            KeyState = GetAsyncKeyState(VK_HOME);
            break;
        case KeyEventDetails::KEY_UP:
            KeyState = GetAsyncKeyState(VK_UP);
            break;
        case KeyEventDetails::KEY_DOWN:
            KeyState = GetAsyncKeyState(VK_DOWN);
            break;
        case KeyEventDetails::KEY_LEFT:
            KeyState = GetAsyncKeyState(VK_LEFT);
            break;
        case KeyEventDetails::KEY_RIGHT:
            KeyState = GetAsyncKeyState(VK_RIGHT);
            break;
        case KeyEventDetails::KEY_PRINTSCREEN:
            KeyState = GetAsyncKeyState(VK_SNAPSHOT);
            break;
        case KeyEventDetails::KEY_INSERT:
            KeyState = GetAsyncKeyState(VK_INSERT);
            break;
        case KeyEventDetails::KEY_DELETE:
            KeyState = GetAsyncKeyState(VK_DELETE);
            break;
        case KeyEventDetails::KEY_HELP:
            KeyState = GetAsyncKeyState(VK_HELP);
            break;
        case KeyEventDetails::KEY_NUM_LOCK:
            KeyState = GetAsyncKeyState(VK_NUMLOCK);
            break;
        case KeyEventDetails::KEY_SCROLL_LOCK:
            KeyState = GetAsyncKeyState(VK_SCROLL);
            break;
        case KeyEventDetails::KEY_BACK_SPACE:
            KeyState = GetAsyncKeyState(VK_BACK);
            break;

            //Function Keys
        case KeyEventDetails::KEY_F1:
            KeyState = GetAsyncKeyState(VK_F1);
            break;
        case KeyEventDetails::KEY_F2:
            KeyState = GetAsyncKeyState(VK_F2);
            break;
        case KeyEventDetails::KEY_F3:
            KeyState = GetAsyncKeyState(VK_F3);
            break;
        case KeyEventDetails::KEY_F4:
            KeyState = GetAsyncKeyState(VK_F4);
            break;
        case KeyEventDetails::KEY_F5:
            KeyState = GetAsyncKeyState(VK_F5);
            break;
        case KeyEventDetails::KEY_F6:
            KeyState = GetAsyncKeyState(VK_F6);
            break;
        case KeyEventDetails::KEY_F7:
            KeyState = GetAsyncKeyState(VK_F7);
            break;
        case KeyEventDetails::KEY_F8:
            KeyState = GetAsyncKeyState(VK_F8);
            break;
        case KeyEventDetails::KEY_F9:
            KeyState = GetAsyncKeyState(VK_F9);
            break;
        case KeyEventDetails::KEY_F10:
            KeyState = GetAsyncKeyState(VK_F10);
            break;
        case KeyEventDetails::KEY_F11:
            KeyState = GetAsyncKeyState(VK_F11);
            break;
        case KeyEventDetails::KEY_F12:
            KeyState = GetAsyncKeyState(VK_F12);
            break;
        case KeyEventDetails::KEY_F13:
            KeyState = GetAsyncKeyState(VK_F13);
            break;
        case KeyEventDetails::KEY_F14:
            KeyState = GetAsyncKeyState(VK_F14);
            break;
        case KeyEventDetails::KEY_F15:
            KeyState = GetAsyncKeyState(VK_F15);
            break;
        case KeyEventDetails::KEY_F16:
            KeyState = GetAsyncKeyState(VK_F16);
            break;
        case KeyEventDetails::KEY_F17:
            KeyState = GetAsyncKeyState(VK_F17);
            break;
        case KeyEventDetails::KEY_F18:
            KeyState = GetAsyncKeyState(VK_F18);
            break;
        case KeyEventDetails::KEY_F19:
            KeyState = GetAsyncKeyState(VK_F19);
            break;
        case KeyEventDetails::KEY_F20:
            KeyState = GetAsyncKeyState(VK_F20);
            break;
        case KeyEventDetails::KEY_F21:
            KeyState = GetAsyncKeyState(VK_F21);
            break;
        case KeyEventDetails::KEY_F22:
            KeyState = GetAsyncKeyState(VK_F22);
            break;
        case KeyEventDetails::KEY_F23:
            KeyState = GetAsyncKeyState(VK_F23);
            break;
        case KeyEventDetails::KEY_F24:
            KeyState = GetAsyncKeyState(VK_F24);
            break;

            //Numpad Keys
        case KeyEventDetails::KEY_NUMPAD_0:
            KeyState = GetAsyncKeyState(VK_NUMPAD0);
            break;
        case KeyEventDetails::KEY_NUMPAD_1:
            KeyState = GetAsyncKeyState(VK_NUMPAD1);
            break;
        case KeyEventDetails::KEY_NUMPAD_2:
            KeyState = GetAsyncKeyState(VK_NUMPAD2);
            break;
        case KeyEventDetails::KEY_NUMPAD_3:
            KeyState = GetAsyncKeyState(VK_NUMPAD3);
            break;
        case KeyEventDetails::KEY_NUMPAD_4:
            KeyState = GetAsyncKeyState(VK_NUMPAD4);
            break;
        case KeyEventDetails::KEY_NUMPAD_5:
            KeyState = GetAsyncKeyState(VK_NUMPAD5);
            break;
        case KeyEventDetails::KEY_NUMPAD_6:
            KeyState = GetAsyncKeyState(VK_NUMPAD6);
            break;
        case KeyEventDetails::KEY_NUMPAD_7:
            KeyState = GetAsyncKeyState(VK_NUMPAD7);
            break;
        case KeyEventDetails::KEY_NUMPAD_8:
            KeyState = GetAsyncKeyState(VK_NUMPAD8);
            break;
        case KeyEventDetails::KEY_NUMPAD_9:
            KeyState = GetAsyncKeyState(VK_NUMPAD9);
            break;
    }
    if(KeyState != 0)
    {
        if(KeyState &0x0001)
        {
            return KeyEventDetails::KEY_STATE_TOGGLED;
        }
        else
        {
            return KeyEventDetails::KEY_STATE_DOWN;
        }
    }
    else
    {
        return KeyEventDetails::KEY_STATE_UP;
    }
}

KeyEventDetails::Key WIN32Window::determineKey(WPARAM key)
{
    KeyEventDetails::Key OSGKey;
    switch(key)
    {
        //Alphabet
        case 'A':
            OSGKey = KeyEventDetails::KEY_A;
            break;
        case 'B':
            OSGKey = KeyEventDetails::KEY_B;
            break;
        case 'C':
            OSGKey = KeyEventDetails::KEY_C;
            break;
        case 'D':
            OSGKey = KeyEventDetails::KEY_D;
            break;
        case 'E':
            OSGKey = KeyEventDetails::KEY_E;
            break;
        case 'F':
            OSGKey = KeyEventDetails::KEY_F;
            break;
        case 'G':
            OSGKey = KeyEventDetails::KEY_G;
            break;
        case 'H':
            OSGKey = KeyEventDetails::KEY_H;
            break;
        case 'I':
            OSGKey = KeyEventDetails::KEY_I;
            break;
        case 'J':
            OSGKey = KeyEventDetails::KEY_J;
            break;
        case 'K':
            OSGKey = KeyEventDetails::KEY_K;
            break;
        case 'L':
            OSGKey = KeyEventDetails::KEY_L;
            break;
        case 'M':
            OSGKey = KeyEventDetails::KEY_M;
            break;
        case 'N':
            OSGKey = KeyEventDetails::KEY_N;
            break;
        case 'O':
            OSGKey = KeyEventDetails::KEY_O;
            break;
        case 'P':
            OSGKey = KeyEventDetails::KEY_P;
            break;
        case 'Q':
            OSGKey = KeyEventDetails::KEY_Q;
            break;
        case 'R':
            OSGKey = KeyEventDetails::KEY_R;
            break;
        case 'S':
            OSGKey = KeyEventDetails::KEY_S;
            break;
        case 'T':
            OSGKey = KeyEventDetails::KEY_T;
            break;
        case 'U':
            OSGKey = KeyEventDetails::KEY_U;
            break;
        case 'V':
            OSGKey = KeyEventDetails::KEY_V;
            break;
        case 'W':
            OSGKey = KeyEventDetails::KEY_W;
            break;
        case 'X':
            OSGKey = KeyEventDetails::KEY_X;
            break;
        case 'Y':
            OSGKey = KeyEventDetails::KEY_Y;
            break;
        case 'Z':
            OSGKey = KeyEventDetails::KEY_Z;
            break;
            //Numbers
        case '0':
            OSGKey = KeyEventDetails::KEY_0;
            break;
        case '1':
            OSGKey = KeyEventDetails::KEY_1;
            break;
        case '2':
            OSGKey = KeyEventDetails::KEY_2;
            break;
        case '3':
            OSGKey = KeyEventDetails::KEY_3;
            break;
        case '4':
            OSGKey = KeyEventDetails::KEY_4;
            break;
        case '5':
            OSGKey = KeyEventDetails::KEY_5;
            break;
        case '6':
            OSGKey = KeyEventDetails::KEY_6;
            break;
        case '7':
            OSGKey = KeyEventDetails::KEY_7;
            break;
        case '8':
            OSGKey = KeyEventDetails::KEY_8;
            break;
        case '9':
            OSGKey = KeyEventDetails::KEY_9;
            break;

            //Other
        case VK_OEM_MINUS:
            OSGKey = KeyEventDetails::KEY_MINUS;
            break;
        case VK_OEM_PLUS:
            OSGKey = KeyEventDetails::KEY_EQUALS;
            break;
        case VK_OEM_3:
            OSGKey = KeyEventDetails::KEY_BACK_QUOTE;
            break;
        case VK_TAB:
            OSGKey = KeyEventDetails::KEY_TAB;
            break;
        case VK_SPACE:
            OSGKey = KeyEventDetails::KEY_SPACE;
            break;
        case VK_OEM_4:
            OSGKey = KeyEventDetails::KEY_OPEN_BRACKET;
            break;
        case VK_OEM_6:
            OSGKey = KeyEventDetails::KEY_CLOSE_BRACKET;
            break;
        case VK_OEM_1:
            OSGKey = KeyEventDetails::KEY_SEMICOLON;
            break;
        case VK_OEM_COMMA:
            OSGKey = KeyEventDetails::KEY_COMMA;
            break;
        case VK_OEM_PERIOD:
            OSGKey = KeyEventDetails::KEY_PERIOD;
            break;
        case VK_OEM_5:
            OSGKey = KeyEventDetails::KEY_BACK_SLASH;
            break;
        case VK_OEM_7:
            OSGKey = KeyEventDetails::KEY_APOSTROPHE;
            break;
        case VK_OEM_2:
            OSGKey = KeyEventDetails::KEY_SLASH;
            break;

            //Non-visible
        case VK_ESCAPE:
            OSGKey = KeyEventDetails::KEY_ESCAPE;
            break;
        case VK_SHIFT:
            OSGKey = KeyEventDetails::KEY_SHIFT;
            break;
        case VK_CONTROL:
            OSGKey = KeyEventDetails::KEY_CONTROL;
            break;
        case VK_MENU:
            OSGKey = KeyEventDetails::KEY_ALT;
            break;
        case VK_RETURN:
            OSGKey = KeyEventDetails::KEY_ENTER;
            break;
        case VK_CANCEL:
            OSGKey = KeyEventDetails::KEY_CANCEL;
            break;
        case VK_CLEAR:
            OSGKey = KeyEventDetails::KEY_CLEAR;
            break;
        case VK_PAUSE:
            OSGKey = KeyEventDetails::KEY_PAUSE;
            break;
        case VK_CAPITAL:
            OSGKey = KeyEventDetails::KEY_CAPS_LOCK;
            break;
        case VK_END:
            OSGKey = KeyEventDetails::KEY_END;
            break;
        case VK_PRIOR:
            OSGKey = KeyEventDetails::KEY_PAGE_UP;
            break;
        case VK_NEXT:
            OSGKey = KeyEventDetails::KEY_PAGE_DOWN;
            break;
        case VK_HOME:
            OSGKey = KeyEventDetails::KEY_HOME;
            break;
        case VK_UP:
            OSGKey = KeyEventDetails::KEY_UP;
            break;
        case VK_DOWN:
            OSGKey = KeyEventDetails::KEY_DOWN;
            break;
        case VK_LEFT:
            OSGKey = KeyEventDetails::KEY_LEFT;
            break;
        case VK_RIGHT:
            OSGKey = KeyEventDetails::KEY_RIGHT;
            break;
        case VK_SNAPSHOT:
            OSGKey = KeyEventDetails::KEY_PRINTSCREEN;
            break;
        case VK_INSERT:
            OSGKey = KeyEventDetails::KEY_INSERT;
            break;
        case VK_DELETE:
            OSGKey = KeyEventDetails::KEY_DELETE;
            break;
        case VK_HELP:
            OSGKey = KeyEventDetails::KEY_HELP;
            break;
        case VK_NUMLOCK:
            OSGKey = KeyEventDetails::KEY_NUM_LOCK;
            break;
        case VK_SCROLL:
            OSGKey = KeyEventDetails::KEY_SCROLL_LOCK;
            break;
        case VK_BACK:
            OSGKey = KeyEventDetails::KEY_BACK_SPACE;
            break;

            //Function Keys
        case VK_F1:
            OSGKey = KeyEventDetails::KEY_F1;
            break;
        case VK_F2:
            OSGKey = KeyEventDetails::KEY_F2;
            break;
        case VK_F3:
            OSGKey = KeyEventDetails::KEY_F3;
            break;
        case VK_F4:
            OSGKey = KeyEventDetails::KEY_F4;
            break;
        case VK_F5:
            OSGKey = KeyEventDetails::KEY_F5;
            break;
        case VK_F6:
            OSGKey = KeyEventDetails::KEY_F6;
            break;
        case VK_F7:
            OSGKey = KeyEventDetails::KEY_F7;
            break;
        case VK_F8:
            OSGKey = KeyEventDetails::KEY_F8;
            break;
        case VK_F9:
            OSGKey = KeyEventDetails::KEY_F9;
            break;
        case VK_F10:
            OSGKey = KeyEventDetails::KEY_F10;
            break;
        case VK_F11:
            OSGKey = KeyEventDetails::KEY_F11;
            break;
        case VK_F12:
            OSGKey = KeyEventDetails::KEY_F12;
            break;
        case VK_F13:
            OSGKey = KeyEventDetails::KEY_F13;
            break;
        case VK_F14:
            OSGKey = KeyEventDetails::KEY_F14;
            break;
        case VK_F15:
            OSGKey = KeyEventDetails::KEY_F15;
            break;
        case VK_F16:
            OSGKey = KeyEventDetails::KEY_F16;
            break;
        case VK_F17:
            OSGKey = KeyEventDetails::KEY_F17;
            break;
        case VK_F18:
            OSGKey = KeyEventDetails::KEY_F18;
            break;
        case VK_F19:
            OSGKey = KeyEventDetails::KEY_F19;
            break;
        case VK_F20:
            OSGKey = KeyEventDetails::KEY_F20;
            break;
        case VK_F21:
            OSGKey = KeyEventDetails::KEY_F21;
            break;
        case VK_F22:
            OSGKey = KeyEventDetails::KEY_F22;
            break;
        case VK_F23:
            OSGKey = KeyEventDetails::KEY_F23;
            break;
        case VK_F24:
            OSGKey = KeyEventDetails::KEY_F24;
            break;

            //Numpad Keys
        case VK_NUMPAD0:
            OSGKey = KeyEventDetails::KEY_NUMPAD_0;
            break;
        case VK_NUMPAD1:
            OSGKey = KeyEventDetails::KEY_NUMPAD_1;
            break;
        case VK_NUMPAD2:
            OSGKey = KeyEventDetails::KEY_NUMPAD_2;
            break;
        case VK_NUMPAD3:
            OSGKey = KeyEventDetails::KEY_NUMPAD_3;
            break;
        case VK_NUMPAD4:
            OSGKey = KeyEventDetails::KEY_NUMPAD_4;
            break;
        case VK_NUMPAD5:
            OSGKey = KeyEventDetails::KEY_NUMPAD_5;
            break;
        case VK_NUMPAD6:
            OSGKey = KeyEventDetails::KEY_NUMPAD_6;
            break;
        case VK_NUMPAD7:
            OSGKey = KeyEventDetails::KEY_NUMPAD_7;
            break;
        case VK_NUMPAD8:
            OSGKey = KeyEventDetails::KEY_NUMPAD_8;
            break;
        case VK_NUMPAD9:
            OSGKey = KeyEventDetails::KEY_NUMPAD_9;
            break;

        default:
            OSGKey = KeyEventDetails::KEY_UNKNOWN;
            break;
    }
    return OSGKey;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

BoostPath WIN32Window::saveFileDialog(const std::string& DialogTitle,
                const std::vector<FileDialogFilter>& Filters,
                const std::string& InitialFile,
                const BoostPath& InitialDirectory,
                bool PromptForOverwrite
                )
{
    BoostPath Result;

    const UInt32 MAX_FILTER_STING_SIZE = 900;
    char FilterString[MAX_FILTER_STING_SIZE];
    UInt32 FilterSize(0);
    for(std::vector<FileDialogFilter>::const_iterator Itor(Filters.begin()) ; Itor != Filters.end(); ++Itor)
    {
        for(UInt32 i(0) ; i<Itor->getName().size(); ++i)
        {
            FilterString[FilterSize] = Itor->getName()[i];
            ++FilterSize;
        }
        FilterString[FilterSize] = '\0';
        ++FilterSize;

        //Split the Filters
        typedef std::vector< std::string > split_vector_type;
        
        split_vector_type SplitVec;
        boost::split( SplitVec, Itor->getFilter(), boost::is_any_of(";,") );

        for(UInt32 j(0) ; j<SplitVec.size() ; ++j)
        {
            if(j != 0)
            {
                FilterString[FilterSize] = ';';
                ++FilterSize;
            }
            FilterString[FilterSize] = '*';
            ++FilterSize;
            FilterString[FilterSize] = '.';
            ++FilterSize;
            for(UInt32 i(0) ; i<SplitVec[j].size(); ++i)
            {
                FilterString[FilterSize] = SplitVec[j][i];
                ++FilterSize;
            }
        }
        FilterString[FilterSize] = '\0';
        ++FilterSize;

        if(FilterSize > MAX_FILTER_STING_SIZE)
        {
            SWARNING << "Filter String too long.  Max length is " << MAX_FILTER_STING_SIZE << std::endl;
            return Result;
        }
    }
    FilterString[FilterSize] = '\0';
    ++FilterSize;

	LPSTR WindowTitleLPC = _strdup(DialogTitle.c_str());
	LPSTR InitialDirLPC = _strdup(InitialDirectory.string().c_str());

    OPENFILENAME ofn;       // common dialog box structure
    const UInt32 MAX_FILE_STING_SIZE = 300;
	char szFile[MAX_FILE_STING_SIZE];       // buffer for file name
    UInt32 i(0);
    for( ; i<osgMin<UInt32>(InitialFile.size(),MAX_FILE_STING_SIZE); ++i)
    {
        szFile[i] = InitialFile[i];
    }
    szFile[i] = '\0'; 
     
	ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME); 
    ofn.hwndOwner = getHwnd(); 
    ofn.lpstrFilter = FilterString; 
    ofn.lpstrFile= szFile; 
    ofn.nMaxFile = sizeof(szFile)/ sizeof(*szFile); 
	ofn.lpstrTitle = WindowTitleLPC;
	ofn.lpstrInitialDir = InitialDirLPC;
    ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT; 


    const UInt32 MAX_CURDIR_STING_SIZE = 300;
    char currentdir[MAX_CURDIR_STING_SIZE];
    GetCurrentDirectory(sizeof(currentdir),currentdir);
    if(GetSaveFileName(&ofn)==TRUE)
    {
        Result = BoostPath(ofn.lpstrFile);
    }
    SetCurrentDirectory(currentdir);
    
	free(WindowTitleLPC);
	free(InitialDirLPC);

    return Result;
}

std::vector<BoostPath> WIN32Window::openFileDialog(const std::string& WindowTitle,
		const std::vector<FileDialogFilter>& Filters,
		const BoostPath& InitialDir,
		bool AllowMultiSelect)
{
	std::vector<BoostPath> Result;

    const UInt32 MAX_FILTER_STING_SIZE = 900;
    char FilterString[MAX_FILTER_STING_SIZE];
    UInt32 FilterSize(0);
    for(std::vector<FileDialogFilter>::const_iterator Itor(Filters.begin()) ; Itor != Filters.end(); ++Itor)
    {
        for(UInt32 i(0) ; i<Itor->getName().size(); ++i)
        {
            FilterString[FilterSize] = Itor->getName()[i];
            ++FilterSize;
        }
        FilterString[FilterSize] = '\0';
        ++FilterSize;

        //Split the Filters
        typedef std::vector< std::string > split_vector_type;
        
        split_vector_type SplitVec;
        boost::split( SplitVec, Itor->getFilter(), boost::is_any_of(";,") );

        for(UInt32 j(0) ; j<SplitVec.size() ; ++j)
        {
            if(j != 0)
            {
                FilterString[FilterSize] = ';';
                ++FilterSize;
            }
            FilterString[FilterSize] = '*';
            ++FilterSize;
            FilterString[FilterSize] = '.';
            ++FilterSize;
            for(UInt32 i(0) ; i<SplitVec[j].size(); ++i)
            {
                FilterString[FilterSize] = SplitVec[j][i];
                ++FilterSize;
            }
        }
        FilterString[FilterSize] = '\0';
        ++FilterSize;

        if(FilterSize > MAX_FILTER_STING_SIZE)
        {
            SWARNING << "Filter String too long.  Max length is " << MAX_FILTER_STING_SIZE << std::endl;
            return Result;
        }
    }
    FilterString[FilterSize] = '\0';
    ++FilterSize;

	LPSTR WindowTitleLPC = _strdup(WindowTitle.c_str());
	LPSTR InitialDirLPC = _strdup(InitialDir.string().c_str());


	OPENFILENAME ofn;       // common dialog box structure
    const UInt32 MAX_FILE_STING_SIZE = 300;
	char szFile[MAX_FILE_STING_SIZE];       // buffer for file name

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = getHwnd();
	ofn.lpstrFile = szFile;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = FilterString;
	ofn.nFilterIndex = 1;
	ofn.lpstrTitle = WindowTitleLPC;
	ofn.lpstrInitialDir = InitialDirLPC;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 
    
    const UInt32 MAX_CURDIR_STING_SIZE = 300;
    char currentdir[MAX_CURDIR_STING_SIZE];
    GetCurrentDirectory(sizeof(currentdir),currentdir);

    // GetOpenFileName stuffs


	if (GetOpenFileName(&ofn)==TRUE)
	{
        Result.push_back(BoostPath(ofn.lpstrFile));
	}
	else
	{
	}
    SetCurrentDirectory(currentdir);

	free(WindowTitleLPC);
	free(InitialDirLPC);
	return Result;
}

Vec2f WIN32Window::getDesktopSize(void) const
{
    DEVMODE dm;
    // initialize the DEVMODE structure
    ZeroMemory(&dm, sizeof(dm));
    dm.dmSize = sizeof(dm);
    if (0 != EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm))
    {
        return Vec2f(dm.dmPelsWidth,dm.dmPelsHeight);
    }
    else
    {
        return Vec2f(0.0f,0.0f);
    }
}

void WIN32Window::draw(void)
{
    //SendMessage(getHwnd(),WIN32_DRAW_MESSAGE,0,0);
    internalDraw();
}

void WIN32Window::update(void)
{
    //SendMessage(getHwnd(),WIN32_UPDATE_MESSAGE,0,0);
    //Updating
    Time Now(getSystemTime());
    Time ElapsedTime(Now - getLastUpdateTime());
    if(ElapsedTime > 0.0 && ElapsedTime < 10.0)
    {
        produceUpdate(ElapsedTime);
    }
    setLastUpdateTime(Now);
}

Window* WIN32Window::initWindow(void)
{
	WindowRefPtr MyWindow = Inherited::initWindow();
    //Create the Win32 Window
    WNDCLASS  wndClass;
    HWND           hwnd;

    // Win32 Init
    memset(&wndClass, 0, sizeof(wndClass));
    
    std::string ClassName("OpenSG Window");
    wndClass.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// Redraw On Move, And Own DC For Window
	wndClass.lpfnWndProc		= (WNDPROC) WIN32Window::staticWndProc;				// WndProc Handles Messages
	wndClass.cbClsExtra		= 0;						// No Extra Window Data
	wndClass.cbWndExtra		= 0;						// No Extra Window Data
	wndClass.hInstance		= GetModuleHandle(NULL);					// Set The Instance
	wndClass.hIcon		= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	//wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wndClass.hbrBackground	= NULL;						// No Background Required For GL
	wndClass.lpszMenuName		= NULL;						// We Don't Want A Menu
	wndClass.lpszClassName	= ClassName.c_str();

    if (!RegisterClass(&wndClass)) 
    {
        MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
        return NULL;
    }


    RECT WindowRect;							// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=0;						// Set Left Value To 0
	WindowRect.right=10;						// Set Right Value To Requested Width
	WindowRect.top=0;							// Set Top Value To 0
	WindowRect.bottom=20;						// Set Bottom Value To Requested Height

    //Fullscreen
    bool fullscreen(_IsFullscreen);
    //bool fullscreen(false);
    if(fullscreen)
    {
        DEVMODE dmScreenSettings;					// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));		// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		//dmScreenSettings.dmPelsWidth	= _Size.x();			// Selected Screen Width
		//dmScreenSettings.dmPelsHeight	= _Size.y();			// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= 32;				// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

        // Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
            // If The Mode Fails, Offer Two Options.  Quit Or Run In A Window.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
                	fullscreen=FALSE;				// Select Windowed Mode (Fullscreen=FALSE)
			}
			else
			{
                // Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return NULL;					// Exit And Return FALSE
			}
		}
	}

    DWORD		dwExStyle;						// Window Extended Style
	DWORD		dwStyle;						// Window Style

    if (fullscreen)								// Are We Still In Fullscreen Mode?
	{
	    WindowRect.left=(long)0;						// Set Left Value To 0
	    WindowRect.top=(long)0;						// Set Top Value To 0
        dwExStyle=WS_EX_APPWINDOW;					// Window Extended Style
		dwStyle=WS_POPUP;						// Windows Style
        AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size
	}
	else
	{
        dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;					// Windows Style
	}
    
    //ShowCursor(true);						// Show/Hide Mouse Pointer

    // Create a Window
    hwnd = CreateWindowEx(	dwExStyle,				// Extended Style For The Window
				ClassName.c_str(),				// Class Name
				"Temp",					// Window Title
				WS_CLIPSIBLINGS |			// Required Window Style
				WS_CLIPCHILDREN |			// Required Window Style
				dwStyle,				// Selected Window Style
				WindowRect.left, WindowRect.top,					// Window Position
				WindowRect.right-WindowRect.left,	// Calculate Adjusted Window Width
				WindowRect.bottom-WindowRect.top,	// Calculate Adjusted Window Height
				NULL,					// No Parent Window
				NULL,					// No Menu
				wndClass.hInstance,				// Instance
				NULL);					// Don't Pass Anything To WM_CREATE

    if(!hwnd)
    {
        DWORD LastError = GetLastError();
        MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
        return NULL;
    }

    //Attach Window
    setHwnd(hwnd);

    _IsFullscreen = fullscreen;

    return MyWindow;
}

void WIN32Window::openWindow(const Pnt2f& ScreenPosition,
                    const Vec2f& Size,
                    const std::string& WindowName)
{

    attachWindow();
	
    if(_IsFullscreen)
    {
        //internalReshape(Vec2f(WindowRect.right-WindowRect.left, WindowRect.bottom-WindowRect.top));
    }

    init();
    deactivate();

    
    //Open the Window and enter the main event loop
    if(_IsFullscreen)
    {
        setPosition(Pnt2f(0.0f,0.0f));
        setSize(Vec2us(getDesktopSize().x(),getDesktopSize().y()));
    }
    else
    {
        setPosition(ScreenPosition);
        setSize(Vec2us(Size.x(),Size.y()));
    }
    setTitle(WindowName);
	ShowWindow( getHwnd(), SW_SHOWNORMAL );
    SetForegroundWindow(getHwnd());
    SetFocus(getHwnd());
	//SetActiveWindow( getHwnd() );
}

bool WIN32Window::attachWindow(void)
{
    if(_WIN32HWNDToProducerMap.find(getHwnd()) != _WIN32HWNDToProducerMap.end())
    {
        return false;
    }
    
    _WIN32HWNDToProducerMap[getHwnd()] = this;
    
    return true;
}

LRESULT WIN32Window::WndProc(HWND hwnd, UINT uMsg,
                     WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {       
        case WM_LBUTTONDOWN:
            produceMousePressed(MouseEventDetails::BUTTON1, Pnt2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            SetCapture(hwnd);
            break;
        case WM_MBUTTONDOWN:
            produceMousePressed(MouseEventDetails::BUTTON2, Pnt2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            SetCapture(hwnd);
            break;
        case WM_RBUTTONDOWN:
            produceMousePressed(MouseEventDetails::BUTTON3, Pnt2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            SetCapture(hwnd);
            break;   
        case WM_LBUTTONUP:
            produceMouseReleased(MouseEventDetails::BUTTON1, Pnt2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            ReleaseCapture();
            break;              
        case WM_MBUTTONUP:
            produceMouseReleased(MouseEventDetails::BUTTON2, Pnt2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            ReleaseCapture();
            break;
        case WM_RBUTTONUP:
            produceMouseReleased(MouseEventDetails::BUTTON3, Pnt2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            ReleaseCapture();
            break;
        case WM_MOUSEWHEEL:
			{
				//The lParam gives the Mouse location in screen space
				//Convert it to client area space
				LPPOINT ClientPoint = new POINT;
				ClientPoint->x = GET_X_LPARAM(lParam);
				ClientPoint->y = GET_Y_LPARAM(lParam);
				if(ScreenToClient(hwnd, ClientPoint))
				{
					produceMouseWheelMoved(static_cast<short>(HIWORD(wParam))/WHEEL_DELTA, Pnt2f(ClientPoint->x,ClientPoint->y));
				}
				else
				{
				}
                delete ClientPoint;
			}
            break;

        case WM_MOUSEMOVE:
            {

                Pnt2f Position(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Vec2f MouseDelta(0.0f,0.0f);
                if(_PreviousCursorPos != Pnt2f(-1.0f,-1.0f))
                {
                    MouseDelta = Position - _PreviousCursorPos;
                }
                _PreviousCursorPos = Position;

                if(!_HandleNextMouseMove)
                {
                    _HandleNextMouseMove = true;
                    return 0;
                }
			    if(wParam & MK_LBUTTON)
			    {
				    produceMouseDragged(MouseEventDetails::BUTTON1,Position, MouseDelta);
			    }
			    if(wParam & MK_MBUTTON)
			    {
				    produceMouseDragged(MouseEventDetails::BUTTON2,Position, MouseDelta);
			    }
			    if(wParam & MK_RBUTTON)
			    {
				    produceMouseDragged(MouseEventDetails::BUTTON3,Position, MouseDelta);
			    }
			    produceMouseMoved(Position, MouseDelta);


                break;
            }
                                    
        case WM_KEYDOWN:
            produceKeyPressed(determineKey(wParam),getKeyModifiers());
            break;                 
        case WM_KEYUP:
            produceKeyReleased(determineKey(wParam),getKeyModifiers());
            break;
                                    
        case WM_SIZE:
            resize( LOWORD(lParam), HIWORD( lParam ) );
            internalReshape(Vec2f(LOWORD(lParam), HIWORD( lParam )));
            break;

        case WM_CLOSE:
            produceWindowClosing();
            //Hide the window
            ShowWindow(hwnd, SW_HIDE);
            _RunMainLoop = false;
            _WIN32HWNDToProducerMap.erase(_WIN32HWNDToProducerMap.find(getHwnd()));
            //Don't actually destroy the window yet
            //return DefWindowProc(hwnd,uMsg,wParam,lParam);
            break;
            
        case WIN32_DRAW_MESSAGE:
            internalDraw();
            break;

        case WIN32_UPDATE_MESSAGE:
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
            break;

        case WM_ACTIVATE:
            if(LOWORD(wParam) == WA_ACTIVE || LOWORD(wParam) == WA_CLICKACTIVE)
            {
                _Active = true;
                produceWindowActivated();
            }
            else
            {
                _Active = false;
                produceWindowDeactivated();
            }
            return DefWindowProc(hwnd,uMsg,wParam,lParam);
            break;
        case WM_SYSCOMMAND:
           if (wParam == SC_MINIMIZE)
           {
               produceWindowIconified();
           }
           else if (wParam ==  SC_RESTORE)
           {
               produceWindowDeiconified();
           }

        case WM_SHOWWINDOW:
            if(wParam == TRUE && lParam == 0)
            {
               produceWindowOpened();
            }
            return DefWindowProc(hwnd,uMsg,wParam,lParam);
            break;

        case WM_DESTROY:
            produceWindowClosed();
            PostQuitMessage(0);
            _WIN32HWNDToProducerMap.erase(_WIN32HWNDToProducerMap.find(getHwnd()));
            break;

		case WM_SETCURSOR:
			setCursor();
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
    }
    return 0;
}

void WIN32Window::setShowCursor(bool showCursor)
{
    while(getShowCursor() != showCursor)
    {
        ShowCursor(showCursor);
    }
}

bool WIN32Window::getShowCursor(void) const
{
    CURSORINFO TheCursorInfo;
    TheCursorInfo.cbSize = sizeof(CURSORINFO);

    if(!GetCursorInfo(&TheCursorInfo))
    {
        SWARNING << "WIN32Window::getShowCursor: Failed to get cursor info " << GetLastError() << std::endl;
    }
    return TheCursorInfo.flags == CURSOR_SHOWING;
}

void WIN32Window::setAttachMouseToCursor(bool attachCursor)
{
    _IsMouseCursorAssociated = attachCursor;
}

bool WIN32Window::getAttachMouseToCursor(void) const
{
    return _IsMouseCursorAssociated;
}

void WIN32Window::setCursorPos(Vec2f Pos)
{
    if(!SetCursorPos(static_cast<int>(Pos.x()), static_cast<int>(Pos.y())))
    {
        SWARNING << "WIN32Window::setCursorPos: Failed to set cursor position" << std::endl;
    }
}

//Set the Window Position
void WIN32Window::setPosition(Pnt2f Pos)
{
    SetWindowPos(getHwnd(),HWND_NOTOPMOST, Pos.x(), Pos.y(), 0,0,
         SWP_NOSIZE | SWP_NOZORDER);
}

//Set the Window Position
Pnt2f WIN32Window::getPosition(void) const
{
    RECT r;
    GetWindowRect(getHwnd(), &r);
    return Pnt2f(r.left, r.top);
}

//Set the Window size
void WIN32Window::setSize(Vec2us Size)
{
    SetWindowPos(getHwnd(),HWND_NOTOPMOST, 0, 0, Size.x(),Size.y(),
         SWP_NOMOVE | SWP_NOZORDER);
}

//Get the Window size
Vec2f WIN32Window::getSize(void) const
{
    RECT r;
    GetWindowRect(getHwnd(), &r);
    return Vec2f(r.right-r.left, r.bottom-r.top);
}

//Focused
//Set the Window Focus
void WIN32Window::setFocused(bool Focused)
{
    if(Focused)
    {
        SetFocus(getHwnd());
    }
    else
    {
        SetFocus(NULL);
    }
    
}

//Get the Window Focus
bool WIN32Window::getFocused(void) const
{
   return GetForegroundWindow() == getHwnd();
}

//Visible / Iconify / Normal
//Set the Window Visible
void WIN32Window::setVisible(bool Visible)
{
    if(Visible)
    {
        ShowWindow(getHwnd(),SW_SHOW);
    }
    else
    {
        ShowWindow(getHwnd(),SW_HIDE);
    }
}

//Get the Window Visible
bool WIN32Window::getVisible(void) const
{
   return static_cast<bool>(IsWindowVisible(getHwnd()));
}

//Set the Window Iconify
void WIN32Window::setIconify(bool Iconify)
{
    if(Iconify)
    {
        ShowWindow(getHwnd(),SW_MINIMIZE);
    }
    else
    {
        ShowWindow(getHwnd(),SW_SHOWNORMAL);
    }
}

//Get the Window Iconify
bool WIN32Window::getIconify(void) const
{
   return static_cast<bool>(IsIconic(getHwnd()));
}

//Fullscreen
void WIN32Window::setFullscreen(bool Fullscreen)
{
    //TODO: find a better way to do this
    if(Fullscreen && !getFullscreen())
    {
        _PreviousWindowPosition = getPosition();
        _PreviousWindowSize = getSize();
        //SetWindowPos(getHwnd(),HWND_NOTOPMOST, 0, 0, GetSystemMetrics(SM_CXFULLSCREEN),GetSystemMetrics(SM_CYFULLSCREEN),
        //    SWP_NOZORDER);
        _IsFullscreen = true;
    }
    else if(!Fullscreen && getFullscreen())
    {
        SetWindowPos(getHwnd(),HWND_NOTOPMOST,
            static_cast<int>(_PreviousWindowPosition.x()),
            static_cast<int>(_PreviousWindowPosition.y()),
            static_cast<int>(_PreviousWindowSize.x()),
            static_cast<int>(_PreviousWindowSize.y()),
            SWP_NOZORDER);
        _IsFullscreen = false;
    }
}

//Get the Window Fullscreen
bool WIN32Window::getFullscreen(void) const
{
    return _IsFullscreen;
}

void WIN32Window::closeWindow(void)
{
    SendMessage(getHwnd(),WM_CLOSE,0,0);
}

void WIN32Window::setTitle(const std::string& TitleText)
{
    SetWindowText(getHwnd(), TitleText.c_str());
}

std::string WIN32Window::getTitle(void)
{
    int TextLength = GetWindowTextLength(getHwnd());
    PTSTR Text = (PSTR) VirtualAlloc((LPVOID) NULL, 
                    (DWORD) (TextLength + 1), MEM_COMMIT, 
                    PAGE_READWRITE);

    GetWindowText(getHwnd(), Text, 
                    TextLength + 1);
    
    return std::string(Text);
}

void WIN32Window::setRisizable(bool IsResizable)
{
    //TODO:Implement
}

bool WIN32Window::getRisizable(void)
{
    //TODO:Implement
    return true;
}

void WIN32Window::setDrawBorder(bool DrawBorder)
{
    //TODO:Implement
}

bool WIN32Window::getDrawBorder(void)
{
    //TODO:Implement
    return true;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void WIN32Window::onCreate(const WIN32Window *source)
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

void WIN32Window::onDestroy(UInt32 uiContainerId)
{

    Inherited::onDestroy(uiContainerId);

    if(IsWindow(getHwnd()))
    {
        DestroyWindow(getHwnd());
        produceWindowClosed();
        //PostQuitMessage(0);
    }
}

/*----------------------- constructors & destructors ----------------------*/

WIN32Window::WIN32Window(void) :
    Inherited(),
    _MouseOverWindow(false),
    _IsFullscreen(false),
    _IsMouseCursorAssociated(true),
    _HandleNextMouseMove(true),
    _PreviousCursorPos(-1.0,-1.0)
{
}

WIN32Window::WIN32Window(const WIN32Window &source) :
    Inherited(source),
    _MouseOverWindow(false),
    _IsFullscreen(false),
    _IsMouseCursorAssociated(true),
    _HandleNextMouseMove(true),
    _PreviousCursorPos(-1.0,-1.0)
{
}

WIN32Window::~WIN32Window(void)
{
}

/*----------------------------- class specific ----------------------------*/

void WIN32Window::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void WIN32Window::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump WIN32Window NI" << std::endl;
}

/*! init the window: create the HDC and HGLRC
*/
void WIN32Window::init(GLInitFunctor oFunc)
{
    setHdc(GetDC(getHwnd()));

    if(getHglrc() == NULL)
    {
        setHglrc(wglCreateContext(getHdc()));
        
        if(getHglrc() == NULL)
        {
            SFATAL << "WIN32Window::init: failed: "
                      << GetLastError() 
                      << std::endl;        
        }
    }

    Inherited::init(oFunc);

    if(getHdc() != NULL) 
    {
        ReleaseDC(getHwnd(), getHdc());

        setHdc(NULL);
    }
}

void WIN32Window::terminate(void)
{
    Inherited::doTerminate();

     if(getHglrc() != NULL)
     {
         this->doDeactivate();

         wglDeleteContext(getHglrc());
     }
}


/*! activate the window: set the HDC and bind the OGL context
*/
void WIN32Window::doActivate( void )
{    
    if(getHdc() == NULL)
        setHdc(GetDC(getHwnd()));

    if(!wglMakeCurrent(getHdc(), getHglrc()))
    {
        SWARNING << "WIN32Window::activate: failed: "
                  << GetLastError() 
                  << std::endl;        
    }
}

void WIN32Window::doDeactivate ( void )
{
    // unbind the context
    wglMakeCurrent(NULL, NULL);

    // release the hardware device context
    if(getHdc() != NULL) 
    {
        ReleaseDC(getHwnd(), getHdc());
        setHdc(NULL);
    }
}

// swap front and back buffers
bool WIN32Window::doSwap(void)
{
    if(getHdc() == NULL)
        setHdc(GetDC(getHwnd()));

    return SwapBuffers(getHdc());
}

bool WIN32Window::hasContext(void)
{
    return (this->getHglrc() != NULL);
}

OSG_END_NAMESPACE
