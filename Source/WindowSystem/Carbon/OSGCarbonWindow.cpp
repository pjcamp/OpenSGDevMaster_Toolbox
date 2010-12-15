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

// Forget everything if we're not doing a Mac OS X compile
#if defined(__APPLE__) || defined(OSG_DO_DOC)

#include <AGL/agl.h>
#include <boost/algorithm/string.hpp>

#include "OSGCarbonWindow.h"

#define KeyBackspace 	51
#define KeyEnter 	76
#define KeyHome 	115
#define KeyEnd 	119
#define KeyPageDown 	121
#define KeyPageUp 	116
#define KeyReturn 	36 	
#define KeyDelete 	117
#define KeyTab 	48
#define KeySpacebar 	49
#define KeyShift 	56 	
#define KeyControl 	59 	
#define KeyMenu 	58
//#define KeyPrintScreen 	*
#define KeyEscape 	53
#define KeyCapsLock 	57
#define KeyHelp 	114
#define KeyF1 	122
#define KeyF2 	120
#define KeyF3 	99
#define KeyF4 	118
#define KeyF5 	96
#define KeyF6 	97
#define KeyF7 	98
#define KeyF8 	100
#define KeyF9 	101
#define KeyF10 	109
#define KeyF11 	103
#define KeyF12 	111
#define KeyMacFn 	63
#define KeyMacOption 	58
#define KeyMacCommand 	55
#define KeyWinApplication 	110
#define KeyQ 	12
#define KeyW 	13
#define KeyE 	14 	
#define KeyR 	15 	
#define KeyT 	17 	
#define KeyY 	16 	
#define KeyU 	32 	
#define KeyI 	34 	
#define KeyO 	31 	
#define KeyP 	35 	
#define KeyA 	0 	
#define KeyS 	1 	
#define KeyD 	2 	
#define KeyF 	3 	
#define KeyG 	5 	
#define KeyH 	4 	
#define KeyJ 	38 	
#define KeyK 	40 	
#define KeyL 	37 	
#define KeyZ 	6 	
#define KeyX 	7 	
#define KeyC 	8 	
#define KeyV 	9 	
#define KeyB 	11 	
#define KeyN 	45 	
#define KeyM 	46 	
#define Key0 	29
#define Key1 	18
#define Key2 	19
#define Key3 	20
#define Key4 	21
#define Key5 	23
#define Key6 	22
#define Key7 	26
#define Key8 	28
#define Key9 	25
#define KeyPeriod 	47
#define KeyComma 	43
#define KeySlash 	44
#define KeyNum0 	82
#define KeyNum1 	83
#define KeyNum2 	84
#define KeyNum3 	85
#define KeyNum4 	86
#define KeyNum5 	87
#define KeyNum6 	88
#define KeyNum7 	89
#define KeyNum8 	91
#define KeyNum9 	92
#define KeyMultiply 	67
#define KeyAdd 	69
#define KeySubtract 	78
#define KeyDivide 	75
#define KeyDecimal 	65
#define KeyNumEqual 	81

#define KeyBackquote 50
#define KeyMinus 27
#define KeyEquals 24
#define KeyLeftBracket 33
#define KeyRightBracket 30
#define KeyBackslash 42
#define KeySemicolon 41
#define KeyApostrophe 39
#define KeyClear 71
#define KeyUp 126
#define KeyDown 125
#define KeyLeft 123
#define KeyRight 124

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCarbonWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGCarbonWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CarbonWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        // A magic method that allows applications to react to events even
        // when they are not organized in a bundle
        ProcessSerialNumber psn = { 0, kCurrentProcess };
        TransformProcessType(&psn, kProcessTransformToForegroundApplication);
        SetFrontProcess(&psn);
    }
}

OSStatus CarbonWindow::eventHandler(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    CarbonWindow* TheWindow(static_cast<CarbonWindow*>(userData));

    if(TheWindow != NULL)
    {
        return TheWindow->internalEventHandler(nextHandler,
                                               event,
                                               userData);
    }
    else
    {
        return eventNotHandledErr;
    }
}

