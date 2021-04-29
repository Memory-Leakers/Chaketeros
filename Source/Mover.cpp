#include "Mover.h"

Mover::Mover(iPoint spawnPos, iPoint* playerPos, Tile* level1Tile)
{
	position.x = spawnPos.x;
	position.y = spawnPos.y;
	bounds.x = position.x;
	bounds.y = position.y;
	bounds.w = 16;
	bounds.h = 16;
	this->playerPos = playerPos;
	this->level1Tile = level1Tile;

	#pragma region Init Anim

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

	#pragma endregion
	currentAnimation = &downAnim;

	// Init destroyed particle
	dieParticle = new Particle(500.0f, 0.05f, texture);
	dieParticle->anim.PushBack({ 232,166,23,30 });

}

Mover::~Mover() 
{
	delete dieParticle;
	dieParticle = nullptr;
}

bool Mover::Start() 
{
	LOG("LOADING ENEMY MOVER");

	texture = App->textures->Load("Assets/Images/Sprites/Enemies_Sprites/Enemies.png");

	col = App->collisions->AddCollider(bounds, Type::ENEMY, App->scene);

	moverTimer = Timer::Instance();

	return true;
}

UpdateResult Mover::PreUpdate()
{
	iPoint tilePos =  level1Tile->getTilePos(position);
	iPoint centerTile = level1Tile->getWorldPos(tilePos);

	if (position == centerTile)
	{
		moveDirIndex = AStar();
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult Mover::Update() 
{
	col->SetPos(this->position.x, this->position.y);

	moverTimer->Update();

	if (moverTimer->getDeltaTime() >= 0.2f)
	{
		if (moveDirIndex != -1)
		{
			FixedUpdate();
		}		
		moverTimer->Reset();
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void Mover::FixedUpdate()
{
	position += moveDir[moveDirIndex];
}

UpdateResult Mover::PostUpdate() {

	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	iPoint tempPos = position;
	tempPos += {-4, -14};

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

void Mover::RandomMov() {
	
	if ((position.x - 8) % (32) == 0 && position.y % 32 == 0) 
	{
		randomDir = rand() % 4;
	}

	switch (randomDir)
	{
	case 0: //UP
		isFlip = false;
		currentAnimation = &upAnim;
		currentAnimation->hasIdle = false;
		position.y -= speed;
		break;
	case 1: //DOWN
		isFlip = false;
		currentAnimation = &downAnim;
		currentAnimation->hasIdle = false;
		position.y += speed;
		break;
	case 2: //RIGHT
		isFlip = false;
		currentAnimation = &rightAnim;
		currentAnimation->hasIdle = false;
		position.x += speed;
		break;
	case 3: //LEFT
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

int Mover::AStar()
{
	// 我的初始格子的坐标 // mi posicion (tile)
	iPoint myTilePos = level1Tile->getTilePos(position);	
	myTilePos.y--;
	// 目标的格子的坐标 // posicion de destinatario (tile)
	iPoint playerTilePos = level1Tile->getTilePos(*playerPos);
	playerTilePos.y--;

	// 我到目标的距离 // distancia entre yo y destinatario
	int distance = position.DistanceManhattan(myTilePos, playerTilePos);

	// 我当前在的格子 // grid que estoy ubicado
	PathNode currentGrid;
	// 起始格子到达当前格子的花费 // el coste de grid que estaba en principio hasta este grid
	currentGrid.g_cost = 0;
	// 当前格子到达目标格子的花费 // el coste del grid que estoy hasta el destinatatio
	currentGrid.h_cost = distance;
	// 上面两个加起来 // suma de los dos = coste de este grid
	currentGrid.total_cost = currentGrid.g_cost + currentGrid.h_cost;
	// Inicial la posicion del primer grid
	currentGrid.pos.x = myTilePos.x;
	currentGrid.pos.y = myTilePos.y;
	// el primer indice es -1
	currentGrid.lastIndex = -1;

	// 储存当前检测到但还没走的格子 // guarda los grids que detectadas 
	vector<PathNode> openGrid;
	// 储存已经走过的格子 // guarda los grids que esta usada
	vector<PathNode> closeGrid;	
	// 将其实格子存入到检测里面 // guardar el grid que estamos ahora dentro de grid detectada
	openGrid.push_back(currentGrid);

	// 判断当前检测的格子是否是个有效的格子 // detectar si es un grid util o no
	bool pass = false;

	// 如果检测到的格子还没用完 // si nos quedan grids para detectar
	while (!openGrid.empty())
	{	
		// 最便宜的格子 // grid que tiene menos coste
		int lessGrid[2] = { 0, openGrid[0].total_cost };

		for (int i = 0; i < openGrid.size(); i++)
		{
			if (openGrid[i].total_cost < openGrid[lessGrid[0]].total_cost)
			{
				// 刷新最便宜的格子 // actuaizar el grid que tiene menos coste
				lessGrid[0] = i;
				lessGrid[1] = openGrid[i].total_cost;		
			}
		}

		// 保存最便宜的格子为当前处理的格子 // guardar el grid que tiene menos coste como el grid acutual
		PathNode lessNode = openGrid[lessGrid[0]];
		// 删除原有的格子 // eleminarlo del openGrid
		openGrid.erase(openGrid.begin() + lessGrid[0]);

		// 如果当前格子是最后的格子 // si el grid actual es el grid de destinatario
		if (lessNode.h_cost == 0)
		{
			closeGrid.push_back(lessNode);
		
			vector <int> instruction;

			for (int i = closeGrid.size() -1 ; i >= 0; i = closeGrid[i].lastIndex)
			{
				instruction.push_back(closeGrid[i].dir);
			}

			return instruction[instruction.size() - 2];
		}
		
		// 获取四个方向的格子 // obtener grid de 4 direcciones alrededor del grid actual
		iPoint dir[4] =
		{{ lessNode.pos.x + 1, lessNode.pos.y}, // Right
		{ lessNode.pos.x - 1, lessNode.pos.y }, // Left
		{ lessNode.pos.x , lessNode.pos.y - 1 }, // Up
		{ lessNode.pos.x , lessNode.pos.y + 1}}; // Down
		
		// 判断四个方向的格子是否有效 // detectar si puedes avanzar en alguna de las 4 direcciones
		for (int i = 0; i < 4; ++i)
		{
			pass = false;

			// 如果当前格子是障碍物 // si el grid que vamos a ir no es 0 o 4
			if(level1Tile->Level1TileMap[dir[i].y][dir[i].x] != 0 && level1Tile->Level1TileMap[dir[i].y][dir[i].x] != 4)
			{
				// 跳过当前格子 // ignoramos este grid
				pass = true;
				continue;
			}

			for (int j = 0; j < closeGrid.size(); ++j)
			{
				// 如果当前格子已经存在在closeGrid里面 // si ya existe en close grid
				if (closeGrid[j].pos == dir[i])
				{
					// 跳过当前格子
					pass = true;
					break;
				}
			}

			for (int k = 0; k < openGrid.size(); ++k)
			{
				// 如果当前格子已经存在在openGrid里面 // si ya existe en opengrid
				if (openGrid[k].pos == dir[i])
				{
					// 跳过当前格子
					pass = true;
					break;
				}
			}

			// 如果有效，则加入到检测的格子里 // si es un grid valido
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

void Mover::OnCollision(Collider* col) 
{
	if (col->type == Type::EXPLOSION) 
	{
		die();
	}
}

void Mover::die()
{
	isDead = false;

	col->pendingToDelete = true;

	App->particle->AddParticle(*dieParticle, position, Type::NONE, true, 0, 0);

	moverTimer->Release();

	delete dieParticle;
	dieParticle = nullptr;
}