#include "testApp.h"
int N_boxes_in_Width = 5;
int N_boxes_in_height = 5;
//--------------------------------------------------------------
void testApp::setup(){
    DropMenu = new dropDownMenu;
    
     N_boxes_in_Width = 5;
     N_boxes_in_height = 5;

    
    //let's create some fake textboxes (you can use ofTextInputField addon)
    for (int i=0; i<N_boxes_in_height; i++) {
    vector<button> temp_row;
    for (int j=0; j<N_boxes_in_Width; j++) {
        button b;
    b.ANSWER = ofToString(char(ofRandom(256)))+ofToString(char(ofRandom(256)))+ofToString(char(ofRandom(256)))+ofToString(i)+ofToString(j)+ofToString(char(ofRandom(256)))+ofToString(char(ofRandom(256)));
        temp_row.push_back(b);
    }
        textBoxes.push_back(temp_row);
        
    }
    
    
    //orUse a raw string directly:
    TitleText = "COPY PASTE ME";

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(0);
    ofDrawBitmapString(TitleText, 10,40);
    
    int width =150;
    int height = 30;
    
    int posX = ofGetWidth()/2 - ((N_boxes_in_Width*width)/2);
    int posY = ofGetHeight()/2 - ((N_boxes_in_height*height)/2);
    
    for (int i=0; i<textBoxes.size(); i++) {
        for (int j=0; j<textBoxes[i].size(); j++) {

        
            
    textBoxes[i][j].draw(posX+(5+width)*i, posY+(5+height)*j, width, height);
            
            
        }
    }
    

    
    
    DropMenu->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

    
    if (button==2) {
    

        for (int i=0; i<textBoxes.size(); i++) {
            for (int j=0; j<textBoxes[i].size(); j++) {
               
                if(textBoxes[i][j].isActive())DropMenu->assign(&textBoxes[i][j].ANSWER);
                
                
            }}

        ///copy the title as well
        if(ofDist(10, 40, x, y)<100)DropMenu->assign(&TitleText);
    
    }
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}