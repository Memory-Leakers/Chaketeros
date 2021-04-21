#include "ModulePlayer.h"
#include <iostream>;
using namespace std;


ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;
	//Rect for col
	bounds.x = 0;
	bounds.y = 0;
	bounds.w = 16;
	bounds.h = 22;

	//Animation Down
	downAnim.PushBack({ 17, 2, 16, 22 });//IDLE
	downAnim.PushBack({0, 2, 16, 22});
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

ModulePlayer::~ModulePlayer()
{
	
}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Images/Sprites/Player_Sprites/BombermanSheet.png"); // arcade version

	col = App->collisions->AddCollider(bounds, Type::PLAYER, this);

	return ret;
}

UpdateResult ModulePlayer::Update()
{
	// Player Movement keys
	// Reset the currentAnimation back to idle before updating the logic
	currentAnimation->hasIdle = false;
	if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
	{
		currentAnimation = &rightAnim;
		position.x += speed;
		isFlip = true;
	}
	if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
	{
		currentAnimation = &leftAnim;
		position.x -= speed;
		isFlip = false;
	}
	if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT)
	{
		currentAnimation = &upAnim;
		position.y -= speed;
		isFlip = false;
	}
	if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT)
	{
		currentAnimation = &downAnim;
		position.y += speed;
		isFlip = false;
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

UpdateResult ModulePlayer::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	//BUG
	//BUG
	//BUG
	//BUG
	// Flip Intennt
	/*
	if(isFlip)
	{
		SDL_Rect r1 = { 0,0,384,224 };
		SDL_Rect tempRect = rect;

		int mul = 3;
		tempRect.w *= mul;
		tempRect.h *= mul;

		SDL_Point center = { (rect.x + rect.w) / 2,(rect.y + rect.h) / 2 };
		//rect.x = 256 - rect.x;
		//rect.x += 5;
		SDL_RendererFlip flip = SDL_FLIP_VERTICAL;

		//cout << "\nx1: " << tempRect.x << "\ty1: " << tempRect.y << "\tw1: " << tempRect.w << "\th1: " << tempRect.h;

		SDL_RenderCopyEx(App->render->renderer, texture, &rect, &tempRect, 180, &center, flip);

		//tempRect.x +=5;
		//tempRect.y = 100;
		//cout << "\nx2: " << tempRect.x << "\ty2: " << tempRect.y << "\tw2: " << tempRect.w << "\th2: " << tempRect.h;

		//App->render->DrawTexture(texture, position.x, position.y - rect.h, &tempRect);
	}
	else
	{
		App->render->DrawTexture(texture, position.x, position.y - rect.h, &rect);
	}
	*/

	App->render->DrawTexture(texture, position.x, position.y, &rect);

	return UpdateResult::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{

}
