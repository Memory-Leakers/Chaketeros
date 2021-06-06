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

    maxBomb = 1;

    remainBomb = maxBomb;

    powerUpFlame = 0;

    powerUpKick = false;

    for (int i = 0; i < 4; i++)
    {
        powerUpLouies[i] = false;
    }
    for (int i = 0; i < 3; i++)
    {
        isLevelCompleted[i] = false;
    }
}

void PlayerSettings::RemainBomb(bool remain)
{
    if (remain)
    {
        if (++remainBomb > maxBomb) 
        {
            remainBomb = maxBomb;
        }
    }
    
    else if (--remainBomb < 0)
    {
        remainBomb = 0;
    }
}

PlayerSettings::PlayerSettings()
{
    Reset();
}
PlayerSettings::~PlayerSettings()
{

}