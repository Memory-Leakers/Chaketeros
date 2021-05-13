#include "Mover.h"

SDL_Rect* rectMover;

Mover::Mover(iPoint spawnPos, iPoint* playerPos, Tile* level1Tile)
{
	this->playerPos = playerPos; // Player pivot
	this->level1Tile = level1Tile;
	position.x = spawnPos.x;
	position.y = spawnPos.y;
	bounds.x = position.x;
	bounds.y = position.y;
	bounds.w = 16;
	bounds.h = 16;	
}

Mover::~Mover() 
{
	if(dieParticle!=nullptr)
	{
		delete dieParticle;
		dieParticle = nullptr;
	}
}

bool Mover::Start() 
{
	LOG("LOADING ENEMY MOVER");

	texture = App->textures->Load("Assets/Images/Sprites/Enemies_Sprites/Enemies.png");

	col = App->collisions->AddCollider(bounds, Type::ENEMY, App->scene);

	#pragma region Init Anim

	// Anim DOWN
	downAnim.PushBack({ 5,166,23,30 });//IDLE
	downAnim.PushBack({ 37,166,23,30 });
	downAnim.PushBack({ 5,166,23,30 });//IDLE
	downAnim.PushBack({ 37,166,23,30 });
	downAnim.speed = 0.08f;
	downAnim.loop = true;
	downAnim.hasIdle = false;

	// Animation UP
	upAnim.PushBack({ 69,166,23,30 });//IDLE
	upAnim.PushBack({ 101,166,23,30 });
	upAnim.PushBack({ 69,166,23,30 });//IDLE
	upAnim.PushBack({ 101,166,23,30 });
	upAnim.speed = 0.08f;
	upAnim.loop = true;
	upAnim.hasIdle = false;

	// Animation RIGHT
	rightAnim.PushBack({ 135,166,23,30 });//IDLE
	rightAnim.PushBack({ 168,166,23,30 });
	rightAnim.PushBack({ 135,166,23,30 });//IDLE
	rightAnim.PushBack({ 201,166,23,30 });
	rightAnim.speed = 0.08f;
	rightAnim.loop = true;
	rightAnim.hasIdle = false;

	//Animation LEFT
	leftAnim.PushBack({ 135,166,23,30 });//IDLE
	leftAnim.PushBack({ 168,166,23,30 });
	leftAnim.PushBack({ 135,166,23,30 });//IDLE
	leftAnim.PushBack({ 201,166,23,30 });
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
	dieParticle = new Particle(500.0f, 0.05f, texture);
	dieParticle->anim.PushBack({ 232,166,23,30 });
	dieParticle->anim.speed = 0.02f;
	#pragma endregion

	return true;
}

