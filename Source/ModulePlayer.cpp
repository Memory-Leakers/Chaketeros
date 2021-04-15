#include "ModulePlayer.h"



ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	//Animation Down
	downAnim.PushBack({ 17, 2, 16, 22 });//IDLE
	downAnim.PushBack({0, 2, 16, 22});
	downAnim.PushBack({ 17, 2, 16, 22 });//IDLE
	downAnim.PushBack({ 33, 2, 16, 22 });
	downAnim.speed = defaultSpeed;

	//Animation UP
	upAnim.PushBack({ 65,2,16,22 });//IDLE
	upAnim.PushBack({ 49,2,16,22 });
	upAnim.PushBack({ 65,2,16,22 });//IDLE
	upAnim.PushBack({ 81,2,16,22 });
	upAnim.speed = defaultSpeed;

	//Animation RIGHT
	rightAnim.PushBack({ 17,26,16,22 });//IDLE
	rightAnim.PushBack({ 0,26,16,22 });
	rightAnim.PushBack({ 17,26,16,22 });//IDLE
	rightAnim.PushBack({ 33,26,16,22 });
	rightAnim.speed = defaultSpeed;

	//Animation LEFT
	leftAnim.PushBack({ 17,26,16,22 });//IDLE
	leftAnim.PushBack({ 0,26,16,22 });
	leftAnim.PushBack({ 17,26,16,22 });//IDLE
	leftAnim.PushBack({ 33,26,16,22 });
	leftAnim.speed = defaultSpeed;

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


	return ret;
}

UpdateResult ModulePlayer::Update()
{
	// Reset the currentAnimation back to idle before updating the logic
	//currentAnimation = &idleAnim;
	currentAnimation->hasIdle = false;
	if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
	{
		currentAnimation = &rightAnim;
		position.x += speed;
	}
	if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
	{
		currentAnimation = &leftAnim;
		position.x -= speed;
	}
	if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT)
	{
		currentAnimation = &upAnim;
		position.y -= speed;
	}
	if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT)
	{
		currentAnimation = &downAnim;
		position.y += speed;
	}
	if (App->input->keys[SDL_SCANCODE_D] != KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_A] != KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_W] != KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_S] != KEY_REPEAT) {
		currentAnimation->hasIdle = true;
	}

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
	App->render->DrawTexture(texture, position.x, position.y - rect.h, &rect);

	return UpdateResult::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{

}
