#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// fond noir
	ofBackground(ofColor(0,0,0));

	// init classe
	menuPrincipal.init();

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	menuPrincipal.afficherMenu();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	/****************************** CONTROLE LES LETTRE POUR INDIQUER SON NOM *********************************************/
	if ( menuPrincipal.etatMenu == 3 ){

		// Decale a gauche
		if ( key == OF_KEY_LEFT ){
			menuPrincipal.changeNameRight();
		// decale a droite
		} else if ( key == OF_KEY_DOWN ){
			menuPrincipal.changeNameRight();
		// changer la lettre ( ++ )
		} else if ( key == OF_KEY_UP ){
			menuPrincipal.changeLetter();
		// valide le nom
		} else if ( key == OF_KEY_RIGHT ){
			menuPrincipal.etatMenu = 4;
		}

	}

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	// simule la première insertion de pièce
	menuPrincipal.etatMenu++;
	if ( menuPrincipal.etatMenu > 3 ){ menuPrincipal.etatMenu = 0; }

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
