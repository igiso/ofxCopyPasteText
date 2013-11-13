//
//  ofxCopyPasteText.cpp
//  emptyExample
//
//  Created by kyriacos on 11/13/13.
//
//

#include "ofxCopyPasteText.h"


#ifdef TARGET_WIN32

#include <windows.h>
bool  setTextToPasteboard(string as){
    
    size_t reqLength = ::MultiByteToWideChar( CP_UTF8, 0, as.c_str(), (int)as.length(), 0, 0 );
    
    std::wstring text( reqLength, L'\0' );
    
    ::MultiByteToWideChar( CP_UTF8, 0, as.c_str(), (int)as.length(), &text[0], (int)text.length() );
    
    bool ok = false;
    if (OpenClipboard(NULL)){
        EmptyClipboard();
        HGLOBAL hClipboardData;
        size_t bytes = text.length()+1 * sizeof(wchar_t);
        
        hClipboardData = GlobalAlloc(GMEM_DDESHARE, bytes*2);
        wchar_t * pchData = (wchar_t*)GlobalLock(hClipboardData);
        
        wcscpy(pchData, text.c_str());
        
        GlobalUnlock(hClipboardData);
        SetClipboardData(CF_UNICODETEXT,hClipboardData);
        CloseClipboard();
        ok = true;
    }
    return ok;
}

string getTextFromPasteboard(){
    string clipBoardText;
    if (OpenClipboard(NULL)){
        HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
        if(IsClipboardFormatAvailable(CF_UNICODETEXT)){
            
            wstring  pchData = (wchar_t *)GlobalLock(hClipboardData);
            char mbstr2[pchData.size()*4];
            
            size_t bytes = pchData.length()+1 * sizeof(wchar_t);
            WideCharToMultiByte(CP_UTF8,0,pchData.c_str(),bytes*2,mbstr2,bytes*2,NULL,NULL);
            clipBoardText.append(mbstr2);
            
            
            GlobalUnlock(hClipboardData);
            CloseClipboard();
        }
    }
    
    return clipBoardText;
}


#else

char* getTextFromPasteboard() {
    
    OSStatus err = noErr;
    ItemCount  itemCount;
    PasteboardSyncFlags  syncFlags;
    static PasteboardRef inPasteboard = NULL;
    PasteboardCreate( kPasteboardClipboard, &inPasteboard );
    char* data;
    
    syncFlags = PasteboardSynchronize( inPasteboard );
    err = badPasteboardSyncErr;
    
    err = PasteboardGetItemCount( inPasteboard, &itemCount );
    require_noerr( err, CantGetPasteboardItemCount );
    
    for( int itemIndex = 1; itemIndex <= itemCount; itemIndex++ ) {
        PasteboardItemID itemID;
        CFDataRef flavorData;
        
        err = PasteboardGetItemIdentifier( inPasteboard, itemIndex, &itemID );
        require_noerr( err, CantGetPasteboardItemIdentifier );
        
        err = PasteboardCopyItemFlavorData( inPasteboard, itemID, CFSTR("public.utf8-plain-text"), &flavorData );
        data = (char*)CFDataGetBytePtr(flavorData);
        
    CantGetPasteboardItemIdentifier:
        ;
    }
    
CantGetPasteboardItemCount:
    
    return data;
    
}

static OSStatus setTextToPasteboard(char* byteArrayIndex) {
    
    OSStatus err = noErr;
    static PasteboardRef	pasteboard = NULL;
    PasteboardCreate( kPasteboardClipboard, &pasteboard );
    
    err = PasteboardClear( pasteboard );
    require_noerr( err, PasteboardClear_FAILED );
    
    CFDataRef data;
    
    data =   CFDataCreate(kCFAllocatorDefault, (UInt8*)byteArrayIndex, strlen(byteArrayIndex)+1);
    
    err = PasteboardPutItemFlavor( pasteboard, (PasteboardItemID)1, kUTTypeUTF8PlainText, data, 0);
    require_noerr( err, PasteboardPutItemFlavor_FAILED );
    
PasteboardPutItemFlavor_FAILED:
PasteboardClear_FAILED:
    return err;
}

#endif












bool ofCopyText(string text){
    
#ifdef TARGET_WIN32
    return setTextToPasteboard(text);
    
#else
    char * tempText = (char*)text.c_str();
    return  setTextToPasteboard(tempText);
    
#endif
    
    
}


string ofPasteText(){
    
    string text_to_return;
    
#ifdef TARGET_WIN32
    text_to_return = getTextFromPasteboard();
    
#else
    
    text_to_return.assign(getTextFromPasteboard());
#endif
    
    return text_to_return;
    
    
}






