#pragma once
#include "ofMain.h"

class game {
public:
	game(){};
	~game(){};

	void calculTout();
	void displayGame();
	void init();

	int choixGame=-1;

private:

	// methode interne private
	// G1
	void displayTutoGame01();
	void displayGame01();

	// all game
	int gallTimeDisplayInfo=-1;

	// game 1 : Bourrinage
	int g1NumberOfPlayer;
	float g1MaxTimer;
};

