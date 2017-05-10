#include "SoundManagement.h"

void SoundManagement::init(){
	// charge tous les sons.
	string name[] = {
		"alarm01",
		"clap01",
		"credit01",
		"fail01","fail02","fail03",
		"forceHammer01",
		"hammer01",
		"megaSucess01",
		"sucess01","sucess02",
		"typingLetter01",
		"valide01","valide02","valide03",
		"waiting01",
		"youpi01",
		
	};
	/*

	/* NE FONCTIONNE PAS SUR LE RASPBERRY
	METTRE A JOUR LE COMPILATEUR GCC POUR QU'IL FONCTIONNE

	for each (string str in name){

		// charge le son temporairement
		ofSoundPlayer tmp;
		tmp.loadSound("sound\\" + str + ".mp3");
		// crée une copie dans la map pour l'utiliser plus tard au besoin.
		soundPlayer[str] = tmp;
	}
	*/
	for (short int i=0; i<17; i++){
		// charge le son temporairement
		ofSoundPlayer tmp;
		tmp.loadSound("sound/" + name[i] + ".mp3");
		// crée une copie dans la map pour l'utiliser plus tard au besoin.
		soundPlayer[(name[i])] = tmp;
	}

}


void SoundManagement::playSound(string name, bool verifIfSoundIsPlaying){

	soundPlayer[name].setVolume(soundVolume);

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