void  CarbonWindow::mainLoop(void)
{
	// Main loop ( event dispatching )
    EventRef theEvent;    
    EventTargetRef theTarget;    
    theTarget = GetEventDispatcherTarget(); 
    while (_IsWindowOpen)
    {
        update();
        draw();
	
        while  ( ReceiveNextEvent(0, NULL,0 /*kEventDurationForever*/ ,true,
                                 &theEvent)== noErr)
        {
            SendEventToEventTarget (theEvent, theTarget);        
            ReleaseEvent(theEvent);
        }
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CarbonWindow::setShowCursor(bool show)
{
    if(show)
    {
        ShowCursor();
    }
    else
	{
        HideCursor();
	}
}

bool CarbonWindow::getShowCursor() const
{
	return CGCursorIsVisible();
}

void CarbonWindow::setAttachMouseToCursor(bool attach)
{
    _AttachMouseToCursor = attach;
    CGAssociateMouseAndMouseCursorPosition(_AttachMouseToCursor);
}

bool CarbonWindow::getAttachMouseToCursor(void) const
{
	return _AttachMouseToCursor;
}


Vec2f CarbonWindow::getDesktopSize() const
{

    HIRect DesktopRect;
    OSStatus status = HIWindowGetAvailablePositioningBounds(kCGNullDirectDisplay, kHICoordSpaceScreenPixel, &DesktopRect);
    if(status == noErr)
    {
        return Vec2f(DesktopRect.size.width, DesktopRect.size.height);
    }
    else
    {
        SWARNING << "CarbonWindow::getDesktopSize: Error" << std::endl;
        return Vec2f();
    }
}

// TRY TO CONVERT AN AEDesc TO AN FSSpec
//     As per Apple Technical Q&A QA1274
//     eg: http://developer.apple.com/qa/qa2001/qa1274.html
//     Returns 'noErr' if OK,
//             or an 'OSX result code' on error.
//
int AEDescToFSSpec(const AEDesc* desc, FSSpec* fsspec) {
    OSStatus err = noErr;
    AEDesc coerceDesc;
    // If AEDesc isn't already an FSSpec, convert it to one
    if ( desc->descriptorType != typeFSS ) {
        if ( ( err = AECoerceDesc(desc, typeFSS, &coerceDesc) ) == noErr ) {
        // Get FSSpec out of AEDesc
            err = AEGetDescData(&coerceDesc, fsspec, sizeof(FSSpec));
            AEDisposeDesc(&coerceDesc);
        }
    } else {
        err = AEGetDescData(desc, fsspec, sizeof(FSSpec));
    }
    return( err );
}

// CONVERT REGULAR PATH -> FSSpec
//     If file does not exist, expect fnfErr.
//     Returns 'noErr' if OK,
//             or an 'OSX result code' on error.
//
static OSStatus PathToFSSpec(const char *path, FSSpec &spec) {
    OSStatus err;
    FSRef ref;
    if ((err = FSPathMakeRef((const UInt8*)path, &ref, NULL)) != noErr) {
    return(err);
    }
    // FSRef -> FSSpec
    if ((err = FSGetCatalogInfo(&ref, kFSCatInfoNone, NULL, NULL, &spec,
                                     NULL)) != noErr) {
    return(err);
    }
    return(noErr);
}

std::vector<BoostPath> CarbonWindow::openFileDialog(const std::string& WindowTitle,
		const std::vector<FileDialogFilter>& Filters,
		const BoostPath& InitialDir,
		bool AllowMultiSelect)
{
	std::vector<BoostPath, std::allocator<BoostPath> > FilesToOpen;
    OSStatus status;
    NavDialogRef OpenFileDialog;

    NavDialogCreationOptions dialogOptions;

    //Default options for dialog
    status = NavGetDefaultDialogCreationOptions(&dialogOptions);
    if(status != noErr)
    {
        SWARNING << "CarbonWindow::openFileDialog: NavGetDefaultDialogCreationOptions Error: "<< status << std::endl;
	    return FilesToOpen;
    }

   // Make the window app-wide modal
   dialogOptions.modality = kWindowModalityAppModal;
   dialogOptions.parentWindow = _WindowRef;
   dialogOptions.windowTitle = CFStringCreateWithCString(NULL, WindowTitle.c_str(), WindowTitle.size());
   if(AllowMultiSelect)
   {
       dialogOptions.optionFlags = dialogOptions.optionFlags | kNavAllowMultipleFiles;
   }
   else
   {
       dialogOptions.optionFlags = dialogOptions.optionFlags ^ kNavAllowMultipleFiles;
   }
   
   status = NavCreateGetFileDialog (
       &dialogOptions,
       NULL,
       NULL,//_EventHandlerUPP,
       NULL,
       NULL,//NavObjectFilterUPP inFilterProc,
       NULL,//void *inClientData,
       &OpenFileDialog);
    
    if(status != noErr)
    {
        NavDialogDispose(OpenFileDialog);
        SWARNING << "CarbonWindow::openFileDialog: NavCreateGetFileDialog Error: "<< status << std::endl;
	    return FilesToOpen;
    }
    
    // Image Browser can open files with the ".imagebrowser" extension
    CFMutableArrayRef identifiers = CFArrayCreateMutable( kCFAllocatorDefault,
                                                          0,
                                                          NULL );
    if(identifiers == NULL)
    {
        NavDialogDispose(OpenFileDialog);
        SWARNING << "CarbonWindow::openFileDialog: CFArrayCreateMutable Error: NULL " <<  std::endl;
	    return FilesToOpen;
    }

    //Initial directory 
    FSSpec spec;
    status = PathToFSSpec(InitialDir.string().c_str(), spec);
    if(status != noErr)
    {
        NavDialogDispose(OpenFileDialog);
        SWARNING << "CarbonWindow::openFileDialog: PathToFSSpec Error: "<< status << std::endl;
	    return FilesToOpen;
    }

    AEDesc DefaultLocationAEDesc;
    status = AECreateDesc(typeFSS, &spec, sizeof(FSSpec), &DefaultLocationAEDesc);
    if(status != noErr)
    {
        NavDialogDispose(OpenFileDialog);
        SWARNING << "CarbonWindow::openFileDialog: AECreateDesc Error: "<< status << std::endl;
	    return FilesToOpen;
    }
    status = NavCustomControl( OpenFileDialog, kNavCtlSetLocation, &DefaultLocationAEDesc );
    if(status != noErr)
    {
        NavDialogDispose(OpenFileDialog);
        SWARNING << "CarbonWindow::openFileDialog: NavCustomControl Error: "<< status << std::endl;
	    return FilesToOpen;
    }
    AEDisposeDesc(&DefaultLocationAEDesc);

    //Filters
    //for(std::vector<FileDialogFilter>::const_iterator Itor(Filters.begin()) ; Itor != Filters.end(); ++Itor)
    //{
        ////Split the Filters
        //typedef std::vector< std::string > split_vector_type;
        
        //split_vector_type SplitVec;
        //boost::split( SplitVec, Itor->getFilter(), boost::is_any_of(";,") );

        //for(UInt32 j(0) ; j<SplitVec.size() ; ++j)
        //{
            //if(j != 0)
            //{
                //CFStringRef ExtStr = CFStringCreateWithCString(NULL,
                                                            //SplitVec[j].c_str(),
                                                            //SplitVec[j].size());
                //CFStringRef extUTI= UTTypeCreatePreferredIdentifierForTag(kUTTagClassFilenameExtension,
                                                                          //ExtStr,
                                                                          //kUTTypeData);
                //CFArrayAppendValue( identifiers, extUTI );

            //}
        //}
        ////if(Itor->getFilter().compare("*") != 0)
        ////{
            ////CFStringRef FilterCFString = UTTypeCreatePreferredIdentifierForTag( kUTTagClassFilenameExtension, CFStringCreateWithCString(NULL, Itor->getFilter().c_str(), Itor->getFilter().size()),kUTTypeData );

            ////if(FilterCFString == NULL)
            ////{
                ////NavDialogDispose(OpenFileDialog);
                ////SWARNING << "CarbonWindow::openFileDialog: UTTypeCreatePreferredIdentifierForTag Error: NULL " <<  std::endl;
                ////return FilesToOpen;
            ////}
            //////Itor->getName();
            ////CFArrayAppendValue( identifiers, FilterCFString );
        ////}
    //}
    
    //status = NavDialogSetFilterTypeIdentifiers( OpenFileDialog, identifiers );
    //if(status != noErr)
    //{
        //NavDialogDispose(OpenFileDialog);
        //SWARNING << "CarbonWindow::openFileDialog: NavDialogRun Error: "<< status << std::endl;
        //return FilesToOpen;
    //}
 
    //Open the dialog
    status = NavDialogRun(OpenFileDialog);
    if(status != noErr)
    {
        NavDialogDispose(OpenFileDialog);
        SWARNING << "CarbonWindow::openFileDialog: NavDialogRun Error: "<< status << std::endl;
        return FilesToOpen;
    }

    //Get Reply
    NavReplyRecord replyRecord;
    status = NavDialogGetReply(OpenFileDialog, &replyRecord);
    NavDialogDispose(OpenFileDialog);
    //If user canceled then return empty
    if (!replyRecord.validRecord ||  status == userCanceledErr )
    {
        NavDisposeReply(&replyRecord);
        return FilesToOpen;
    }
    
    //Other Errors
    if(status != noErr)
    {
        NavDisposeReply(&replyRecord);
        SWARNING << "CarbonWindow::openFileDialog: NavDialogGetReply Error: "<< status << std::endl;
        return FilesToOpen;
    }
    // How many items selected?
    long count = 0;
    if ( AECountItems(&replyRecord.selection, &count) != noErr ) 
    {
        NavDisposeReply(&replyRecord);
        SWARNING << "CarbonWindow::openFileDialog: AECountItems Error: "<< status << std::endl;
        return FilesToOpen;
    }

    // Walk list of pathnames selected
    for (unsigned int index=1; index<=count; index++)
    {
        FSRef parentDirectory;
        if (AEGetNthPtr(&(replyRecord.selection), index, typeFSRef, NULL, NULL, &parentDirectory, sizeof(FSRef), NULL)== noErr)
        {
            UInt8 FilePath[2048];
            if( FSRefMakePath (&parentDirectory, FilePath, sizeof(FilePath)) == noErr)
            {
                FilesToOpen.push_back(BoostPath(reinterpret_cast<Char8*>(FilePath)));
            }
        }
    }
    NavDisposeReply(&replyRecord);
    
    return FilesToOpen;
}

BoostPath CarbonWindow::saveFileDialog(const std::string& DialogTitle,
                const std::vector<FileDialogFilter>& Filters,
                const std::string& InitialFile,
                const BoostPath& InitialDirectory,
                bool PromptForOverwrite
                )
{
	BoostPath FileToSave;
    OSStatus status;
    NavDialogRef SaveFileDialog;

    NavDialogCreationOptions dialogOptions;

    //Default options for dialog
    status = NavGetDefaultDialogCreationOptions(&dialogOptions);
    if(status != noErr)
    {
        SWARNING << "CarbonWindow::saveFileDialog: NavGetDefaultDialogCreationOptions Error: "<< status << std::endl;
	    return FileToSave;
    }

   // Make the window app-wide modal
   dialogOptions.modality = kWindowModalityAppModal;
   dialogOptions.parentWindow = _WindowRef;
   dialogOptions.optionFlags = kNavDefaultNavDlogOptions;
   dialogOptions.windowTitle = CFStringCreateWithCString(NULL, DialogTitle.c_str(), DialogTitle.size());
   if(PromptForOverwrite)
   {
       dialogOptions.optionFlags = dialogOptions.optionFlags ^ kNavDontConfirmReplacement;
   }
   else
   {
       dialogOptions.optionFlags = dialogOptions.optionFlags | kNavDontConfirmReplacement;
   }
   
   status = NavCreatePutFileDialog (
       &dialogOptions,
       kUnknownType,
       kUnknownType,
       NULL,
       NULL,
       &SaveFileDialog);
    
    if(status != noErr)
    {
        NavDialogDispose(SaveFileDialog);
        SWARNING << "CarbonWindow::saveFileDialog: NavCreateGetFileDialog Error: "<< status << std::endl;
	    return FileToSave;
    }
    
    // Image Browser can open files with the ".imagebrowser" extension
    CFMutableArrayRef identifiers = CFArrayCreateMutable( kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks );
    if(identifiers == NULL)
    {
        NavDialogDispose(SaveFileDialog);
        SWARNING << "CarbonWindow::saveFileDialog: CFArrayCreateMutable Error: NULL " <<  std::endl;
	    return FileToSave;
    }

    //Initial directory 
    FSSpec spec;
    status = PathToFSSpec(InitialDirectory.string().c_str(), spec);
    if(status != noErr)
    {
        NavDialogDispose(SaveFileDialog);
        SWARNING << "CarbonWindow::saveFileDialog: PathToFSSpec Error: "<< status << std::endl;
	    return FileToSave;
    }
    AEDesc DefaultLocationAEDesc;
    status = AECreateDesc(typeFSS, &spec, sizeof(FSSpec), &DefaultLocationAEDesc);
    if(status != noErr)
    {
        NavDialogDispose(SaveFileDialog);
        SWARNING << "CarbonWindow::saveFileDialog: AECreateDesc Error: "<< status << std::endl;
	    return FileToSave;
    }
    status = NavCustomControl( SaveFileDialog, kNavCtlSetLocation, &DefaultLocationAEDesc );
    if(status != noErr)
    {
        NavDialogDispose(SaveFileDialog);
        SWARNING << "CarbonWindow::saveFileDialog: NavCustomControl Error: "<< status << std::endl;
	    return FileToSave;
    }
    AEDisposeDesc(&DefaultLocationAEDesc);
    
    //Initial filename
    status = NavDialogSetSaveFileName(SaveFileDialog,CFStringCreateWithCString(NULL, InitialFile.c_str(), InitialFile.size()));
    if(status != noErr)
    {
        NavDialogDispose(SaveFileDialog);
        SWARNING << "CarbonWindow::saveFileDialog: NavDialogSetSaveFileName Error: "<< status << std::endl;
	    return FileToSave;
    }


    //Filters
    for(std::vector<FileDialogFilter>::const_iterator Itor(Filters.begin()) ; Itor != Filters.end(); ++Itor)
    {
        // create the image browser UTI conforming to "public.data" because it's a data file rather than a bundle 
        if(Itor->getFilter().compare("*") != 0)
        {
            CFStringRef FilterCFString = UTTypeCreatePreferredIdentifierForTag( kUTTagClassFilenameExtension, CFStringCreateWithCString(NULL, Itor->getFilter().c_str(), Itor->getFilter().size()),kUTTypeData );

            if(FilterCFString == NULL)
            {
                NavDialogDispose(SaveFileDialog);
                SWARNING << "CarbonWindow::saveFileDialog: UTTypeCreatePreferredIdentifierForTag Error: NULL " <<  std::endl;
                return FileToSave;
            }
            //Itor->getName();
            CFArrayAppendValue( identifiers, FilterCFString );
        }
    }
    
    // filter by UTI
    //status = NavDialogSetFilterTypeIdentifiers( SaveFileDialog, identifiers );
    //if(status != noErr)
    //{
        //NavDialogDispose(SaveFileDialog);
        //SWARNING << "CarbonWindow::saveFileDialog: NavDialogRun Error: "<< status << std::endl;
        //return FileToSave;
    //}
 
    //Open the dialog
    status = NavDialogRun(SaveFileDialog);
    if(status != noErr)
    {
        NavDialogDispose(SaveFileDialog);
        SWARNING << "CarbonWindow::saveFileDialog: NavDialogRun Error: "<< status << std::endl;
        return FileToSave;
    }

    //Get Reply
    NavReplyRecord replyRecord;
    status = NavDialogGetReply(SaveFileDialog, &replyRecord);
    NavDialogDispose(SaveFileDialog);
    //If user canceled then return empty
    if (!replyRecord.validRecord ||  status == userCanceledErr )
    {
        NavDisposeReply(&replyRecord);
        return FileToSave;
    }
    
    //Other Errors
    if(status != noErr)
    {
        NavDisposeReply(&replyRecord);
        SWARNING << "CarbonWindow::saveFileDialog: NavDialogGetReply Error: "<< status << std::endl;
        return FileToSave;
    }

    //Path to save file to
    long count = 0;
    if ( AECountItems(&replyRecord.selection, &count) != noErr ) 
    {
        NavDisposeReply(&replyRecord);
        SWARNING << "CarbonWindow::saveFileDialog: AECountItems Error: "<< status << std::endl;
        return FileToSave;
    }

    // Get Path
    if (count==1)
    {
        FSRef parentDirectory;
        if (AEGetNthPtr(&(replyRecord.selection), 1, typeFSRef, NULL, NULL, &parentDirectory, sizeof(FSRef), NULL)== noErr)
        {
            UInt8 FilePath[2048];
            if( FSRefMakePath (&parentDirectory, FilePath, sizeof(FilePath)) == noErr)
            {
                FileToSave = BoostPath(reinterpret_cast<Char8*>(FilePath));
            }
        }
    }
    NavDisposeReply(&replyRecord);

    //Filename
    CFStringRef SaveFileCFString = NavDialogGetSaveFileName(SaveFileDialog);
	char FileName[1024];
	CFStringGetCString(SaveFileCFString, FileName, sizeof(FileName), 0);
    FileToSave                   = FileToSave / BoostPath(FileName);

    return FileToSave;
}

CGKeyCode CarbonWindow::getKeyCode(KeyEventDetails::Key TheKey)
{
    switch(TheKey)
    {
	////Alphabet
    case KeyEventDetails::KEY_A:
      return KeyA;
      break;
    case KeyEventDetails::KEY_B:
      return KeyB;
      break;
    case KeyEventDetails::KEY_C:
      return KeyC;
      break;
    case KeyEventDetails::KEY_D:
      return KeyD;
      break;
    case KeyEventDetails::KEY_E:
      return KeyE;
      break;
    case KeyEventDetails::KEY_F:
      return KeyF;
      break;
    case KeyEventDetails::KEY_G:
      return KeyG;
      break;
    case KeyEventDetails::KEY_H:
      return KeyH;
      break;
    case KeyEventDetails::KEY_I:
      return KeyI;
      break;
    case KeyEventDetails::KEY_J:
      return KeyJ;
      break;
    case KeyEventDetails::KEY_K:
      return KeyK;
      break;
    case KeyEventDetails::KEY_L:
      return KeyL;
      break;
    case KeyEventDetails::KEY_M:
      return KeyM;
      break;
    case KeyEventDetails::KEY_N:
      return KeyN;
      break;
    case KeyEventDetails::KEY_O:
      return KeyO;
      break;
    case KeyEventDetails::KEY_P:
      return KeyP;
      break;
    case KeyEventDetails::KEY_Q:
      return KeyQ;
      break;
    case KeyEventDetails::KEY_R:
      return KeyR;
      break;
    case KeyEventDetails::KEY_S:
      return KeyS;
      break;
    case KeyEventDetails::KEY_T:
      return KeyT;
      break;
    case KeyEventDetails::KEY_U:
      return KeyU;
      break;
    case KeyEventDetails::KEY_V:
      return KeyV;
      break;
    case KeyEventDetails::KEY_W:
      return KeyW;
      break;
    case KeyEventDetails::KEY_X:
      return KeyX;
      break;
    case KeyEventDetails::KEY_Y:
      return KeyY;
      break;
    case KeyEventDetails::KEY_Z:
      return KeyZ;
      break;
    //Numbers
    case KeyEventDetails::KEY_0:
      return Key0;
      break;
    case KeyEventDetails::KEY_1:
      return Key1;
      break;
    case KeyEventDetails::KEY_2:
      return Key2;
      break;
    case KeyEventDetails::KEY_3:
      return Key3;
      break;
    case KeyEventDetails::KEY_4:
      return Key4;
      break;
    case KeyEventDetails::KEY_5:
      return Key5;
      break;
    case KeyEventDetails::KEY_6:
      return Key6;
      break;
    case KeyEventDetails::KEY_7:
      return Key7;
      break;
    case KeyEventDetails::KEY_8:
      return Key8;
      break;
    case KeyEventDetails::KEY_9:
      return Key9;
      break;

    //Other
    case KeyEventDetails::KEY_MINUS:
      return KeyMinus;
      break;
    case KeyEventDetails::KEY_EQUALS:
      return KeyEquals;
      break;
    case KeyEventDetails::KEY_BACK_QUOTE:
      return KeyBackquote;
      break;
    case KeyEventDetails::KEY_TAB:
      return KeyTab;
      break;
    case KeyEventDetails::KEY_SPACE:
      return KeySpacebar;
      break;
    case KeyEventDetails::KEY_OPEN_BRACKET:
      return KeyLeftBracket;
      break;
    case KeyEventDetails::KEY_CLOSE_BRACKET:
      return KeyRightBracket;
      break;
    case KeyEventDetails::KEY_SEMICOLON:
      return KeySemicolon;
      break;
    case KeyEventDetails::KEY_COMMA:
      return KeyComma;
      break;
    case KeyEventDetails::KEY_PERIOD:
      return KeyPeriod;
      break;
    case KeyEventDetails::KEY_BACK_SLASH:
      return KeyBackslash;
      break;
    case KeyEventDetails::KEY_APOSTROPHE:
      return KeyApostrophe;
      break;
    case KeyEventDetails::KEY_SLASH:
      return KeySlash;
      break;

    //Non-visible
    case KeyEventDetails::KEY_ESCAPE:
      return KeyEscape;
      break;
    case KeyEventDetails::KEY_SHIFT:
      return KeyShift;
      break;
    case KeyEventDetails::KEY_CONTROL:
      return KeyControl;
      break;
    case KeyEventDetails::KEY_META:
      return KeyMacCommand;
      break;
    case KeyEventDetails::KEY_ALT:
      return KeyMenu;
      break;
    case KeyEventDetails::KEY_ENTER:
      return KeyReturn;
      break;
    //case KeyEventDetails::KEY_CANCEL:
      //return KeyCancel;
    //  break;
    case KeyEventDetails::KEY_CLEAR:
      return KeyClear;
      break;
    //case KeyEventDetails::KEY_PAUSE:
      //return KeyPause;
    //  break;
    case KeyEventDetails::KEY_CAPS_LOCK:
      return KeyCapsLock;
      break;
    case KeyEventDetails::KEY_END:
      return KeyEnd;
      break;
    case KeyEventDetails::KEY_HOME:
      return KeyHome;
      break;
    case KeyEventDetails::KEY_PAGE_UP:
      return KeyPageUp;
      break;
    case KeyEventDetails::KEY_PAGE_DOWN:
      return KeyPageDown;
      break;
    case KeyEventDetails::KEY_UP:
      return KeyUp;
      break;
    case KeyEventDetails::KEY_DOWN:
      return KeyDown;
      break;
    case KeyEventDetails::KEY_LEFT:
      return KeyLeft;
      break;
    case KeyEventDetails::KEY_RIGHT:
      return KeyRight;
      break;
    //case KeyEventDetails::KEY_PRINTSCREEN:
      //return KeySNAPSHOT;
    //  break;
    //case KeyEventDetails::KEY_INSERT:
      //return KeyInsert;
    //  break;
    case KeyEventDetails::KEY_DELETE:
      return KeyDelete;
      break;
    case KeyEventDetails::KEY_HELP:
      return KeyHelp;
      break;
    //case KeyEventDetails::KEY_NUM_LOCK:
      //return KeyNUMLOCK;
    //  break;
    //case KeyEventDetails::KEY_SCROLL_LOCK:
      //return KeySCROLL;
    //  break;
    case KeyEventDetails::KEY_BACK_SPACE:
      return KeyBackspace;
      break;

    //Function Keys
    case KeyEventDetails::KEY_F1:
      return KeyF1;
      break;
    case KeyEventDetails::KEY_F2:
      return KeyF2;
      break;
    case KeyEventDetails::KEY_F3:
      return KeyF3;
      break;
    case KeyEventDetails::KEY_F4:
      return KeyF4;
      break;
    case KeyEventDetails::KEY_F5:
      return KeyF5;
      break;
    case KeyEventDetails::KEY_F6:
      return KeyF6;
      break;
    case KeyEventDetails::KEY_F7:
      return KeyF7;
      break;
    case KeyEventDetails::KEY_F8:
      return KeyF8;
      break;
    case KeyEventDetails::KEY_F9:
      return KeyF9;
      break;
    case KeyEventDetails::KEY_F10:
      return KeyF10;
      break;
    case KeyEventDetails::KEY_F11:
      return KeyF11;
      break;
    case KeyEventDetails::KEY_F12:
      return KeyF12;
      break;
      
    //Numpad Keys
    case KeyEventDetails::KEY_NUMPAD_0:
      return KeyNum0;
      break;
    case KeyEventDetails::KEY_NUMPAD_1:
      return KeyNum1;
      break;
    case KeyEventDetails::KEY_NUMPAD_2:
      return KeyNum2;
      break;
    case KeyEventDetails::KEY_NUMPAD_3:
      return KeyNum3;
      break;
    case KeyEventDetails::KEY_NUMPAD_4:
      return KeyNum4;
      break;
    case KeyEventDetails::KEY_NUMPAD_5:
      return KeyNum5;
      break;
    case KeyEventDetails::KEY_NUMPAD_6:
      return KeyNum6;
      break;
    case KeyEventDetails::KEY_NUMPAD_7:
      return KeyNum7;
      break;
    case KeyEventDetails::KEY_NUMPAD_8:
      return KeyNum8;
      break;
    case KeyEventDetails::KEY_NUMPAD_9:
      return KeyNum9;
      break;
    case KeyEventDetails::KEY_MULTIPLY:
      return KeyMultiply;
      break;
    case KeyEventDetails::KEY_ADD:
      return KeyAdd;
      break;
    case KeyEventDetails::KEY_SUBTRACT:
      return KeySubtract;
      break;
    case KeyEventDetails::KEY_DIVIDE:
      return KeyDivide;
      break;
    case KeyEventDetails::KEY_DECIMAL:
      return KeyDecimal;
      break;
    case KeyEventDetails::KEY_NUMPAD_EQUALS:
      return KeyNumEqual;
      break;
	
    case KeyEventDetails::KEY_UNKNOWN:
	default:
	  return 0;
	}
}

KeyEventDetails::KeyState CarbonWindow::getKeyState(KeyEventDetails::Key TheKey) const
{
    if(CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState,getKeyCode(TheKey)))
	{
        return KeyEventDetails::KEY_STATE_DOWN;
	}
	else
	{
		return KeyEventDetails::KEY_STATE_UP;
	}
}

Window* CarbonWindow::initWindow(void)
{
    OSStatus ErrCode;

	WindowUnrecPtr MyWindow = Inherited::initWindow();
    
    attachWindow();
    
    EventTypeSpec eventList[] =
    {
		{ kEventClassKeyboard, kEventRawKeyDown},
        { kEventClassKeyboard, kEventRawKeyRepeat},
        { kEventClassKeyboard, kEventRawKeyUp},
        { kEventClassKeyboard, kEventRawKeyModifiersChanged},
        { kEventClassMouse, kEventMouseDown },
        { kEventClassMouse, kEventMouseUp },
        { kEventClassMouse, kEventMouseMoved },
        { kEventClassMouse, kEventMouseDragged },
        { kEventClassMouse, kEventMouseWheelMoved },
        //{ kEventClassWindow, kEventWindowActivate },
        //{ kEventClassWindow, kEventWindowDeactivate },
        { kEventClassWindow, kEventWindowCollapsed },
        { kEventClassWindow, kEventWindowExpanded },
        { kEventClassWindow, kEventWindowClose },
        { kEventClassWindow, kEventWindowClosed },
        { kEventClassWindow, kEventWindowDrawContent },
        { kEventClassWindow, kEventWindowBoundsChanged },
        { kEventClassWindow, kEventAppActivated },
        { kEventClassWindow, kEventAppDeactivated },
    };
    if(getFullscreen())
    {
        ErrCode = InstallApplicationEventHandler(_EventHandlerUPP,
                                                 GetEventTypeCount(eventList),
                                                 eventList,
                                                 this,
                                                 0);
    }
    else
    {
        ErrCode = InstallWindowEventHandler(_WindowRef,
                                            _EventHandlerUPP,
                                            GetEventTypeCount(eventList),
                                            eventList,
                                            this,
                                            0);
    }
    if(ErrCode != noErr){SFATAL << "Error calling InstallWindowEventHandler(), Error code: " << ErrCode << std::endl;}

    // Initialize OpenGL
    GLint attribs[] = {
        AGL_RGBA,
        AGL_DOUBLEBUFFER,
        //AGL_DEPTH_SIZE,   16,
        AGL_DEPTH_SIZE,   24,
        AGL_STENCIL_SIZE,  8,
        AGL_ACCELERATED,
        AGL_NO_RECOVERY,
        AGL_NONE
    };
    AGLPixelFormat pixelFormat = aglChoosePixelFormat(NULL, 0, attribs);
    if (pixelFormat == 0)
    {
        SFATAL << "Cannot choose pixel format" << std::endl;
    }
    _Context = aglCreateContext(pixelFormat, 0);
    aglDestroyPixelFormat(pixelFormat);
    if (_Context == 0)
    {
        SFATAL << "Cannot create context" << std::endl;
    }

    if(getFullscreen())
    {
        aglSetCurrentContext(_Context);
        aglSetFullScreen(_Context,0,0,0,0);
        GLint displayCaps [3];
        aglGetInteger (_Context, AGL_FULLSCREEN, displayCaps);
        resize(displayCaps[0],displayCaps[1]);
    }
    else
    {
        aglSetWindowRef(_Context,_WindowRef);
    }
    setContext(_Context);
	
    return MyWindow;
}


OSStatus CarbonWindow::internalEventHandler(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    ::UInt32 eventClass = GetEventClass(event);
    switch (eventClass)
    {
    // Mouse events
    case kEventClassMouse:
		return handleMouseEvent(nextHandler, event, userData);

    // Key press events
    case kEventClassKeyboard:
		return handleKeyEvent(nextHandler, event, userData);

    // Window events
    case kEventClassWindow:
		return handleWindowEvent(nextHandler, event, userData);

    //App events
    case kEventClassApplication:
		return handleAppEvent(nextHandler, event, userData);

    default:
        return eventNotHandledErr;
    }   
    return noErr;
}


OSStatus CarbonWindow::handleMouseEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    OSStatus err;

    if(!getFullscreen())
    {
        // Get the window
        WindowRef window;
        err = GetEventParameter(event, kEventParamWindowRef, typeWindowRef, 0, sizeof(window), 0, &window);
        if (err != noErr)
        {
            return err;
        }

        SetPortWindowPort(window);
    }

    // Get the location of the cursor
    ::HIPoint location;
    if(getFullscreen())
    {
        err = GetEventParameter(event, kEventParamMouseLocation, typeHIPoint, 0, sizeof(location), 0, &location);
    }
    else
    {
        err = GetEventParameter(event, kEventParamWindowMouseLocation, typeHIPoint, 0, sizeof(location), 0, &location);
        location.y -= 22.0f;
    }
    if (err != noErr)
    {
        return err;
    }

    //Check that the mouse is withing the content area
    if(!getFullscreen())
    {
        WindowPartCode part;
        GetEventParameter (event, kEventParamWindowPartCode, typeWindowPartCode,
                NULL, sizeof(part), NULL, &part);

        if(part != inContent)
        {
            return eventNotHandledErr;
        }
    }

    // Handle the different kinds of events
    ::UInt32 eventKind = GetEventKind(event);
    //Get Mouse Delta
    Vec2f MouseDelta;
    switch(eventKind)
    {
        case kEventMouseMoved:
        case kEventMouseDragged:
            {
                ::HIPoint delta;
                err = GetEventParameter(event, kEventParamMouseDelta, typeHIPoint, 0, sizeof(delta), 0, &delta);
                if (err != noErr)
                {
                    return err;
                }
                MouseDelta.setValues(delta.x,delta.y);
            }
            break;
    }

    //Get Mouse Button
    MouseEventDetails::MouseButton TheMouseButton;
    switch(eventKind)
    {
        case kEventMouseDown:
        case kEventMouseUp:
        case kEventMouseDragged:
            {
                // Get the mouse button
                EventMouseButton mouseButton;
                err = GetEventParameter(event, kEventParamMouseButton, typeMouseButton, 0, sizeof(mouseButton), 0, &mouseButton);
                if (err != noErr)
                {
                    return err;
                }

                switch (mouseButton)
                {
                    case kEventMouseButtonPrimary: // left button
                        TheMouseButton = MouseEventDetails::BUTTON1;
                        break;
                    case kEventMouseButtonSecondary: // right button
                        TheMouseButton = MouseEventDetails::BUTTON3;
                        break;
                    case kEventMouseButtonTertiary: // middle button
                        TheMouseButton = MouseEventDetails::BUTTON2;
                        break;
                    case 4:
                        TheMouseButton = MouseEventDetails::BUTTON4;
                        break;
                    case 5:
                        TheMouseButton = MouseEventDetails::BUTTON5;
                        break;
                    case 6:
                        TheMouseButton = MouseEventDetails::BUTTON6;
                        break;
                    case 7:
                        TheMouseButton = MouseEventDetails::BUTTON7;
                        break;
                    case 8:
                        TheMouseButton = MouseEventDetails::BUTTON8;
                        break;
                    case 9:
                        TheMouseButton = MouseEventDetails::BUTTON9;
                        break;
                    case 10:
                        TheMouseButton = MouseEventDetails::BUTTON10;
                        break;
                    default:
                        TheMouseButton = MouseEventDetails::NO_BUTTON;
                        break;
                }
                break;
            }
    }
    switch (eventKind)
    {
        // mouse button pressed
        case kEventMouseDown:
            produceMousePressed(TheMouseButton, Pnt2f(location.x, location.y));
            break;


            // mouse button released
        case kEventMouseUp:
            produceMouseReleased(TheMouseButton, Pnt2f(location.x, location.y));
            break;

            //Mouse Moved
        case kEventMouseMoved:
            produceMouseMoved(Pnt2f(location.x, location.y), MouseDelta);
            break;

            // mouse moved while a button is pressed
        case kEventMouseDragged:
            produceMouseMoved(Pnt2f(location.x, location.y), MouseDelta);
            produceMouseDragged(TheMouseButton, Pnt2f(location.x, location.y), MouseDelta);
            break;

            // mouse wheel moved
        case kEventMouseWheelMoved:
            {
                EventMouseWheelAxis axis;
                SInt32 delta;

                err = GetEventParameter( event, kEventParamMouseWheelAxis, 
                        typeMouseWheelAxis, NULL, sizeof(axis), NULL, &axis );
                if (err != noErr)
                    return err;

                err = GetEventParameter( event, kEventParamMouseWheelDelta, 
                        typeLongInteger, NULL, sizeof(delta), NULL, &delta );
                if (err != noErr)
                    return err;

                if ( axis == kEventMouseWheelAxisY )
                {
                    produceMouseWheelMoved(delta, Pnt2f(location.x, location.y));
                }
            }
            break;

        default:
            SWARNING << "handleMouseEvent event not handled" << std::endl;
            break;

    }

    // We have to return eventNotHandledErr, otherwise the system is
    // not able to operate the menu and the window border
    return eventNotHandledErr;
}

