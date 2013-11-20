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

string getTextFromPasteboard();

#endif







bool ofCopyText(string text);

string ofPasteText();














///
///////////////////////////////////////////////a dummy drop down menu to make things more easy (no need to use this though)




enum menu_name{
    cut____,
    copy___,
    paste__,
    clear__,
    nothing
    
};



////not the smartest button outhere but it will do
class button {
    bool isActive_;
    float dist,timer,timerDir;
    bool toggle_mode;
public:
    bool TRASPARENT;
    
    ofColor color;
    bool ISABLETOCLICk,grabbed;
    
    void setColour(int r, int g, int b, int al =255){
        
        color.set(r, g, b,al);
    }
    bool toggle;
    bool onlyOnce,solid,additive,settle;
    int ID;
    int timerActive;
    string ANSWER;
    ofImage * asset;
    
    button(){
        
        TRASPARENT=false;
        asset = NULL;
        ISABLETOCLICk=true;
        timerActive=0;
        solid = false;
        additive = true;
        onlyOnce =false;
        isActive_=false;
        settle = false;
        timer=0;
        timerDir=ofRandom(1,-1);
        toggle=true;
        ID=0;
        ANSWER = "_";
        color.set(255,255,255,250);
        toggle_mode =false;
        grabbed = false;
        dist=0;
        
    }
    
    
    void makeActive(bool truFalse){
        ISABLETOCLICk = truFalse;
        
    }
    void toggleModeON(){
        if(!toggle_mode){
         //   asset = & img_tickBox_png;
            toggle_mode=true;
        }
    }
    
    void draw(int x, int y, int w, int h,ofColor textCol = ofColor::black){
        
        if(ISABLETOCLICk){
            dist = ofDist(x+(w/2),0,ofGetMouseX(),0);
            float    disty = ofDist(0,y+(h/2),0,ofGetMouseY());
            if(dist<w/2&&disty<h/2)isActive_=true;else isActive_ =false;
        }
        
        if(isActive_)ofSetColor(timer,timer);else ofSetColor(255,0);
        if(asset!=NULL){
            if(isActive_){
                if(!toggle_mode){
                    if(!solid){
                        timerActive++;
                        if(timerActive>40)onlyOnce=false;
                        if(additive){ofEnableBlendMode(OF_BLENDMODE_ADD);
                            
                            if(!settle)ofSetColor(timer,255,124,200);else{
                                ofSetColor(color.g-10,color.b-10,color.r-10);
                            }
                        }else{
                            if(timer<250)timer+=10;
                            
                            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
                            ofSetColor(timer,color.g+timer,color.b+timer,timer);
                            
                        }
                    }else{
                        ofSetColor(255,255);
                        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
                    }
                    
                }else{
                    
                    ofSetColor(0);
                    ofRect(x,y,w,h);
                    if(asset!=NULL)asset->draw(x,y,w,h);
                    if (toggle) {
                        ofSetColor(100);
                        ofRect(x+5,y+5,w-10,h-10);
                        
                    }
                    
                    
                }
                //^toggle;
                
            }else{
                timerActive=0;
                if(!solid){
                    if(!additive)if(timer>0)timer=0;
                    
                    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
                    ofSetColor(color);
                }else{
                    ofSetColor(255,255);
                    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
                }
                onlyOnce=false;
                
            }
            
            if(!toggle_mode){
                if(!toggle){
                    ANSWER = "OK";
                    //if(IS_ABLE_TO_FILLED)ofSetColor(0, 255, 100);else{
                      //  ofSetColor(255, 255, 255);
                   // }
                    ofFill();
                    ofRect(x+5, y+5, w-10, h-10);
                    ofSetColor(0);
                    ofDrawBitmapString(ANSWER, x+(w/4),y+(h/1.5));
                    ofSetColor(255);
                    ofEnableAlphaBlending();
                }else ANSWER="  ";
                if(asset!=NULL)asset->draw(x,y,w,h);
            }else{
                //togglemode
                ofEnableAlphaBlending();
                ofSetColor(255,100);
                if(asset!=NULL)asset->draw(x,y,w,h);
                ofDisableAlphaBlending();
                if (toggle) {
                    ofSetColor(100);
                    ofRect(x+5,y+5,w-10,h-10);
                }else{
                    ofSetColor(100);
                    ofRect(x+5,y+10,w-10,1);
                    ofRect(x+5,y+15,w-10,1);
                    ofRect(x+5,y+20,w-10,1);
                    
                    
                }
                
            }
            
        }else{
            if(!TRASPARENT){
                ofEnableBlendMode(OF_BLENDMODE_ALPHA);
                if(isActive_){
                    if(timer<100)timer++;
                    ofFill();
                    if(!solid)ofSetColor(50,timer);else ofSetColor(200);
                }
                else{
                    timer=0;
                    ofFill();
                    ofSetColor(color);
                }
                ofRect(x, y, w, h);
            }
            ofSetColor(textCol);
            ofDrawBitmapString(ANSWER, x+((w/2)-(ANSWER.size()*5)),y+(h/2)+(h/4));
        }
        
        ofDisableBlendMode();
        ofSetColor(255);
    }
    bool isActive(){return isActive_;}
    ~button(){
        
        if (asset!= NULL) {
            
            asset = NULL;
        }
        
    }
    
    
    
};



