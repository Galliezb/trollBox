#pragma once
#include "../ofMain.h"

class menuStart {
public:
	menuStart();

	void afficherMenu();
	void init();

	~menuStart();

private:
	
	bool etatPiece = false;
	int etatMenu = 0,etatPoints=0;
	float tps;
	ofImage img1,img2;
	ofTrueTypeFont	verdana;

};