OSStatus CarbonWindow::handleWindowEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    OSStatus err;

    // Get the window
    WindowRef window;
    err = GetEventParameter(event, kEventParamDirectObject, typeWindowRef, 0, sizeof(window), 0, &window);
    if (err != noErr)
        return err;

    // Handle the different kinds of events
    ::UInt32 eventKind = GetEventKind(event);
    switch (eventKind)
    {
    case kEventWindowClosed:
            aglSetCurrentContext( NULL );
            aglDestroyContext(_Context);
            produceWindowClosing();
            DisposeEventHandlerUPP(_EventHandlerUPP);
            produceWindowClosed();
            _IsWindowOpen = false;
            return noErr;
		  break;
    
	 // Quit the application when the user closes the window
    case kEventWindowClose:
          disposeWindow();
        return noErr;
		  break;

    case kEventWindowCollapsed:
		  produceWindowIconified();
        return noErr;
		  break;

    case kEventWindowExpanded:
		  produceWindowDeiconified();
        return noErr;
		  break;

    // Draw the contents of the window
    case kEventWindowDrawContent:
        internalDraw();
        return noErr;

    case kEventWindowBoundsChanged:
        {
            // Update the GL context
            aglUpdateContext(getContext());

            // Find out if we have a move or a resize situation
            ::UInt32 attributes;
            GetEventParameter(event, kEventParamAttributes, typeUInt32, 0, sizeof(attributes), 0, &attributes);

            if ((attributes & kWindowBoundsChangeSizeChanged) != 0)
            {
                GLsizei width, height;
                if(getFullscreen())
                {
                    aglSetCurrentContext(_Context);
                    aglSetFullScreen(_Context,0,0,0,0);
                    GLint displayCaps [3];
                    aglGetInteger (_Context, AGL_FULLSCREEN, displayCaps);
                    width = displayCaps[0];
                    height = displayCaps[1];
                }
                else
                {
                    // Get the new bounds of the window
                    Rect bounds;
                    GetEventParameter(event, kEventParamCurrentBounds, typeQDRectangle, 0, sizeof(Rect), 0, &bounds);

                    // Resize the OpenSG Window
                    width = bounds.right - bounds.left;
                    height = bounds.bottom - bounds.top;
                }
                resize(width, height );
                internalReshape(Vec2f(width, height));
            }

            return noErr;
        }

    default:
        return eventNotHandledErr;
    }
}

