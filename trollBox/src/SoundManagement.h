#pragma once
#include "ofMain.h"

namespace SoundManagement{

	static map<string,ofSoundPlayer> soundPlayer;
	static string soundPlayed;

	void static init(){
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

			ofSoundPlayer tmp;
			tmp.loadSound("sound\\" + str + ".mp3");
			soundPlayer[str] = tmp;
		}

	};


	void static playSound(string name){

		soundPlayed = name;
		soundPlayer[name].play();

	};


	void static stopSound(string name){

		if ( soundPlayer[name].isPlaying() ){
			soundPlayer[name].stop();
		}

	};
};

