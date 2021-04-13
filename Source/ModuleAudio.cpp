#include "ModuleAudio.h"

#include "Application.h"

#include "External/SDL_mixer/include/SDL_mixer.h"

ModuleAudio::ModuleAudio() : Module() {

}

ModuleAudio::~ModuleAudio()
{}

bool ModuleAudio::Init() {	//Default Initialization of the audio libraries. used MIX_INIT_OGG and MIX_INIT_MOD flags

	LOG("Initializing audio libraries");
	bool ret = true;

	//Initializes flags and Mixer libraries
	int flags = MIX_INIT_OGG|MIX_INIT_MOD;
	int init = Mix_Init(flags);

	// Check if all flags were initialized correctly
	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mix lib. Mix_Init(): %s", Mix_GetError());
		ret = false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		LOG("Could not initialize Mix_OpenAudio: %s", Mix_GetError());
		ret = false;
	}

	return ret;

}

bool ModuleAudio::CleanUp() {	//Frees all Mix_Music from the musics array and exits MIX library

	LOG("Cleaning up Audio libraries");

	// Free all textures sill existing in the textures array
	for (uint i = 0; i < MAX_MUSICS; ++i)
	{
		if (musics[i] != nullptr)
		{
			Mix_FreeMusic(musics[i]);
			musics[i] = nullptr;
		}
	}

	Mix_Quit();
	return true;
}

Mix_Music* ModuleAudio::LoadMusic(const char* path) {	//Loads and returns a Mix_Music* from the given path

	Mix_Music *music = Mix_LoadMUS(path);

	if (music == NULL) { LOG("Could not load music with path %s. Mix_LoadMUS: %s", path, Mix_GetError()) }
	else
	{
		for (uint i = 0; i < MAX_MUSICS; ++i) {	//Puts the music pointer into the musics array
			if (musics[i] == nullptr)
			{
				musics[i] = music;
				break;
			}
		}
	}
	

	return music;	//Returns the music 
}