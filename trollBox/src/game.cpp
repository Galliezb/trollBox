#include "game.h"

int game::selectGame(){

	int selected = (int)ofRandom(0.f,0.f);
	timer = ofGetElapsedTimef();

	return selected;
}

void game::displayGame0(){

	socleMarteau.draw(578,160);

	ofPushMatrix();

		ofTranslate(528,520);
		
		ofPushMatrix();
			ofRotate(angleMarteau,0.0,0.0,1.0);
			marteau.draw(-25,-132);
		ofPopMatrix();

	ofPopMatrix();

	angleMarteau+=3*sensMarteau;
	if ( angleMarteau > 84 ){ sensMarteau=-1; }
	if ( angleMarteau < -89 ){ sensMarteau=1; }

}

void game::displaytutoriel(){

	/*
	TODO : animation + centrer les images + ordinateur
	*/

	if ( timer+5.0f > ofGetElapsedTimef() ){

		if ( choixGame == 0 ){
			troll01.draw(0,104,575,616);
			ptrMafonte->drawString("Spammez les boutons",550,150);
			ptrMafonte->drawString("pour augmenter la force de frappe du marteau",400,200);
		}

	} else {
	
		switch (choixGame){

			case 0 :
				displayGame0();
				break;

		}

	}

}

void game::init(SoundManagement* ptrMyPlayerRecieved, ofTrueTypeFont* maFonte){

	ptrMafonte = maFonte;
	myPlayer = ptrMyPlayerRecieved;

	// game 0
	marteau.load("marteau.png");
	socleMarteau.load("socleMarteau.png");

	// image du troll
	troll01.load("troll01.png");

	// init timer
	timer = ofGetElapsedTimef();

}