class dropDownMenu{
    vector<button> menuButtons;
    button mainPanel;
    ofPoint menuPos;
    string * BUFFER;
    string computer_buffer;
public:
    
    menu_name status;
    dropDownMenu();
    ~dropDownMenu();
    void draw();
    void mouseReleased(ofMouseEventArgs& eventArgs){
        if(eventArgs.button==0){
            bool isnotSomethingSelected =true;
            for (int i=0; i<menuButtons.size(); i++) {
                if(menuButtons[i].isActive()){
                    
                    isnotSomethingSelected = false;
                }
            }
            if(mainPanel.isActive()&&isnotSomethingSelected)BUFFER=NULL;
            
            
        }else{
            
            menuPos.x = eventArgs.x;
            menuPos.y = eventArgs.y;
        }
    }
    void mouseMoved(ofMouseEventArgs & args){}
    void mouseDragged(ofMouseEventArgs & args){}
    void mousePressed(ofMouseEventArgs & args){
        
        if(mainPanel.isActive()){
            if(BUFFER!=NULL){
                
                switch (this->getKeyPressed()) {
                    case cut____:
                        if(BUFFER->size()>0){ofCopyText(*BUFFER);
                            BUFFER->clear();
                        }
                        break;
                    case copy___:
                        
                        
                        if(BUFFER->size()>0)ofCopyText(*BUFFER);
                        
                        break;
                    case paste__:
                        
                        if(ofPasteText().size()>0){

                            BUFFER->assign(ofPasteText());

                            
                        }
                        
                        
                        break;
                        
                    case clear__:
                        
                        if(BUFFER->size()>0)BUFFER->clear();
                        
                        
                        break;
                        
                        
                        
                    default:
                        break;
                }
                
                
                this->Hide();
                
                
            }
        }else{
            status = nothing;
            
            
            BUFFER=NULL;
        }
        
        
        
    }
    
    void keyPressed(ofKeyEventArgs& eventArgs){
        
        BUFFER = NULL;
    }
    void keyReleased(ofKeyEventArgs& eventArgs){
        
        
    }
    menu_name getKeyPressed(){
        
        return status;
    }
    
    void insertButton(string name){
        
        button b_temp;
        
        b_temp.ANSWER = name;
        
        b_temp.TRASPARENT = true;
        menuButtons.push_back(b_temp);
        
    }
    void Hide(){
        BUFFER=NULL;
    }
    
    void assign(string * pointer){
        
        BUFFER = pointer;
        computer_buffer = ofPasteText();
        
    }
    
    
    
};



extern dropDownMenu * DropMenu;


#endif
