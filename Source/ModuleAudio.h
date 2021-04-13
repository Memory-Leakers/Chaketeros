#ifndef _MODULEAUDIO_H_
#define _MODULEAUDIO_H_

#include "Module.h"

#include "External/SDL_mixer/include/SDL_mixer.h"
#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_SOUNDS 32



class ModuleAudio : public Module {

public:

	ModuleAudio();	

	~ModuleAudio();	//Default Destructor

	bool Init() override; //Inits MIX libraries and OpenAudio()

	bool CleanUp() override; //Frees Music and exits MIX

	//Loads the introduced path into a Mix_Music pointer
	//and locates it into de musics[MAX_MUSICS] array
	bool PlayMusic(const char* path, float fade_time); 

	uint LoadSound(const char* path);

	bool PlaySound(uint index, int repeat);

	//Array of total musics

	Mix_Music* music;
	Mix_Chunk* sounds[MAX_SOUNDS] = { nullptr };

};



#endif // !_MODULEAUDIO_H_