OSStatus CarbonWindow::handleAppEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    OSStatus err;

    // Get the window
    WindowRef window;
    err = GetEventParameter(event, kEventParamDirectObject, typeWindowRef, 0, sizeof(window), 0, &window);
    if (err != noErr)
        return err;

    // Handle the different kinds of events
    ::UInt32 eventKind = GetEventKind(event);
    switch (eventKind)
    {
    case kEventAppActivated:
		  produceWindowActivated();
        return noErr;
		  break;

    case kEventAppDeactivated:
		  produceWindowDeactivated();
        return noErr;
		  break;
	 }
}

OSStatus CarbonWindow::handleKeyEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    OSStatus err;

	::UInt32 key;
	err = GetEventParameter(event, kEventParamKeyCode, typeUInt32, 0, sizeof(key), 0, &key);
	if (err != noErr)
		return err;
	
	
	::UInt32 keyModifiers;
	err = GetEventParameter(event, kEventParamKeyModifiers, typeUInt32, 0, sizeof(keyModifiers), 0, &keyModifiers);
	if (err != noErr)
		return err;
		
    ::UInt32 eventKind = GetEventKind(event);
	switch(eventKind)
	{
		case kEventRawKeyDown:
			produceKeyPressed(determineKey(key),determineKeyModifiers(keyModifiers));				
			break;
		case kEventRawKeyUp:
			produceKeyReleased(determineKey(key),determineKeyModifiers(keyModifiers));
			break;
		case kEventRawKeyRepeat:
			produceKeyPressed(determineKey(key),determineKeyModifiers(keyModifiers));
			break;
		case kEventRawKeyModifiersChanged:
			if((determineKeyModifiers(keyModifiers) & KeyEventDetails::KEY_MODIFIER_META) &&
			   !(_modifierKeyState & KeyEventDetails::KEY_MODIFIER_META))
			{
				//Meta key pressed
				produceKeyPressed(KeyEventDetails::KEY_META, determineKeyModifiers(keyModifiers));
			}
			if(!(determineKeyModifiers(keyModifiers) & KeyEventDetails::KEY_MODIFIER_META) &&
			   (_modifierKeyState & KeyEventDetails::KEY_MODIFIER_META))
			{
				//Meta key released
				produceKeyReleased(KeyEventDetails::KEY_META, determineKeyModifiers(keyModifiers));
			}
			if((determineKeyModifiers(keyModifiers) & KeyEventDetails::KEY_MODIFIER_ALT) &&
			   !(_modifierKeyState & KeyEventDetails::KEY_MODIFIER_ALT))
			{
				//Alt key pressed
				produceKeyPressed(KeyEventDetails::KEY_ALT, determineKeyModifiers(keyModifiers));
			}
			if(!(determineKeyModifiers(keyModifiers) & KeyEventDetails::KEY_MODIFIER_ALT) &&
			   (_modifierKeyState & KeyEventDetails::KEY_MODIFIER_ALT))
			{
				//Alt key released
				produceKeyReleased(KeyEventDetails::KEY_ALT, determineKeyModifiers(keyModifiers));
			}
			if((determineKeyModifiers(keyModifiers) & KeyEventDetails::KEY_MODIFIER_CONTROL) &&
			   !(_modifierKeyState & KeyEventDetails::KEY_MODIFIER_CONTROL))
			{
				//Control key pressed
				produceKeyPressed(KeyEventDetails::KEY_CONTROL, determineKeyModifiers(keyModifiers));
			}
			if(!(determineKeyModifiers(keyModifiers) & KeyEventDetails::KEY_MODIFIER_CONTROL) &&
			   (_modifierKeyState & KeyEventDetails::KEY_MODIFIER_CONTROL))
			{
				//Control key released
				produceKeyReleased(KeyEventDetails::KEY_CONTROL, determineKeyModifiers(keyModifiers));
			}
			_modifierKeyState = determineKeyModifiers(keyModifiers);
			break;
		default:
			break;
	}

    return noErr;
}

