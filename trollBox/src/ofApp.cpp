#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// fond noir
	ofBackground(ofColor(0,0,0));

	// init classe
	menuPrincipal.init();

	// conf serial connection
	coSerial.setup("/dev/ttyACM0", 9600);

	// police d'affichage
	verdana.load("verdana.ttf", 30, true, true);
	verdana.setLineHeight(34.0f);
	verdana.setLetterSpacing(1.035);

	// init byteToSend
	byteToSend = 0;
	tpsByteToSend = ofGetElapsedTimeMillis();
	tpsByteRecieve = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void ofApp::update(){

	/*************** RECEPTION UN BYTE SI PRESENT **********************/
	int monByte = 0;
	
	
	if ( coSerial.available() ){

		monByte = coSerial.readByte();
		printf("Byte recu : %d",monByte);

		if ( monByte == OF_SERIAL_NO_DATA ){

			serialtoTransmit = "Dernier byte recu : OFF";

		} else if ( monByte == OF_SERIAL_ERROR ){

			serialtoTransmit = "Dernier byte recu : ERROR";

		} else {

			serialtoTransmit = "Dernier byte recu : " + monByte;

			if ( monByte == 5){
				exit();
			}

		}

		tpsByteRecieve = ofGetElapsedTimeMillis();

	}

	float diff = ofGetElapsedTimeMillis() - tpsByteRecieve / 1000;
	if ( serialRecieve.length() < 1 ){
		serialRecieve = "Dernier byte recu : en attente ( " + ofToString(round(diff/1000)) + " s )";
	} else {
		serialRecieve = serialtoTransmit + "( " + ofToString(round(diff/1000)) + " s )";
	}

	
	/*************** ENVOI UN BYTE TOUTES LES SECONDES **********************/
	if (  tpsByteToSend+1000 < ofGetElapsedTimeMillis() ){

		// essai d'envoyer un byte
		bool byteWasWritten = coSerial.writeByte(byteToSend);
		if ( !byteWasWritten ){
			serialSend = "Valeur du byte envoye : ERROR BYTE NON ENVOYE";
		} else {
			serialSend = "Valeur du byte envoye : " + ofToString(byteToSend);
		}
		byteToSend++;
		if ( byteToSend > 9 ){ byteToSend = 0; }

		// reset timer
		tpsByteToSend = ofGetElapsedTimeMillis();

	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	//menuPrincipal.afficherMenu();
	verdana.drawString( serialSend, 50,150);
	verdana.drawString( serialRecieve, 50,545);


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
