#include "menuStart.h"



menuStart::menuStart(){
}

void menuStart::afficherMenu(){

	// démarrage
	if ( etatMenu == 0 ){
		
		if ( tps+1 < ofGetElapsedTimef() ){
			
			// timer update
			tps = ofGetElapsedTimef();
			// etat des points update
			etatPoints++;
			if ( etatPoints > 3 ){ etatPoints = 0; }

		}

		// affichage
		switch (etatPoints){
			case 0 :
				verdana.drawString("Insert Coin", 550,345);
				break;
			case 1 :
				verdana.drawString("Insert Coin.", 550,345);
				break;
			case 2 :
				verdana.drawString("Insert Coin..", 550,345);
				break;
			case 3 :
				verdana.drawString("Insert Coin...", 550,345);
				break;
		}

	}

}

void menuStart::init(){

	verdana.load("verdana.ttf", 30, true, true);
	verdana.setLineHeight(34.0f);
	verdana.setLetterSpacing(1.035);

	img1.load("warning01.jpg");
	img2.load("warning01.jpg");

	tps = ofGetElapsedTimef();

}


menuStart::~menuStart(){
}
