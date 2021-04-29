#include "Player.h";

#include <iostream>;
using namespace std;

Player::Player(Tile* level1Tile)
{
	this->level1Tile = level1Tile;

	position.x = 40;
	position.y = 32;
	//Rect for col
	bounds.x = 0;
	bounds.y = 0;
	bounds.w = 16;
	bounds.h = 16;

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
}

Player::~Player()
{
	col->pendingToDelete = true;

	if (playerDestroyed != nullptr)
	{
		delete playerDestroyed;
		playerDestroyed = nullptr;
	}
}

bool Player::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Images/Sprites/Player_Sprites/BombermanSheet.png"); // arcade version

	col = App->collisions->AddCollider(bounds, Type::PLAYER, App->scene);

	playerDestroyed = new Particle(500.0f, 0.05f, texture);

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

	

	return ret;
}

UpdateResult Player::Update()
{
	int speedX = 0;
	int speedY = 0;

	

	if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT)
	{
		isFlip = false;
		currentAnimation = &upAnim;
		currentAnimation->hasIdle = false;
		if (position.y > 32 && canMoveDir[UP]) // Limiitar movimiento en la mapa
		{
			//position.y -= speed;
			speedY = -1;
		}
		else if (App->input->keys[SDL_SCANCODE_A] == KEY_IDLE && App->input->keys[SDL_SCANCODE_D] == KEY_IDLE)
		{
			int tileX = level1Tile->getWorldPos(level1Tile->getTilePos(position)).x;

			if (pivotPoint.x <= (tileX + 4))
			{
				position.x -= speed;
			}
			else if (pivotPoint.x > (tileX + 4) &&
				pivotPoint.x < (tileX + 8))
			{
				position.x += speed;
			}
			else if (pivotPoint.x < (tileX + 10) &&
				pivotPoint.x >(tileX + 8))
			{
				position.x -= speed;
			}
			else if (pivotPoint.x >= (tileX + 10))
			{
				position.x += speed;
			}
		}
		playerTimer.Update();

		if (playerTimer.getDeltaTime() >= 0.5f) {

			if (ExtraPoints == true) {
				App->audio->PlaySound(SFX::EXTRA_COINS_STEP_SFX, 0);

			}
			playerTimer.Reset();

		}
	}

	

	if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_W] != KEY_REPEAT)
	{
		isFlip = false;
		currentAnimation = &downAnim;
		currentAnimation->hasIdle = false;
		if (position.y < 208 - 16 && canMoveDir[DOWN]) // Limiitar movimiento en la mapa
		{
			//position.y += speed;
			speedY = 1;
		}
		else if (App->input->keys[SDL_SCANCODE_A] == KEY_IDLE && App->input->keys[SDL_SCANCODE_D] == KEY_IDLE)
		{
			int tileX = level1Tile->getWorldPos(level1Tile->getTilePos(position)).x;

			if (pivotPoint.x <= (tileX + 4))
			{
				position.x -= speed;
			}
			else if (pivotPoint.x > (tileX + 4) &&
				pivotPoint.x < (tileX + 8))
			{
				position.x += speed;
			}
			else if (pivotPoint.x < (tileX + 10) &&
				pivotPoint.x >(tileX + 8))
			{
				position.x -= speed;
			}
			else if (pivotPoint.x >= (tileX + 10))
			{
				position.x += speed;
			}
		}
		playerTimer.Update();

		if (playerTimer.getDeltaTime() >= 0.5f) {

			if (ExtraPoints == true) {
				App->audio->PlaySound(SFX::EXTRA_COINS_STEP_SFX, 0);

			}
			playerTimer.Reset();

		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] != KEY_REPEAT)
	{
		isFlip = true;
		currentAnimation = &rightAnim;
		currentAnimation->hasIdle = false;
		if (canMoveDir[RIGHT])
		{
			if (position.x < 216) // Limiitar movimiento en la mapa
			{
				//position.x += speed;
				speedX = 1;
			}
		}
		else if (App->input->keys[SDL_SCANCODE_W] == KEY_IDLE && App->input->keys[SDL_SCANCODE_S] == KEY_IDLE)
		{
			int tileY = level1Tile->getWorldPos(level1Tile->getTilePos(position)).y;

			if (pivotPoint.y <= (tileY + 4))
			{
				position.y -= speed;
			}
			else if (pivotPoint.y > (tileY + 4) &&
				pivotPoint.y < (tileY + 8))
			{
				position.y += speed;
			}
			else if (pivotPoint.y < (tileY + 10) &&
				pivotPoint.y >(tileY + 8))
			{
				position.y -= speed;
			}
			else if (pivotPoint.y >= (tileY + 10))
			{
				position.y += speed;
			}
		}
		playerTimer.Update();

		if (playerTimer.getDeltaTime() >= 0.5f) {

			if (ExtraPoints == true) {
				App->audio->PlaySound(SFX::EXTRA_COINS_STEP_SFX, 0);

			}
			playerTimer.Reset();

		}
	}

	if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
	{
		isFlip = false;
		currentAnimation = &leftAnim;
		currentAnimation->hasIdle = false;

		if (position.x > 24 && canMoveDir[LEFT]) // Limiitar movimiento en la mapa
		{
			//position.x -= speed;
			speedX = -1;
		}
		else if (App->input->keys[SDL_SCANCODE_W] == KEY_IDLE && App->input->keys[SDL_SCANCODE_S] == KEY_IDLE)
		{
			int tileY = level1Tile->getWorldPos(level1Tile->getTilePos(position)).y;

			if (pivotPoint.y <= (tileY + 4))
			{
				position.y -= speed;
			}
			else if (pivotPoint.y > (tileY + 4) &&
				pivotPoint.y < (tileY + 8))
			{
				position.y += speed;
			}
			else if (pivotPoint.y < (tileY + 10) &&
				pivotPoint.y >(tileY + 8))
			{
				position.y -= speed;
			}
			else if (pivotPoint.y >= (tileY + 10))
			{
				position.y += speed;
			}
		}
		playerTimer.Update();

		if (playerTimer.getDeltaTime() >= 0.5f) {

			if (ExtraPoints == true) {
				App->audio->PlaySound(SFX::EXTRA_COINS_STEP_SFX, 0);

			}
			playerTimer.Reset();

		}
	}



	if (App->input->keys[SDL_SCANCODE_P] == KEY_DOWN) {
		score += 100;
	}

	if(App->input->keys[SDL_SCANCODE_S] == KEY_UP || App->input->keys[SDL_SCANCODE_W] == KEY_UP)
	{
		speedY = 0;
	}
	if (App->input->keys[SDL_SCANCODE_A] == KEY_UP || App->input->keys[SDL_SCANCODE_D] == KEY_UP)
	{
		speedX = 0;
	}

	position += {speedX, speedY};

	if (App->input->keys[SDL_SCANCODE_D] == KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_A] == KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_W] == KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_S] == KEY_IDLE)
	{
		currentAnimation->hasIdle = true;
	}

	col->SetPos(position);
	currentAnimation->Update();

	// Update Pivot Point
	pivotPoint = { position.x + 8, position.y + 8 };

	#pragma region Debug Mods
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
	{
		godMode = !godMode;
	}

	if (App->input->keys[SDL_SCANCODE_F10] == KEY_DOWN)
	{
		posMode = !posMode;

		if(posMode)
		{
			lastTilePos = tilePos;
		}
		else
		{
			level1Tile->Level1TileMap[tilePos.y - 1][tilePos.x] = 0;
		}
	}
	#pragma endregion

	// Reset Move
	for (int i = 0; i < 4; i++)
	{
		canMoveDir[i] = true;
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult Player::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	iPoint tempPos = position;
	tempPos.y -= 6;

	if(isFlip)
	{
		App->render->DrawRotateTexture(texture, tempPos, &rect, false, 180);
	}
	else
	{
		App->render->DrawTexture(texture, tempPos, &rect);
	}


	// Console Pos
	if (posMode)
	{
		// Update tile Point
		tilePos = getCurrentTilePos();
		if (tilePos != lastTilePos)
		{
			level1Tile->Level1TileMap[lastTilePos.y - 1][lastTilePos.x] = 0;
			level1Tile->Level1TileMap[tilePos.y - 1][tilePos.x] = -1;
			lastTilePos = tilePos;
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void Player::OnCollision(Collider* col)
{
	if(!godMode)
	{
		if (col->type == Type::EXPLOSION || col->type == Type::ENEMY)
		{
			App->audio->PlaySound(SFX::DEATH_SFX, 0);
			App->audio->PlaySound(SFX::GAME_OVER_SFX, 0);
			pendingToDelete = true;

			// Create die particle
			iPoint tempPos = position;
			tempPos -= {3, 5};
			App->particle->AddParticle(*playerDestroyed, tempPos.x, tempPos.y, Type::NONE, 0);
		}

		if (col->type == Type::FIREPOWER)
		{
			pUpFlame++;
		}
	}
}

void Player::WillCollision(Collider* col)
{
	if (!godMode)
	{
		// Choc
		if (col->type == Type::WALL || col->type == Type::DESTRUCTABLE_WALL)
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

iPoint Player::getCurrentTilePos()
{
	iPoint ret = pivotPoint;

	ret = level1Tile->getTilePos(ret);

	return ret;
}

iPoint Player::getCurrentTilewWorldPos()
{
	iPoint ret = pivotPoint;

	ret = level1Tile->getTilePos(ret);
	ret = level1Tile->getWorldPos(ret);

	return ret;
}
