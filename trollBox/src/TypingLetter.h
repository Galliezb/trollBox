#pragma once
#include "ofMain.h"
#include "SoundManagement.h"

class TypingLetter{
public:
	TypingLetter();
	void init(SoundManagement* ptrMyPlayerRecieved, ofTrueTypeFont* maFonte, vector<string>* ptrStr);
	void type();
	~TypingLetter();
private:

	SoundManagement* myPlayer;
	ofTrueTypeFont* ptrMaFonte;
	vector<string>* ptrVectorString;

	void drawtypingLetter(string str, int positionInVector);
	int toDraw[10]={0,0,0,0,0,0,0,0,0,0};
	int indexStringToType = 0, timerForTypingLetter=0;
	//bool stringMustBeDraw[10]={false,false,false,false,false,false,false,false,false,false};
	int displayOnY[10] = {100,150,200,250,450,500,550,600,650,700};

};

