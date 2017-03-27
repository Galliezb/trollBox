#pragma once
#include "ofMain.h"

class game {
public:
	game(){};
	~game(){};

	// G1
	void displayTuto(string txt1,string txt2,string txt3,string txt4);


	int etatGame=-1;

private:
	// all game
	int gallTimeDisplayInfo=-1;

	// game 1 : Bourrinage
	int g1NumberOfPlayer;
	float g1MaxTimer;
};

