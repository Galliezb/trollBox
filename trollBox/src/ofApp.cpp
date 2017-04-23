#include "ofApp.h"
#include "wiringPi.h"



//--------------------------------------------------------------
void ofApp::setup(){

	// fond noir
	ofBackground(ofColor(0,0,0));

	// init des sons
	myPlayer.init();

	// init classe
	mesJeux.init(&myPlayer,&maFonte);
	menuPrincipal.init(&myPlayer,&maFonte,&mesJeux);

	timerDetection = ofGetElapsedTimeMillis();

	/* FACE A LA TROLLBOX
	5 = Bouton Gauche
	6 = Bouton milieu gauche
	13 = Bouton Milieu Droit
	19 = Bouton Droit
	26 = Detecteur de pièce
	*/
	wiringPiSetupGpio();
	pinMode(5,INPUT);
	pinMode(6,INPUT);
	pinMode(13,INPUT);
	pinMode(19,INPUT);
	pinMode(26,INPUT);

}

//--------------------------------------------------------------
void ofApp::update(){

	// emp�che les d�tections � moind d' 1 par 300 ms
	if ( timerDetection+300 < ofGetElapsedTimeMillis() ){

		ofLog() << digitalRead(5) << " " << digitalRead(6) << " " << digitalRead(13) << " " << digitalRead(19) << " " << digitalRead(26);

		/********************************* INSERTION PIECE ********************************/
		if ( menuPrincipal.etatMenu < 3 ){

			// 1 par d�faut, d�tection  = 0
			if ( digitalRead(37) == 0 ){
				myPlayer.playSound("sucess01");
				menuPrincipal.etatMenu++;
			}

		}
		timerDetection = ofGetElapsedTimeMillis();
	}

	// si un jeu se fini, on renvoi au d�marrage
	if ( mesJeux.gameIsEnd ){
		mesJeux.choixGame=-1;
		mesJeux.gameIsEnd=false;
		menuPrincipal.etatMenu=6;
	}

}

//--------------------------------------------------------------
void ofApp::draw(){


	if ( mesJeux.choixGame == -1 ){
		menuPrincipal.afficherMenu();
	} else {
		mesJeux.displaytutoriel();
	}



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	if ( key == OF_KEY_ESC ){
		exit();
	}

	/****************************** JEUX 0 BOURRINNAGE *********************************************/
	if ( mesJeux.choixGame == 0 ){

		// charge la force du marteau s'il reste du temps
		if ( mesJeux.tpsTimerAnimHammer > 0 ){
			mesJeux.loadHammer();
		}



	/****************************** CONTROLE LES LETTRE POUR INDIQUER SON NOM *********************************************/
	} else if ( menuPrincipal.etatMenu == 3 ){

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

	/****************************** PASSWORD ADMINISTRATION *********************************************/
	} else if ( menuPrincipal.etatMenu == 8 ){
		// bouton 1
		if ( key == OF_KEY_LEFT ){
			menuPrincipal.sequenceHistory[menuPrincipal.indexSequence] = 1;
			// bouton 2
		} else if ( key == OF_KEY_DOWN ){
			menuPrincipal.sequenceHistory[menuPrincipal.indexSequence] = 2;
			// bouton 3
		} else if ( key == OF_KEY_UP ){
			menuPrincipal.sequenceHistory[menuPrincipal.indexSequence] = 3;
			// bouton 4
		} else if ( key == OF_KEY_RIGHT ){
			menuPrincipal.sequenceHistory[menuPrincipal.indexSequence] = 4;
		}
		menuPrincipal.indexSequence--;
		menuPrincipal.decoupeXBomb01++;
		if ( menuPrincipal.decoupeXBomb01 > 8 ){ menuPrincipal.decoupeXBomb01 = 8;}


	/****************************** CREDITS *********************************************/
	} else if ( menuPrincipal.etatMenu == 9 ){

		menuPrincipal.etatEtapeCredits++;
		if ( menuPrincipal.etatEtapeCredits == 9 ){ 
			myPlayer.stopSound();
			menuPrincipal.etatMenu = 0;
		}

	/****************************** ADMINISTRATION *********************************************/
	} else if ( menuPrincipal.etatMenu == 10 ){

		// bouton 1
		if ( key == OF_KEY_LEFT ){
			if ( myPlayer.soundVolume < 0.04f ){
				myPlayer.playSound("fail01",true);
			} else {
				myPlayer.soundVolume-=0.05f;
			}
			// bouton 2
		} else if ( key == OF_KEY_DOWN ){
			menuPrincipal.optionSelectionAdminsitration--;
			if ( menuPrincipal.optionSelectionAdminsitration < 0 ){ menuPrincipal.optionSelectionAdminsitration = 0 ;}
			// bouton 3
		} else if ( key == OF_KEY_UP ){
			menuPrincipal.optionSelectionAdminsitration++;
			menuPrincipal.etatMenu=6;
			// bouton 4
		} else if ( key == OF_KEY_RIGHT ){
			if ( myPlayer.soundVolume > 0.96f ){
				myPlayer.playSound("fail01",true);
			} else {
				myPlayer.soundVolume+=0.05f;
			}

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
