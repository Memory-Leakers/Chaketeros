#include "Player.h";

#include <iostream>;
using namespace std;

SDL_Texture* flipTest;

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

}

bool Player::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Images/Sprites/Player_Sprites/BombermanSheet.png"); // arcade version
	flipTest = App->textures->Load("Assets/Images/Sprites/flipTest.png");

	col = App->collisions->AddCollider(bounds, Type::PLAYER, App->scene);

	return ret;
}

UpdateResult Player::Update()
{
	// Player Movement keys
	// Reset the currentAnimation back to idle before updating the logic
	currentAnimation->hasIdle = false;
	if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
	{
		currentAnimation = &rightAnim;
		if (position.x < 216) // Limiitar movimiento en la mapa
		{
			position.x += speed;
			isFlip = true;
		}
	}
	if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
	{
		currentAnimation = &leftAnim;
		if (position.x > 24) // Limiitar movimiento en la mapa
		{
			position.x -= speed;
			isFlip = false;
		}	
	}
	if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT)
	{
		currentAnimation = &upAnim;
		if (position.y > 32) // Limiitar movimiento en la mapa
		{
			position.y -= speed;
			isFlip = false;
		}	
	}
	if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT)
	{
		currentAnimation = &downAnim;
		if (position.y < 208 - 16) // Limiitar movimiento en la mapa
		{
			position.y += speed;
			isFlip = false;
		}
	}
	
	if (App->input->keys[SDL_SCANCODE_D] != KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_A] != KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_W] != KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_S] != KEY_REPEAT) {
		currentAnimation->hasIdle = true;
	}

	col->SetPos(position);
	currentAnimation->Update();

	//------------------SFX TEST--------------------------
	if (App->input->keys[SDL_SCANCODE_E] == KEY_DOWN) {
		App->audio->PlaySound(SFX::PUT_BOMB_SFX, 0);
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

}
