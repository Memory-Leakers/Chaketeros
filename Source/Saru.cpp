#include "Saru.h"

Saru::Saru(iPoint spawnPos, iPoint* playerPos, Tile* tileMap) {
	this->playerPos = playerPos;
	bounds.w = 16;
	bounds.h = 16;
	bounds.x = position.x = spawnPos.x;
	bounds.y = position.y = spawnPos.y;
	this->tileMap = tileMap;
	life = 4;
}

Saru::~Saru() {
	
}

bool Saru::Start() {
	LOG("-LOADING ENEMY SARU-");
	bool ret = true;

	texture = App->textures->Load("Assets/Images/Sprites/Enemies_Sprites/Monkey.png");

	col = App->collisions->AddCollider(bounds, Type::ENEMY, App->scene);


	//Animation DOWN
	downAnim.PushBack({ 5,48,21,18 });
	downAnim.PushBack({ 31,48,21,19 });
	downAnim.speed = saruAnimSpeed;
	idleAnim.hasIdle = false;

	//Animation UP
	upAnim.PushBack({ 4,95,21,18 });
	upAnim.PushBack({ 31,95,21,19 });
	upAnim.speed = saruAnimSpeed;
	idleAnim.hasIdle = false;

	//Animation RIGHT
	rightAnim.PushBack({ 3,71,21,18 });
	rightAnim.PushBack({ 33, 71,21,18 });
	rightAnim.speed = saruAnimSpeed;
	idleAnim.hasIdle = false;

	//Animation LEFT || Must be flipped
	leftAnim.PushBack({ 3,71,21,18 });
	leftAnim.PushBack({ 33, 71,21,18 });
	leftAnim.speed = saruAnimSpeed;
	idleAnim.hasIdle = false;

	//Animation IDLE
	idleAnim.PushBack({ 3,3,24,19 });
	idleAnim.PushBack({ 30, 3,24,19 });
	idleAnim.speed = saruAnimSpeed;
	idleAnim.loop = true;
	idleAnim.hasIdle = false;

	currentAnimation = &idleAnim;

	/*
	DIE PARTICLE
	*/



	return ret;
}

