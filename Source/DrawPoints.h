#ifndef _DRAWPOINTS_H_
#define _DRAWPOINTS_H_

#include "Timer.h"
#include "NumText.h"

class DrawPoints
{
private:
	int numsArray[4];
	bool boolsArray[4];
	iPoint positionsArray[4];
	Timer timers[4];

public:

	void Start();

	void Update();

	void DrawScore(int score, iPoint position);

	DrawPoints();
	~DrawPoints();

};



#endif // !_DRAWPOINTS_H_


