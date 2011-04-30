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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGPassiveWindow.h"
#include "OSGRenderActionBase.h"
#include "OSGRenderActionTask.h"

#ifdef OSG_USE_GLX
#include <GL/glx.h>
#endif
#ifdef __APPLE__
//#include "OSGCocoaWindowWrapper.h"
#include "OSGCarbonWindowWrapper.h"
#endif

#include "OSGKeyEventDetails.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGPassiveWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGPassiveWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PassiveWindow::initMethod (InitPhase ePhase)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PassiveWindow::PassiveWindow(void) :
    Inherited()
{
    _sfDrawMode.setValue(
        (_sfDrawMode.getValue()  & ~Window::ContextMask   ) | 
        (Window::ExternalContext |  Window::PassiveContext) );
}

PassiveWindow::PassiveWindow(const PassiveWindow &source) :
    Inherited(source)
{
    _sfDrawMode.setValue(
        (_sfDrawMode.getValue()  & ~Window::ContextMask   ) | 
        (Window::ExternalContext |  Window::PassiveContext) );
}

PassiveWindow::~PassiveWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PassiveWindow::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PassiveWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PassiveWindow NI" << std::endl;
}

/*! Just call the standard OpenGL setup.
 */
void PassiveWindow::init(GLInitFunctor oFunc)
{
#if defined(WIN32)
    Inherited::setHdc  (wglGetCurrentDC     ());
    Inherited::setHglrc(wglGetCurrentContext());
#elif defined(__APPLE__)
    //Inherited::setContext(cocoaWrapperCurrentContext());
    Inherited::setContext(carbonWrapperCurrentContext());
#else
    Inherited::setDisplay(glXGetCurrentDisplay ());
    Inherited::setContext(glXGetCurrentContext ());
    Inherited::setWindow (glXGetCurrentDrawable());
#endif

    this->doActivate();

    Window::init(oFunc);
}

void PassiveWindow::terminate(void)
{
    Window::doTerminate();

    Inherited::setContext(NULL);
}

void PassiveWindow::setShowCursor(bool show)
{
    //Do nothing
}

bool PassiveWindow::getShowCursor(void) const
{
    //Do nothing
    return false;
}

void PassiveWindow::setAttachMouseToCursor(bool attach)
{
    //Do nothing
}

bool PassiveWindow::getAttachMouseToCursor(void) const
{
    //Do nothing
    return false;
}

Vec2f PassiveWindow::getDesktopSize(void) const
{
    //Do nothing
    return Vec2f();
}

std::vector<BoostPath, std::allocator<BoostPath> >
    PassiveWindow::openFileDialog(const std::string&,
                   const std::vector<WindowEventProducer::FileDialogFilter,
                   std::allocator<WindowEventProducer::FileDialogFilter> >&,
                   const BoostPath&, bool)
{
    //Do nothing
    return std::vector<BoostPath, std::allocator<BoostPath> >();
}

BoostPath
    PassiveWindow::saveFileDialog(const std::string&,
                   const std::vector<WindowEventProducer::FileDialogFilter,
                   std::allocator<WindowEventProducer::FileDialogFilter> >&,
                   const std::string&, const BoostPath&, bool)
{
    //Do nothing
    return BoostPath();
}

KeyEventDetails::KeyState PassiveWindow::getKeyState(KeyEventDetails::Key) const
{
    //Do nothing
    return KeyEventDetails::KEY_STATE_UP;
}

void PassiveWindow::openWindow(const Pnt2f& ScreenPosition,
                        const Vec2f& Size,
                        const std::string& WindowName)
{
    //Do nothing
}

void PassiveWindow::closeWindow(void)
{
    //Do nothing
}

void PassiveWindow::mainLoop(void)
{
    //Do nothing
}

OSG::Window* PassiveWindow::initWindow(void)
{
    //Do nothing
    return NULL;
}

void PassiveWindow::setPosition(Pnt2f Pos)
{
    //Do nothing
}

Pnt2f PassiveWindow::getPosition(void) const
{
    //Do nothing
    return Pnt2f();
}

void PassiveWindow::setSize(Vec2us Size)
{
    //Do nothing
}

Vec2f PassiveWindow::getSize(void) const
{
    //Do nothing
    return Vec2f();
}

void PassiveWindow::setFocused(bool Focused)
{
    //Do nothing
}

bool PassiveWindow::getFocused(void) const
{
    //Do nothing
    return false;
}

void PassiveWindow::setVisible(bool Visible)
{
    //Do nothing
}

bool PassiveWindow::getVisible(void) const
{
    //Do nothing
    return false;
}

void PassiveWindow::setIconify(bool Iconify)
{
    //Do nothing
}

bool PassiveWindow::getIconify(void) const
{
    //Do nothing
    return false;
}