UInt32 CarbonWindow::determineKeyModifiers(::UInt32 keyModifiers)
{
   UInt32 Modifiers = 0;

   if(keyModifiers & shiftKey)
   {
      Modifiers |= KeyEventDetails::KEY_MODIFIER_SHIFT;
   }
   if(keyModifiers & controlKey)
   {
      Modifiers |= KeyEventDetails::KEY_MODIFIER_CONTROL;
   }
   if(keyModifiers & optionKey)
   {
      Modifiers |= KeyEventDetails::KEY_MODIFIER_ALT;
   }
   if(keyModifiers & alphaLock)
   {
      Modifiers |= KeyEventDetails::KEY_MODIFIER_CAPS_LOCK;
   }
   if(keyModifiers & cmdKey)
   {
      Modifiers |= KeyEventDetails::KEY_MODIFIER_META;
   }
   //if(GetKeyState(VK_NUMLOCK)>0)
   //{
   //   Modifiers |= KeyEventDetails::KEY_MODIFIER_NUM_LOCK;
   //}
   //if(GetKeyState(VK_SCROLL)>0)
   //{
   //   Modifiers |= KeyEventDetails::KEY_MODIFIER_SCROLL_LOCK;
   //}
   return Modifiers;
}

KeyEventDetails::Key CarbonWindow::determineKey(::UInt32 key)
{
    KeyEventDetails::Key OSGKey;
	switch(key)
	{
	//Alphabet
	case KeyA:
	  OSGKey = KeyEventDetails::KEY_A;
	  break;
	case KeyB:
	  OSGKey = KeyEventDetails::KEY_B;
	  break;
	case KeyC:
	  OSGKey = KeyEventDetails::KEY_C;
	  break;
	case KeyD:
	  OSGKey = KeyEventDetails::KEY_D;
	  break;
	case KeyE:
	  OSGKey = KeyEventDetails::KEY_E;
	  break;
	case KeyF:
	  OSGKey = KeyEventDetails::KEY_F;
	  break;
	case KeyG:
	  OSGKey = KeyEventDetails::KEY_G;
	  break;
	case KeyH:
	  OSGKey = KeyEventDetails::KEY_H;
	  break;
	case KeyI:
	  OSGKey = KeyEventDetails::KEY_I;
	  break;
	case KeyJ:
	  OSGKey = KeyEventDetails::KEY_J;
	  break;
	case KeyK:
	  OSGKey = KeyEventDetails::KEY_K;
	  break;
	case KeyL:
	  OSGKey = KeyEventDetails::KEY_L;
	  break;
	case KeyM:
	  OSGKey = KeyEventDetails::KEY_M;
	  break;
	case KeyN:
	  OSGKey = KeyEventDetails::KEY_N;
	  break;
	case KeyO:
	  OSGKey = KeyEventDetails::KEY_O;
	  break;
	case KeyP:
	  OSGKey = KeyEventDetails::KEY_P;
	  break;
	case KeyQ:
	  OSGKey = KeyEventDetails::KEY_Q;
	  break;
	case KeyR:
	  OSGKey = KeyEventDetails::KEY_R;
	  break;
	case KeyS:
	  OSGKey = KeyEventDetails::KEY_S;
	  break;
	case KeyT:
	  OSGKey = KeyEventDetails::KEY_T;
	  break;
	case KeyU:
	  OSGKey = KeyEventDetails::KEY_U;
	  break;
	case KeyV:
	  OSGKey = KeyEventDetails::KEY_V;
	  break;
	case KeyW:
	  OSGKey = KeyEventDetails::KEY_W;
	  break;
	case KeyX:
	  OSGKey = KeyEventDetails::KEY_X;
	  break;
	case KeyY:
	  OSGKey = KeyEventDetails::KEY_Y;
	  break;
	case KeyZ:
	  OSGKey = KeyEventDetails::KEY_Z;
	  break;
	//Numbers
	case Key0:
	  OSGKey = KeyEventDetails::KEY_0;
	  break;
	case Key1:
	  OSGKey = KeyEventDetails::KEY_1;
	  break;
	case Key2:
	  OSGKey = KeyEventDetails::KEY_2;
	  break;
	case Key3:
	  OSGKey = KeyEventDetails::KEY_3;
	  break;
	case Key4:
	  OSGKey = KeyEventDetails::KEY_4;
	  break;
	case Key5:
	  OSGKey = KeyEventDetails::KEY_5;
	  break;
	case Key6:
	  OSGKey = KeyEventDetails::KEY_6;
	  break;
	case Key7:
	  OSGKey = KeyEventDetails::KEY_7;
	  break;
	case Key8:
	  OSGKey = KeyEventDetails::KEY_8;
	  break;
	case Key9:
	  OSGKey = KeyEventDetails::KEY_9;
	  break;

	//Other
	case KeyMinus:
	  OSGKey = KeyEventDetails::KEY_MINUS;
	  break;
	case KeyEquals:
	  OSGKey = KeyEventDetails::KEY_EQUALS;
	  break;
	case KeyBackquote:
	  OSGKey = KeyEventDetails::KEY_BACK_QUOTE;
	  break;
	case KeyTab:
	  OSGKey = KeyEventDetails::KEY_TAB;
	  break;
	case KeySpacebar:
	  OSGKey = KeyEventDetails::KEY_SPACE;
	  break;
	case KeyLeftBracket:
	  OSGKey = KeyEventDetails::KEY_OPEN_BRACKET;
	  break;
	case KeyRightBracket:
	  OSGKey = KeyEventDetails::KEY_CLOSE_BRACKET;
	  break;
	case KeySemicolon:
	  OSGKey = KeyEventDetails::KEY_SEMICOLON;
	  break;
	case KeyComma:
	  OSGKey = KeyEventDetails::KEY_COMMA;
	  break;
	case KeyPeriod:
	  OSGKey = KeyEventDetails::KEY_PERIOD;
	  break;
	case KeyBackslash:
	  OSGKey = KeyEventDetails::KEY_BACK_SLASH;
	  break;
	case KeyApostrophe:
	  OSGKey = KeyEventDetails::KEY_APOSTROPHE;
	  break;
	case KeySlash:
	  OSGKey = KeyEventDetails::KEY_SLASH;
	  break;

	//Non-visible
	case KeyEscape:
	  OSGKey = KeyEventDetails::KEY_ESCAPE;
	  break;
	case KeyShift:
	  OSGKey = KeyEventDetails::KEY_SHIFT;
	  break;
	case KeyControl:
	  OSGKey = KeyEventDetails::KEY_CONTROL;
	  break;
	case KeyMacCommand:
	  OSGKey = KeyEventDetails::KEY_META;
	  break;
	case KeyMenu:
	  OSGKey = KeyEventDetails::KEY_ALT;
	  break;
	case KeyReturn:
	  OSGKey = KeyEventDetails::KEY_ENTER;
	  break;
	//case KeyCancel:
	//  OSGKey = KeyEventDetails::KEY_CANCEL;
	//  break;
	case KeyClear:
	  OSGKey = KeyEventDetails::KEY_CLEAR;
	  break;
	//case KeyPause:
	//  OSGKey = KeyEventDetails::KEY_PAUSE;
	//  break;
	case KeyCapsLock:
	  OSGKey = KeyEventDetails::KEY_CAPS_LOCK;
	  break;
	case KeyEnd:
	  OSGKey = KeyEventDetails::KEY_END;
	  break;
	case KeyHome:
	  OSGKey = KeyEventDetails::KEY_HOME;
	  break;
	case KeyPageUp:
	  OSGKey = KeyEventDetails::KEY_PAGE_UP;
	  break;
	case KeyPageDown:
	  OSGKey = KeyEventDetails::KEY_PAGE_DOWN;
	  break;
	case KeyUp:
	  OSGKey = KeyEventDetails::KEY_UP;
	  break;
	case KeyDown:
	  OSGKey = KeyEventDetails::KEY_DOWN;
	  break;
	case KeyLeft:
	  OSGKey = KeyEventDetails::KEY_LEFT;
	  break;
	case KeyRight:
	  OSGKey = KeyEventDetails::KEY_RIGHT;
	  break;
	//case KeySNAPSHOT:
	//  OSGKey = KeyEventDetails::KEY_PRINTSCREEN;
	//  break;
	//case KeyInsert:
	//  OSGKey = KeyEventDetails::KEY_INSERT;
	//  break;
	case KeyDelete:
	  OSGKey = KeyEventDetails::KEY_DELETE;
	  break;
	case KeyHelp:
	  OSGKey = KeyEventDetails::KEY_HELP;
	  break;
	//case KeyNUMLOCK:
	//  OSGKey = KeyEventDetails::KEY_NUM_LOCK;
	//  break;
	//case KeySCROLL:
	//  OSGKey = KeyEventDetails::KEY_SCROLL_LOCK;
	//  break;
	case KeyBackspace:
	  OSGKey = KeyEventDetails::KEY_BACK_SPACE;
	  break;

	//Function Keys
	case KeyF1:
	  OSGKey = KeyEventDetails::KEY_F1;
	  break;
	case KeyF2:
	  OSGKey = KeyEventDetails::KEY_F2;
	  break;
	case KeyF3:
	  OSGKey = KeyEventDetails::KEY_F3;
	  break;
	case KeyF4:
	  OSGKey = KeyEventDetails::KEY_F4;
	  break;
	case KeyF5:
	  OSGKey = KeyEventDetails::KEY_F5;
	  break;
	case KeyF6:
	  OSGKey = KeyEventDetails::KEY_F6;
	  break;
	case KeyF7:
	  OSGKey = KeyEventDetails::KEY_F7;
	  break;
	case KeyF8:
	  OSGKey = KeyEventDetails::KEY_F8;
	  break;
	case KeyF9:
	  OSGKey = KeyEventDetails::KEY_F9;
	  break;
	case KeyF10:
	  OSGKey = KeyEventDetails::KEY_F10;
	  break;
	case KeyF11:
	  OSGKey = KeyEventDetails::KEY_F11;
	  break;
	case KeyF12:
	  OSGKey = KeyEventDetails::KEY_F12;
	  break;
	  
	//Numpad Keys
	case KeyNum0:
	  OSGKey = KeyEventDetails::KEY_NUMPAD_0;
	  break;
	case KeyNum1:
	  OSGKey = KeyEventDetails::KEY_NUMPAD_1;
	  break;
	case KeyNum2:
	  OSGKey = KeyEventDetails::KEY_NUMPAD_2;
	  break;
	case KeyNum3:
	  OSGKey = KeyEventDetails::KEY_NUMPAD_3;
	  break;
	case KeyNum4:
	  OSGKey = KeyEventDetails::KEY_NUMPAD_4;
	  break;
	case KeyNum5:
	  OSGKey = KeyEventDetails::KEY_NUMPAD_5;
	  break;
	case KeyNum6:
	  OSGKey = KeyEventDetails::KEY_NUMPAD_6;
	  break;
	case KeyNum7:
	  OSGKey = KeyEventDetails::KEY_NUMPAD_7;
	  break;
	case KeyNum8:
	  OSGKey = KeyEventDetails::KEY_NUMPAD_8;
	  break;
	case KeyNum9:
	  OSGKey = KeyEventDetails::KEY_NUMPAD_9;
	  break;
	case KeyMultiply:
	  OSGKey = KeyEventDetails::KEY_MULTIPLY;
	  break;
	case KeyAdd:
	  OSGKey = KeyEventDetails::KEY_ADD;
	  break;
	case KeySubtract:
	  OSGKey = KeyEventDetails::KEY_SUBTRACT;
	  break;
	case KeyDivide:
	  OSGKey = KeyEventDetails::KEY_DIVIDE;
	  break;
	case KeyDecimal:
	  OSGKey = KeyEventDetails::KEY_DECIMAL;
	  break;
	case KeyNumEqual:
	  OSGKey = KeyEventDetails::KEY_NUMPAD_EQUALS;
	  break;
	  
	default:
	  OSGKey = KeyEventDetails::KEY_UNKNOWN;
	  break;
	}
	return OSGKey;
}

