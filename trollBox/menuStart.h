#pragma once
#include "../ofMain.h"

class menuStart {
public:
	menuStart();

	void afficherMenu();
	string createText(string str);
	void init();
	void setEtatMenu(int v);

	~menuStart();

	// variable public
	/*
	0 => INSERT COINS
	1 => INSERT MORE COINS
	2 => INSERT MORE MORE COINS
	3 => SUCCES ! START OF TROLLBOX !
	*/
	int etatMenu = 0;

private:
	
	bool etatPiece = false;
	int etatPoints=0;
	float tps;
	ofImage img1,img2;
	ofTrueTypeFont	verdana;

};