UpdateResult Mover::PreUpdate()
{
	iPoint tilePos =  level1Tile->getTilePos(position);
	iPoint centerTile = level1Tile->getWorldPos(tilePos);

	// Deteci if mover is center of grid
	if (position == centerTile)
	{
		AStarMoveDirIndex = AStar();

		randomMoveDirIndex = RandomMov();
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult Mover::Update() 
{
	col->SetPos(this->position.x, this->position.y);

	moverTimer.Update();

	if (moverTimer.getDeltaTime() >= 0.05f)
	{
		FixedUpdate();

		moverTimer.Reset();	
	}

	if(App->input->keys[SDL_SCANCODE_F6] == KEY_DOWN)
	{
		debugAStarPath = !debugAStarPath;
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void Mover::FixedUpdate()
{
	if (AStarMoveDirIndex != -1)
	{
		position += moveDir[AStarMoveDirIndex];
		currentDir = AStarMoveDirIndex;
	}
	else if(randomMoveDirIndex != -1)
	{
		position += moveDir[randomMoveDirIndex];
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

UpdateResult Mover::PostUpdate() {

	currentAnimation->Update();

	rectMover = &currentAnimation->GetCurrentFrame();

	iPoint tempPos = position;
	tempPos += {-4, -14};

	if(currentAnimation == &downAnim || currentAnimation == &upAnim)
	{
		if (currentAnimation->getCurrentFrameF() >= 3 && currentAnimation->getCurrentFrameF() <= 4)
		{
			isFlip = true;
		}
	}

	if (isFlip)
	{
		//App->render->DrawRotateTexture(texture, tempPos, &rect, false, 180);
		App->render->AddTextureRenderQueue(texture, tempPos, rectMover, 1, position.y, false, 180);
	}
	else
	{
		//App->render->DrawTexture(texture, tempPos, &rect);
		App->render->AddTextureRenderQueue(texture, tempPos, rectMover, 1, position.y);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void Mover::OnCollision(Collider* col)
{
	if (col->type == Type::EXPLOSION)
	{
		die();
		App->scene->currentScene->score += 800;
	}
}

int Mover::RandomMov()
{
	// Get mover tile posiion
	iPoint myTilePos = level1Tile->getTilePos(position);
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
		int thisGrid = level1Tile->Level1TileMap[dir[i].y][dir[i].x];
		if(thisGrid == 0 || thisGrid == 4)
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
			if(moveDirContrary[currentDir] == dirIndex[i])
			{
				// quit turn around option
				dirIndex.erase(dirIndex.begin() + i);
			}
		}
	}

	// if has usable direccion
	if(!dirIndex.empty())
	{
		// return random usable direccion	
		return dirIndex[rand() % dirIndex.size()];
	}

	return -1;
}

int Mover::AStar()
{
	if (playerPos == nullptr)
	{
		return -1;
	}

	// mi posicion (tile)
	iPoint myTilePos = level1Tile->getTilePos(position);	
	myTilePos.y--;

	// posicion de destinatario (tile)
	iPoint playerTilePos = level1Tile->getTilePos(*playerPos);
	playerTilePos.y--;

	if (myTilePos == playerTilePos)
	{
		return -1;
	}

	// distancia entre yo y destinatario
	int distance = position.DistanceManhattan(myTilePos, playerTilePos);

	// grid que estoy ubicado
	PathNode currentGrid;

	// el coste de grid que estaba en principio hasta este grid
	currentGrid.g_cost = 0;

	// el coste del grid que estoy hasta el destinatatio
	currentGrid.h_cost = distance;

	// suma de los dos = coste de este grid
	currentGrid.total_cost = currentGrid.g_cost + currentGrid.h_cost;

	// Inicial la posicion del primer grid
	currentGrid.pos.x = myTilePos.x;
	currentGrid.pos.y = myTilePos.y;

	// el primer indice es -1
	currentGrid.lastIndex = -1;

	// guarda los grids que detectadas 
	vector<PathNode> openGrid;

	// guarda los grids que esta usada
	vector<PathNode> closeGrid;	

	// guardar el grid que estamos ahora dentro de grid detectada
	openGrid.push_back(currentGrid);

	// detectar si es un grid util o no
	bool pass = false;

	// si nos quedan grids para detectar
	while (!openGrid.empty())
	{	
		// grid que tiene menos coste
		int lessGrid[2] = { 0, openGrid[0].total_cost };

		for (int i = 0; i < openGrid.size(); i++)
		{
			if (openGrid[i].total_cost < openGrid[lessGrid[0]].total_cost)
			{
				// actuaizar el grid que tiene menos coste
				lessGrid[0] = i;
				lessGrid[1] = openGrid[i].total_cost;		
			}
		}

		// guardar el grid que tiene menos coste como el grid acutual
		PathNode lessNode = openGrid[lessGrid[0]];

		// eleminarlo del openGrid
		openGrid.erase(openGrid.begin() + lessGrid[0]);

		// si el grid actual es el grid de destinatario
		if (lessNode.h_cost == 0)
		{
			closeGrid.push_back(lessNode);
		
			vector <int> instruction;

			// closeGrid[i].lastIndex apunta hacia el grid anterior del que esta ahora para evitar las bifurcacion
			for (int i = closeGrid.size() -1 ; i >= 0; i = closeGrid[i].lastIndex)
			{
				if(debugAStarPath)
				{
					// Draw path
					iPoint tempPos = closeGrid[i].pos;
					App->render->AddRectRenderQueue({ tempPos.x * 16 + 12,tempPos.y * 16 + 18,10,10 }, { 255, 0, 0, 255 });
				}
						
				instruction.push_back(closeGrid[i].dir);
			}

			// instruction.size() -> out range
			// instruction.size()-1 -> current grid
			// instruction.size()-2 -> good direction
			return instruction[instruction.size() - 2];
		}
		
		// obtener grid de 4 direcciones alrededor del grid actual
		iPoint dir[4] =
		{{ lessNode.pos.x + 1, lessNode.pos.y}, // Right
		{ lessNode.pos.x - 1, lessNode.pos.y }, // Left
		{ lessNode.pos.x , lessNode.pos.y - 1 }, // Up
		{ lessNode.pos.x , lessNode.pos.y + 1}}; // Down
		
		// detectar si puedes avanzar en alguna de las 4 direcciones
		for (int i = 0; i < 4; ++i)
		{
			pass = false;

			int thisGrid = level1Tile->Level1TileMap[dir[i].y][dir[i].x];
			// si el grid que vamos a ir no es 0 o 4
			if(thisGrid != 0 && thisGrid != 4)
			{
				// ignoramos este grid
				pass = true;
				continue;
			}

			for (int j = 0; j < closeGrid.size(); ++j)
			{
				// si ya existe en close grid
				if (closeGrid[j].pos == dir[i])
				{
					pass = true;
					break;
				}
			}

			for (int k = 0; k < openGrid.size(); ++k)
			{
				// si ya existe en opengrid
				if (openGrid[k].pos == dir[i])
				{
					pass = true;
					break;
				}
			}

			// si es un grid valido
			if(!pass)
			{
				// creamos un nuevo nodo para el grid
				PathNode node;
				node.lastIndex = closeGrid.size();
				node.dir = i;
				node.pos.x = dir[i].x;
				node.pos.y = dir[i].y;
				node.h_cost = position.DistanceManhattan(dir[i], playerTilePos);
				node.g_cost = position.DistanceManhattan(dir[i], myTilePos);
				node.total_cost = node.g_cost + node.h_cost;

				// metemos dentro del openGrid
				openGrid.push_back(node);
			}
		}
		// metemos el grid que estamos gestionando dentro del closeGrid
		closeGrid.push_back(lessNode);
	}

	// si no ha encontrado ningun camino, devolvemos un -1
	return { -1 };
}

void Mover::die()
{
	if(pendingToDelete) return;

	col->pendingToDelete = true;

	iPoint tempPos = position;
	tempPos += {-4, -14};
	App->particle->AddParticle(*dieParticle, tempPos, Type::NONE, true, 0, 0);

	pendingToDelete = true;

	delete dieParticle;
	dieParticle = nullptr;
}