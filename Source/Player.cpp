#include "Player.h";

#include <iostream>;
using namespace std;


Tile tileMapPlayer;

Player::Player()
{
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
}

bool Player::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Images/Sprites/Player_Sprites/BombermanSheet.png"); // arcade version
	

	col = App->collisions->AddCollider(bounds, Type::PLAYER, App->scene);

	for (int i = 0; i < 4; i++)
	{
		canMoveDir[i] = true;
	}

	return ret;
}

UpdateResult Player::Update()
{
	// Player Movement keys
	// Reset the currentAnimation back to idle before updating the logic
	if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
	{
		isFlip = true;
		currentAnimation = &rightAnim;
		currentAnimation->hasIdle = false;
		if (position.x < 216 && canMoveDir[RIGHT]) // Limiitar movimiento en la mapa
		{
			position.x += speed;
		}
	}
	if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
	{
		isFlip = false;
		currentAnimation = &leftAnim;
		currentAnimation->hasIdle = false;
		if (position.x > 24 && canMoveDir[LEFT]) // Limiitar movimiento en la mapa
		{
			position.x -= speed;
		}
	}
	if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT)
	{
		isFlip = false;
		currentAnimation = &upAnim;
		currentAnimation->hasIdle = false;
		if (position.y > 32 && canMoveDir[UP]) // Limiitar movimiento en la mapa
		{
			position.y -= speed;
		}
	}
	if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT)
	{
		isFlip = false;
		currentAnimation = &downAnim;
		currentAnimation->hasIdle = false;
		if (position.y < 208 - 16 && canMoveDir[DOWN]) // Limiitar movimiento en la mapa
		{
			position.y += speed;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_A] == KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_W] == KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_S] == KEY_IDLE)
	{
		currentAnimation->hasIdle = true;
	}

	col->SetPos(position);
	currentAnimation->Update();

	

	//Update Pivot Point
	pivotPoint = { position.x + 8, position.y + 8 };

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

	return UpdateResult::UPDATE_CONTINUE;
}

void Player::OnCollision(Collider* col)
{
	if (col->type == Type::EXPLOSION || col->type == Type::ENEMY)
	{
		pendingToDelete = true;
	}

	if (col->type == Type::FIREPOWER)
	{
		pUpFlame++;
	}
}

void Player::WillCollision(Collider* col)
{
	// Choc
	if (col->type == Type::WALL || col->type == Type::DESTRUCTABLE_WALL)
	{
		// Detect if player can move or not
		if (col->getPos().x == (position.x + bounds.w))
		{
			if(col->getPos().y != (position.y + bounds.h) && col->getPos().y + bounds.h != position.y)
			{
				//cout << "Colision a la derecha de player" << endl;
				canMoveDir[RIGHT] = false;
			}
		}
		if (col->getPos().x + bounds.w == (position.x))
		{
			if (col->getPos().y != (position.y + bounds.h) && col->getPos().y + bounds.h != position.y)
			{
				//cout << "Colision a la izquierda de player" << endl;
				canMoveDir[LEFT] = false;
			}
		}
		if (col->getPos().y == (position.y + bounds.h))
		{
			if (col->getPos().x != (position.x + bounds.w) && col->getPos().x + bounds.w != (position.x))
			{
				//cout << "Colision abajo del player" << endl;
				canMoveDir[DOWN] = false;
			}
		}
		if (col->getPos().y + bounds.h == position.y)
		{
			if (col->getPos().x != (position.x + bounds.w) && col->getPos().x + bounds.w != (position.x))
			{
				//cout << "Colision arriba del player" << endl;
				canMoveDir[UP] = false;
			}		
		}
	}
}

iPoint Player::getCurrentTilePos()
{
	iPoint ret = pivotPoint;

	ret = tileMapPlayer.getTilePos(ret);
	ret = tileMapPlayer.getWorldPos(ret);

	return ret;
}
