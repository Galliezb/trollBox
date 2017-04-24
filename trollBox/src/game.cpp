#include "game.h"

int game::selectGame(){

	int selected = (int)ofRandom(0.f,0.f);
	restartAllGame();

	return selected;
}

void game::restartAllGame(){

	// game0
	angleMarteau = 90;
	sensMarteau = 1;
	timerAnimHammer = -1;
	timerEndGame0 = 0;
	forceHeight = 0;
	animForceHeight = 0;
	tpsTimerAnimHammer = 5.0;
	timer = ofGetElapsedTimef();

}

void game::displayGame0(){

	socleMarteau.draw(578,160);


	// 634 de gauche + 6 de large
	
	if ( tpsTimerAnimHammer < 0 && angleMarteau > 85 ){

		if ( animForceHeight!= forceHeight ){
			myPlayer->playSound("forceHammer01",true);
		// fin de la partie
		} else {
			
			if ( timerEndGame0 == 0 ){
				myPlayer->stopSound();
				myPlayer->playSound("fail03");
				timerEndGame0 = ofGetElapsedTimef();
			}
			
			if ( timerEndGame0+2.0f > ofGetElapsedTimef() ){
				troll01.draw(0,104,575,616);
				ptrMafonte->drawString("GAME OVER",550,150);
				
			} else {
				gameIsEnd=true;
			}

		}

		if ( animForceHeight < forceHeight ){ animForceHeight++; }

		ofSetColor(255,0,0);
		ofFill();  
		ofRect(633, 528-animForceHeight, 7, animForceHeight);
		ofSetColor(255,255,255);

	}

	tpsTimerAnimHammer = timerAnimHammer - ofGetElapsedTimef();





	

	// on attend la fin du décompte
	if ( tpsTimerAnimHammer > 0 ){
	
		ptrMafonte->drawString( ofToString(tpsTimerAnimHammer,2),600,50 );
		drawHammer();

		// règle la force de monter du trait rouge  // taille max = 307
		if ( angleMarteau > -180 && angleMarteau < -150 ) { forceHeight = 270;}
		if ( angleMarteau > -150 && angleMarteau < -120 ) { forceHeight = 240;}
		if ( angleMarteau > -120 && angleMarteau <  -90 ) { forceHeight = 210;}
		if ( angleMarteau > -90 && angleMarteau  <  -60 ) { forceHeight = 180;}
		if ( angleMarteau > -60 && angleMarteau  <  -30 ) { forceHeight = 150;}
		if ( angleMarteau > -30 && angleMarteau  <    0 ) { forceHeight = 120;}
		if ( angleMarteau >   0 && angleMarteau  <   30 ) { forceHeight = 90;}
		if ( angleMarteau >  30 && angleMarteau  <   60 ) { forceHeight = 60;}
		if ( angleMarteau >  60 && angleMarteau  <   90 ) { forceHeight = 30;}
	
	// animation frappe
	} else if ( angleMarteau < 90 ){

		angleMarteau+=5*sensMarteau;
		if ( angleMarteau > 42 ){ myPlayer->playSound("hammer01",true); }
		drawHammer();

	}

}

void game::loadHammer(){

	float rnd = ofRandom(0.5f,2.5f);
	angleMarteau-=5;
	if ( angleMarteau < -180 ){ angleMarteau=-180; }

}

void game::drawHammer(){
	
	ofPushMatrix();

		ofTranslate(528,520);

		ofPushMatrix();
		ofRotate(angleMarteau,0.0,0.0,1.0);
		marteau.draw(-25,-132);
		ofPopMatrix();

	ofPopMatrix();

}


void game::displaytutoriel(){

	if ( timer+5.0f > ofGetElapsedTimef() ){

		if ( choixGame == 0 ){
			troll01.draw(0,104,575,616);
			ptrMafonte->drawString("Spammez les boutons",550,150);
			ptrMafonte->drawString("pour augmenter la force de frappe du marteau",400,200);
			timerAnimHammer = ofGetElapsedTimef()+3;
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

}