void CarbonWindow::setPosition(Pnt2f Pos)
{
	::Rect GlobalBounds;
	GetWindowBounds(_WindowRef, kWindowStructureRgn, &GlobalBounds);
	
	Vec3s Size(GlobalBounds.right - GlobalBounds.left, GlobalBounds.bottom - GlobalBounds.top);
	GlobalBounds.left = Pos.x();
	GlobalBounds.top = Pos.y();
	GlobalBounds.right = GlobalBounds.left + Size.x();
	GlobalBounds.bottom = GlobalBounds.top + Size.y();
	SetWindowBounds(_WindowRef,kWindowStructureRgn, &GlobalBounds);
}

Pnt2f CarbonWindow::getPosition(void) const
{
	::Rect GlobalBounds;
	GetWindowBounds(_WindowRef, kWindowStructureRgn, &GlobalBounds);
    return Pnt2f(GlobalBounds.left, GlobalBounds.top);
}


void CarbonWindow::setSize(Vec2us Size)
{
	::Rect GlobalBounds;
	GetWindowBounds(_WindowRef, kWindowStructureRgn, &GlobalBounds);
	
	GlobalBounds.right = GlobalBounds.left + Size.x();
	GlobalBounds.bottom = GlobalBounds.top + Size.y();
	SetWindowBounds(_WindowRef,kWindowStructureRgn, &GlobalBounds);
}

