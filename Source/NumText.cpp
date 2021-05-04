#include "NumText.h"

#include <iostream>
#include <vector>
#include <stack>


NumText::NumText()
{
	//	Init Font 0 (standard) Rects
	for (int i = 0; i < 10; i++)
	{
		fonts[0][i] = { 8 * i, 16, 8, 8 };
	}

	//	Init Font 1 (Game Over) Rects
	for (int i = 0; i < 10; i++)
	{
		fonts[1][i] = { 14 * i, 64, 14, 15 };
	}

	chars[0] = { 80, 16, 8, 8 };
	chars[1] = { 0,32,16,8 };
}

NumText::~NumText()
{
}

void NumText::Start()
{
	texFonts = App->textures->Load("Assets/Images/Sprites/UI_Sprites/Misc.png");
}

void NumText::DrawNum(int num, iPoint pos, int font)
{
	//	Declare Variables
	stack<int> digits;
	vector<int> digitVec;
	int totalDigits;

	#pragma region Digit Order Logic
	//Getting digits from number in order Logic
	while (num > 0)
	{
		int digit = num % 10;
		num /= 10;
		digits.push(digit);
	}

	totalDigits = digits.size();

	while (!digits.empty())
	{
		int digit = digits.top();
		digitVec.push_back(digit);
		digits.pop();
	}
	#pragma endregion

	#pragma region Drawing Num Logic
	//Check wich font we're using
	switch (font)
	{
	case 0:
		for (int i = 0; i < totalDigits; ++i)
		{
			iPoint tempPos = pos;
			tempPos.x += (9 * i);						//Offset from num to num
			//App->render->DrawTexture(texFonts, tempPos, &fonts[font][digitVec.at(i)]); //digitVec returns the number that must be shown
			App->render->AddTextureRenderQueue(texFonts, tempPos, &fonts[font][digitVec.at(i)], 2);
		}
		break;
	case 1:

		//	Variables to control digit separation
		bool isOneBefore = false;
		int xOffset = 15;
		int xPos = pos.x;

		//	Logic to control digit separation (if there's a 1 after another 1 or not, and what to do)
		for (int i = 0; i < totalDigits; i++)
		{
			if (isOneBefore)
			{
				if (!digitVec.at(i) == 1)
				{
					xOffset = 12;
				}
				else
				{
					xOffset = 11;
				}
				isOneBefore = false;
			}

			if (digitVec.at(i) == 1)
			{
				if (xOffset == 15)
				{
					xOffset = 12;
				}
				isOneBefore = true;
			}

			//App->render->DrawTexture(texFonts, { xPos + (xOffset * i), 152 }, &fonts[1][digitVec.at(i)]);	//	Drawing Num
			App->render->AddTextureRenderQueue(texFonts, { xPos + (xOffset * i), 152 }, &fonts[1][digitVec.at(i)], 2);
		}
	}

	#pragma endregion

}

/// <summary>
/// Draw Non-Number character
/// </summary>
/// <param name="character">0 = " : " 1 = "SC"</param>
/// <param name="pos">Position where the character will be displayed on the screen</param>
void NumText::DrawChar(int character, iPoint pos)
{
	switch (character)
	{
	case 0:
		//App->render->DrawTexture(texFonts, pos, &chars[0]);
		App->render->AddTextureRenderQueue(texFonts, pos, &chars[0], 2);
		break;
	case 1:
		//App->render->DrawTexture(texFonts, pos, &chars[1]);
		App->render->AddTextureRenderQueue(texFonts, pos, &chars[1], 2);
		break;
	}
}
