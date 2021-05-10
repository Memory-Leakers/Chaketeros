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
}

PlayerSettings::PlayerSettings()
{
    Reset();
}
PlayerSettings::~PlayerSettings()
{

}