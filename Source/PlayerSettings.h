#ifndef _PLAYERSETTINGS_H_
#define _PLAYERSETTINGS_H_

class PlayerSettings
{
private:

	static PlayerSettings* playerSettings;

	PlayerSettings();
	~PlayerSettings();

	enum Kangaroos
	{
		BLUE,
		GREEN,
		PINK,
		PURPLE,
		YELLOW
	};

public:

	static PlayerSettings* Instance();
	static void Release();
	void Reset();

public:

	 int playerLifes;

	 int playerScore;

	 int powerUpFlame;

	 int maxBombs = 1;

	 bool powerUpKick;

	 bool powerUpLouies[5];
};
#endif
