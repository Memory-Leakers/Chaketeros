#include "PlayerSettings.h"

PlayerSettings* PlayerSettings::playerSettings = nullptr;

PlayerSettings* PlayerSettings::Instance()
{
    if (playerSettings == nullptr)
    {
        playerSettings = new PlayerSettings();
    }
    return playerSettings;
}

void PlayerSettings::Release()
{
    delete playerSettings;
    playerSettings = nullptr;
}

void PlayerSettings::Reset()
{
    playerLifes = 3;
    playerScore = 0;
    powerUpBomb = 0;
    powerUpFlame = 0;
    powerUpKick = false;
    powerUpVest = false;

    for (int i = 0; i < 4; i++)
    {
        powerUpKangaroo[i] = false;
    }
}

PlayerSettings::PlayerSettings()
{
    Reset();
}
PlayerSettings::~PlayerSettings()
{

}