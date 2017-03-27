#pragma once
#include "ofMain.h"

class SoundManagement{

	map<string,ofSoundPlayer> soundPlayer;
	string soundPlayed;
public:
	void init();
	void playSound(string name, bool verifIfSoundIsPlaying=false);
	void stopSound();

	// variables
	float soundVolume=1.0f;
};

