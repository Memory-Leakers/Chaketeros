#include "Player.h";

#include "Bomb.h"

#include <iostream>;
using namespace std;

SDL_Rect* rect;

Player::Player(Tile* tileMap, Obstacle** obs)
{
	this->tileMap = tileMap;
	obstacles = obs;

	position.x = 40;
	position.y = 32;

	//Rect for col
	bounds.x = position.x;
	bounds.y = position.y;
	bounds.w = 16;
	bounds.h = 16;

	#pragma region Init Anim

	//Animation Down
	downAnim.PushBack({ 17, 2, 16, 22 });//IDLE
	downAnim.PushBack({ 0, 2, 16, 22 });
	downAnim.PushBack({ 17, 2, 16, 22 });//IDLE
	downAnim.PushBack({ 33, 2, 16, 22 });
	downAnim.speed = defaultPlayerSpeed;

	//Animation UP
	upAnim.PushBack({ 65,2,16,22 });//IDLE
	upAnim.PushBack({ 49,2,16,22 });
	upAnim.PushBack({ 65,2,16,22 });//IDLE
	upAnim.PushBack({ 81,2,16,22 });
	upAnim.speed = defaultPlayerSpeed;

	//Animation RIGHT
	rightAnim.PushBack({ 17,26,16,22 });//IDLE
	rightAnim.PushBack({ 0,26,16,22 });
	rightAnim.PushBack({ 17,26,16,22 });//IDLE
	rightAnim.PushBack({ 33,26,16,22 });
	rightAnim.speed = defaultPlayerSpeed;

	//Animation LEFT
	leftAnim.PushBack({ 17,26,16,22 });//IDLE
	leftAnim.PushBack({ 0,26,16,22 });
	leftAnim.PushBack({ 17,26,16,22 });//IDLE
	leftAnim.PushBack({ 33,26,16,22 });
	leftAnim.speed = defaultPlayerSpeed;

	currentAnimation = &downAnim;

	#pragma endregion

	//Load Sound
	extraCoinsStepSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Extra_Points_Sounds/G_ExtraPointsStep.wav");
	deathSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Basic_Sounds/G_DeathSound.wav");
	gameOverSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Basic_Sounds/G_GameOverSound.wav");
}

Player::~Player()
{
	if (playerDestroyed != nullptr)
	{
		delete playerDestroyed;
		playerDestroyed = nullptr;
	}
}

bool Player::Start()
{
	bool ret = true;

	col = App->collisions->AddCollider(bounds, Type::PLAYER, App->scene);

	texture = App->textures->Load("Assets/Images/Sprites/Player_Sprites/BombermanSheet.png");
	texBomb = App->textures->Load("Assets/Images/Sprites/Player_Sprites/Bomb.png");
	playerInvensible.texInvensible = App->textures->Load("Assets/Images/Sprites/PowerUps_Sprites/Powerups.png");

#pragma region Init particle

	playerDestroyed = new Particle(500.0f, 0.2f, texture);

	playerDestroyed->anim.PushBack({ 4, 71, 22, 21});
	playerDestroyed->anim.PushBack({ 26, 71, 22, 21});
	playerDestroyed->anim.PushBack({ 48, 71, 22, 21});
	playerDestroyed->anim.PushBack({ 70, 71, 22, 21});
	playerDestroyed->anim.PushBack({ 92, 71, 22, 21});
	playerDestroyed->anim.PushBack({ 114, 71, 22, 21});

	// Init move direccion
	for (int i = 0; i < 4; i++)
	{
		canMoveDir[i] = true;
	}

	// Las tile position of player
	lastTilePos = getCurrentTilePos();

#pragma endregion

	return ret;
}

