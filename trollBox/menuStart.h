#pragma once
#include "../ofMain.h"

class menuStart {
public:
	menuStart();

	void afficherMenu();
	void changeNameLeft();
	void changeNameRight();
	void changeLetter();
	string createName();
	string createText(string str);
	void init();

	~menuStart();

	// variable public
	/*
	0 => INSERT COINS
	1 => INSERT MORE COINS
	2 => INSERT MORE MORE COINS
	3 => SUCCES ! START OF TROLLBOX !
	*/
	int etatMenu = 3;
	bool endWriteUserName = false;
	int nameIndexCharacter=0,nameNumberOfLetter=65;

private:
	
	bool etatPiece = false;
	int etatPoints=0;
	float tps;
	// 20 espace, mode bourrin
	char name[20] = {'A',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
	float tpsLettre = ofRandom( 0.4f, 2.0f);
	ofImage img1,img2;
	ofTrueTypeFont	verdana;

};

