/**
 * Written by William Corsel - 2049481
 * For the Computer Graphics 2019 course at Leiden University
 */

#ifndef SOUND_H
#define SOUND_H

#include <string>
#include "AL/alut.h"


// Class dealing with playing sounds
class Sound{
private:

    // Buffer for storing sound data
    ALuint buffer;
    
    // Sound source
    ALuint source;

    // Flag for enabling the sound engine
    bool enabled = true;

public:

    // Flag for letting know the sound file is being played
    bool playing = false;

    Sound(void);
    ~Sound(void);

    // Reads in a file from the sounds/ directory and stores it in the buffer
    // Sets playing to true
    void playSound(const std::string file);

    // Gets sound data to be played from the buffer
    // Checks if the sound has ended. If so set playing to false
    const void getSound(void);

	// Cleanup function for emptying buffers
	void cleanup(void);

    // Functions to switch sound engine on or off
    void disable(void);
    void enable(void);
    void switchEnable(void);

};

#endif
