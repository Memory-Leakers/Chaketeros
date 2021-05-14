#include "PokaPoka.h"

#include <iostream>
using namespace std;

SDL_Rect* rectPoka;

PokaPoka::PokaPoka(int x, int y, iPoint* playerPos, Tile* level1Tile) {
	
	this->level1Tile = level1Tile;
	this->playerPos = playerPos;
	position.x = x;
	position.y = y;
	bounds.x = position.x;
	bounds.y = position.y;
	bounds.w = 16;
	bounds.h = 16;
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

	#pragma region Init anim

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
	/*
	attackAnim.PushBack({ 121,1,15,28 });//1
	attackAnim.PushBack({ 139,1,15,28 });//2
	attackAnim.PushBack({ 155,1,15,28 });//3
	attackAnim.PushBack({ 173,5,15,28 });//4
	attackAnim.PushBack({ 190,5,15,28 });//5
	*/
	attackAnim.PushBack({ 121,1,15,28 });//1 //0
	attackAnim.PushBack({ 155,1,15,28 });//3 //1
	attackAnim.PushBack({ 121,1,15,28 });//1	//2
	attackAnim.PushBack({ 155,1,15,28 });//3	//3
	attackAnim.PushBack({ 121,1,15,28 });//1	4
	attackAnim.PushBack({ 139,1,15,28 });//2	5
	attackAnim.PushBack({ 121,1,15,28 });//1	6
	attackAnim.PushBack({ 155,1,15,28 });//3	7
	attackAnim.PushBack({ 121,1,15,28 });//1	8
	attackAnim.PushBack({ 155,1,15,28 });//3	9
	attackAnim.PushBack({ 173,1,15,28 });//4	10
	attackAnim.PushBack({ 173,1,15,28 });//4	11

	attackAnim.PushBack({ 121,1,15,28 });//1	12
	attackAnim.PushBack({ 190,1,15,40 });//5 //13
	attackAnim.PushBack({ 121,1,15,28 });//1	14
	attackAnim.PushBack({ 190,1,15,40 });//5 //15
	attackAnim.PushBack({ 121,1,15,28 });//1	16
	attackAnim.PushBack({ 190,1,15,40 });//5 //17
	attackAnim.PushBack({ 121,1,15,28 });//1	17

	attackAnim.speed = 0.06f;

	currentAnimation = &downAnim;

#pragma endregion

	#pragma region Init destroy particle
	dieParticle = new Particle(500.0f, 0.3f, texture);

	dieParticle->anim.PushBack({ 206,1,15,28 });
	dieParticle->anim.PushBack({ 223,1,15,28 });
	dieParticle->anim.PushBack({ 240,1,15,28 });
	dieParticle->anim.PushBack({ 2,29,15,28 });
	dieParticle->anim.PushBack({ 19,29,15,28 });
	dieParticle->anim.PushBack({ 37,29,15,28 });
	dieParticle->anim.PushBack({ 71,29,15,28 });

	#pragma endregion

	//lastTilePos = getCurrentTilePos();

	return ret;
}

UpdateResult PokaPoka::Update() {
	if (isDead) {
		//Play dead Animation

	}
	col->SetPos(this->position.x, this->position.y);
	if (attacking == 1 || attacking == 2) {

		attackTimer.Update();
	}
	
	moveTimer.Update();
	if (moveTimer.getDeltaTime() >= 0.15f)
	{
		movement();
		moveTimer.Reset();
	}
	currentAnimation->Update();

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult PokaPoka::PostUpdate() {

	rectPoka = &currentAnimation->GetCurrentFrame();

	iPoint tempPos = position;

	int cF = (int)currentAnimation->getCurrentFrameF();

	if ((cF == 13 || cF == 15 || cF == 17)) {
		tempPos.y -= 38;
	}
	else {
		tempPos.y -= 14;
	}

	if (isFlip)
	{
		//App->render->DrawRotateTexture(texture, tempPos, &rect, false, 180);
		App->render->AddTextureRenderQueue(texture, tempPos, rectPoka, 1, position.y, false, 180);
	}
	else
	{
		//App->render->DrawTexture(texture, tempPos, &rect);
		App->render->AddTextureRenderQueue(texture, tempPos, rectPoka, 1, position.y);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void PokaPoka::movement() {
	nPoint = level1Tile->getTilePos(position);
	nPoint.y -= 1;

	//Posició del Jugador
	iPoint playerTilePos = level1Tile->getTilePos(*playerPos);
	
	//Steps
	if (pC >= 17 || pC == 0) {
		pC = 0;
		//moveRandom();
	}

	if (attacking == 1 || attacking == 2) {
		attack();
		currentAnimation->Update();
		return;
	}


	playerTilePos.y -= 1;//Correction
	/*
	if (playerTilePos.x == (nPoint.x - 1) && playerTilePos.y == nPoint.y && attacking == 3) {
		attacking = 1;
	}
	else if (playerTilePos.x == (nPoint.x + 1) && playerTilePos.y == nPoint.y && attacking == 3) {
		attacking = 2;
	}
	*/
	int aP = playerPos->x - position.x; //Posicion del jugador respecto al PokaPoka
	if(abs(aP) < attackRange && playerTilePos.y == nPoint.y){
		if (attackRange >= aP && 0 < aP && attacking == 3) { // RIGHT
			attacking = 2;
		}
		else if (-attackRange <= aP && attacking == 3) { // LEFT
			attacking = 1;
		}
	}
	else {
		switch (moveRand) {
			case 0://DOWN
				if (level1Tile->LevelsTileMaps[App->scene->currentLevel][nPoint.y + 1][nPoint.x] == 0 ||
					level1Tile->LevelsTileMaps[App->scene->currentLevel][nPoint.y + 1][nPoint.x] == 4) { // 0 i 4 son l'id de la tile
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
					moveRandom(0);
				}
				break;
			case 1://UP
				if (level1Tile->LevelsTileMaps[App->scene->currentLevel][nPoint.y - 1][nPoint.x] == 0 ||
					level1Tile->LevelsTileMaps[App->scene->currentLevel][nPoint.y - 1][nPoint.x] == 4) {
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
					moveRandom(1);
				}
				break;
			case 2://RIGHT
				if (level1Tile->LevelsTileMaps[App->scene->currentLevel][nPoint.y][nPoint.x + 1] == 0 ||
					level1Tile->LevelsTileMaps[App->scene->currentLevel][nPoint.y][nPoint.x + 1] == 4) {
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
					moveRandom(2);
				}
				break;
			case 3://LEFT
				if (level1Tile->LevelsTileMaps[App->scene->currentLevel][nPoint.y][nPoint.x - 1] == 0 ||
					level1Tile->LevelsTileMaps[App->scene->currentLevel][nPoint.y][nPoint.x - 1] == 4) {
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
					moveRandom(3);
				}
		}
	}
}

void PokaPoka::moveRandom(int i) {
	while (moveRand == i) {
		moveRand = rand() % 4;
	}
}


void PokaPoka::OnCollision(Collider* col) {
	if (col->type == Type::EXPLOSION) 
	{
		die();
	}
}


void PokaPoka::die() {

	if (pendingToDelete) return;

	App->scene->currentScene->score += 200;
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
	currentAnimation = &attackAnim;
	currentAnimation->hasIdle = false;
	if (attacking == 1) {
		isFlip = false;
	}
	else {
		isFlip = true;
	}
	
	if (attackTimer.getDeltaTime() >= 2.0f) {
		attacking = 3;
		attackTimer.Reset();
	}
}