UpdateResult Saru::PreUpdate() {
	iPoint tilePos = tileMap->getTilePos(position);
	iPoint centerTile = tileMap->getWorldPos(tilePos);


	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult Saru::Update() {

	// Update Col
	col->SetPos(this->position.x, this->position.y);

	updateTimer.Update();

	if (updateTimer.getDeltaTime() >= 0.05f) {
		ProtectCountdown();

		logic();

		updateTimer.Reset();
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult Saru::PostUpdate() {

	currentAnimation->Update();
	rectSaru = &currentAnimation->GetCurrentFrame();
	iPoint tempPos = position;
	tempPos.y -= 1; //Texture position fix
	tempPos.x -= 2; //Texture position fix


	//Render flip
	if (isFlip) App->render->AddTextureRenderQueue(texture, tempPos, rectSaru, 1, position.y, false, 180);
	else App->render->AddTextureRenderQueue(texture, tempPos, rectSaru, 1, position.y);


	return UpdateResult::UPDATE_CONTINUE;
}

void Saru::logic() {
	int playerPosX = playerPos->x - position.x;//Player distance on X from Saru position
	int playerPosY = playerPos->y - position.y;//Player distance on Y from Saru position

	if(!onMovement) {
		//Each one of this if checks if player is inside vRange and if on the opossite side there is a wall
		if((playerPosY <= vRange && playerPosY >= 0) && (playerPosX * -1 <= vRange && playerPosX <= vRange) && position.y <= 32 && 
			(tileMap->LevelsTileMaps[App->scene->currentLevel][nPoint.y][nPoint.x + 1] == 0 ||
			tileMap->LevelsTileMaps[App->scene->currentLevel][nPoint.y][nPoint.x + 1] == 4)) {
			//direction = rand() % 2+2;
			direction = 2;
		}
		else if ((playerPosY * -1 <= vRange && playerPosY * -1 >= 0) && (playerPosX * -1 <= vRange && playerPosX <= vRange) && position.x <= 24 &&
			(tileMap->LevelsTileMaps[App->scene->currentLevel][nPoint.y - 1][nPoint.x] == 0 ||
			tileMap->LevelsTileMaps[App->scene->currentLevel][nPoint.y - 1][nPoint.x] == 4)) {
			direction = 1;
			//movementTot = moveTotDefault*3;
			movementTot = moveTotDefault;
		}
		else if ((playerPosY * -1 <= vRange && playerPosY * -1 >= 0) && (playerPosX * -1 <= vRange && playerPosX <= vRange) && position.x >= 216 &&
			(tileMap->LevelsTileMaps[App->scene->currentLevel][nPoint.y - 1][nPoint.x] == 0 ||
			tileMap->LevelsTileMaps[App->scene->currentLevel][nPoint.y - 1][nPoint.x] == 4)) {
			direction = 1;
			//movementTot = moveTotDefault*3;
		}
		else if ((playerPosX * -1 <= vRange && playerPosX * -1 >= 0) && (playerPosY <= 20 && playerPosY * -1 <= 20) &&
			(tileMap->LevelsTileMaps[App->scene->currentLevel][nPoint.y][nPoint.x + 1] == 0 ||
			tileMap->LevelsTileMaps[App->scene->currentLevel][nPoint.y][nPoint.x + 1] == 4)) {
			direction = 2;//Goes RIGHT
			movementTot = moveTotDefault;
		}
		else if ((playerPosX <= vRange && playerPosX >= 0) && (playerPosY <= 20 && playerPosY * -1 <= 20) &&
				(tileMap->LevelsTileMaps[App->scene->currentLevel][nPoint.y][nPoint.x - 1] == 0 ||
				tileMap->LevelsTileMaps[App->scene->currentLevel][nPoint.y][nPoint.x - 1] == 4)) {
			direction = 3;//Goes LEFT
			movementTot = moveTotDefault;
		}
		else if ((playerPosY <= vRange && playerPosY >= 0) && (playerPosX * -1 <= vRange && playerPosX <= vRange) &&
				(tileMap->LevelsTileMaps[App->scene->currentLevel][nPoint.y - 1][nPoint.x] == 0 ||
				tileMap->LevelsTileMaps[App->scene->currentLevel][nPoint.y - 1][nPoint.x] == 4)) {
			direction = 1;//Goes UP
			movementTot = moveTotDefault;
		}
		else if ((playerPosY * -1 <= vRange && playerPosY* -1 >= 0) && (playerPosX * -1 <= vRange && playerPosX <= vRange) &&
				(tileMap->LevelsTileMaps[App->scene->currentLevel][nPoint.y + 1][nPoint.x] == 0 ||
				tileMap->LevelsTileMaps[App->scene->currentLevel][nPoint.y + 1][nPoint.x] == 4)) {
			direction = 0;//Goes DOWN
			movementTot = moveTotDefault*5;
		}
		else {
			direction = 4;
		}
	}
	else if (pC <= movementTot){
		++pC;
	}
	else if (pC >= movementTot) {
		pC = 0;
		onMovement = false;
		direction = 4;
	}

	cout << "PosX->" << position.x <<" || PosY->" << playerPosY<< " | Direction -> " << direction << endl;
	movement(direction);
}

void Saru::movement(int direction) {
	nPoint = tileMap->getTilePos(position);
	nPoint.y -= 1;

	switch (direction) {
		case 0://DOWN
			currentAnimation = &downAnim;
			currentAnimation->hasIdle = false;
			isFlip = false;
			position.y += speed;
			onMovement = true;
			break;
		case 1://UP
			currentAnimation = &upAnim;
			currentAnimation->hasIdle = false;
			isFlip = false;
			position.y -= speed;
			onMovement = true;
			break;
		case 2://RIGHT
			currentAnimation = &rightAnim;
			currentAnimation->hasIdle = false;
			isFlip = false;
			position.x += speed;
			onMovement = true;
			break;
		case 3://LEFT
			currentAnimation = &leftAnim;
			currentAnimation->hasIdle = false;
			isFlip = true;
			position.x -= speed;
			onMovement = true;
			break;
		default:
			currentAnimation = &idleAnim;
			currentAnimation->hasIdle = true;
			isFlip = false;
	}
}

void Saru::shot() {

}

void Saru::OnCollision(Collider* col) {
	ModuleEnemy::OnCollision(col);
}


void Saru::Die() {
	if (pendingToDelete) return;
	App->scene->playerSettings->playerScore += 1000; //Temporal score
	isDead = true;

	col->pendingToDelete = true;

	pendingToDelete = true;
}

void Saru::ProtectCountdown() {
	if (protect) {
		//injureAnim = !injureAnim;
		protectCount++;

		if (protectCount >= 40) {
			protect = false;
			protectCount = 0;
			cout << "Protect Finish" << endl;
		}
	}
}
