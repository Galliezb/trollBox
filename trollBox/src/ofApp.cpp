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
	26 = Detecteur de piece
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

	// empêche les détections à moind d' 1 par 300 ms
	if ( timerDetection+300 < ofGetElapsedTimeMillis() ){

		timerDetection = ofGetElapsedTimeMillis();

		/********************************* INSERTION PIECE ********************************/
		if ( menuPrincipal.etatMenu < 3 ){

			// 1 par défaut, détection  = 0
			if ( digitalRead(26) == 0 ){
				myPlayer.playSound("sucess01");
				menuPrincipal.etatMenu++;
			}

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
			if ( digitalRead(5) == 0 ){
				menuPrincipal.changeNameRight();
				// decale a droite
			} else if ( digitalRead(6) == 0 ){
				menuPrincipal.changeLetter(false);
				// changer la lettre ( ++ )
			} else if ( digitalRead(13) == 0 ){
				menuPrincipal.changeLetter(true);
				// valide le nom
			} else if ( digitalRead(19) == 0 ){
				menuPrincipal.etatMenu = 4;
			}

			/****************************** LOADING BAR *********************************************/
		}  else if ( menuPrincipal.etatMenu == 5 ){

			bool a=false,b=false,c=false,d=false;

			// bouton 1
			if ( digitalRead(5) == 0 ){
				a=true;
				// bouton 2
			} else if ( digitalRead(6) == 0 ){
				b=true;
				// bouton 3
			} else if ( digitalRead(13) == 0 ){
				c=true;
				// bouton 4
			} else if ( digitalRead(19) == 0 ){
				d=true;
			}

			// detection boutons plus lente
			if ( digitalRead(5) == 0 || digitalRead(6) == 0 || digitalRead(13) == 0 || digitalRead(19) == 0){
				timerDetection += 200;
			}

			menuPrincipal.newModificateur(a,b,c,d);
			/****************************** CHOIX MENU *********************************************/
		} else if ( menuPrincipal.etatMenu == 6 ){

			// Decale a gauche
			if ( digitalRead(5) == 0 ){
				menuPrincipal.changeChoixMenu(false);
				// decale a droite
			} else if ( digitalRead(6) == 0 ){
				menuPrincipal.changeChoixMenu(true);
				// changer la lettre ( ++ )
			} else if ( digitalRead(13) == 0 || digitalRead(19) == 0 ){
				menuPrincipal.valideChoixMenu();
			}

			// detection boutons plus lente
			if ( digitalRead(5) == 0 || digitalRead(6) == 0 || digitalRead(13) == 0 || digitalRead(19) == 0){
				timerDetection += 1200;
			}

			/****************************** PASSWORD ADMINISTRATION *********************************************/
		} else if ( menuPrincipal.etatMenu == 8 ){

			
			if ( digitalRead(5) == 0 || digitalRead(6) == 0 || digitalRead(13) == 0 || digitalRead(19) == 0){

				// bouton 1
				if ( digitalRead(5) == 0 ){
					menuPrincipal.sequenceHistory[menuPrincipal.indexSequence] = 1;
					// bouton 2
				} else if ( digitalRead(6) == 0 ){
					menuPrincipal.sequenceHistory[menuPrincipal.indexSequence] = 2;
					// bouton 3
				} else if ( digitalRead(13) == 0 ){
					menuPrincipal.sequenceHistory[menuPrincipal.indexSequence] = 3;
					// bouton 4
				} else if ( digitalRead(19) == 0 ){
					menuPrincipal.sequenceHistory[menuPrincipal.indexSequence] = 4;
				}
				menuPrincipal.indexSequence--;
				menuPrincipal.decoupeXBomb01++;
				if ( menuPrincipal.decoupeXBomb01 > 8 ){ menuPrincipal.decoupeXBomb01 = 8;}

				// detection boutons plus lente
				timerDetection += 200;
			}


			/****************************** CREDITS *********************************************/
		} else if ( menuPrincipal.etatMenu == 9 ){

			if ( digitalRead(5) == 0 || digitalRead(6) == 0 || digitalRead(13) == 0 || digitalRead(19) == 0){
				menuPrincipal.etatEtapeCredits++;
				if ( menuPrincipal.etatEtapeCredits == 9 ){ 
					myPlayer.stopSound();
					menuPrincipal.etatMenu = 0;
				}

				// detection boutons plus lente
				timerDetection += 1200;

			}

			/****************************** ADMINISTRATION *********************************************/
		} else if ( menuPrincipal.etatMenu == 10 ){

			// bouton 1
			if ( digitalRead(5) == 0 ){
				if ( myPlayer.soundVolume < 0.04f ){
					myPlayer.playSound("fail01",true);
				} else {
					myPlayer.soundVolume-=0.05f;
				}
				// bouton 2
			} else if ( digitalRead(6) == 0 ){
				menuPrincipal.optionSelectionAdminsitration--;
				if ( menuPrincipal.optionSelectionAdminsitration < 0 ){ menuPrincipal.optionSelectionAdminsitration = 0 ;}
				// bouton 3
			} else if ( digitalRead(13) == 0 ){
				menuPrincipal.optionSelectionAdminsitration++;
				menuPrincipal.etatMenu=6;
				// bouton 4
			} else if ( digitalRead(19) == 0 ){
				if ( myPlayer.soundVolume > 0.96f ){
					myPlayer.playSound("fail01",true);
				} else {
					myPlayer.soundVolume+=0.05f;
				}

			}


		}

	}

	// si un jeu se fini, on renvoi au démarrage
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