Vec2f CarbonWindow::getSize(void) const
{
	::Rect GlobalBounds;
	GetWindowBounds(_WindowRef, kWindowStructureRgn, &GlobalBounds);
    return Vec2f(GlobalBounds.right - GlobalBounds.left, GlobalBounds.bottom - GlobalBounds.top);
}

void CarbonWindow::setFocused(bool Focused)
{
	ActivateWindow(_WindowRef, Focused);
}

bool CarbonWindow::getFocused(void) const
{
    return IsWindowActive(_WindowRef);
}

void CarbonWindow::setVisible(bool Visible)
{
	if(Visible)
	{
		ShowWindow(_WindowRef);
	}
	else
	{
		HideWindow(_WindowRef);
	}
}

bool CarbonWindow::getVisible(void) const
{
    return IsWindowVisible(_WindowRef);
}

void CarbonWindow::setIconify(bool Iconify)
{
	CollapseWindow(_WindowRef, Iconify);
}

bool CarbonWindow::getIconify(void) const
{
    return IsWindowCollapsed(_WindowRef);
}

void CarbonWindow::setFullscreen(bool Fullscreen)
{
    _IsFullscreen = Fullscreen;
	//if()
	//{
		//::Ptr      _OldScreenState;
          //assert(false && "Not Implemented");
		////CGCaptureAllDisplays();
		////BeginFullScreen(&_OldScreenState, NULL, 0, 0, &_WindowRef, NULL, 0);
	//}
	//else
	//{
		////EndFullScreen(NULL, NULL);
	//}
}

bool CarbonWindow::getFullscreen(void) const
{
    //return _IsFullscreen;
    return false;
}

void CarbonWindow::setTitle(const std::string& TitleText)
{
    SetWindowTitleWithCFString(_WindowRef, CFStringCreateWithCString(NULL, TitleText.c_str(), TitleText.size()));
}

std::string CarbonWindow::getTitle(void)
{
	CFStringRef AppleString;
	CopyWindowTitleAsCFString(_WindowRef, &AppleString);
	char value[1024];
	CFStringGetCString(AppleString, value, sizeof(value), 0);
	CFRelease(AppleString);
	
    return std::string(value);
}

void CarbonWindow::setRisizable(bool IsResizable)
{
	//_WindowRef->kWindowResizableAttribute = (1L << 4);

	
    //TODO: Implement
    assert(false && "Not Implemented");
	
}

bool CarbonWindow::getRisizable(void)
{
	WindowAttributes Attributes;
	GetWindowAttributes(_WindowRef, &Attributes);
	
    //TODO: Implement
	
    
    return (Attributes & kWindowResizableAttribute);
	
}

void CarbonWindow::setDrawBorder(bool DrawBorder)
{
    //TODO: Implement
    assert(false && "Not Implemented");
}

bool CarbonWindow::getDrawBorder(void)
{
    //TODO: Implement
    assert(false && "Not Implemented");
    return false;
}


void CarbonWindow::draw(void)
{
    internalDraw();
}

void CarbonWindow::update(void)
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

bool CarbonWindow::attachWindow(void)
{
    return true;
}

UInt32 CarbonWindow::getKeyModifiers(void) const
{
    return determineKeyModifiers(GetCurrentEventKeyModifiers());
}

Pnt2f CarbonWindow::getMousePosition(void) const
{
	::Point MousePositioon;
	GetGlobalMouse(&MousePositioon);
	
	//SetPortWindowPort(_WindowRef);

    return Pnt2f(MousePositioon.h, MousePositioon.v-22.0f) - Vec2f(getPosition());
}


