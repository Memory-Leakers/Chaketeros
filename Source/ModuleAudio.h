#ifndef _MODULEAUDIO_H_
#define _MODULEAUDIO_H_

#include "Module.h"

#include "External/SDL_mixer/include/SDL_mixer.h"

#define MAX_MUSICS 8
#define MAX_SOUNDS 32

class ModuleAudio : public Module {

public:

	ModuleAudio();	

	~ModuleAudio();	//Default Destructor

	bool Init() override; //Inits MIX libraries and OpenAudio()

	bool CleanUp() override; //Frees Music and exits MIX

	//Loads the introduced path into a Mix_Music pointer
	//and locates it into de musics[MAX_MUSICS] array
	Mix_Music* LoadMusic(const char* path); 

	Mix_Chunk* LoadSound(const char* path);

	//Array of total musics

	Mix_Music* musics[MAX_MUSICS] = { nullptr };
	Mix_Chunk* sounds[MAX_SOUNDS] = { nullptr };

};



#endif // !_MODULEAUDIO_H_

