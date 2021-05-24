#include "Snail.h"

SDL_Rect* rectSnail;

Snail::Snail(iPoint spawnPos, SDL_Texture* tex, Tile* levelMap) {
	texture = tex;
	position.x = spawnPos.x;
	position.y = spawnPos.y;
	bounds.x = position.x;
	bounds.y = position.y;
	bounds.w = 16;
	bounds.h = 16;
	tileMap = levelMap;
	points = 100;
}

Snail::~Snail() {

}

bool Snail::Start() {

	LOG("LOADING ENEMY SNAIL");

	col = App->collisions->AddCollider(bounds, Type::ENEMY, App->scene);

#pragma region Init Anim

	// Anim DOWN
	downAnim.PushBack({ 2,58,22,28 });//IDLE
	downAnim.PushBack({ 35,59,22,28 });
	downAnim.PushBack({ 68,59,22,28 });
	downAnim.PushBack({ 2,58,22,28 });//IDLE
	downAnim.speed = 0.03f;
	downAnim.loop = true;
	downAnim.hasIdle = false;

	// Animation UP
	upAnim.PushBack({ 200,56,22,32 });//IDLE
	upAnim.PushBack({ 233,56,22,32 });
	upAnim.PushBack({ 2,95,22,32 });
	upAnim.PushBack({ 200,56,22,32 });//IDLE
	upAnim.speed = 0.03f;
	upAnim.loop = true;
	upAnim.hasIdle = false;

	// Animation RIGHT
	rightAnim.PushBack({ 99,56,27,30 });//IDLE
	rightAnim.PushBack({ 129,56,28,30 });
	rightAnim.PushBack({ 166,56,26,30 });
	rightAnim.speed = 0.03f;
	rightAnim.loop = true;
	rightAnim.hasIdle = false;

	//Animation LEFT
	leftAnim.PushBack({ 99,56,27,30 });//IDLE
	leftAnim.PushBack({ 129,56,28,30 });
	leftAnim.PushBack({ 166,56,26,30 });
	leftAnim.speed = 0.03f;
	leftAnim.loop = true;
	leftAnim.hasIdle = false;

	// Current anim
	currentAnimation = &downAnim;
	currentAnimation->loop = true;
	currentAnimation->hasIdle = false;
	currentAnimation->speed = 0.03f;

#pragma endregion
#pragma region Init destroy particle
	dieParticle.InitParticle(500.0f, 0.1f, texture);
	dieParticle.anim.PushBack({ 35,97,28,30 });
	dieParticle.anim.PushBack({ 68,97,28,30 });
	dieParticle.anim.speed = 0.08f;
#pragma endregion

	return true;
}

UpdateResult Snail::PreUpdate()
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

UpdateResult Snail::Update() {

	col->SetPos(this->position.x, this->position.y);

	snailTimer.Update();

	if (snailTimer.getDeltaTime() >= 0.1f)
	{
		FixedUpdate();

		snailTimer.Reset();
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult Snail::PostUpdate() {

	currentAnimation->Update();

	rectSnail = &currentAnimation->GetCurrentFrame();

	iPoint tempPos = position;
	tempPos += {-4, -14};

	if (currentAnimation == &downAnim || currentAnimation == &upAnim)
	{
		if (currentAnimation->getCurrentFrameF() >= 3 && currentAnimation->getCurrentFrameF() <= 4)
		{
			isFlip = true;
		}
	}

	if (isFlip)
	{
		//App->render->DrawRotateTexture(texture, tempPos, &rect, false, 180);
		App->render->AddTextureRenderQueue(texture, tempPos, rectSnail, 1, position.y, false, 180);
	}
	else
	{
		//App->render->DrawTexture(texture, tempPos, &rect);
		App->render->AddTextureRenderQueue(texture, tempPos, rectSnail, 1, position.y);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void Snail::Die()
{
	if (pendingToDelete) return;

	col->pendingToDelete = true;

	iPoint tempPos = position;
	tempPos += {-4, -14};
	App->particle->AddParticle(dieParticle, tempPos, Type::NONE, true, 0, 0);

	pendingToDelete = true;
}

int Snail::RandomMov()
{
	// Get snail tile posiion
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

void Snail::FixedUpdate()
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
		isFlip = true;
		if (currentAnimation != &rightAnim)
		{
			currentAnimation = &rightAnim;
		}
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