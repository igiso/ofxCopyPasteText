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
    string clipBoardText="";
    if (OpenClipboard(NULL)){
        HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
        if(IsClipboardFormatAvailable(CF_UNICODETEXT)){
            wchar_t * pszText =NULL;
            pszText = (wchar_t *)GlobalLock(hClipboardData);
            if (pszText == NULL){
                
            }else{
                wstring  pchData = pszText;
                char mbstr2[pchData.size()*4];
                size_t bytes = pchData.length()+1 * sizeof(wchar_t);
                WideCharToMultiByte(CP_UTF8,0,pchData.c_str(),bytes*2,mbstr2,bytes*2,NULL,NULL);
                clipBoardText.append(mbstr2);
            }
            
            GlobalUnlock(hClipboardData);
            CloseClipboard();
        }
    }
    
    return clipBoardText;
}


#else

string getTextFromPasteboard() {
    
    string clipBoard = "";
    OSStatus err = noErr;
    ItemCount  itemCount;
    PasteboardSyncFlags  syncFlags;
    static PasteboardRef inPasteboard = NULL;
    PasteboardCreate( kPasteboardClipboard, &inPasteboard );
    char* data = NULL;
    
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
        if(err==noErr)data = (char*)CFDataGetBytePtr(flavorData);
        if(data!=NULL&&err==noErr)clipBoard.append(data);else return "Error Pasting";
    CantGetPasteboardItemIdentifier:
        ;
    }
    
CantGetPasteboardItemCount:
    
    
    return clipBoard;
    
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
    
    string text_to_return="";
    
#ifdef TARGET_WIN32
    text_to_return = getTextFromPasteboard();
    
#else
    
    text_to_return.append(getTextFromPasteboard());
#endif
    
    return text_to_return;
    
    
}




dropDownMenu::dropDownMenu(){
    
    ofRegisterMouseEvents(this);
    ofRegisterKeyEvents(this);
    mainPanel.TRASPARENT = true;
    insertButton("Cut");
    insertButton("Copy");
    insertButton("Paste");
    insertButton("Clear");
    status = nothing;
    BUFFER=NULL;
    
}

void dropDownMenu::draw(){
    
    
    int x,y,w,h,cellHeight;
    int calibration = 15;
    cellHeight=25;
    
    
    if(BUFFER!=NULL){
        x= menuPos.x;
        y= menuPos.y;
        w =100;
        h =cellHeight*menuButtons.size()+(calibration*2);
        ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
        for (int i=0; i<5; i++) {
            ofSetColor(150,20-(i*2));
            ofRectRounded(i+x,i+y,w+i,h+i, i*4);
        }
        mainPanel.draw(x-5,y-5,w,h);
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofSetColor(225,240);
        ofRectRounded(x-5,y-5,w,h, 1);
        ofSetLineWidth(0.5);
        ofNoFill();
        ofSetColor(210);
        ofRectRounded(x-5,y-5,w,h, 1);
        ofSetColor(100,100);
        ofRect(-5+x+calibration-.5, y-5, 1, h);
        ofSetColor(235,200);
        ofRect(-5+x+calibration+.5, y-5, 1, h);
        ofFill();
        ofDisableAlphaBlending();
        
        int color_forText = 0;

        
        //0=cut//1=copy//2=paste//3==clear
        for (int i=0; i<menuButtons.size(); i++) {
            ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
            if(menuButtons[i].isActive()){
                ofSetColor(100, 100, 245);
                ofRect(x-5,(i*cellHeight)+y+(calibration/2), w, cellHeight);
                color_forText = 255;
                status = menu_name(i);
                
            }else {
                if((i!=2&&BUFFER->size()==0)||(i==2&&computer_buffer.size()<1)){
                    color_forText =150;
                }else
                    color_forText =0;
                
                
            }
            menuButtons[i].draw(x+calibration,(i*cellHeight)+y+(calibration/2), w-(calibration*2), cellHeight,ofColor(color_forText));

            
        }
        
    }
    
}

dropDownMenu::~dropDownMenu(){
    
    ofUnregisterMouseEvents(this);
    ofUnregisterKeyEvents(this);
}

dropDownMenu * DropMenu;



