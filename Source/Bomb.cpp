#include "Bomb.h"

#include <iostream>
using namespace std;

Bomb::Bomb()
{
	LOG("Bomb constructor");
}

Bomb::Bomb(iPoint pos, SDL_Texture* tex, Particle* e1, Particle* e2, Particle* e3) :Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::BOMB, App->scene), tex)
{
	explosionCenter = *e1;
	explosionMiddle = *e2;
	explosionEnd = *e3;

	// Inicializar animacion prestablecida de la bomba
	defaultAnim.hasIdle = false;
	defaultAnim.speed = 0.02f;
	defaultAnim.loop = true;
	defaultAnim.PushBack({ 1,1,16,16 });  //small
	defaultAnim.PushBack({ 1,21,16,16 }); //midle
	defaultAnim.PushBack({ 1,39,16,16 }); //big
	defaultAnim.PushBack({ 1,21,16,16 }); //midle

	// Assignar anamacion prestablecida a currentAnim
	currentAnim = &defaultAnim;

	// Init TimeCount
	startCountTime = SDL_GetPerformanceCounter();

	// SFX Put bomb
	App->audio->PlaySound(SFX::PUT_BOMB_SFX, 0);
}


Bomb::Bomb(Player* player, SDL_Texture* tex, Particle* e1, Particle* e2, Particle* e3, Tile* tile)
:Obstacle({ player->getCurrentTilewWorldPos().x, player->getCurrentTilewWorldPos().y, 16, 16 }, true, App->collisions->AddCollider({ player->getCurrentTilewWorldPos().x, player->getCurrentTilewWorldPos().y, 16, 16 }, Type::BOMB, App->scene), tex)
{
 	this->player = player;
	lv1Tile = tile;

	explosionCenter = *e1;
	explosionMiddle = *e2;
	explosionEnd = *e3;

	explotionRange += player->pUpFlame;

	// Inicializar animacion prestablecida de la bomba
	defaultAnim.hasIdle = false;
	defaultAnim.speed = 0.02f;
	defaultAnim.loop = true;
	defaultAnim.PushBack({ 1,1,16,16 });  //small
	defaultAnim.PushBack({ 1,21,16,16 }); //midle
	defaultAnim.PushBack({ 1,39,16,16 }); //big
	defaultAnim.PushBack({ 1,21,16,16 }); //midle

	// Assignar anamacion prestablecida a currentAnim
	currentAnim = &defaultAnim;

	// Init TimeCount
	startCountTime = SDL_GetPerformanceCounter();

	// SFX Put bomb
	App->audio->PlaySound(SFX::PUT_BOMB_SFX, 0);
}

Bomb::~Bomb()
{
}

void Bomb::Update()
{
	ColUpdate();

	currentAnim->Update();

	// Count down
	if (!pendingToDelete)
	{
		// Cuenta Atras para que la bomba se explota
		double currentCountTime = SDL_GetPerformanceCounter();
		double timeOffset = SDL_GetPerformanceFrequency();

		if (((currentCountTime - startCountTime) / timeOffset) >= explotionTime)
		{
			App->audio->PlaySound(SFX::EXPLOSION_BOMB_SFX, 0);
			Die();
		}
	}
}

void Bomb::PostUpdate()
{
	if(!pendingToDelete)
	{
		App->render->DrawTexture(texture, getPosition(), &currentAnim->GetCurrentFrame());
	}
}

void Bomb::Die()
{
	LOG("BombDie");
	pendingToDelete = true;
	// Centro de la explocion
	App->particle->AddParticle(explosionCenter, getPosition(), Type::EXPLOSION);

	// Calculate spawn number for dir
	int explotionNum[4] = { 0,0,0,0 };
	int tileX, tileY;
	tileX = lv1Tile->getTilePos(getPosition()).x;
	tileY = (lv1Tile->getTilePos(getPosition()).y) - 1;
	iPoint dirSpawn[4] = { {1,0},{0,1},{-1,0},{0,-1} };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= explotionRange; j++)
		{
			if (lv1Tile->Level1TileMap[tileY + (dirSpawn[i].y) * j][tileX + (dirSpawn[i].x) * j ] == 0||
				lv1Tile->Level1TileMap[tileY + (dirSpawn[i].y) * j][tileX + (dirSpawn[i].x) * j] == 4)
			{
				explotionNum[i]++;
			}
			else
			{
				if(lv1Tile->Level1TileMap[tileY + (dirSpawn[i].y) * j][tileX + (dirSpawn[i].x) * j] !=1
					&&lv1Tile->Level1TileMap[tileY + (dirSpawn[i].y) * j][tileX + (dirSpawn[i].x) * j] != 2
					&& lv1Tile->Level1TileMap[tileY + (dirSpawn[i].y) * j][tileX + (dirSpawn[i].x) * j] != 7
					&& lv1Tile->Level1TileMap[tileY + (dirSpawn[i].y) * j][tileX + (dirSpawn[i].x) * j] != 9)
				{
					explotionNum[i]++;
				}
				break;
			}
		}
	}

	// Create explotion
	for (int i = 1; i < explotionRange; i++)
	{
		// 4 direction for explotion
		iPoint dir[4] = {
		{ (i) * 16, 0 }, // Right
		{ 0, (i) * 16 }, // Down
		{ (i) * -16, 0 },// Left
		{ 0, (i) * -16 } // Up
		};

		// 4 rotation for explotion
		float rotation[4] = { 0, 270, 180, 90 };
		bool flipHor = true;

		for (int j = 0; j < 4; ++j)
		{
			if (explotionNum[j]-- > 0)
			{
				flipHor = true;
				// Explosopn End
				if (i == explotionRange - 1)
				{
					++i;
					if (j == 2)
					{
						flipHor = false;
					}
					App->particle->AddParticle(explosionEnd, getPosition() + dir[j], Type::EXPLOSION, flipHor, rotation[j]);
					--i;
				}
				else
				{
					// Explosion Middle
					App->particle->AddParticle(explosionMiddle, (getPosition() + dir[j]), Type::EXPLOSION, flipHor, rotation[j]);
				}
			}			
		}
	}
}

void Bomb::CleanUp()
{
	player->maxBombs++;
	getCollider()->pendingToDelete = true;
}
