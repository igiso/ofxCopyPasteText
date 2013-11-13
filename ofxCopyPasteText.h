//
//  ofCopyPasteText.h
//  emptyExample
//
//  Created by kyriacos on 11/13/13.
//
//

#ifndef emptyExample_ofxCopyPasteText_h
#define emptyExample_ofxCopyPasteText_h

#include "ofMain.h"






#ifdef TARGET_WIN32
bool setTextToPasteboard(string text);

string getTextFromPasteboard();

#else

static OSStatus setTextToPasteboard(char* byteArrayIndex);

char* getTextFromPasteboard();

#endif







bool ofCopyText(string text);

string ofPasteText();







#endif
