#include "TypingLetter.h"



TypingLetter::TypingLetter(){
}

void TypingLetter::init(SoundManagement* ptrMyPlayerRecieved, ofTrueTypeFont* maFonte, vector<string>* ptrStr){

	myPlayer = ptrMyPlayerRecieved;
	ptrMaFonte = maFonte;
	ptrVectorString = ptrStr;

}

void TypingLetter::type(){

	for (int i = 0; i< ptrVectorString->size(); i++){
	
		drawtypingLetter( (*ptrVectorString)[i], i );

	}

}




void TypingLetter::drawtypingLetter(string str, int positionInVector){

	int displayPostionX = 50;
	if (positionInVector <= 3 ){ displayPostionX = 500;}



	// cette chaine a été entièrement tapé, elle doit être affiché
	if ( positionInVector < indexStringToType ){
	
		ptrMaFonte->drawString( str , displayPostionX , displayOnY[positionInVector] );

	// Cette chaine est en court de frappe
	} else if ( indexStringToType == positionInVector ){
	
		int stringLength = str.length();

		// est on sur le caractere de fin ?
		if( toDraw[positionInVector] == str.length() ){

			ptrMaFonte->drawString( str,displayPostionX,displayOnY[positionInVector]);
			indexStringToType++;
			if ( indexStringToType == ptrVectorString->size()-1 ){ indexStringToType = ptrVectorString->size()-1; }

		// alors on tape le caractere
		} else {

			ptrMaFonte->drawString( str.substr(0,toDraw[positionInVector]),displayPostionX,displayOnY[positionInVector]);
			myPlayer->playSound("typingLetter01",true);

			if ( timerForTypingLetter + 30 < ofGetElapsedTimeMillis() ){
				toDraw[positionInVector]++;
				timerForTypingLetter = ofGetElapsedTimef();
			}

		}

	}
	// SINON on fait rien, et on attends qu'elle soit en droit de s'afficher

}


TypingLetter::~TypingLetter(){
}