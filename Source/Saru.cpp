#include "Saru.h"

Saru::Saru(iPoint spawnPos, iPoint* playerPos, iPoint* bananacherPos, Tile* tileMap) {
	this->playerPos = playerPos;
	this->bananacherPos = bananacherPos;
	bounds.w = 16;
	bounds.h = 16;
	bounds.x = position.x = spawnPos.x;
	bounds.y = position.y = spawnPos.y;
	this->tileMap = tileMap;
	life = 5; //5 It has to be this number so it can trigger the death animation at 1. It actually keeps having 4 lifes

	stopTimer[0] = 1.40f;
	stopTimer[1] = 1.80f;
	stopTimer[2] = 10.0f;
	stopTimer[3] = 1.05f;
	stopTimer[4] = 3.0f;
	stopTimer[5] = 0.60f;
}

Saru::~Saru() {
	
}

bool Saru::Start() {
	LOG("-LOADING ENEMY SARU-");
	bool ret = true;

	texture = App->textures->Load("Assets/Images/Sprites/Enemies_Sprites/Monkey.png");

	col = App->collisions->AddCollider(bounds, Type::ENEMY, App->scene);

	DeadSFX = App->audio->LoadSound("Assets/Audio/SFX/Boss_Battle_Sounds/BB_BossDeath.wav");

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
	DIE Animation
	*/

	/*Secuencia: 1 2 3 4*/
	dieAnim[0].PushBack({ 57 , 71, 23, 19 }); //Fase 1.1
	dieAnim[0].PushBack({ 84 , 71, 23, 19 }); //Fase 1.2
	dieAnim[0].PushBack({ 111 , 71, 23, 19 }); //Fase 1.3
	dieAnim[0].PushBack({ 138 , 71, 23, 19 }); //Fase 1.4
	dieAnim[0].speed = 0.05f;
	dieAnim[0].hasIdle = false;

	/*Secuencia: 1 2 1*/
	dieAnim[1].PushBack({ 165 , 54, 24, 36 }); //Fase 2.1
	dieAnim[1].PushBack({ 192 , 54, 24, 36 }); //Fase 2.2
	dieAnim[1].speed = 0.05f;
	dieAnim[1].hasIdle = false;

	/*Secuencia: Right(1 2 1 2 1 2) Left (1 2 1 2 1 2) X3*/
	dieAnim[2].PushBack({ 57 , 91, 24, 26 }); //Fase 3.1
	dieAnim[2].PushBack({ 83 , 91, 24, 26 }); //Fase 3.2
	dieAnim[2].speed = saruAnimSpeed;
	dieAnim[2].hasIdle = false;

	/*Secuencia: 1 2*Permanet* (Goes up and falls down slowly while moving backwards, it bounces a bit)*/
	dieAnim[3].PushBack({ 111 , 97, 31, 23 }); //Fase 4.1
	dieAnim[3].PushBack({ 149 , 97, 16, 19 });  //Fase 4.2
	dieAnim[3].speed = saruAnimSpeed;
	dieAnim[3].hasIdle = false;

	/*Secuencia: 1 2 1 2 1 2*/
	dieAnim[4].PushBack({ 167 , 91, 22, 29 }); //Fase 5.1
	dieAnim[4].PushBack({ 194 , 91, 22, 29 });  //Fase 5.2
	dieAnim[4].speed = saruAnimSpeed;
	dieAnim[4].hasIdle = false;

	/*Secuencia: 1 2 3*/
	dieAnim[5].PushBack({ 4 , 123, 76, 76 }); //Fase 6.1
	dieAnim[5].PushBack({ 96 , 123, 68, 76 });  //Fase 6.2
	dieAnim[5].PushBack({ 165 , 123, 76, 76 });  //Fase 6.2
	dieAnim[5].speed = saruAnimSpeed;
	dieAnim[5].hasIdle = false;


	/*
	SHOT PARTICLE
	*/
	theShot.InitParticle(500.0f, 0.25f, texture);
	theShot.anim.PushBack({ 58, 49, 12, 5 });
	theShot.setLifeTime(100.0f);
	theShot.anim.hasIdle = true;

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
		shot();

		updateTimer.Reset();
	}

	deathAnimSequence();

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult Saru::PostUpdate() {
	iPoint tempPos;
	
	if (life != 1) {
		currentAnimation->Update();
		rectSaru = &currentAnimation->GetCurrentFrame();
		tempPos = position;
		tempPos.y -= 1; //Texture position fix
		tempPos.x -= 2; //Texture position fix
	}
	else {
		currentAnimation->Update();
		if (countDeath == 2 || countDeath == 4) {
			rectSaru = &currentAnimation->GetCurrentFrame();
		}
		
		tempPos = position;
		tempPos.y -= tempY;
		tempPos.x -= tempX;
	}
	


	//Render flip
	if (isFlip) App->render->AddTextureRenderQueue(texture, tempPos, rectSaru, 1, position.y, false, 180);
	else App->render->AddTextureRenderQueue(texture, tempPos, rectSaru, 1, position.y);


	return UpdateResult::UPDATE_CONTINUE;
}

