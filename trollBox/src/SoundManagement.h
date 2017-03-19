#pragma once
#include "ofMain.h"

class SoundManagement{

	map<string,ofSoundPlayer> soundPlayer;
	string soundPlayed;
public:
	void init(){
		// charge tous les sons.
		string name[] = {"fail01",
			"megaSucess01",
			"sucess01",
			"sucess02",
			"sucess03",
			"valide01",
			"valide02",
			"valide03",
			"youpi01",
			"clap01"
		};

		for each (string str in name){

			// charge le son temporairement
			ofSoundPlayer tmp;
			tmp.loadSound("sound\\" + str + ".mp3");
			// crée une copie dans la map pour l'utiliser plus tard au besoin.
			soundPlayer[str] = tmp;
		}

	};


	void playSound(string name){

		soundPlayed = name;
		soundPlayer[name].play();

	};


	void stopSound(){

		if ( soundPlayer[soundPlayed].isPlaying() ){
			soundPlayer[soundPlayed].stop();
		}

	};
};

