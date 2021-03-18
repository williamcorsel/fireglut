/**
 * Written by William Corsel - 2049481
 * For the Computer Graphics 2019 course at Leiden University
 */

#include "sound.h"

#include <iostream>

Sound::Sound(void){
    std::cout << "OpenAL init" << std::endl;
    alutInit(0, NULL);
    alGetError();
}


Sound::~Sound(void){
	cleanup();
    alutExit();
}


void Sound::playSound(const std::string file){
    if(!enabled) // if sound is disabled don't play
        return;

    buffer = alutCreateBufferFromFile(file.c_str()); // load data in buffer

    alGenSources(1, &source); // generate source
    alSourcei(source, AL_BUFFER, buffer);

    alSourcePlay(source); // Play the sound file
    playing = true;

    std::cout << "Loaded effect: " << file << std::endl;
}


const void Sound::getSound(void){
    if(!enabled) // if sound is disabled read the buffer
        return;

    ALint state; // State for checking if the sound is still playing

    alGetSourcei(source, AL_SOURCE_STATE, &state); // Get sound

    if(state != AL_PLAYING){ // If not playing anymore
        cleanup();
    }
}

void Sound::cleanup(void){
	alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    playing = false;
}


void Sound::enable(void){ enabled = true; }
void Sound::disable(void){ enabled = false; }

void Sound::switchEnable(void){
    if(enabled){
        disable();
    }else{
        enable();
    }
}