void Saru::logic() {
	if (life == 1) return;
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

	//cout << "PosX->" << position.x <<" || PosY->" << playerPosY<< " | Direction -> " << direction << endl;
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
	if (bananacherPos == nullptr) { return; }

	int theNum = 46;
	int random = rand() % 120;


	if (theNum == random) {
		theShot.position.x = position.x;
		theShot.position.y = position.y;
		int auxX = (bananacherPos->x - position.x) / 20;
		int auxY = (bananacherPos->y - position.y) / 20;

		if (auxX < -3) auxX = -3;
		else if (auxX > 3 ) auxX = 3;
		if (auxY < -3) auxY = -3;
		else if (auxY > 3) auxY = 3;

		cout << auxX << " | " << auxY << endl;
		theShot.setSpeed({ auxX , auxY });
		App->particle->AddParticle(theShot, position, Type::SARUSHOT, true, 0, 66.1f);
		
		shooting = true;
	}
}

void Saru::OnCollision(Collider* col) {
	ModuleEnemy::OnCollision(col);
}

void Saru::deathAnimSequence() {
	if (life != 1 || pendingToDelete) return;
	if (countDeath >= 6) Die();
	if (countDeath == -1) {
		++countDeath;
		f3CBottom = position.y;
		f3CTop = position.y - 30;
		deathTimer[countDeath].Reset();
	}
	/*Secuencia: 1 2 3 4*/
	/*Secuencia: 1 2 1*/
	/*Secuencia: Right(1 2 1 2 1 2) Left (1 2 1 2 1 2) X3*/
	/*Secuencia: 1 2*Permanet* (Goes up and falls down slowly while moving backwards, it bounces a bit)*/
	/*Secuencia: 1 2 1 2 1 2*/
	/*Secuencia: 1 2 3*/

		temporalTimer.Update();
		for (int k = 0; k <= dieAnim[countDeath].size(); ++k) {
			currentAnimation = &dieAnim[countDeath];
			//rectSaru = &currentAnimation->GetCurrentFrame();
			switch (countDeath) {
				case 0:	
					tempX = 2;
					tempY = 1;
					switch (tempCount) {
						case 0:
							rectSaru = &currentAnimation->getFrame(0);
							if (temporalTimer.getDeltaTime() >= 0.35) {
								++tempCount;
								temporalTimer.Reset();
							}
							break;
						case 1:
							rectSaru = &currentAnimation->getFrame(1);
							if (temporalTimer.getDeltaTime() >= 0.35) {
								++tempCount;
								temporalTimer.Reset();
							}
							break;
						case 2:
							rectSaru = &currentAnimation->getFrame(2);
							if (temporalTimer.getDeltaTime() >= 0.35) {
								++tempCount;
								temporalTimer.Reset();
							}
							break;
						case 3:
							rectSaru = &currentAnimation->getFrame(4);
							if (temporalTimer.getDeltaTime() >= 0.35) {
								tempCount = 0;
								temporalTimer.Reset();
							}
							break;
					}
					break;
				case 1:
					tempY = 18;
					tempX = 2;
					switch (tempCount) {
						case 0:
							rectSaru = &currentAnimation->getFrame(0);
							if (temporalTimer.getDeltaTime() >= 0.60) {
								++tempCount;
								temporalTimer.Reset();
							}
							break;
						case 1:
							rectSaru = &currentAnimation->getFrame(1);
							if (temporalTimer.getDeltaTime() >= 0.60) {
								++tempCount;
								temporalTimer.Reset();
							}
							break;
						case 2:
							rectSaru = &currentAnimation->getFrame(0);
							if (temporalTimer.getDeltaTime() >= 0.60) {
								tempCount = 0;
								temporalTimer.Reset();
							}
							break;
					}
					break;
				case 2:
					tempX = 1;
					tempY = 9;
					switch (tempCount) {
						case 0:
						case 2:
						case 4:
							position.x += 1;
							isFlip = true;
							if (temporalTimer.getDeltaTime() >= 0.25) {
								++tempCount;
								temporalTimer.Reset();
							}
							break;
						case 1:
						case 3:
							position.x -= 1;
							isFlip = false;
							if (temporalTimer.getDeltaTime() >= 0.25) {
								++tempCount;
								temporalTimer.Reset();
							}
							break;
						case 5:
							if (position.x <= 10) {
								++countDeath;
								deathTimer[countDeath].Reset();
								tempCount = 0;
								temporalTimer.Reset();
							}
							else {
								position.x -= 1;
								isFlip = false;
							}
							break;
					}
					break;
				case 3:
					switch (tempCount) {
						case 0:
							rectSaru = &currentAnimation->getFrame(0);
							if (temporalTimer.getDeltaTime() >= 0.05) {
								++tempCount;
								temporalTimer.Reset();
							}
							break;
						case 1:
							f3CTimer.Update();
							if (f3CTimer.getDeltaTime() >= 0.03) {
								rectSaru = &currentAnimation->getFrame(1);
								if (position.y >= f3CTop && f3CDir) {
									position.y -= 3;
									position.x += 1;
								}
								else if (position.y <= f3CBottom && !f3CDir) {
									position.y += 3;
									position.x += 1;
								}
								else {
									f3CDir = !f3CDir;
									f3CTop += 15;
								}
								
								f3CTimer.Reset();
							}
							if (temporalTimer.getDeltaTime() >= 2.00f) {
								tempCount = 0;
								
								++countDeath;
								deathTimer[countDeath].Reset();
								temporalTimer.Reset();
							}
							break;
					}
					break;
				case 4:
					tempX = 2;
					tempY = 10;
					tempCount = 0;
					temporalTimer.Reset();
					break;
				case 5:
					switch (tempCount) {
						case 0:
							rectSaru = &currentAnimation->getFrame(0);
							tempX = 30;//1
							tempY = 31;
							if (temporalTimer.getDeltaTime() >= 0.20f) {
								++tempCount;
								temporalTimer.Reset();
							}
							break;
						case 1:
							rectSaru = &currentAnimation->getFrame(1);
							tempX = 20;//1
							tempY = 33;
							if (temporalTimer.getDeltaTime() >= 0.20f) {
								++tempCount;
								temporalTimer.Reset();
							}
							break;
						case 2:
							rectSaru = &currentAnimation->getFrame(2);
							tempX = 21;//3
							tempY = 33;
							if (temporalTimer.getDeltaTime() >= 0.20f) {
								++tempCount;
								temporalTimer.Reset();
							}
							break;
					}
					break;
			}
			deathTimer[countDeath].Update();
			if (deathTimer[countDeath].getDeltaTime() >= stopTimer[countDeath]) {
				++countDeath;
				deathTimer[countDeath].Reset();
			}
		}
}

void Saru::Die() {
	if (pendingToDelete) return;

	isDead = true;

	App->audio->PlaySound(DeadSFX, 0);

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
