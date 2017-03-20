#pragma once
#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

	// fond noir
	ofBackground(ofColor(0,0,0));

	// init des sons
	myPlayer.init();

	// init classe
	menuPrincipal.init(&myPlayer);

	// police d'affichage
	verdana.load("verdana.ttf", 30, true, true);
	verdana.setLineHeight(34.0f);
	verdana.setLetterSpacing(1.035);


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
			menuPrincipal.changeLetter(false);
		// changer la lettre ( ++ )
		} else if ( key == OF_KEY_UP ){
			menuPrincipal.changeLetter(true);
		// valide le nom
		} else if ( key == OF_KEY_RIGHT ){
			menuPrincipal.etatMenu = 4;
		}

	/****************************** LOADING BAR *********************************************/
	}  else if ( menuPrincipal.etatMenu == 5 ){

		bool a=false,b=false,c=false,d=false;

		// bouton 1
		if ( key == OF_KEY_LEFT ){
			a=true;
		// bouton 2
		} else if ( key == OF_KEY_DOWN ){
			b=true;
		// bouton 3
		} else if ( key == OF_KEY_UP ){
			c=true;
		// bouton 4
		} else if ( key == OF_KEY_RIGHT ){
			d=true;
		}

		menuPrincipal.newModificateur(a,b,c,d);
	/****************************** CHOIX MENU *********************************************/
	} else if ( menuPrincipal.etatMenu == 6 ){

		// Decale a gauche
		if ( key == OF_KEY_LEFT ){
			menuPrincipal.changeChoixMenu(false);
			// decale a droite
		} else if ( key == OF_KEY_DOWN ){
			menuPrincipal.changeChoixMenu(true);
			// changer la lettre ( ++ )
		} else if ( key == OF_KEY_UP || key == OF_KEY_RIGHT ){
			menuPrincipal.valideChoixMenu();
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
	if ( menuPrincipal.etatMenu < 3 ){
		myPlayer.playSound("sucess01");
		menuPrincipal.etatMenu++;
	}

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
