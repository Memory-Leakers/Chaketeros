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

	void RemainBomb(bool remain);

public:

	 int playerLifes;

	 int playerScore;

	 int powerUpFlame;

	 int maxBomb = 1;

	 int remainBomb = maxBomb;

	 bool powerUpKick;

	 bool powerUpLouies[5];

	 bool isLevelCompleted[3];
};
#endif