std::string CarbonWindow::getClipboard(void) const
{
    OSStatus            err = noErr;
    std::string Result("");
    
    //Create clipboard reference
    PasteboardRef theClipboard;
    err = PasteboardCreate( kPasteboardClipboard, &theClipboard );
    if(err != noErr)
    {
        SWARNING << "CarbonWindow::getClipboard: PasteboardCreate Error: "<< err << std::endl;
        return Result;
    }

    PasteboardSyncFlags syncFlags;
    ItemCount           itemCount;

    syncFlags = PasteboardSynchronize( theClipboard );// 1
    if(syncFlags&kPasteboardModified)
    {
        SWARNING << "CarbonWindow::getClipboard: PasteboardSynchronize Error: badPasteboardSyncErr "<< badPasteboardSyncErr << std::endl;
        CFRelease (theClipboard);
        return Result;
    }

    err = PasteboardGetItemCount( theClipboard, &itemCount );// 2
    if(err != noErr)
    {
        SWARNING << "CarbonWindow::getClipboard: PasteboardGetItemCount Error: "<< err << std::endl;
        CFRelease (theClipboard);
        return Result;
    }

    for( UInt32 itemIndex = 1; itemIndex <= itemCount; itemIndex++ )
    {
        PasteboardItemID    itemID;
        CFArrayRef          flavorTypeArray;
        CFIndex             flavorCount;

        err = PasteboardGetItemIdentifier( theClipboard, itemIndex, &itemID );// 3
        if(err != noErr)
        {
            SWARNING << "carbonwindoweventproducer::getclipboard: PasteboardGetItemIdentifier error: "<< err << std::endl;
            CFRelease (theClipboard);
            return Result;
        }

        err = PasteboardCopyItemFlavors( theClipboard, itemID, &flavorTypeArray );// 4
        if(err != noErr)
        {
            SWARNING << "carbonwindoweventproducer::getclipboard: PasteboardCopyItemFlavors error: "<< err << std::endl;
            CFRelease (theClipboard);
            return Result;
        }

        flavorCount = CFArrayGetCount( flavorTypeArray );// 5

        for( CFIndex flavorIndex = 0; flavorIndex < flavorCount; flavorIndex++ )
        {
            CFStringRef             flavorType;
            CFDataRef               flavorData;
            CFIndex                 flavorDataSize;

            flavorType = (CFStringRef)CFArrayGetValueAtIndex( flavorTypeArray,// 6
                                                                 flavorIndex );
 

            if (UTTypeConformsTo(flavorType, CFSTR("public.utf8-plain-text")))// 7
            {
                err = PasteboardCopyItemFlavorData( theClipboard, itemID, // 8
                                                    flavorType, &flavorData );
                if(err != noErr)
                {
                    SWARNING << "CarbonWindow::getClipboard: PasteboardCopyItemFlavorData Error: "<< err << std::endl;
                    CFRelease (flavorTypeArray);
                    CFRelease (theClipboard);
                    return Result;
                }
                
                flavorDataSize = CFDataGetLength( flavorData );

                for( short dataIndex = 0; dataIndex < flavorDataSize; ++dataIndex )
                {
                    Result += *(CFDataGetBytePtr( flavorData ) + dataIndex);
                }
                
                CFRelease (flavorData);
            }
        }
        CFRelease (flavorTypeArray);
    }
    CFRelease (theClipboard);
    return Result;
}

void CarbonWindow::putClipboard(const std::string Value)
{
    OSStatus err = noErr;

    //Create clipboard reference
    PasteboardRef theClipboard;
    err = PasteboardCreate( kPasteboardClipboard, &theClipboard );
    if(err != noErr)
    {
        SWARNING << "CarbonWindow::putClipboard: PasteboardCreate Error: "<< err << std::endl;
        return;
    }

    //Add text to clipboard
    PasteboardSyncFlags syncFlags;
    TXNOffset           start, end;
    Handle              dataHandle;
    CFDataRef           textData = NULL;
     

    //Clear clipboard
    err = PasteboardClear( theClipboard );
    if(err != noErr)
    {
        SWARNING << "CarbonWindow::putClipboard: PasteboardClear Error: "<< err << std::endl;
        CFRelease (theClipboard);
        return;
    }

    syncFlags = PasteboardSynchronize( theClipboard );
    //if(!(syncFlags&kPasteboardModified))
    //{
        //SWARNING << "CarbonWindow::putClipboard: PasteboardSynchronize Error: kPasteboardModified "<< badPasteboardSyncErr << std::endl;
        //return;
    //}
    if(!(syncFlags&kPasteboardClientIsOwner))
    {
        SWARNING << "CarbonWindow::putClipboard: PasteboardSynchronize Error: kPasteboardClientIsOwner "<< notPasteboardOwnerErr << std::endl;
        CFRelease (theClipboard);
        return;
    }

    textData = CFDataCreate( NULL, reinterpret_cast<const UInt8*>(Value.c_str()), Value.size() );

    err = PasteboardPutItemFlavor( theClipboard, (PasteboardItemID)1,
                        CFSTR("public.utf8-plain-text"),
                        textData, 0 );
    if(err != noErr)
    {
        SWARNING << "CarbonWindow::putClipboard: PasteboardPutItemFlavor Error: "<< err << std::endl;
        CFRelease (theClipboard);
        return;
    }

    CFRelease(theClipboard);
}

void CarbonWindow::openWindow(const Pnt2f& ScreenPosition,
				   const Vec2f& Size,
				   const std::string& WindowName)
{
    SetWindowTitleWithCFString(_WindowRef, CFStringCreateWithCString(NULL, WindowName.c_str(),WindowName.size()));
   
    init();
    deactivate();
    
    if(!getFullscreen())
    {
        // Show window
        RepositionWindow(_WindowRef, 0, kWindowCascadeOnMainScreen);
        setPosition(ScreenPosition);

        //For some reason the Viewport is not set up right unless I force the window to resize
        //there must be a better way of doing this
        setSize(Vec2us(Size[0],Size[1])+Vec2us(-1,0));
        setSize(Vec2us(Size[0],Size[1]));
        
        ShowWindow(_WindowRef);
    }
	produceWindowOpened();
    _modifierKeyState = getKeyModifiers();
	_IsWindowOpen = true;
}

void CarbonWindow::closeWindow(void)
{
    disposeWindow();
}

void CarbonWindow::disposeWindow(void)
{
    DisposeWindow(_WindowRef);
}

void CarbonWindow::setCursor(void)
{
	ThemeCursor c;
	switch(getCursorType())
	{
        case CURSOR_HAND:
            c = kThemePointingHandCursor;
            break;
        case CURSOR_I_BEAM:
            c = kThemeIBeamCursor;
            break;
        case CURSOR_WAIT:
            c = kThemeWatchCursor;
            break;
        case CURSOR_RESIZE_W_TO_E:
            c = kThemeResizeLeftRightCursor;
            break;
        case CURSOR_RESIZE_N_TO_S:
            c = kThemeResizeUpDownCursor;
            break;
        case CURSOR_RESIZE_NW_TO_SE:
            c = kThemeResizeUpDownCursor;
            break;
        case CURSOR_RESIZE_SW_TO_NE:
            c = kThemeResizeUpDownCursor;
            break;
        case CURSOR_RESIZE_ALL:
            c = kThemeClosedHandCursor;
            break;
        case CURSOR_NONE:
            c = kThemeArrowCursor;
            break;
        case CURSOR_POINTER:
        default:
            c = kThemeArrowCursor;
            break;
	}
	SetThemeCursor(c);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void OSG::CarbonWindow::onCreate(const CarbonWindow *source)
{
    Inherited::onCreate(source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;
   
    if(source != NULL)
    {
        // Create window
        WindowRef window;
        WindowAttributes windowAttrs =
            kWindowStandardDocumentAttributes |
            kWindowLiveResizeAttribute |
            kWindowStandardHandlerAttribute;
        Rect contentRect;
        SetRect(&contentRect, 0, 0, 400, 400);
        
        CreateNewWindow(kDocumentWindowClass, windowAttrs, &contentRect, &window);
        
        // Install event handler
        _EventHandlerUPP = NewEventHandlerUPP(eventHandler);
        
        _WindowRef = window;
    }
}

/*! instance deletion
*/

void OSG::CarbonWindow::onDestroy(UInt32 uiContainerId)
{

    Inherited::onDestroy(uiContainerId);
}

/*----------------------- constructors & destructors ----------------------*/

CarbonWindow::CarbonWindow(void) :
    Inherited(),
    _IsWindowOpen(false),
    _AttachMouseToCursor(true)
{
}

CarbonWindow::CarbonWindow(const CarbonWindow &source) :
    Inherited(source),
    _IsWindowOpen(false),
    _AttachMouseToCursor(true)
{
}

CarbonWindow::~CarbonWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CarbonWindow::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CarbonWindow::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CarbonWindow NI" << std::endl;
}

/*-------------------------- your_category---------------------------------*/

/*! Init the window: create the context and setup the OpenGL.
*/
void CarbonWindow::init(GLInitFunctor oFunc)
{
    Inherited::init(oFunc);
}

void CarbonWindow::terminate(void)
{
}

// activate the window: bind the OGL context
void CarbonWindow::doActivate( void )
{
    aglSetCurrentContext(getContext());
}

// activate the window: bind the OGL context
void CarbonWindow::doDeactivate( void )
{
    aglSetCurrentContext(0);
}

// swap front and back buffers
bool CarbonWindow::doSwap( void )
{
    aglSwapBuffers(getContext());
    return true;
}

bool CarbonWindow::hasContext(void)
{
    return (this->getContext() != NULL);
}

OSG_END_NAMESPACE

#endif // __APPLE__
