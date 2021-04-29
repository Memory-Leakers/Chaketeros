#include "PokaPoka.h"

#include <iostream>
using namespace std;

PokaPoka::PokaPoka(int x, int y, Tile* level1Tile) {
	this->level1Tile = level1Tile;
	position.x = x;
	position.y = y;
	bounds.x = position.x;
	bounds.y = position.y;
	bounds.w = 16;
	bounds.h = 16;

	//Animation DOWN
	downAnim.PushBack({ 2,1,15, 28 });//IDLE
	downAnim.PushBack({ 19, 1, 15,28 });
	downAnim.PushBack({ 2,1,15,28 });//IDLE
	downAnim.PushBack({ 19, 1, 15,28 });
	downAnim.speed = defaultEnemySpeed;

	//Animation UP
	upAnim.PushBack({ 87,1,15,28 });//IDLE
	upAnim.PushBack({ 104,1,15,28 });
	upAnim.PushBack({ 87,1,15,28 });//IDLE
	upAnim.PushBack({ 87,29,15,28 }); //Falta 1 girat
	//upAnim.PushBack({ 65,2,16,22 });//IDLE
	//upAnim.PushBack({ 81,2,16,22 });
	upAnim.speed = defaultEnemySpeed;

	//Animation RIGHT
	rightAnim.PushBack({ 36,1,16,28 });//IDLE
	rightAnim.PushBack({ 54, 1,15,28 });
	rightAnim.PushBack({ 71,1,15,28 });
	rightAnim.PushBack({ 54, 1,15,28 });
	//rightAnim.PushBack({ 17,26,16,22 });//IDLE
	//rightAnim.PushBack({ 33,26,16,22 });
	rightAnim.speed = defaultEnemySpeed;

	//Animation LEFT
	leftAnim.PushBack({ 36,1,16,28 });//IDLE
	leftAnim.PushBack({ 54, 1,15,28 });
	leftAnim.PushBack({ 71,1,15,28 });
	leftAnim.PushBack({ 54, 1,15,28 });
	//leftAnim.PushBack({ 17,26,16,22 });//IDLE
	//leftAnim.PushBack({ 33,26,16,22 });
	leftAnim.speed = defaultEnemySpeed;


	//Animation Attack
	//attackAnim.PushBack();


	currentAnimation = &downAnim;
}

PokaPoka::~PokaPoka() {
	if (dieParticle != nullptr)
	{
		delete dieParticle;
		dieParticle = nullptr;
	}
}

bool PokaPoka::Start() {
	LOG("LOADING ENEMY POKAPOKA");
	bool ret = true;

	texture = App->textures->Load("Assets/Images/Sprites/Enemies_Sprites/Enemies.png");

	col = App->collisions->AddCollider(bounds, Type::ENEMY, App->scene);

	//Die Particle(Animation)
	dieParticle = new Particle(500.0f, 0.05f, texture);

	dieParticle->anim.PushBack({ 206,1,15,28 });
	dieParticle->anim.PushBack({ 223,1,15,28 });
	dieParticle->anim.PushBack({ 240,1,15,28 });
	dieParticle->anim.PushBack({ 2,29,15,28 });
	dieParticle->anim.PushBack({ 19,29,15,28 });
	dieParticle->anim.PushBack({ 37,29,15,28 });
	dieParticle->anim.PushBack({ 71,29,15,28 });

	dieParticle->anim.speed = 0.06f;
	//lastTilePos = getCurrentTilePos();

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
	tempPos.y -= 14;

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
	nPoint = level1Tile->getTilePos(position);
	nPoint.y -= 1;

	if (pC >= 17 || pC == 0) {
		pC = 0;
		moveRand = rand() % 4;
	}

	switch (moveRand) {

		case 0://DOWN
			if (level1Tile->Level1TileMap[nPoint.y + 1][nPoint.x] == 0 ||
				level1Tile->Level1TileMap[nPoint.y + 1][nPoint.x] == 4) {
				isFlip = false;
				currentAnimation = &downAnim;
				currentAnimation->hasIdle = false;

				if (pC == 0) ++pC;
			}

			if (pC >= 1) {
				position.y += speed;
				 ++pC;
			}
			else if (pC == 0) {
				currentAnimation->hasIdle = true;
				while (moveRand == 0) { moveRand = rand() % 4; }
			}
			break;
		case 1://UP
			if (level1Tile->Level1TileMap[nPoint.y - 1][nPoint.x] == 0 ||
				level1Tile->Level1TileMap[nPoint.y - 1][nPoint.x] == 4) {
				isFlip = false;
				currentAnimation = &upAnim;
				currentAnimation->hasIdle = false;

				if (pC == 0) ++pC;
			}

			if (pC >= 1) {
				position.y -= speed;
				++pC;
			}
			else {
				currentAnimation->hasIdle = true;
				while (moveRand == 1) { moveRand = rand() % 4; }
			}
			break;


		case 2://RIGHT
			if (level1Tile->Level1TileMap[nPoint.y][nPoint.x + 1] == 0 ||
				level1Tile->Level1TileMap[nPoint.y][nPoint.x + 1] == 4) {
				isFlip = true;
				currentAnimation = &rightAnim;
				currentAnimation->hasIdle = false;

				if (pC == 0)  ++pC;
			}

			if (pC >= 1) {
				position.x += speed;
				++pC;
			}
			else if (pC == 0) {
				currentAnimation->hasIdle = true;
				while (moveRand == 2) { moveRand = rand() % 4; }
			}
			break;

		case 3://LEFT
			if (level1Tile->Level1TileMap[nPoint.y][nPoint.x - 1] == 0 ||
				level1Tile->Level1TileMap[nPoint.y][nPoint.x - 1] == 4) {
				isFlip = false;
				currentAnimation = &leftAnim;
				currentAnimation->hasIdle = false;

				if(pC == 0) ++pC;
			}

			if (pC >= 1) {
				position.x -= speed;
				++pC;
			}
			else if (pC == 0) {
				currentAnimation->hasIdle = true;
				while (moveRand == 3) { moveRand = rand() % 4; }
			}
			break;
		default:
			moveRand = rand() % 10;
			break;

	}
	
	currentAnimation->Update();
}

void PokaPoka::OnCollision(Collider* col) {
	if (col->type == Type::EXPLOSION) {
		die();

	}
}


void PokaPoka::die() {
	if (pendingToDelete) return;

	isDead = true;

	col->pendingToDelete = true;
	iPoint tempPos = position;
	tempPos += {0, -14};
	App->particle->AddParticle(*dieParticle, tempPos, Type::NONE, true, 0, 0);

	pendingToDelete = true;

	delete dieParticle;
	dieParticle = nullptr;
}

void PokaPoka::attack() {

}