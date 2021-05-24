#include "Bananacher.h"


Bananacher::Bananacher()
{
}

Bananacher::Bananacher(iPoint spawnPos, Tile* tileMap)
{
	bounds.x = position.x = spawnPos.x;
	bounds.y = position.y = spawnPos.y;
	bounds.w = bounds.h = 16;
	this->tileMap = tileMap;
	life = 8;
}

Bananacher::~Bananacher()
{
}

bool Bananacher::Start()
{
	texture = App->textures->Load("Assets/Images/Sprites/Enemies_Sprites/Banana.png");

	col = App->collisions->AddCollider({ 0,0,16,16 }, Type::ENEMY, App->scene);

	#pragma region Init Anim

	// Anim DOWN
	downAnim.PushBack({ 3,2,47,74 });
	downAnim.PushBack({ 54,2,47,74 });
	downAnim.PushBack({ 105,2,47,74 });
	downAnim.PushBack({ 156,2,47,74 });
	downAnim.PushBack({ 207,2,47,74 });
	downAnim.PushBack({ 258,2,47,74 });
	downAnim.PushBack({ 309,2,47,74 });
	downAnim.PushBack({ 360,2,47,74 });
	downAnim.speed = 0.08f;
	downAnim.loop = true;
	downAnim.hasIdle = false;

	// Animation UP
	upAnim.PushBack({ 3,164,47,74 });
	upAnim.PushBack({ 54,164,47,74 });
	upAnim.PushBack({ 105,164,47,74 });
	upAnim.PushBack({ 156,164,47,74 });
	upAnim.PushBack({ 207,164,47,74 });
	upAnim.PushBack({ 258,164,47,74 });
	upAnim.PushBack({ 309,164,47,74 });
	upAnim.speed = 0.08f;
	upAnim.loop = true;
	upAnim.hasIdle = false;

	// Animation RIGHT
	rightAnim.PushBack({ 3,84,47,74 });
	rightAnim.PushBack({ 54,84,47,74 });
	rightAnim.PushBack({ 105,84,47,74 });
	rightAnim.PushBack({ 156,84,47,74 });
	rightAnim.PushBack({ 207,84,47,74 });
	rightAnim.PushBack({ 258,84,47,74 });
	rightAnim.PushBack({ 309,84,47,74 });
	rightAnim.PushBack({ 360,84,47,74 });
	rightAnim.speed = 0.08f;
	rightAnim.loop = true;
	rightAnim.hasIdle = false;

	//Animation LEFT
	leftAnim.PushBack({ 3,84,47,74 });
	leftAnim.PushBack({ 54,84,47,74 });
	leftAnim.PushBack({ 105,84,47,74 });
	leftAnim.PushBack({ 156,84,47,74 });
	leftAnim.PushBack({ 207,84,47,74 });
	leftAnim.PushBack({ 258,84,47,74 });
	leftAnim.PushBack({ 309,84,47,74 });
	leftAnim.PushBack({ 360,84,47,74 });
	leftAnim.speed = 0.08f;
	leftAnim.loop = true;
	leftAnim.hasIdle = false;

	// Current anim
	currentAnimation = &downAnim;
	currentAnimation->loop = true;
	currentAnimation->hasIdle = false;
	currentAnimation->speed = 0.08f;

#pragma endregion

	#pragma region Init destroy particle
	dieParticle.InitParticle(500.0f, 0.25f, texture);

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 6; j++)
		{
			dieParticle.anim.PushBack({ j * 79 + 3, i * 92 + 240,76,89 });
		}
	}
	#pragma endregion

	return true;
}

