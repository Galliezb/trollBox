#pragma once
#include "SoundManagement.h"

void SoundManagement::init(){
	// charge tous les sons.
	string name[] = {
		"alarm01",
		"clap01",
		"fail01","fail02",
		"megaSucess01",
		"sucess01","sucess02","sucess03",
		"valide01","valide02","valide03",
		"waiting01",
		"youpi01",
		
	};

	for each (string str in name){

		// charge le son temporairement
		ofSoundPlayer tmp;
		tmp.loadSound("sound\\" + str + ".mp3");
		// crée une copie dans la map pour l'utiliser plus tard au besoin.
		soundPlayer[str] = tmp;
	}

};


void SoundManagement::playSound(string name, bool verifIfSoundIsPlaying){

	// si on demande à vérifier la lecture en cours
	if ( verifIfSoundIsPlaying ){
		// lance uniquement si le son n'est pas en cours
		if ( !soundPlayer[soundPlayed].isPlaying() ){
			soundPlayed = name;
			soundPlayer[name].play();
		}
	// si false, alors on joue quitte à redémarrer le son
	} else {

		soundPlayed = name;
		soundPlayer[name].play();

	}

}


void SoundManagement::stopSound(){

	if ( soundPlayer[soundPlayed].isPlaying() ){
		soundPlayer[soundPlayed].stop();
	}

}