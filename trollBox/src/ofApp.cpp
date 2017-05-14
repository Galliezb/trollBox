#include "ofApp.h"
//#include "wiringPi.h"



//--------------------------------------------------------------
void ofApp::setup(){

	// fond noir
	ofBackground(ofColor(0,0,0));

	// init des sons
	myPlayer.init();
	myPlayer.soundVolume = 1.0f;

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
	/*
	wiringPiSetupGpio();
	pinMode(5,INPUT);    // Bouton gauche remplacé par F ( 102 )
	pinMode(6,INPUT);    // Bouton milieu gauche remplacé par G ( 103 )
	pinMode(13,INPUT);   // Bouton milieu droit remplacé par H ( 104 )
	pinMode(19,INPUT);   // bouton droite remplacé par J ( 106 )
	pinMode(26,INPUT);   // Pièce remplacé par touche K ( 107 )
	*/
}

//--------------------------------------------------------------
void ofApp::update(){
	/*
	// empêche les détections à moind d' 1 par 300 ms
	if ( timerDetection+300 < ofGetElapsedTimeMillis() ){

		timerDetection = ofGetElapsedTimeMillis();

		//********************************* INSERTION PIECE ********************************
		if ( menuPrincipal.etatMenu < 3 ){

			// 1 par défaut, détection  = 0
			if ( digitalRead(26) == 0 ){
				myPlayer.playSound("sucess01");
				menuPrincipal.etatMenu++;
			}

			timerDetection += 200;

		}

		//****************************** JEUX 0 BOURRINNAGE *********************************************
		if ( mesJeux.choixGame == 0 ){

			// charge la force du marteau s'il reste du temps
			if ( mesJeux.tpsTimerAnimHammer > 0 && ( digitalRead(5) == 0 || digitalRead(6) == 0 || digitalRead(13) == 0 || digitalRead(19) == 0 ) ){
				mesJeux.loadHammer();
			}

			timerDetection -= 200;

		//****************************** CONTROLE LES LETTRE POUR INDIQUER SON NOM *********************************************
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

		//****************************** LOADING BAR *********************************************
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
		//****************************** CHOIX MENU *********************************************
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
				timerDetection += 50;
			}

		//****************************** PASSWORD ADMINISTRATION *********************************************
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


		//****************************** CREDITS *********************************************
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

		//****************************** ADMINISTRATION *********************************************
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

				if ( myPlayer.soundVolume > 0.96f ){
					myPlayer.playSound("fail01",true);
				} else {
					myPlayer.soundVolume+=0.05f;
				}

				// bouton 3
			} else if ( digitalRead(13) == 0 ){
				menuPrincipal.optionSelectionAdminsitration--;
				if ( menuPrincipal.optionSelectionAdminsitration < 0 ){ menuPrincipal.optionSelectionAdminsitration = 0 ;}
				// bouton 4
			} else if ( digitalRead(19) == 0 ){

				menuPrincipal.optionSelectionAdminsitration++;
				menuPrincipal.etatMenu=6;

			}


		}

	}
	*/

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

	// empêche les détections à moind d' 1 par 300 ms
	if ( timerDetection+300 < ofGetElapsedTimeMillis() ){

		timerDetection = ofGetElapsedTimeMillis();

		/********************************* INSERTION PIECE ********************************/
		if ( menuPrincipal.etatMenu < 3 && (key == OF_KEY_LEFT || key == OF_KEY_RIGHT || key == OF_KEY_UP || key == OF_KEY_DOWN) ){
			
			myPlayer.playSound("sucess01");
			menuPrincipal.etatMenu++;

			timerDetection += 200;

		}

		/****************************** JEUX 0 BOURRINNAGE *********************************************/
		if ( mesJeux.choixGame == 0 ){

			// charge la force du marteau s'il reste du temps
			//if ( mesJeux.tpsTimerAnimHammer > 0 && ( digitalRead(5) == 0 || digitalRead(6) == 0 || digitalRead(13) == 0 || digitalRead(19) == 0 ) ){
			if ( mesJeux.tpsTimerAnimHammer > 0 && ( key == OF_KEY_LEFT || key == OF_KEY_DOWN || key == OF_KEY_UP || key == OF_KEY_RIGHT ) ){
				mesJeux.loadHammer();
			}

			timerDetection -= 200;

			/****************************** CONTROLE LES LETTRE POUR INDIQUER SON NOM *********************************************/
		} else if ( menuPrincipal.etatMenu == 3 ){

			// Decale a gauche
			//if ( digitalRead(5) == 0 ){
			if ( key == OF_KEY_LEFT ){
				menuPrincipal.changeNameRight();
				// decale a droite
				//} else if ( digitalRead(6) == 0 ){
			} else if ( key == OF_KEY_DOWN ){
				menuPrincipal.changeLetter(false);
				// changer la lettre ( ++ )
				//} else if ( digitalRead(13) == 0 ){
			} else if ( key == OF_KEY_UP ){
				menuPrincipal.changeLetter(true);
				// valide le nom
				//} else if ( digitalRead(19) == 0 ){
			} else if ( key == OF_KEY_RIGHT ){
				menuPrincipal.etatMenu = 4;
			}

			/****************************** LOADING BAR *********************************************/
		}  else if ( menuPrincipal.etatMenu == 5 ){

			bool a=false,b=false,c=false,d=false;

			// bouton 1
			//if ( digitalRead(5) == 0 ){
			if ( key == OF_KEY_LEFT ){
				a=true;
				// bouton 2
				//} else if ( digitalRead(6) == 0 ){
			} else if ( key == OF_KEY_DOWN ){
				b=true;
				// bouton 3
				//} else if ( digitalRead(13) == 0 ){
			} else if ( key == OF_KEY_UP ){
				c=true;
				// bouton 4
				//} else if ( digitalRead(19) == 0 ){
			} else if ( key == OF_KEY_RIGHT ){
				d=true;
			}

			// detection boutons plus lente
			//if ( digitalRead(5) == 0 || digitalRead(6) == 0 || digitalRead(13) == 0 || digitalRead(19) == 0){
			if ( key == OF_KEY_LEFT || key == OF_KEY_DOWN || key == OF_KEY_UP || key == OF_KEY_RIGHT){
				timerDetection += 200;
			}

			menuPrincipal.newModificateur(a,b,c,d);
			/****************************** CHOIX MENU *********************************************/
		} else if ( menuPrincipal.etatMenu == 6 ){

			// Decale a gauche
			//if ( digitalRead(5) == 0 ){
			if ( key == OF_KEY_LEFT ){
				menuPrincipal.changeChoixMenu(false);
				// decale a droite
				//} else if ( digitalRead(6) == 0 ){
			} else if ( key == OF_KEY_DOWN ){
				menuPrincipal.changeChoixMenu(true);
				// changer la lettre ( ++ )
				//} else if ( digitalRead(13) == 0 || digitalRead(19) == 0 ){
			} else if ( key == OF_KEY_UP || key == OF_KEY_RIGHT ){
				menuPrincipal.valideChoixMenu();
			}



			// detection boutons plus lente
			//if ( digitalRead(5) == 0 || digitalRead(6) == 0 || digitalRead(13) == 0 || digitalRead(19) == 0){
			if ( key == OF_KEY_LEFT || key == OF_KEY_DOWN || key == OF_KEY_UP || key == OF_KEY_RIGHT){
				timerDetection += 50;
			}

			/****************************** PASSWORD ADMINISTRATION *********************************************/
		} else if ( menuPrincipal.etatMenu == 8 ){


			//if ( digitalRead(5) == 0 || digitalRead(6) == 0 || digitalRead(13) == 0 || digitalRead(19) == 0){
			if ( key == OF_KEY_LEFT || key == OF_KEY_DOWN || key == OF_KEY_UP || key == OF_KEY_RIGHT){

				// bouton 1
				//if ( digitalRead(5) == 0 ){
				if ( key == OF_KEY_LEFT ){
					menuPrincipal.sequenceHistory[menuPrincipal.indexSequence] = 1;
					// bouton 2
					//} else if ( digitalRead(6) == 0 ){
				} else if ( key == OF_KEY_DOWN ){
					menuPrincipal.sequenceHistory[menuPrincipal.indexSequence] = 2;
					// bouton 3
					//} else if ( digitalRead(13) == 0 ){
				} else if ( key == OF_KEY_UP ){
					menuPrincipal.sequenceHistory[menuPrincipal.indexSequence] = 3;
					// bouton 4
					//} else if ( digitalRead(19) == 0 ){
				} else if ( key == OF_KEY_RIGHT ){
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

			//if ( digitalRead(5) == 0 || digitalRead(6) == 0 || digitalRead(13) == 0 || digitalRead(19) == 0){
			if ( key == OF_KEY_LEFT || key == OF_KEY_DOWN || key == OF_KEY_UP || key == OF_KEY_RIGHT){
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
			//if ( digitalRead(5) == 0 ){
			if ( key == OF_KEY_LEFT ){
				if ( myPlayer.soundVolume < 0.04f ){
					myPlayer.playSound("fail01",true);
				} else {
					myPlayer.soundVolume-=0.05f;
				}
				// bouton 2
				//} else if ( digitalRead(6) == 0 ){
			} else if ( key == OF_KEY_DOWN ){

				if ( myPlayer.soundVolume > 0.96f ){
					myPlayer.playSound("fail01",true);
				} else {
					myPlayer.soundVolume+=0.05f;
				}

				// bouton 3
				//} else if ( digitalRead(13) == 0 ){
			} else if ( key == OF_KEY_UP ){
				menuPrincipal.optionSelectionAdminsitration--;
				if ( menuPrincipal.optionSelectionAdminsitration < 0 ){ menuPrincipal.optionSelectionAdminsitration = 0 ;}
				// bouton 4
				//} else if ( digitalRead(19) == 0 ){
			} else if ( key == OF_KEY_RIGHT ){

				menuPrincipal.optionSelectionAdminsitration++;
				menuPrincipal.etatMenu=6;

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