UpdateResult Bananacher::PreUpdate()
{
	iPoint tilePos = tileMap->getTilePos(position);
	iPoint centerTile = tileMap->getWorldPos(tilePos);

	// Deteci if mover is center of grid
	if (position == centerTile)
	{
		randomMoveDirIndex = RandomMov();
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult Bananacher::Update()
{
	// Update Col
	col->SetPos(this->position.x, this->position.y);

	bananaTimer.Update();

	if (bananaTimer.getDeltaTime() >= 0.05f)
	{
		ProtectCountdown();

		FixedUpdate();

		bananaTimer.Reset();
	}

	return UpdateResult();
}

UpdateResult Bananacher::PostUpdate()
{
	if(injureAnim)
	{
		SDL_Rect tempRect = { 0,0,1,1 };
		
		App->render->AddTextureRenderQueue(texture, position, &tempRect, 1, position.y, false, 180);
	}
	else
	{
		currentAnimation->Update();

		rectBanana = &currentAnimation->GetCurrentFrame();

		iPoint tempPos = position;

		tempPos += {-16, -54};

		if (currentAnimation == &rightAnim)
		{
			isFlip = true;
		}

		if (isFlip)
		{
			App->render->AddTextureRenderQueue(texture, tempPos, rectBanana, 1, position.y, false, 180);
		}
		else
		{
			App->render->AddTextureRenderQueue(texture, tempPos, rectBanana, 1, position.y);
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void Bananacher::OnCollision(Collider* col)
{
	ModuleEnemy::OnCollision(col);
}

void Bananacher::FixedUpdate()
{
	if (randomMoveDirIndex != -1)
	{
		position += moveDir[randomMoveDirIndex];
		currentDir = randomMoveDirIndex;
	}

	isFlip = false;

	switch (currentDir)
	{
	case 0:
		if (currentAnimation != &rightAnim)
		{
			currentAnimation = &rightAnim;
		}
		isFlip = true;
		break;
	case 1:
		if (currentAnimation != &leftAnim)
		{
			currentAnimation = &leftAnim;
		}
		break;
	case 2:
		if (currentAnimation != &upAnim)
		{
			currentAnimation = &upAnim;
		}
		break;
	case 3:
		if (currentAnimation != &downAnim)
		{
			currentAnimation = &downAnim;
		}
		break;
	}
}

int Bananacher::RandomMov()
{
	// Get mover tile posiion
	iPoint myTilePos = tileMap->getTilePos(position);
	// offset
	myTilePos.y--;

	iPoint dir[4] =
	{ { myTilePos.x + 1, myTilePos.y}, // Right
	{ myTilePos.x - 1, myTilePos.y }, // Left
	{ myTilePos.x , myTilePos.y - 1 }, // Up
	{myTilePos.x , myTilePos.y + 1} }; // Down

	vector <int> dirIndex;

	for (int i = 0; i < 4; ++i)
	{
		int thisGrid = tileMap->LevelsTileMaps[App->scene->currentLevel][dir[i].y][dir[i].x];
		if (thisGrid == 0 || thisGrid == 4)
		{
			// Save usable direccion
			dirIndex.push_back(i);
		}
	}

	// if has 2 or more dieccion
	if (dirIndex.size() > 1)
	{
		for (int i = 0; i < dirIndex.size(); ++i)
		{
			// if has option turn around
			if (moveDirContrary[currentDir] == dirIndex[i])
			{
				// quit turn around option
				dirIndex.erase(dirIndex.begin() + i);
			}
		}
	}

	// if has usable direccion
	if (!dirIndex.empty())
	{
		// return random usable direccion	
		return dirIndex[rand() % dirIndex.size()];
	}

	return -1;
}

void Bananacher::ProtectCountdown()
{
	if (protect)
	{
		injureAnim = !injureAnim;
		protectCount++;
		if (protectCount >= 40)
		{
			protect = false;
			protectCount = 0;
			cout << "Protect Finish" << endl;
		}
	}
}

void Bananacher::Die()
{
	if (pendingToDelete) return;

	col->pendingToDelete = true;

	iPoint tempPos = position;
	tempPos += {-28, -66};
	App->particle->AddParticle(dieParticle, tempPos, Type::NONE, true, 0, 66.1f);

	pendingToDelete = true;
}
