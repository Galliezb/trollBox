#include "menuStart.h"



menuStart::menuStart(){
}

void menuStart::afficherMenu(){

	/****************************************  DEMARRAGE  *******************************************/
	if ( etatMenu == 0 ){
		
		// affichage du text
		maFonte.drawString( createText("Insert Coins").c_str(), 350,545);

	
	} else if ( etatMenu == 1 ){

		maFonte.drawString( createText("Insert MORE Coins").c_str(), 350,545);
		img1.draw(25,25);

	} else if ( etatMenu == 2 ){

		maFonte.drawString( createText("Insert MORE MORE Coins").c_str(), 350,545);
		img2.draw(25,25);

	/*************************************  ENREGISTREMENT NOM  *****************************************/
	} else if ( etatMenu == 3 ){
	
		// MAJ 65-90
		// MIN 97-122
		// 32 = espace
		// 45 = -

		string descr = "Insert your name";

		maFonte.drawString( descr.c_str() , 150,545);
		maFonte.drawString( createName() , 300,585);
		maFonte.drawString( "_ _ _ _ _ _ _ _ _ _" , 300,595);

	} else if ( etatMenu = 4 ){
		maFonte.drawString( createName() , 300,545);
	}
}

void menuStart::changeNameLeft(){

	// on recule ( en sautant l'espace blanc )
	nameIndexCharacter-=2;

	// si on est tout a gauche, fail
	if ( nameIndexCharacter < 0 ){ 

		nameIndexCharacter=0;
		SoundManagement::playSound("fail02");

	}

	
	// si on est pas tout à gauche
	if ( name[nameIndexCharacter] != ' ' ){
		nameNumberOfLetter = name[nameIndexCharacter];
	} else {
		nameNumberOfLetter = 65;
	}
	
}

void menuStart::changeNameRight(){

	// on avance dans les lettre du nom en sautant les espaces
	nameIndexCharacter+=2;

	// si on dépasse le nombre max de caractère, on bloque
	if ( nameIndexCharacter > 18 ){ 
		nameIndexCharacter=18; 
		SoundManagement::playSound("fail02");
	}

	
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
	
	if ( nameNumberOfLetter == 90 ){
		nameNumberOfLetter = 32;
	} else if ( nameNumberOfLetter == 32 ){
		nameNumberOfLetter = 45;
	} else if ( nameNumberOfLetter == 45 ){
		nameNumberOfLetter = 65;
	} else {
		nameNumberOfLetter++;
	}
	
	SoundManagement::playSound("sucess01");

	name[nameIndexCharacter] = char(nameNumberOfLetter);

}

string menuStart::createName(){

	// create string
	string str;
	for ( int i=0; i<20; i++){
		str+=name[i];
	}



	// blink selection letter
	if ( etatBlinkLettrer ){
		str[nameIndexCharacter]=' ';
	}

	if ( timeBlinkLetter+450 < ofGetElapsedTimeMillis() ){
		timeBlinkLetter = ofGetElapsedTimeMillis();
		(etatBlinkLettrer) ? etatBlinkLettrer=false: etatBlinkLettrer=true;
	}



	return str;
}

string menuStart::createText(string str){
	
	if ( tpsBlinkPoint+1 < ofGetElapsedTimef() ){

		// timer update
		tpsBlinkPoint = ofGetElapsedTimef();
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

	maFonte.load("monospacedfont_03.ttf", 30, true, true);
	maFonte.setLineHeight(34.0f);
	maFonte.setLetterSpacing(1.035);

	img1.load("warning01.jpg");
	img2.load("warning02.jpg");

	tpsBlinkPoint = ofGetElapsedTimef();
	timeBlinkLetter = ofGetElapsedTimeMillis();

}


menuStart::~menuStart(){
}
