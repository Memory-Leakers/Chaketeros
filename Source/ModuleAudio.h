#ifndef _MODULEAUDIO_H_
#define _MODULEAUDIO_H_

#include "Module.h"

#include "External/SDL_mixer/include/SDL_mixer.h"
#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_SOUNDS 32

enum SFX {

	//Menu SFX
	INTRO_SFX,
	SELECT_SFX,
	CHANGE_SELECT_SFX,

	//In-Game SFX
	PUT_BOMB_SFX,
	EXPLOSION_BOMB_SFX,
	DEATH_SFX,
	GAME_OVER_SFX,
	LEVEL_COMPLETE_SFX,
	EXTRA_COINS_BCKGR_SFX,
	EXTRA_COINS_STEP_SFX,
	PICK_COIN_SFX,
	PICK_POWERUP_SFX,
	COLLISION_IN_BOMB_SFX,
	COLLISION_OUT_BOMB_SFX,
	ONE_MINUTE_LEFT_SFX,
	OUT_OF_TIME_SFX,
	ORBS_DESTROYED_SFX,
	END_WHISTLING_SFX,

};

class ModuleAudio : public Module {

public:

	ModuleAudio();	

	~ModuleAudio();	//Default Destructor

	bool Init() override; //Inits MIX libraries and OpenAudio()

	bool CleanUp() override; //Frees Music and exits MIX

	bool CleanUpScene();

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

