#include "headers\menuStart.h"



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

	}
	/*************************************  ENREGISTREMENT NOM  *****************************************/
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

void menuStart::setEtatMenu(int v){
	etatMenu=v;
}


menuStart::~menuStart(){
}
