#include "Mover.h"

Mover::Mover(iPoint pos) 
{
	position.x = pos.x;
	position.y = pos.y;
	bounds.x = position.x;
	bounds.y = position.y;
	bounds.w = 16;
	bounds.h = 16;

	// Anim Down
	downAnim.PushBack({ 5,166,23,30 });//IDLE
	downAnim.PushBack({ 37,166,23,30 });
	downAnim.PushBack({ 5,166,23,30 });//IDLE
	downAnim.PushBack({ 37,166,23,30 });
	downAnim.speed = defaultEnemySpeed;

	//Animation UP
	upAnim.PushBack({ 69,166,23,30 });//IDLE
	upAnim.PushBack({ 101,166,23,30 });
	upAnim.PushBack({ 69,166,23,30 });//IDLE
	upAnim.PushBack({ 101,166,23,30 });
	upAnim.speed = defaultEnemySpeed;

	//Animation RIGHT
	rightAnim.PushBack({ 135,166,23,30 });//IDLE
	rightAnim.PushBack({ 168,166,23,30 });
	rightAnim.PushBack({ 135,166,23,30 });//IDLE
	rightAnim.PushBack({ 201,166,23,30 });
	rightAnim.speed = defaultEnemySpeed;

	//Animation LEFT
	leftAnim.PushBack({ 135,166,23,30 });//IDLE
	leftAnim.PushBack({ 168,166,23,30 });
	leftAnim.PushBack({ 135,166,23,30 });//IDLE
	leftAnim.PushBack({ 201,166,23,30 });
	leftAnim.speed = defaultEnemySpeed;

	currentAnimation = &downAnim;
}

Mover::~Mover() 
{
	
}

bool Mover::Start() {
	LOG("LOADING ENEMY POKAPOKA");
	bool ret = true;

	texture = App->textures->Load("Assets/Images/Sprites/Enemies_Sprites/Enemies.png");

	col = App->collisions->AddCollider(bounds, Type::ENEMY, App->scene);

	return ret;
}

UpdateResult Mover::Update() {
	if (isDead) 
	{
		//Play dead Animation
	}
	col->SetPos(this->position.x, this->position.y);
	movement();

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult Mover::PostUpdate() {

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

void Mover::movement() {
	
	if ((position.x - 8) % (32) == 0 && position.y % 32 == 0) {
		moveRand = rand() % 4;
	}

	switch (moveRand) 
	{
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
}

void Mover::onCollision(Collider* otherCol) 
{
	if (otherCol->type == Type::EXPLOSION) 
	{
		die();
	}
}


void Mover::die() 
{
	isDead = false;
}