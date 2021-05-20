#include "Mouse.h"

SDL_Rect* rectMouse;

Mouse::Mouse(iPoint spawnPos, SDL_Texture* tex, Tile* levelMap) {
	texture = tex;
	position.x = spawnPos.x;
	position.y = spawnPos.y;
	bounds.x = position.x;
	bounds.y = position.y;
	bounds.w = 16;
	bounds.h = 16;
	tileMap = levelMap;
}

Mouse::~Mouse() {

}

bool Mouse::Start() {

	LOG("LOADING ENEMY MOUSE");

	col = App->collisions->AddCollider(bounds, Type::ENEMY, App->scene);

#pragma region Init Anim

	// Anim DOWN
	downAnim.PushBack({ 107,136,26,27 });//IDLE
	downAnim.PushBack({ 140,136,26,27 });
	downAnim.speed = 0.12f;
	downAnim.loop = true;
	downAnim.hasIdle = false;

	// Animation UP
	upAnim.PushBack({ 107,136,26,27 });//IDLE
	upAnim.PushBack({ 140,136,26,27 });
	upAnim.speed = 0.12f;
	upAnim.loop = true;
	upAnim.hasIdle = false;

	// Animation RIGHT
	rightAnim.PushBack({ 107,136,26,27 });//IDLE
	rightAnim.PushBack({ 140,136,26,27 });
	rightAnim.speed = 0.12f;
	rightAnim.loop = true;
	rightAnim.hasIdle = false;

	//Animation LEFT
	leftAnim.PushBack({ 107,136,26,27 });//IDLE
	leftAnim.PushBack({ 140,136,26,27 });
	leftAnim.speed = 0.12f;
	leftAnim.loop = true;
	leftAnim.hasIdle = false;

	// Current anim
	currentAnimation = &downAnim;
	currentAnimation->loop = true;
	currentAnimation->hasIdle = false;
	currentAnimation->speed = 0.12f;

#pragma endregion
#pragma region Init destroy particle
	dieParticle.InitParticle(500.0f, 0.1f, texture);
	dieParticle.anim.PushBack({ 173,136,26,27 });
	dieParticle.anim.PushBack({ 208,136,26,27 });
	dieParticle.anim.speed = 0.08f;
#pragma endregion
	return true;
}

UpdateResult Mouse::PreUpdate()
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

UpdateResult Mouse::Update() {

	col->SetPos(this->position.x, this->position.y);

	mouseTimer.Update();

	if (mouseTimer.getDeltaTime() >= 0.04f)
	{
		FixedUpdate();

		mouseTimer.Reset();
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult Mouse::PostUpdate() {

	currentAnimation->Update();

	rectMouse = &currentAnimation->GetCurrentFrame();

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
		App->render->AddTextureRenderQueue(texture, tempPos, rectMouse, 1, position.y, false, 180);
	}
	else
	{
		//App->render->DrawTexture(texture, tempPos, &rect);
		App->render->AddTextureRenderQueue(texture, tempPos, rectMouse, 1, position.y);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void Mouse::OnCollision(Collider* col)
{
	if (col->type == Type::EXPLOSION)
	{
		Die();
		App->scene->currentScene->score += 400;
	}
}

void Mouse::Die()
{
	if (pendingToDelete) return;

	col->pendingToDelete = true;

	iPoint tempPos = position;
	tempPos += {-4, -14};
	App->particle->AddParticle(dieParticle, tempPos, Type::NONE, true, 0, 0);

	pendingToDelete = true;
}

int Mouse::RandomMov()
{
	// Get Mouse tile posiion
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

void Mouse::FixedUpdate()
{
	if (randomMoveDirIndex != -1)
	{
		iPoint temp = {moveDir[randomMoveDirIndex].x * speed ,moveDir[randomMoveDirIndex].y * speed} ;
		position += temp;
		currentDir = randomMoveDirIndex;
	}

	isFlip = false;

	switch (currentDir)
	{
	case 0:
		if (currentAnimation != &rightAnim)
			currentAnimation = &rightAnim;
		
		isFlip = true;
		break;
	case 1:
		if (currentAnimation != &leftAnim)
			currentAnimation = &leftAnim;
		
		break;
	case 2:
		if (currentAnimation != &upAnim)
			currentAnimation = &upAnim;
		
		break;
	case 3:
		if (currentAnimation != &downAnim)
			currentAnimation = &downAnim;
		
		break;
	default:
		break;
	}
}
