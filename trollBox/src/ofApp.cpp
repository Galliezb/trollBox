#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// fond noir
	ofBackground(ofColor(0,0,0));

	// init classe
	menuPrincipal.init();

	// conf serial connection
	coSerial.setup("/dev/ttyACM0", 9600);
}

//--------------------------------------------------------------
void ofApp::update(){

	int monByte = 0;
	monByte = coSerial.readByte();

	if ( monByte == OF_SERIAL_NO_DATA ){

		printf("Aucune data reçu, alors on communique : \n");

		monByte = 9;
		bool byteWasWritten = coSerial.writeByte(monByte);
		if ( !byteWasWritten ){
			printf("byte was not written to serial port");
		} else {
			printf("Bytes (%d) correctement envoyé",monByte);
		}

	} else if ( monByte == OF_SERIAL_ERROR ){

		printf("an error occurred");

	} else {

		printf("myByte is %d", monByte);
		//ofLog() << "myByte is %d" <<  myByte;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	//menuPrincipal.afficherMenu();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	// simule la première insertion de pièce
	menuPrincipal.etatMenu++;
	if ( menuPrincipal.etatMenu > 2 ){ menuPrincipal.etatMenu = 0; }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
