#pragma once
class PlayerSettings
{
private:
	static PlayerSettings* playerSettings;

	PlayerSettings();
	~PlayerSettings();

public:
	static PlayerSettings* Instance();
	static void Release();
	void Reset();
public:
	 int playerLifes;
	 int playerScore;


};

