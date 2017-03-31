#include "menuStart.h"



menuStart::menuStart(){
}

void menuStart::afficherMenu(){

	/****************************************  DEMARRAGE  *******************************************/
	if ( etatMenu == 0 ){
		
		// affichage du text
		ptrMaFonte->drawString( createText("Insert Coins").c_str(), 350,545);

	
	} else if ( etatMenu == 1 ){

		ptrMaFonte->drawString( createText("Insert MORE Coins").c_str(), 350,545);
		img1.draw(25,25);

	} else if ( etatMenu == 2 ){

		ptrMaFonte->drawString( createText("Insert MORE MORE Coins").c_str(), 350,545);
		img2.draw(25,25);

	/*************************************  ENREGISTREMENT NOM  *****************************************/
	} else if ( etatMenu == 3 ){

		// MAJ 65-90
		// MIN 97-122
		// 32 = espace
		// 45 = -

		string descr = "Insert your name";

		ptrMaFonte->drawString( descr.c_str() , 150,545);
		ptrMaFonte->drawString( createName() , 300,585);

		// pourquoi les lettres le décale bordel ?
		//ptrMaFonte->drawString( "_ _ _ _ _ _ _ _ _ _" , 300,595);

	/*************************************  WELCOME TROLLBOX + NOM  *****************************************/
	} else if ( etatMenu == 4 ){
	
		// Affiche bienvenu
		troll01.draw(0,104,575,616);
		ptrMaFonte->drawString(" WELCOME TO THE TROLLBOX",600,150);
		// troll en inversant le nom
		ptrMaFonte->drawString( invertName() , 600,250);
		// sauvegarde le nom
		nameSaved = invertName();

		if ( timeWaitLeavingWelcome == -1 ){

			// play musique
			myPlayer->playSound("valide02",true);

			// timer avant passage au 5
			timeWaitLeavingWelcome = ofGetElapsedTimef();
		} else if ( timeWaitLeavingWelcome+5.f < ofGetElapsedTimef() ){
			etatMenu = 5;
		}
	
	/*************************************  BARRE DE CHARGEMENT  *****************************************/
	} else if ( etatMenu == 5 ){


		// barre de chargement
		barreIn.draw(posXbarreChargement,327);
		barreOut.draw(0,327);

		// txt
		ptrMaFonte->drawString("Loading... Do not wait please...",375,300);
		ptrMaFonte->drawString(strTimeLoadBar,450,350);

		string str = "Loading State : ";
		str += to_string(posXbarreChargement+1280);
		str += " / 2560 ";
		ptrMaFonte->drawString(str,375,425);

		str = "Loading speed : ";
		str += to_string(avancement);
		ptrMaFonte->drawString(str,375,475);

		str = "Next Loading speed : ";
		str += to_string(avancement + modificateur);
		ptrMaFonte->drawString(str,375,525);

		if ( timerTrollDance+50 < ofGetElapsedTimeMillis() ){
			decoupeTrollDance++;
			if ( decoupeTrollDance > 11 ){ decoupeTrollDance = 0 ;}
			timerTrollDance = ofGetElapsedTimeMillis();
		}
		trollDance.drawSubsection(1130,490,150,230,decoupeTrollDance*150,0,150,230);


		// Avancement de la barre ( interval 1 - 20 soit 64 sec / 0.5 action par sec = 32 sec au max )
		if ( timeLoadBarFPS+500 < ofGetElapsedTimeMillis() ){

			avancement += modificateur;
			if ( avancement < -20 ){ avancement = -20; }
			modificateur = 0;

			myPlayer->playSound("waiting01",true);

			timeLoadBarFPS = ofGetElapsedTimeMillis();
			posXbarreChargement+=avancement;

			if (posXbarreChargement < -1280 ){ posXbarreChargement = -1280; } 
			if (posXbarreChargement > 1280 ){ etatMenu = 6; } 

		}

		/*************************************  MENU JEU  *****************************************/
	} else if ( etatMenu == 6 ){

		if ( etatMenuChoix == 0 ){
			menu.drawSubsection(422,30,435,92,0,92,435,92);
		} else {
			menu.drawSubsection(422,30,435,92,0,0,435,92);
		}
		ptrMaFonte->drawString( "All games",572,90);
		
		if ( etatMenuChoix == 1 ){
			menu.drawSubsection(422,160,435,92,0,92,435,92);
		} else {
			menu.drawSubsection(422,160,435,92,0,0,435,92);
		}
		ptrMaFonte->drawString( "Do not try",572,220);
		
		if ( etatMenuChoix == 2 ){
			menu.drawSubsection(422,290,435,92,0,92,435,92);
		} else {
			menu.drawSubsection(422,290,435,92,0,0,435,92);
		}
		ptrMaFonte->drawString( "Administration",572,350);
		
		if ( etatMenuChoix == 3 ){
			menu.drawSubsection(422,420,435,92,0,92,435,92);
		} else {
			menu.drawSubsection(422,420,435,92,0,0,435,92);
		}
		ptrMaFonte->drawString( "Credits",572,480);
		
	/************************************* MENU CHOIX DES JEUX  *****************************************/
	} else if ( etatMenu == 7 ){

		// On remplace par un jeu aleatoire
		if ( ptrMesJeux->choixGame == -1 ){
			ptrMesJeux->choixGame = (int) round( ofRandom(0.f,0.f) );
		}

	/************************************* ADMINISTRATION ( troll )  *****************************************/
	} else if ( etatMenu == 8 ){

		gyrophare.drawSubsection(0,0,100,95,posXGyrophare*100,0,100,95);
		gyrophare.drawSubsection(1180,0,100,95,posXGyrophare*100,0,100,95);

		if ( timeImageGyrophare+500 < ofGetElapsedTimeMillis() ){
			posXGyrophare++;
			if ( posXGyrophare > 1 ){ posXGyrophare = 0; }
			timeImageGyrophare = ofGetElapsedTimeMillis();
		}
		// alarm avec volume à fond.
		lastVolume = myPlayer->soundVolume;
		myPlayer->soundVolume = 1.0f;
		myPlayer->playSound("alarm01",true);
		myPlayer->soundVolume = lastVolume;

		// Affiche l'image avec le compteur
		ofSetColor(255,0,0);
		ptrMaFonte->drawString(to_string(indexSequence),500,500);
		ofSetColor(255,255,255);

		ptrMaFonte->drawString(to_string(sequenceHistory[7])
							   +to_string(sequenceHistory[6])
							   +to_string(sequenceHistory[5])
							   +to_string(sequenceHistory[4])
							   +to_string(sequenceHistory[3])
							   +to_string(sequenceHistory[2])
							   +to_string(sequenceHistory[1])
							   +to_string(sequenceHistory[0])
							   ,500,550);
		ptrMaFonte->drawString( "index : " + to_string(indexSequence),500,600);

		if ( indexSequence < 0 ){

			if ( sequenceHistory[7] == 1 &&
				sequenceHistory[6] == 2 &&
				sequenceHistory[5] == 4 &&
				sequenceHistory[4] == 2 &&
				sequenceHistory[3] == 1 &&
				sequenceHistory[2] == 2 &&
				sequenceHistory[1] == 4 &&
				sequenceHistory[0] == 2 ){
				
					// pwd ok, on passe en mode config
					etatMenu = 10;
					myPlayer->stopSound();

			} else {
				etatMenu = 5;
			}

		}


	/************************************* CREDITS  *****************************************/
	} else if ( etatMenu == 9 ){

	/************************************* ADMINISTRATION  *****************************************/
	} else if ( etatMenu == 10 ){


		// Volume
		if ( optionSelectionAdminsitration == 0 ){ ofSetColor(255, 0, 0);}
		ptrMaFonte->drawString("Volume : ",50,50);
		if ( optionSelectionAdminsitration == 0 ){ ofSetColor(255, 255, 255);}

		ofNoFill();
		ofDrawRectRounded(199,22,502,32,5);
		ofSetColor(0, 255, 0);
		ofFill();
		ofDrawRectRounded(200,23,500*myPlayer->soundVolume,30,5);
		ofSetColor(255,255,255);

	}
}

