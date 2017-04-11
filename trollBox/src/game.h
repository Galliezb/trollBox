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


	// game 0 : Bourrinage
	void loadHammer();
	float tpsTimerAnimHammer;

	int choixGame=-1;
	bool gameIsEnd=false;

private:

	SoundManagement* myPlayer;
	ofTrueTypeFont* ptrMafonte;
	float timer;
	ofImage troll01;


	// all game
	int gallTimeDisplayInfo=-1;
	void restartAllGame();

	// game 0 : Bourrinage
	void displayGame0();
	void drawHammer();
	float g1MaxTimer;
	ofImage marteau,socleMarteau;
	int angleMarteau = 90;
	int sensMarteau = 1;
	float timerAnimHammer;
	float timerEndGame0 = 0;
	int forceHeight = 0;
	int animForceHeight = 0;


};

