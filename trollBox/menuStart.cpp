#include "menuStart.h"



menuStart::menuStart(){
}

void menuStart::afficherMenu(){

	/****************************************  DEMARRAGE  *******************************************/
	if ( etatMenu == 0 ){
		
		// affichage du text
		verdana.drawString( createText("Insert Coins").c_str(), 350,545);

	
	} else if ( etatMenu == 1 ){

		verdana.drawString( createText("Insert MORE Coins").c_str(), 350,545);
		img1.draw(25,25);

	} else if ( etatMenu == 2 ){

		verdana.drawString( createText("Insert MORE MORE Coins").c_str(), 350,545);
		img2.draw(25,25);

	/*************************************  ENREGISTREMENT NOM  *****************************************/
	} else if ( etatMenu == 3 ){
	
		// MAJ 65-90
		// MIN 97-122
		// 32 = espace
		// 45 = -

		string descr = "Insert your name";

		verdana.drawString( descr.c_str() , 150,545);
		verdana.drawString( createName() , 250,585);
		verdana.drawString( "_ _ _ _ _ _ _ _ _ _" , 275,585);

	} else if ( etatMenu = 4 ){
		verdana.drawString( createName() , 350,545);
	}
}

void menuStart::changeNameLeft(){

	nameIndexCharacter-=2;
	if ( nameIndexCharacter < 0 ){ nameIndexCharacter=0; };

	if ( name[nameIndexCharacter] != ' ' ){
		nameNumberOfLetter = name[nameIndexCharacter];
	} else {
		nameNumberOfLetter = 65;
	}

}

void menuStart::changeNameRight(){

	nameIndexCharacter+=2;
	if ( nameIndexCharacter > 18 ){ nameIndexCharacter=18; };

	if ( name[nameIndexCharacter] != ' ' ){
		nameNumberOfLetter = name[nameIndexCharacter];
	} else {
		nameNumberOfLetter = 65;
	}

}

void menuStart::changeLetter(){


	// MAJ 65-90
	// MIN 97-122
	// 32 = espace
	// 45 = -

	ofLog() << "nameNumberOfletter : " << nameNumberOfLetter;
	ofLog() << "nameIndexCharacter : " << nameIndexCharacter;
	
	if ( nameNumberOfLetter == 90 ){
		nameNumberOfLetter = 32;
	} else if ( nameNumberOfLetter == 32 ){
		nameNumberOfLetter = 45;
	} else if ( nameNumberOfLetter == 45 ){
		nameNumberOfLetter = 65;
	} else {
		nameNumberOfLetter++;
	}

	name[nameIndexCharacter] = nameNumberOfLetter;
}

string menuStart::createName(){

	string str;
	for ( int i=0; i<20; i++){
		str+=name[i];
	}

	return string();
}

string menuStart::createText(string str){
	
	if ( tps+1 < ofGetElapsedTimef() ){

		// timer update
		tps = ofGetElapsedTimef();
		// etat des points update
		etatPoints++;
		if ( etatPoints > 3 ){ etatPoints = 0; }

	}

	string strToReturn = str;

	// affichage
	switch (etatPoints){
		case 1 :
			strToReturn += ".";
			break;
		case 2 :
			strToReturn += "..";
			break;
		case 3 :
			strToReturn += "...";
			break;
	}
	
	return strToReturn;
}


void menuStart::init(){

	verdana.load("verdana.ttf", 30, true, true);
	verdana.setLineHeight(34.0f);
	verdana.setLetterSpacing(1.035);

	img1.load("warning01.jpg");
	img2.load("warning02.jpg");

	tps = ofGetElapsedTimef();

}


menuStart::~menuStart(){
}