UpdateResult Player::Update()
{
	// Invensible Logic
	InvensibleCheck();

	int speedX = 0;
	int speedY = 0;
	GamePad& pad = App->input->pads[0];
	
	if (!App->debug->debugCamera) 
	{
	#pragma region Movements keys

			if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT || pad.left_y < 0.0f)
			{
				isFlip = false;
				currentAnimation = &upAnim;
				currentAnimation->hasIdle = false;
				if (position.y > mapLimits[App->scene->currentLevel][0].y && canMoveDir[UP]) // Limiitar movimiento en la mapa//
				{
					//position.y -= speed;
					speedY = -speed;
				}
				// movemenet fix
				else if (App->input->keys[SDL_SCANCODE_A] == KEY_IDLE && App->input->keys[SDL_SCANCODE_D] == KEY_IDLE && pad.left_x == 0.0f)
				{
					iPoint tempTilePos = getCurrentTilePos();

					int tileX = getCurrentTileWorldPos().x;

					tempTilePos.y--; // offset

					int playerAbove = tileMap->LevelsTileMaps[App->scene->currentLevel][tempTilePos.y - 1][tempTilePos.x];

					//if target grid don't have obstacle
					if (playerAbove == 4 || playerAbove == 0 || playerAbove == 12 || playerAbove == 13)
					{
						// optimize movemente
						if (pivotPoint.x > (tileX + 8))
						{
							position.x -= speed;
						}
						else if (pivotPoint.x < (tileX + 8))
						{
							position.x += speed;
						}
					}
				}

				SpecialSound();
			}

			if ((App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT || pad.left_y > 0.0f) && (App->input->keys[SDL_SCANCODE_W] != KEY_REPEAT || pad.left_y < 0.0f))
			{
				isFlip = false;
				currentAnimation = &downAnim;
				currentAnimation->hasIdle = false;
				if (position.y < mapLimits[App->scene->currentLevel][1].y && canMoveDir[DOWN]) // Limiitar movimiento en la mapa
				{
					//position.y += speed;
					speedY = speed;
				}
				// movement fix
				else if (App->input->keys[SDL_SCANCODE_A] == KEY_IDLE && App->input->keys[SDL_SCANCODE_D] == KEY_IDLE && pad.left_x == 0.0f)
				{
					iPoint tempTilePos = getCurrentTilePos();

					tempTilePos.y--; // offset

					int tileX = getCurrentTileWorldPos().x;

					int playerBelow = tileMap->LevelsTileMaps[App->scene->currentLevel][tempTilePos.y + 1][tempTilePos.x];

					//if target grid don't have obstacle
					if (playerBelow == 4 || playerBelow == 0)
					{
						// optimize movement
						if (pivotPoint.x > (tileX + 8))
						{
							position.x -= speed;
						}
						else if (pivotPoint.x < (tileX + 8))
						{
							position.x += speed;
						}
					}
				}

				SpecialSound();
			}

			if ((App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT || pad.left_x > 0.0f) && (App->input->keys[SDL_SCANCODE_A] != KEY_REPEAT || pad.left_x < 0.0f))
			{
				isFlip = true;
				currentAnimation = &rightAnim;
				currentAnimation->hasIdle = false;
				if (canMoveDir[RIGHT])
				{
					if (position.x < mapLimits[App->scene->currentLevel][1].x) // Limiitar movimiento en la mapa
					{
						speedX = speed;
					}
				}
				// movement fix
				else if (App->input->keys[SDL_SCANCODE_W] == KEY_IDLE && App->input->keys[SDL_SCANCODE_S] == KEY_IDLE && pad.left_y == 0.0f)
				{
					iPoint tempTilePos = getCurrentTilePos();

					int tileY = getCurrentTileWorldPos().y;

					tempTilePos.y--; // offset

					int playerRight = tileMap->LevelsTileMaps[App->scene->currentLevel][tempTilePos.y][tempTilePos.x + 1];

					//if target grid don't have obstacle
					if (playerRight == 4 || playerRight == 0 || playerRight == 12)
					{
						// optimize movement
						if (pivotPoint.y > (tileY + 8))
						{
							position.y -= speed;
						}
						else if (pivotPoint.y < (tileY + 8))
						{
							position.y += speed;
						}
					}
				}

				SpecialSound();
			}

			if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT || pad.left_x < 0.0f)
			{
				isFlip = false;
				currentAnimation = &leftAnim;
				currentAnimation->hasIdle = false;

				if (position.x > mapLimits[App->scene->currentLevel][0].x && canMoveDir[LEFT]) // Limiitar movimiento en la mapa
				{
					//position.x -= speed;
					speedX = -speed;
				}
				// movement fix
				else if (App->input->keys[SDL_SCANCODE_W] == KEY_IDLE && App->input->keys[SDL_SCANCODE_S] == KEY_IDLE && pad.left_y == 0.0f)
				{
					iPoint tempTilePos = getCurrentTilePos();

					int tileY = getCurrentTileWorldPos().y;

					tempTilePos.y--; // offset

					int playerLeft = tileMap->LevelsTileMaps[App->scene->currentLevel][tempTilePos.y][tempTilePos.x - 1];

					//if target grid don't have obstacle
					if (playerLeft == 4 || playerLeft == 0 || playerLeft == 12)
					{
						// optimize movement
						if (pivotPoint.y > (tileY + 8))
						{
							position.y -= speed;
						}
						else if (pivotPoint.y < (tileY + 8))
						{
							position.y += speed;
						}
					}
				}

				SpecialSound();
			}

	#pragma endregion
	}

	// Drop a bomb
	if ((App->input->keys[SDL_SCANCODE_J] == KEY_DOWN || pad.a == true) && App->scene->playerSettings->maxBombs > 0)
	{
		iPoint temp = getCurrentTilePos();
		temp.y--;
		int currentGrid = tileMap->LevelsTileMaps[App->scene->currentLevel][temp.y][temp.x];


		// If player not situate in glass capsule stairs
		if (currentGrid != 13 && currentGrid != 12)
		{
			for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
			{
				if (obstacles[i] == nullptr)
				{
					obstacles[i] = new Bomb(this, texBomb, tileMap);
					App->scene->playerSettings->maxBombs--;
					break;
				}
			}
		}
	}

	// Move
	position += {speedX, speedY};

	//	Move Camera on Player
	if (App->scene->currentLevel == 1)
	{
		iPoint tempPos = { position.x, 0 };

		App->render->CameraMove(tempPos);
	}

	// Player idle or walk state
	if (App->input->keys[SDL_SCANCODE_D] == KEY_IDLE && App->input->keys[SDL_SCANCODE_A] == KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_W] == KEY_IDLE && App->input->keys[SDL_SCANCODE_S] == KEY_IDLE && pad.left_x == 0.0f && pad.left_y == 0.0f)
	{
		currentAnimation->hasIdle = true;
	}

	// Update coliision
	col->SetPos(position);

	// Update animation
	currentAnimation->Update();

	// Update Pivot Point
	pivotPoint = { position.x + 8, position.y + 8 };

	#pragma region Debug keys

	//if(App->input->keys[SDL_SCANCODE_M] == KEY_DOWN)
	//{
	//	App->scene->playerSettings->powerUpFlame++;
	//}
	//if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
	//{
	//	godMode = !godMode;
	//}

	//if (App->input->keys[SDL_SCANCODE_F10] == KEY_DOWN)
	//{
	//	posMode = !posMode;

	//	if(posMode)
	//	{
	//		lastTilePos = getCurrentTilePos();
	//		tileMap->LevelsTileMaps[App->scene->currentLevel][lastTilePos.y - 1][lastTilePos.x] = -1;
	//	}
	//	else
	//	{
	//		tileMap->LevelsTileMaps[App->scene->currentLevel][tilePos.y - 1][tilePos.x] = 0;
	//	}
	//}

	#pragma endregion

	// Reset Movemenet
	for (int i = 0; i < 4; i++)
	{
		canMoveDir[i] = true;
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult Player::PostUpdate()
{
	if(pendingToDelete) return UpdateResult::UPDATE_CONTINUE;

	rect = &currentAnimation->GetCurrentFrame();

	iPoint tempPos = position;
	tempPos.y -= 6;

	if(isFlip)
	{
		//App->render->DrawRotateTexture(texture, tempPos, &rect, false, 180);
		App->render->AddTextureRenderQueue(texture, tempPos, rect, 1, position.y, false, 180);
	}
	else
	{
		//App->render->DrawTexture(texture, tempPos, &rect);
		App->render->AddTextureRenderQueue(texture, tempPos, rect, 1, position.y);
	}

	// Console Pos
	if (posMode)
	{
		// Update tile Point
		tilePos = getCurrentTilePos();
		if (tilePos != lastTilePos)
		{
			tileMap->LevelsTileMaps[App->scene->currentLevel][lastTilePos.y - 1][lastTilePos.x] = 0;
			tileMap->LevelsTileMaps[App->scene->currentLevel][tilePos.y - 1][tilePos.x] = -1;
			lastTilePos = tilePos;
		}
	}

	if(invensibleTime >= 0)
	{
		if (invensibleTime < 3)
		{
			playerInvensible.DrawInvensible = !playerInvensible.DrawInvensible;
			if(playerInvensible.DrawInvensible)
			{
				App->render->AddTextureRenderQueue(playerInvensible.texInvensible, { 95, 4 }, &playerInvensible.recInvensible, 2, 500);
			}			
		}
		else
		{
			App->render->AddTextureRenderQueue(playerInvensible.texInvensible, { 95, 4 }, &playerInvensible.recInvensible, 2, 500);
		}	
	}

	return UpdateResult::UPDATE_CONTINUE;
}

//TODO
iPoint Player::Move(int dir)
{
	GamePad& pad = App->input->pads[0];
	iPoint tempDir[4]
	{
		{ 0,-1 * speed}, // Up
		{ 0, 1 * speed}, // Down
		{-1 * speed, 0}, // Left
		{ 1 * speed, 0} // Right	 
	};

	iPoint tempSpeed = { 0,0 };

	Animation* tempAnim[4] = { &upAnim, &downAnim , &leftAnim, &rightAnim };

	bool tempFlip[] = { false,false,false,true };

	isFlip = tempFlip[dir];
	currentAnimation = tempAnim[dir];
	currentAnimation->hasIdle = false;


	//Left	A	|| pad.left_x < 0.0f
	//Right	D	|| pad.left_x > 0.0f
	//UP	W	|| pad.left_y < 0.0f
	//Down	S	|| pad.left_y > 0.0f

	if (position.y > mapLimits[App->scene->currentLevel][0].y && canMoveDir[dir]) // Limiitar movimiento en la mapa//
	{
		tempSpeed = tempDir[dir];
	}

	// movemenet fix
	else if (App->input->keys[SDL_SCANCODE_A] == KEY_IDLE && App->input->keys[SDL_SCANCODE_D] == KEY_IDLE && pad.left_x == 0.0f)
	{
		iPoint tempTilePos = getCurrentTilePos();

		int tileX = getCurrentTileWorldPos().x;

		tempTilePos.y--; // offset

		int playerAbove = tileMap->LevelsTileMaps[App->scene->currentLevel][tempTilePos.y - 1][tempTilePos.x];

		//if target grid don't have obstacle
		if (playerAbove == 4 || playerAbove == 0 || playerAbove == 13)
		{
			// optimize movemente
			if (pivotPoint.x > (tileX + 8))
			{
				position.x -= speed;
			}
			else if (pivotPoint.x < (tileX + 8))
			{
				position.x += speed;
			}
		}
	}

	SpecialSound();

	return tempSpeed;
}

void Player::OnCollision(Collider* col)
{
	if(!godMode)
	{
		switch (col->type)
		{
		case Type::EXPLOSION:
		case Type::ENEMY:
			if (invensibleTime <= 0 && InGrid(col)) Die(); break;

		case Type::FIREPOWER:
			App->scene->playerSettings->powerUpFlame++; break;

		case Type::BOMBPOWER:
			App->scene->playerSettings->maxBombs++; break;

		case Type::INVINCIBLEPOWER:
			invensibleTime = 10;
			playerInvensible.invensibleCount = SDL_GetTicks() - (App->debug->pauseTimeOffset * 1000);
			break;
		}
	}
}

void Player::WillCollision(Collider* col)
{
	if (!godMode)
	{
		// Choc
		if (col->type == Type::WALL || col->type == Type::DESTRUCTABLE_WALL || col->type == Type::BOMB && !InGrid(col))
		{
			//get col position x
			int bx = col->getPos().x;
			//get col position y
			int by = col->getPos().y;
			int px = position.x;
			int py = position.y;

			// case 1
			if ((px + 1 + bounds.w) >= bx && (px + 1) <= bx)
			{
				if ((py >= by && py < by + 16) || (py + bounds.h > by && py + bounds.h < by + 16))
				{
					canMoveDir[RIGHT] = false;
				}

			}
			// case 2
			if (bx + 16 >= px - 1 && (px - 1 + bounds.w) >= bx + 16)
			{
				if ((py >= by && py < by + 16) || (py + bounds.h > by && py + bounds.h < by + 16))
				{
					canMoveDir[LEFT] = false;
				}
			}
			// case 3
			if ((py + 1 + bounds.h) >= by && (py + 1) <= by)
			{
				if ((px >= bx && px < bx + 16) || (px + bounds.w > bx && px + bounds.w < bx + 16))
				{
					canMoveDir[DOWN] = false;
				}

			}
			// case 4
			if (by + 16 >= py - 1 && (py - 1 + bounds.h) >= by + 16)
			{
				if ((px >= bx && px < bx + 16) || (px + bounds.w > bx && px + bounds.w < bx + 16))
				{
					canMoveDir[UP] = false;
				}
			}
		}
	}
}

void Player::SpecialSound()
{
	// Special SFX
	playerTimer.Update();

	if (playerTimer.getDeltaTime() >= 0.5f) {

		if (ExtraPoints == true) {
			App->audio->PlaySound(extraCoinsStepSFX, 0);

		}
		playerTimer.Reset();
	}
}

void Player::InvensibleCheck()
{
	if (invensibleTime >= 0)
	{
		float tempTime = SDL_GetTicks() - (App->debug->pauseTimeOffset * 1000);

		if (((tempTime - playerInvensible.invensibleCount) * 0.001f) >= 0.1f)
		{
			playerInvensible.invensibleCount = tempTime;

			invensibleTime -= 0.1f;

			if (invensibleTime <= 0)
			{
				cout << "invensible time out" << endl;
			}
		}
	}
}

bool Player::InGrid(Collider* col)
{
	iPoint colGrid = tileMap->getTilePos(col->getPos());

	if(col->type==Type::ENEMY) // Detect enemy pivot point
	{
		iPoint tempPos = col->getPos();
		tempPos += {8, 8};
		colGrid = tileMap->getTilePos(tempPos);
	}
	
	if(colGrid == getCurrentTilePos())
	{
		return true;
	}

	return false;
}

iPoint Player::getCurrentTilePos()
{
	iPoint ret = pivotPoint;

	ret = tileMap->getTilePos(ret);

	return ret;
}

iPoint Player::getCurrentTileWorldPos()
{
	iPoint ret = pivotPoint;

	ret = tileMap->getTilePos(ret);
	ret = tileMap->getWorldPos(ret);

	return ret;
}

void Player::Die()
{
	App->audio->PlaySound(deathSFX, 0);
	App->audio->PlaySound(gameOverSFX, 0);
	pendingToDelete = true;
	posMode = false;

	if (this->col != nullptr)
	{
		this->col->pendingToDelete = true;
	}

	// Create die particle
	iPoint tempPos = position;
	tempPos -= {3, 5};
	App->particle->AddParticle(*playerDestroyed, tempPos.x, tempPos.y, Type::NONE, 5.1f);
}