#pragma once
#include "SoundManagement.h"
#include "game.h"
#include "TypingLetter.h"

class menuStart {
public:
	menuStart();

	void afficherMenu();
	void changeNameRight();
	void changeLetter( bool positif=true );
	string createName();
	string createText(string str);
	void init(SoundManagement* ptrMyPlayerRecieved, ofTrueTypeFont* maFonte, game* instanceDesJeux);
	void newModificateur(bool bt1,bool bt2,bool bt3,bool bt4);

	// choi menu
	void changeChoixMenu( bool goDown = false);
	void valideChoixMenu();

	~menuStart();

	// variable public
	/*
	0 => INSERT COINS
	1 => INSERT MORE COINS
	2 => INSERT MORE MORE COINS
	3 => SUCCES ! START OF TROLLBOX !
	*/
	int etatMenu = 0;
	bool endWriteUserName = false;
	int nameIndexCharacter=0,nameNumberOfLetter=65;

	// administration
	int indexSequence=7,sequenceHistory[8],optionSelectionAdminsitration=0,decoupeXBomb01=0;
	// choix menu jeu
	int etatMenuJeu=0;

	// les credits 
	int etatEtapeCredits = 0;

private:
	
	SoundManagement* myPlayer;
	ofTrueTypeFont* ptrMaFonte;
	game* ptrMesJeux;
	bool etatPiece = false, etatBlinkLettrer = false;
	int etatPoints=0,posXbarreChargement=-1280;
	float tpsBlinkPoint;
	// 20 espace, mode bourrin
	char name[20] = {'A',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
	float tpsLettre = ofRandom( 0.4f, 2.0f);
	ofImage img1,img2,troll01,barreIn,barreOut,trollDance,menu;
	
	// les différents timers
	int timeBlinkLetter,timeWaitLeavingWelcome,timeLoadBarFPS;
	//timer animation + index
	int timerTrollDance, decoupeTrollDance=0;
	// variable pour l'avancement de la barre
	int timeLoadBar,avancement=1,modificateur=0; 
	string nameSaved,strTimeLoadBar;

	// CHOIX MENU
	int etatMenuChoix = -1;

	// Administration
	ofImage gyrophare,bomb01,bomb01Chiffre;
	int timeBeforeAutoLeaveAdministration,timeImageGyrophare=1,posXGyrophare=0;
	float lastVolume=1.0f;

	// les Crédits
	ofImage photoCredit[8];
	int timerForTypingLetter,toDraw = 0;
	vector<string> tabTextToDisplay[8];
	TypingLetter displayText[8];
	float posDefilementY=760.f;
	bool youpiPlayed = false;
	float timerRebooterAfterCredit=0.0f;
	


	// method private
	string invertName();

};

