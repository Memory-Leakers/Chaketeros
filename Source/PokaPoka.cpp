#include "PokaPoka.h"


PokaPoka::PokaPoka(int x, int y) {
	position.x = x;
	position.y = y;
	bounds.x = position.x;
	bounds.y = position.y;
	bounds.w = 16;
	bounds.h = 16;

	//
	downAnim.PushBack({ 2,1,15,28 });//IDLE
	downAnim.PushBack({ 19, 1, 15,28 });
	//downAnim.PushBack({ 2,1,15,28 });//IDLE
	//downAnim.PushBack({ w - 19,1,15,28 });
	downAnim.speed = defaultEnemySpeed;

	//Animation UP
	upAnim.PushBack({ 87,1,15,28 });//IDLE
	upAnim.PushBack({ 104,1,15,28 });
	//upAnim.PushBack({ 65,2,16,22 });//IDLE
	//upAnim.PushBack({ 81,2,16,22 });
	upAnim.speed = defaultEnemySpeed;

	//Animation RIGHT
	rightAnim.PushBack({ 36,1,16,28 });//IDLE
	rightAnim.PushBack({ 54,15,28, });
	//rightAnim.PushBack({ 17,26,16,22 });//IDLE
	//rightAnim.PushBack({ 33,26,16,22 });
	rightAnim.speed = defaultEnemySpeed;

	//Animation LEFT
	leftAnim.PushBack({ 36,1,16,28 });//IDLE
	leftAnim.PushBack({ 54,15,28, });
	//leftAnim.PushBack({ 17,26,16,22 });//IDLE
	//leftAnim.PushBack({ 33,26,16,22 });
	leftAnim.speed = defaultEnemySpeed;


	//Animation Attack
	//attackAnim.PushBack();//


	currentAnimation = &downAnim;
}

PokaPoka::~PokaPoka() {
	//col->pendingToDelete = true;
}

bool PokaPoka::Start() {
	LOG("LOADING ENEMY POKAPOKA");
	bool ret = true;

	texture = App->textures->Load("Assets/Images/Sprites/Enemies_Sprites/Enemies.png");

	col = App->collisions->AddCollider(bounds, Type::ENEMY, App->scene);

	return ret;
}

UpdateResult PokaPoka::Update() {
	if (isDead) {
		//Play dead Animation

	}
	col->SetPos(this->position.x, this->position.y);
	movement();

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult PokaPoka::PostUpdate() {

	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	iPoint tempPos = position;
	tempPos.y -= 10;

	if (isFlip)
	{
		App->render->DrawRotateTexture(texture, tempPos, &rect, false, 180);
	}
	else
	{
		App->render->DrawTexture(texture, tempPos, &rect);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void PokaPoka::movement() {
;
	if ((position.x-8) % (32) == 0 && position.y % 32 == 0) {
		moveRand = rand() % 4;
	}
	
	
	switch (moveRand) {
		case 0://UP
			isFlip = false;
			currentAnimation = &upAnim;
			currentAnimation->hasIdle = false;
			position.y -= speed;
			break;
		case 1://DOWN
			isFlip = false;
			currentAnimation = &downAnim;
			currentAnimation->hasIdle = false;
			position.y += speed;
			break;
		case 2://RIGHT
			isFlip = false;
			currentAnimation = &rightAnim;
			currentAnimation->hasIdle = false;
			position.x += speed;
			break;
		case 3://LEFT
			isFlip = false;
			currentAnimation = &leftAnim;
			currentAnimation->hasIdle = false;
			position.x -= speed;
			break;
	}
	
	//currentAnimation = &downAnim;
	col->SetPos(position);
	currentAnimation->Update();

	bounds.x = position.x;
	bounds.y = position.y;


	pivotPoint = { position.x + 8, position.y + 8 };

	/*
	for (int i = 0; i < 4; i++)
	{
		canMoveDir[i] = true;
	}
	*/

}

void PokaPoka::onCollision(Collider* otherCol) {
	if (otherCol->type == Type::EXPLOSION) {
		die();
	}
}


void PokaPoka::die() {
	//powerUpDrop();
	isDead = false;
	col->pendingToDelete = true;
}