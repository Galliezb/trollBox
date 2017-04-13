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

			// Fin chargement
			if (posXbarreChargement > 1280 ){ 

				// coupe le son + reinit au cas ou on relance la barre ( do not try )
				myPlayer->stopSound();
				posXbarreChargement=-1280;
				avancement=1;
				modificateur=0; 

				etatMenu = 6;
			
			
			} 

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
			ptrMesJeux->choixGame = ptrMesJeux->selectGame();
			etatMenuChoix = -1;
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

		// Affiche l'image avec le compteur 760*290
		bomb01.draw(260,215);
		bomb01Chiffre.drawSubsection(721,334,20,43,decoupeXBomb01*20,0,20,43);

		/* DEBUG
		
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
		*/

		if ( indexSequence < 0 ){

			// on reinit le tout
			myPlayer->stopSound();
			indexSequence = 7;
			decoupeXBomb01 = 0;

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
					

			} else {
				etatMenu = 5;
			}

		}


	/************************************* CREDITS  *****************************************/
	} else if ( etatMenu == 9 ){

		if ( etatEtapeCredits <= 7 ){

			photoCredit[etatEtapeCredits].draw(50,50);

			bool next = false;
			next = displayText[etatEtapeCredits].type();
			if ( next ){ etatEtapeCredits++; }

		}


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

	// les textes des crédits à afficher
	tabTextToDisplay[0].push_back("Prenom   : Byuto");
	tabTextToDisplay[0].push_back("Nom      : Kwouin-Chang");
	tabTextToDisplay[0].push_back("Job      : Beta-testeur");
	tabTextToDisplay[0].push_back("Statut   : Inconnu");
	tabTextToDisplay[0].push_back("Note:");
	tabTextToDisplay[0].push_back("Phobie des mauvais jeux");
	tabTextToDisplay[0].push_back("Phobie des bugs");
	tabTextToDisplay[0].push_back("Reve de mourir d'extase devant le jeu parfait a 69 ans");
	tabTextToDisplay[0].push_back("Reve de mourir d'extase devant le jeu parfait a 69 ans");
	tabTextToDisplay[0].push_back("Reve de mourir d'extase devant le jeu parfait a 69 ans");

	tabTextToDisplay[1].push_back("Prenom   : Nymphne");
	tabTextToDisplay[1].push_back("Nom      : Rhoswen");
	tabTextToDisplay[1].push_back("Job      : Beta-testeur, beta tout court");
	tabTextToDisplay[1].push_back("Statut   : feerique");
	tabTextToDisplay[1].push_back("Note:");
	tabTextToDisplay[1].push_back("Adore les fees, les poneys et les arc-en-ciels");
	tabTextToDisplay[1].push_back("A tres peur de la pluie");
	tabTextToDisplay[1].push_back("A encore mega plus peur des orages");

	tabTextToDisplay[2].push_back("Prenom   : Akeko");
	tabTextToDisplay[2].push_back("Nom      : Olsogo");
	tabTextToDisplay[2].push_back("Job      : Chef de projet");
	tabTextToDisplay[2].push_back("Statut   : Pas sage Japonais");
	tabTextToDisplay[2].push_back("Note:");
	tabTextToDisplay[2].push_back("Adore les poissons lune lors des eclipses");
	tabTextToDisplay[2].push_back("Aime apporter la sagesse a son equipe");
	tabTextToDisplay[2].push_back("Aime pisser dans les etangs au clair de lune");
	tabTextToDisplay[2].push_back("Ne mangera pas les poissons sur lesquels il a pisse");

	tabTextToDisplay[3].push_back("Prenom   : Hannery");
	tabTextToDisplay[3].push_back("Nom      : CasseDock");
	tabTextToDisplay[3].push_back("Job      : Optimisateur de code");
	tabTextToDisplay[3].push_back("Statut   : Cingle et pas qu'a moitie");
	tabTextToDisplay[3].push_back("Note:");
	tabTextToDisplay[3].push_back("Se fait surnomme Looping");
	tabTextToDisplay[3].push_back("Ne support pas les fuites de memoires");
	tabTextToDisplay[3].push_back("80 caracteres maximum par ligne de code");
	tabTextToDisplay[3].push_back("Seul le code fait loi en cas de litige");
	tabTextToDisplay[3].push_back("Regle 1 : Si tout va bien, ne touchez a rien");

	tabTextToDisplay[4].push_back("Prenom   : ACcasse");
	tabTextToDisplay[4].push_back("Nom      : Symphozik");
	tabTextToDisplay[4].push_back("Job      : Compositeur");
	tabTextToDisplay[4].push_back("Statut   : A des vers au cul");
	tabTextToDisplay[4].push_back("Note:");
	tabTextToDisplay[4].push_back("Ne peut pas s'epempecher de bouger");
	tabTextToDisplay[4].push_back("A extremement peur du silence qui tue");
	tabTextToDisplay[4].push_back("Parle peu mais fait pourtant enormement de bruit");

	tabTextToDisplay[5].push_back("Prenom   : Cafette");
	tabTextToDisplay[5].push_back("Nom      : Lachaude");
	tabTextToDisplay[5].push_back("Job      : Secretaire");
	tabTextToDisplay[5].push_back("Statut   : Celibataire ( 0473/69.69.69 )");
	tabTextToDisplay[5].push_back("Note:");
	tabTextToDisplay[5].push_back("Est amie avec Nymphne");
	tabTextToDisplay[5].push_back("A peur de Looping");
	tabTextToDisplay[5].push_back("Fait le pire cafe au monde");

	tabTextToDisplay[6].push_back("Prenom   : Buenosh");
	tabTextToDisplay[6].push_back("Nom      : Elportosh");
	tabTextToDisplay[6].push_back("Job      : Macon");
	tabTextToDisplay[6].push_back("Statut   : Squatte les locaux");
	tabTextToDisplay[6].push_back("Note:");
	tabTextToDisplay[6].push_back("Fuit un sherif hargneux");
	tabTextToDisplay[6].push_back("Pompe un maximum de cafe gratuitement");
	tabTextToDisplay[6].push_back("Possede un casque bizarre qu'il ne retire jamais");
	tabTextToDisplay[6].push_back("A peur que le ciel lui tombe sur la tete");

	tabTextToDisplay[7].push_back("Prenom   : luckypasluc");
	tabTextToDisplay[7].push_back("Nom      : ThewalkerAlive");
	tabTextToDisplay[7].push_back("Job      : Sherif ( deconne pas mec )");
	tabTextToDisplay[7].push_back("Statut   : decede");
	tabTextToDisplay[7].push_back("Note:");
	tabTextToDisplay[7].push_back("Aime manger du serpent au coin du feu");
	tabTextToDisplay[7].push_back("Pourchassera eternellement Buenosh Elportosh");
	tabTextToDisplay[7].push_back("Possede un cheval commme fidele compagnon");
	tabTextToDisplay[7].push_back("Est mort en tentant de traverser l'ocean atlantique avec son cheval");

	// init TypingLetter
	displayText[0].init( ptrMyPlayerRecieved, maFonte, &tabTextToDisplay[0] );
	displayText[1].init( ptrMyPlayerRecieved, maFonte, &tabTextToDisplay[1] );
	displayText[2].init( ptrMyPlayerRecieved, maFonte, &tabTextToDisplay[2] );
	displayText[3].init( ptrMyPlayerRecieved, maFonte, &tabTextToDisplay[3] );
	displayText[4].init( ptrMyPlayerRecieved, maFonte, &tabTextToDisplay[4] );
	displayText[5].init( ptrMyPlayerRecieved, maFonte, &tabTextToDisplay[5] );
	displayText[6].init( ptrMyPlayerRecieved, maFonte, &tabTextToDisplay[6] );
	displayText[7].init( ptrMyPlayerRecieved, maFonte, &tabTextToDisplay[7] );

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
	bomb01.load("bomb01.png");
	bomb01Chiffre.load("bomb01_chiffre.jpg");
	photoCredit[0].load("credit1.jpg");
	photoCredit[1].load("credit2.jpg");
	photoCredit[2].load("credit3.jpg");
	photoCredit[3].load("credit4.jpg");
	photoCredit[4].load("credit5.jpg");
	photoCredit[5].load("credit6.jpg");
	photoCredit[6].load("credit7.jpg");
	photoCredit[7].load("credit8.jpg");

	tpsBlinkPoint = ofGetElapsedTimef();
	timeBlinkLetter = ofGetElapsedTimeMillis();
	timeWaitLeavingWelcome = -1; // = non encore initalisé
	timeLoadBarFPS = ofGetElapsedTimeMillis();
	timerTrollDance = ofGetElapsedTimeMillis();
	timerForTypingLetter = ofGetElapsedTimeMillis();
	
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
