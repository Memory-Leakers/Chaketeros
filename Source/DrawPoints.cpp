#include "DrawPoints.h"

NumText drawPoints;

void DrawPoints::Start()
{
	drawPoints.Start();
}

void DrawPoints::DrawScore(int score, iPoint position)
{
	for (int i = 0; i < 4; ++i)
	{
		if (!boolsArray[i])
		{
			boolsArray[i] = true;
			numsArray[i] = score;
			positionsArray[i] = position;
			timers[i].Reset();
			
			break;
		}
	}
}

int debugInt[4] = { 0 };

void DrawPoints::Update()
{
	for (int i = 0; i < 4 ;++i)
	{
		if (boolsArray[i])
		{
			timers[i].Update();
			if (timers[i].getDeltaTime() <= 1.5f)
			{
				iPoint temp = { -6, 4 };

				debugInt[i]++;

				if ( debugInt[i] % 15 == 0)
				{
					positionsArray[i] += {0, -1};
				}

				drawPoints.DrawNum(numsArray[i], positionsArray[i] + temp ,3 ,1 , 1000.0f);
			}
			else
			{
				boolsArray[i] = false;
				timers[i].Reset();
				debugInt[i] = 0;
			}
			
		}
	}
}

DrawPoints::DrawPoints()
{

}

DrawPoints::~DrawPoints()
{
}
