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


	LOG("Loading SFX");

	sounds[0] = Mix_LoadWAV("Assets/Audio/SFX/Intro_Sounds/INT_SFX.wav");
	sounds[1] = Mix_LoadWAV("Assets/Audio/SFX/General_Sounds/MM_SelectSound.wav");
	sounds[2] = Mix_LoadWAV("Assets/Audio/SFX/General_Sounds/MM_ChangeOptionSound.wav");
	sounds[3] = Mix_LoadWAV("Assets/Audio/SFX/In_Game_Sounds/Basic_Sounds/G_PutBombSound.wav");
	sounds[4] = Mix_LoadWAV("Assets/Audio/SFX/In_Game_Sounds/Basic_Sounds/G_ExplosionSound.wav");
	sounds[5] = Mix_LoadWAV("Assets/Audio/SFX/In_Game_Sounds/Basic_Sounds/G_DeathSound.wav");
	sounds[6] = Mix_LoadWAV("Assets/Audio/SFX/In_Game_Sounds/Basic_Sounds/G_GameOverSound.wav");
	sounds[7] = Mix_LoadWAV("Assets/Audio/SFX/In_Game_Sounds/Basic_Sounds/G_LevelCompleteSound.wav");
	sounds[8] = Mix_LoadWAV("Assets/Audio/SFX/In_Game_Sounds/Extra_Points_Sounds/G_ExtraCoinsBackgroundSound.wav");
	sounds[9] = Mix_LoadWAV("Assets/Audio/SFX/In_Game_Sounds/Extra_Points_Sounds/G_ExtraPointsStep.wav");
	sounds[10] = Mix_LoadWAV("Assets/Audio/SFX/In_Game_Sounds/Extra_Points_Sounds/G_PickCoinSound.wav");
	sounds[11] = Mix_LoadWAV("Assets/Audio/SFX/In_Game_Sounds/Objects_and_PowerUps_Sounds/G_PickPowerUpSound.wav");
	sounds[12] = Mix_LoadWAV("Assets/Audio/SFX/In_Game_Sounds/Miscellaneous_Sounds/G_CollisionWithBombInSound.wav");
	sounds[13] = Mix_LoadWAV("Assets/Audio/SFX/In_Game_Sounds/Miscellaneous_Sounds/G_RunFromBombSound.wav");
	sounds[14] = Mix_LoadWAV("Assets/Audio/SFX/In_Game_Sounds/Miscellaneous_Sounds/G_OneMinuteLeft.wav");
	sounds[15] = Mix_LoadWAV("Assets/Audio/SFX/In_Game_Sounds/Miscellaneous_Sounds/G_RanOutOfTime.wav");
	sounds[16] = Mix_LoadWAV("Assets/Audio/SFX/In_Game_Sounds/Miscellaneous_Sounds/G_OrbsDestroyedSound.wav");
	sounds[17] = Mix_LoadWAV("Assets/Audio/SFX/In_Game_Sounds/Miscellaneous_Sounds/G_WhistlingEndSound.wav");

	return ret;

}

bool ModuleAudio::CleanUp() {	//Frees all Mix_Music from the musics array and exits MIX library

	LOG("Cleaning up Audio libraries");

	// Free all music existing in the musics array
	Mix_FreeMusic(music);

	//Free all sounds existing on the sounds array
	for (uint i = 0; i < MAX_SOUNDS; ++i)
	{
		if (sounds[i] != nullptr)
		{
			Mix_FreeChunk(sounds[i]);
			sounds[i] = nullptr;
		}
	}

	//Quit MIX
	Mix_CloseAudio();
	Mix_Quit();

	return true;
}

bool ModuleAudio::PlayMusic(const char* path, float fade_time) {	//Loads and returns a Mix_Music* from the given path

	bool ret = true;

	if (music != NULL)
	{
		if (fade_time > 0.0f)
		{
			// WARNING: This call blocks the execution until fade out is done
			Mix_FadeOutMusic((int)(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if (music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if (fade_time > 0.0f)
		{
			if (Mix_FadeInMusic(music, -1, (int)(fade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if (Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

uint ModuleAudio::LoadSound(const char* path)
{
	uint ret = 0;
	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if (chunk == nullptr)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		for (ret = 0; ret < MAX_SOUNDS; ++ret)
		{
			if (sounds[ret] == nullptr)
			{
				sounds[ret] = chunk;
				break;
			}
		}
	}

	return ret;
}

bool ModuleAudio::PlaySound(uint index, int repeat)
{
	bool ret = false;

	if (sounds[index] != nullptr)
	{
		Mix_PlayChannel(-1, sounds[index], repeat);
		ret = true;
	}

	return ret;
}