void PassiveWindow::setFullscreen(bool Fullscreen)
{
    //Do nothing
}

bool PassiveWindow::getFullscreen(void) const
{
    //Do nothing
    return false;
}

void PassiveWindow::setTitle(const std::string& TitleText)
{
    //Do nothing
}

std::string PassiveWindow::getTitle(void)
{
    //Do nothing
    return "";
}

void PassiveWindow::setRisizable(bool IsResizable)
{
    //Do nothing
}

bool PassiveWindow::getRisizable(void)
{
    //Do nothing
    return false;
}

void PassiveWindow::setDrawBorder(bool DrawBorder)
{
    //Do nothing
}

bool PassiveWindow::getDrawBorder(void)
{
    //Do nothing
    return false;
}

void PassiveWindow::draw(void)
{
    //Do nothing
}

void PassiveWindow::update(void)
{
    //Do nothing
}

bool PassiveWindow::attachWindow(void)
{
    //Do nothing
    return true;
}

OSG::UInt32 PassiveWindow::getKeyModifiers(void) const
{
    //Do nothing
    return KeyEventDetails::KEY_MODIFIER_UNKNOWN;
}

Pnt2f PassiveWindow::getMousePosition(void) const
{
    //Do nothing
    return Pnt2f();
}

std::string PassiveWindow::getClipboard(void) const
{
    //Do nothing
    return "";
}

void PassiveWindow::putClipboard(const std::string Value)
{
    //Do nothing
}

void PassiveWindow::setCursor(void)
{
    //Do nothing
}

void PassiveWindow::produceMouseClicked(const MouseEventDetails::MouseButton& Button, const Pnt2f& Location)
{
    Inherited::produceMouseClicked(Button, Location);
}

void PassiveWindow::produceMouseEntered(const Pnt2f& Location)
{
    Inherited::produceMouseEntered(Location);
}

void PassiveWindow::produceMouseExited(const Pnt2f& Location)
{
    Inherited::produceMouseExited(Location);
}

void PassiveWindow::produceMousePressed(const MouseEventDetails::MouseButton& Button, const Pnt2f& Location)
{
    Inherited::produceMousePressed(Button, Location);
}

void PassiveWindow::produceMouseReleased(const MouseEventDetails::MouseButton& Button, const Pnt2f& Location)
{
    Inherited::produceMouseReleased(Button, Location);
}


void PassiveWindow::produceMouseWheelMoved(const Int32& WheelRotation,
                                           const Pnt2f& Location,
                                           const MouseWheelEventDetails::ScrollType& TheScrollType)
{
    Inherited::produceMouseWheelMoved(WheelRotation, Location, TheScrollType);
}

void PassiveWindow::produceMouseMoved(const Pnt2f& Location, const Vec2f& Delta)
{
    Inherited::produceMouseMoved(Location, Delta);
}

void PassiveWindow::produceMouseDragged(const MouseEventDetails::MouseButton& Button, const Pnt2f& Location, const Vec2f& Delta)
{
    Inherited::produceMouseDragged(Button, Location, Delta);
}

void PassiveWindow::produceKeyPressed(const KeyEventDetails::Key& TheKey, const UInt32& Modifiers)
{
    Inherited::produceKeyPressed(TheKey, Modifiers);
}

void PassiveWindow::produceKeyReleased(const KeyEventDetails::Key& TheKey, const UInt32& Modifiers)
{
    Inherited::produceKeyReleased(TheKey, Modifiers);
}

void PassiveWindow::produceKeyTyped(const KeyEventDetails::Key& TheKey, const UInt32& Modifiers)
{
    Inherited::produceKeyTyped(TheKey, Modifiers);
}

void PassiveWindow::produceWindowOpened(void)
{
    Inherited::produceWindowOpened();
}

void PassiveWindow::produceWindowClosing(void)
{
    Inherited::produceWindowClosing();
}

void PassiveWindow::produceWindowClosed(void)
{
    Inherited::produceWindowClosed();
}

void PassiveWindow::produceWindowIconified(void)
{
    Inherited::produceWindowIconified();
}

void PassiveWindow::produceWindowDeiconified(void)
{
    Inherited::produceWindowDeiconified();
}

void PassiveWindow::produceWindowActivated(void)
{
    Inherited::produceWindowActivated();
}

void PassiveWindow::produceWindowDeactivated(void)
{
    Inherited::produceWindowDeactivated();
}

void PassiveWindow::produceWindowEntered(void)
{
    Inherited::produceWindowEntered();
}

void PassiveWindow::produceWindowExited(void)
{
    Inherited::produceWindowExited();
}

void PassiveWindow::produceUpdate(const Time& ElapsedTime)
{
    Inherited::produceUpdate(ElapsedTime);
}