void menuStart::changeNameRight(){


	// si on est tout a droite, fail
	if ( nameIndexCharacter+2 > 18 ){ 

		nameIndexCharacter=0;

	} else {
		// on avance dans les lettre du nom en sautant les espaces
		nameIndexCharacter+=2;
	}

	
	if ( name[nameIndexCharacter] != ' ' ){
		nameNumberOfLetter = name[nameIndexCharacter];
	} else {
		nameNumberOfLetter = 65;
		name[nameIndexCharacter] = 65;
	}
	
}

void menuStart::changeLetter( bool positif ){


	// MAJ 65-90
	// MIN 97-122
	// 32 = espace
	// 45 = -
	if ( positif ){

		if ( nameNumberOfLetter == 90 ){
			nameNumberOfLetter = 32;
		} else if ( nameNumberOfLetter == 32 ){
			nameNumberOfLetter = 45;
		} else if ( nameNumberOfLetter == 45 ){
			nameNumberOfLetter = 65;
		} else {
			nameNumberOfLetter++;
		}

	} else {

		if ( nameNumberOfLetter == 65 ){
			nameNumberOfLetter = 45;
		} else if ( nameNumberOfLetter == 45 ){
			nameNumberOfLetter = 32;
		} else if ( nameNumberOfLetter == 32 ){
			nameNumberOfLetter = 90;
		} else {
			nameNumberOfLetter--;
		}

	}
	
	myPlayer->playSound("clap01");

	name[nameIndexCharacter] = char(nameNumberOfLetter);

}

