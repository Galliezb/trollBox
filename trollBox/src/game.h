#pragma once
#include "ofMain.h"
#include "SoundManagement.h"

class game {
public:
	game(){};
	~game(){};

	int selectGame();
	void init(SoundManagement* ptrMyPlayerRecieved, ofTrueTypeFont* maFonte);

	// tutoriel	
	void displaytutoriel();


	int choixGame=-1;

private:




	SoundManagement* myPlayer;
	ofTrueTypeFont* ptrMafonte;
	float timer;
	ofImage troll01;


	// all game
	int gallTimeDisplayInfo=-1;

	// game 0 : Bourrinage
	void displayGame0();
	float g1MaxTimer;
	ofImage marteau,socleMarteau;
	int angleMarteau = -90;
	int sensMarteau = 1;
};

