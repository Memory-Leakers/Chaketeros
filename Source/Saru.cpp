#include "Saru.h"

Saru::Saru(int x, int y, iPoint* playerPos, Tile* level1Tile) {
	this->level1Tile = level1Tile;
	this->playerPos = playerPos;
	position.x = x;
	position.y = y;
	bounds.x = position.x;
	bounds.y = position.y;
	bounds.w = 16;
	bounds.h = 16;
}

Saru::~Saru() {
	
}

bool Saru::Start() {
	LOG("LOADING ENEMY SARU");
	bool ret = true;

	texture = App->textures->Load("Assets/Images/Sprites/Enemies_Sprites/Monkey.png");

	col = App->collisions->AddCollider(bounds, Type::ENEMY, App->scene);


	//Animation DOWN
	downAnim.PushBack({ 5,48,21,18 });
	downAnim.PushBack({ 31,48,21,19 });
	downAnim.speed = defaultEnemySpeed;

	//Animation UP
	upAnim.PushBack({ 4,95,21,18 });
	upAnim.PushBack({ 31,95,21,19 });
	upAnim.speed = defaultEnemySpeed;

	//Animation RIGHT
	rightAnim.PushBack({ 3,71,21,18 });
	rightAnim.PushBack({ 33, 71,21,18 });
	rightAnim.speed = defaultEnemySpeed;

	//Animation LEFT || Must be flipped
	leftAnim.PushBack({ 3,71,21,18 });
	leftAnim.PushBack({ 33, 71,21,18 });
	leftAnim.speed = defaultEnemySpeed;

	//Animation IDLE
	idleAnim.PushBack({ 3,3,24,19 });
	idleAnim.PushBack({ 30, 3,24,19 });
	idleAnim.speed = defaultEnemySpeed;

	currentAnimation = &downAnim;

	return ret;
}

UpdateResult Saru::Update() {
	currentAnimation->Update();

	logic();

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult Saru::PostUpdate() {

	rectSaru = &currentAnimation->GetCurrentFrame();
	iPoint tempPos = position;

	//Render flip
	if (isFlip) App->render->AddTextureRenderQueue(texture, tempPos, rectSaru, 1, position.y, false, 180);
	else App->render->AddTextureRenderQueue(texture, tempPos, rectSaru, 1, position.y);


	return UpdateResult::UPDATE_CONTINUE;
}

void Saru::logic() {

}

void Saru::OnCollision(Collider* col) {
	if (lives == 0) {
		die();
	}
	if (col->type == Type::EXPLOSION) {
		--lives;
	}
}


void Saru::die() {
	if (pendingToDelete) return;
	App->scene->currentScene->score += 1000; //Temporal score
	isDead = true;

	col->pendingToDelete = true;

	pendingToDelete = true;
}