string menuStart::createName(){

	// create string
	string str;
	for ( int i=0; i<20; i++){
		str+=name[i];
	}



	// blink selection letter
	if ( etatBlinkLettrer ){
		str[nameIndexCharacter]=' ';
	}

	if ( timeBlinkLetter+250 < ofGetElapsedTimeMillis() ){
		timeBlinkLetter = ofGetElapsedTimeMillis();
		(etatBlinkLettrer) ? etatBlinkLettrer=false: etatBlinkLettrer=true;
	}



	return str;
}

string menuStart::createText(string str){
	
	if ( tpsBlinkPoint+1 < ofGetElapsedTimef() ){

		// timer update
		tpsBlinkPoint = ofGetElapsedTimef();
		// etat des points update
		etatPoints++;
		if ( etatPoints > 3 ){ etatPoints = 0; }

	}

	string strToReturn = str;

	// affichage
	switch (etatPoints){
		case 1 :
			strToReturn += ".";
			break;
		case 2 :
			strToReturn += "..";
			break;
		case 3 :
			strToReturn += "...";
			break;
	}
	
	return strToReturn;
}


void menuStart::init(SoundManagement* ptrMyPlayerRecieved, ofTrueTypeFont* maFonte, game* instanceDesJeux){

	// Pointeur gestionnaire de sons
	myPlayer = ptrMyPlayerRecieved;
	ptrMaFonte = maFonte;
	ptrMesJeux = instanceDesJeux;

	// créer
	ptrMaFonte->load("monospacedfont_03.ttf", 30);
	//ptrMaFonte->setLineHeight(34.0f);
	//ptrMaFonte->setLetterSpacing(1.035);

	img1.load("warning01.jpg");
	img2.load("warning02.jpg");
	troll01.load("troll01.png");
	barreIn.load("barre_in.png");
	barreOut.load("barre_out.png");
	trollDance.load("trollDance.jpg");
	menu.load("menu01.png");
	gyrophare.load("gyrophare.png");

	tpsBlinkPoint = ofGetElapsedTimef();
	timeBlinkLetter = ofGetElapsedTimeMillis();
	timeWaitLeavingWelcome = -1; // = non encore initalisé
	timeLoadBarFPS = ofGetElapsedTimeMillis();
	timerTrollDance = ofGetElapsedTimeMillis();
	
	timeLoadBar = 1280;

}

void menuStart::newModificateur(bool bt1, bool bt2, bool bt3, bool bt4){

	int verifOnButton = 0;
	if ( bt1 ){ verifOnButton++; }
	if ( bt2 ){ verifOnButton++; }
	if ( bt3 ){ verifOnButton++; }
	if ( bt4 ){ verifOnButton++; }

	modificateur = 0;

	// combien de boutons ?
	if ( verifOnButton > 0 && verifOnButton < 2 ){

		if ( bt1 ){ modificateur = round( ofRandom( 0.f , 3.f ) -1.5 ); }
		if ( bt2 ){ modificateur = round( ofRandom( 0.f , 12.f) -4  ); }
		if ( bt3 ){ modificateur = round( ofRandom( 0.f , 9.f ) -6  ); }
		if ( bt4 ){ modificateur = round( ofRandom( 0.f , 6.f ) -5  ); }

	// fail les amis !
	} else {
		myPlayer->playSound("fail01");
	}

}

void menuStart::changeChoixMenu( bool down ){

	if ( down ){
		etatMenuChoix++;
		if (etatMenuChoix > 3){ etatMenuChoix = 0;}
	} else {
		etatMenuChoix--;
		if (etatMenuChoix < 0){ etatMenuChoix = 3;}
	}
	myPlayer->playSound("clap01");

}

void menuStart::valideChoixMenu(){

	if (etatMenuChoix == -1){
		myPlayer->playSound("fail01");
	} else {
		
		// choix des jeux
		if ( etatMenuChoix == 0 ){
			etatMenu = 7;
		// choix "DO not try" retour barre de chargement
		} else if ( etatMenuChoix == 1 ){
			etatMenu = 5;
		// choix administration
		} else if ( etatMenuChoix == 2 ){
			etatMenu = 8;
			timeBeforeAutoLeaveAdministration = ofGetElapsedTimeMillis();
		// choix Credits
		} else if ( etatMenuChoix == 3 ){
			etatMenu = 9;
		}

	}

}


menuStart::~menuStart(){
}

string menuStart::invertName(){

	int lastLetter=19,firstLetter=0;
	char tmp = ' ';
	string str;

	for (int i = 19;i>0;i-=2){
		
		if ( name[i]!= ' ' ){
			lastLetter=i;
			break;
		}

	}

	for (int i = lastLetter; i>=0; i--){
	
		str+=name[i];
	
	}

	return str;

}
