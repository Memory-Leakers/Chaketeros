#include "SceneLevel1.h"

#include "Collider.h"
#include "ModuleScene.h"
#include "YellowFlower.h"
#include "GlassCapsule.h"
#include "Stone.h"
#include "Bomb.h"
#include "Tile.h"
#include "RedFlower.h"
#include "Coin.h"
#include "CoreMecha.h"
#include "PowerUp.h"

#include <time.h>
#include <iostream>
#include <vector>
using namespace std;

#include "External/SDL_mixer/include/SDL_mixer.h"

// Texture
SDL_Texture* texMap = nullptr;
SDL_Texture* texFG = nullptr;
SDL_Texture* texUI = nullptr;
SDL_Texture* texBomb = nullptr;
SDL_Texture* texStone = nullptr;
SDL_Texture* texGlassCapsule = nullptr;
SDL_Texture* texYellowFlower = nullptr;
SDL_Texture* texEnemies = nullptr;
SDL_Texture* texItemDestroyed = nullptr;
SDL_Texture* texCoin = nullptr;
SDL_Texture* texPowerUpDestroyed = nullptr;
SDL_Texture* texCoreMecha = nullptr;
SDL_Texture* texPowerUps = nullptr;

// Player
Player* bomberman = nullptr;

// Particle
// Template particle for an center of explosion
Particle* explosionCenter = nullptr;

// Template particle for an middle of explosion
Particle* explosionMiddle = nullptr;

// Template particle for an end of explosion
Particle* explosionEnd = nullptr;

// Template particle for an end of powerUp
Particle* powerUpDestroyed = nullptr;

// Template particle for an end of red flower
Particle* redFlowerDestroyed = nullptr;

Obstacle* sceneObstacles[SCENE_OBSTACLES_NUM] = { nullptr };

vector<iPoint> emptySpaces;
int yellowFlowers;
Tile tileMap;
int renderExceptionPos[3];

PowerUp* Powers[MAX_POWERUPS];

SceneLevel1::SceneLevel1()
{
	// Init random system
	srand(time(NULL));
}

SceneLevel1::~SceneLevel1()
{
}

void SceneLevel1::LoadAsset()
{
	// Cargar sprites
	texMap = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/map.png");
	texFG = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/mapEnv.png");
	texUI = App->textures->Load("Assets/Images/Sprites/UI_Sprites/InGameUI.png");
	texBomb = App->textures->Load("Assets/Images/Sprites/Player_Sprites/Bomb.png");
	texStone = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Stone.png");
	texGlassCapsule = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Fragments_with_machine.png");
	texYellowFlower = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Yellow_Flower.png");
	texEnemies = App->textures->Load("Assets/Images/Sprites/Enemies_Sprites/Enemies.png");
	texItemDestroyed = App->textures->Load("Assets/Images/Sprites/PowerUps_Sprites/ItemDestroyedSheet.png");
	texCoin = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Coins.png");
	texPowerUpDestroyed = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Coins.png");
	texCoreMecha = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Core_Mecha.png");
	texPowerUps = App->textures->Load("Assets/Images/Sprites/PowerUps_Sprites/Powerups.png");

	#pragma region Init Particle

	// Explisions General parameter
	explosionCenter = new Particle(500.0f, 0.01f, texBomb);
	explosionMiddle = new Particle(500.0f, 0.01f, texBomb);
	explosionEnd = new Particle(500.0f, 0.01f, texBomb);

	// ExplosionCenter particle
	explosionCenter->anim.PushBack({ 21, 2, 16, 16 });
	explosionCenter->anim.PushBack({ 21, 21, 16, 16 });
	explosionCenter->anim.PushBack({ 21, 40, 16, 16 });

	// ExplosionMiddle particle
	explosionMiddle->anim.PushBack({ 42, 2, 16, 16 });
	explosionMiddle->anim.PushBack({ 42, 21, 16, 16 });
	explosionMiddle->anim.PushBack({ 42, 40, 16, 16 });	

	// ExplosionEnd particle
	explosionEnd->anim.PushBack({ 62, 2, 16, 16 });
	explosionEnd->anim.PushBack({ 62, 21, 16, 16 });
	explosionEnd->anim.PushBack({ 62, 40, 16, 16 });

	// PowerUps destroyed particle
	powerUpDestroyed = new Particle(500.0f, 0.01f, texPowerUpDestroyed);
	powerUpDestroyed->anim.PushBack({ 3,2,26,27 });
	powerUpDestroyed->anim.PushBack({ 35,2,26,27 });
	powerUpDestroyed->anim.PushBack({ 67,4,26,27 });
	powerUpDestroyed->anim.PushBack({ 3,34,26,25 });
	powerUpDestroyed->anim.PushBack({ 35,34,26,25 });
	powerUpDestroyed->anim.PushBack({ 67,34,26,25 });

	// Red Flower destroyed particle
	redFlowerDestroyed = new Particle(500.0f, 0.01f, texEnemies);
	redFlowerDestroyed->anim.PushBack({ 2,133,16,16 });
	redFlowerDestroyed->anim.PushBack({ 19,133,16,16 });
	redFlowerDestroyed->anim.PushBack({ 36,133,16,16 });
	redFlowerDestroyed->anim.PushBack({ 52,133,16,16 });
	redFlowerDestroyed->anim.PushBack({ 69,133,16,16 });
	redFlowerDestroyed->anim.PushBack({ 86,133,16,16 });

#pragma endregion
}

void SceneLevel1::CreateScene()
{
	//Check TileMap y axis
	//sceneObstacles[0] = new Bomb({ 100,100 }, texBomb, explosionCenter, explosionMiddle, explosionEnd);
	
	Powers[0] = new PowerUp({ 20,100 }, texPowerUps);
	
	for (int i = 0, k = 0, l = 0; i < 13; ++i)
	{
		for (int j = 0; j < 15; ++j)	//Check TileMap x axis
		{
			switch (tileMap.Level1TileMap[i][j])
			{
			case 0:
				emptySpaces.push_back(tileMap.getWorldPos({ j,i }) -= {0, -16});
				break;
			case 2:
				sceneObstacles[k++] = new Stone(tileMap.getWorldPos({ j,i }) -= {0, -16}, texStone);
				break;
			case 3:
				sceneObstacles[k++] = new RedFlower(tileMap.getWorldPos({ j,i }) -= {0, -16}, texEnemies, redFlowerDestroyed);
				break;
			case 6:
				renderExceptionPos[l++] = k;
				sceneObstacles[k++] = new CoreMecha(tileMap.getWorldPos({ j,i }) -= {0, -16}, texCoreMecha, texPowerUpDestroyed, powerUpDestroyed);
				break;
			case 9:
				renderExceptionPos[l++] = k;
				sceneObstacles[k++] = new GlassCapsule(tileMap.getWorldPos({ j,i }) -= {0, -16}, texGlassCapsule);
				break;
			default:
				break;
			}
		}
	}

	cout << endl;

	CreateYellowFlowers();
	


	// Check Map in Console
	for (int i = 0, k = 0; i < 13; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			cout << tileMap.Level1TileMap[i][j] << ",";
		}
		cout << endl;
	}
}

void SceneLevel1::CreateYellowFlowers()
{
	//Randomize yellow flowers number
	yellowFlowers = rand() % 6 + 43;

	for (int i = 0; i < yellowFlowers; i++)
	{
		int randomNum = rand() % emptySpaces.size();
		for (int j = 0; j < SCENE_OBSTACLES_NUM; j++)
		{
			if (sceneObstacles[j] == nullptr)
			{
				iPoint temporal = tileMap.getTilePos(emptySpaces.at(randomNum));

				//if (tileMap.Level1TileMap[temporal.x][temporal.y])

				sceneObstacles[j] = new YellowFlower(emptySpaces.at(randomNum), texYellowFlower, texPowerUpDestroyed, powerUpDestroyed);	//emptySpaces.at = return value at index

				iPoint temp = tileMap.getTilePos(emptySpaces.at(randomNum));	//Sets tileMap position to 4 to prevent multiple flowers on the same tile
				tileMap.Level1TileMap[temp.y - 1][temp.x] = 5;	//-1 en Y no sabemos por qu???

				emptySpaces.erase(emptySpaces.begin() + randomNum);	//delete the emptySpace position from the emptySpaces vector

				break;
			}
		}
	}
}

bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	*sceneObstacles = { nullptr };

	// Inicializar jugador
	bomberman = new Player();
	bomberman->Start();

	LoadAsset();

	// Create music
	App->audio->PlayMusic("Assets/Audio/Music/Area1_Jumming_Jungle.ogg", 1.5f);
	Mix_VolumeMusic(10);

	//testFont = App->scene->text->getFonts(36);

	CreateScene();

	return ret;
}

bool SceneLevel1::PreUpdate()
{

	if (bomberman != nullptr && bomberman->pendingToDelete)
	{
		delete bomberman;
		bomberman = nullptr;
	}

	for (int i = 0; i < SCENE_OBSTACLES_NUM; i++)
	{
		if (sceneObstacles[i] != nullptr && sceneObstacles[i]->pendingToDelete)
		{
			sceneObstacles[i]->CleanUp();
			delete sceneObstacles[i];
			sceneObstacles[i] = nullptr;
		}
	}
	if (Powers[0] != nullptr && Powers[0]->pendingToDelete)
	{
		delete Powers[0];
		Powers[0] = nullptr;
	}

	return true;
}

bool SceneLevel1::Update()
{
	// Get keys
	if (App->input->keys[SDL_SCANCODE_T] == KEY_DOWN)
	{
		App->scene->ChangeCurrentScene(INTRO_SCENE, 120);
	}

	// Update bomebrman
	if (bomberman != nullptr)
	{
		bomberman->Update();
	}

	if (App->input->keys[SDL_SCANCODE_J] == KEY_DOWN && bomberman->maxBombs > 0)
	{
		for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
		{
			if(sceneObstacles[i] == nullptr)
			{
				sceneObstacles[i] = new Bomb(bomberman, texBomb, explosionCenter, explosionMiddle, explosionEnd);
				bomberman->maxBombs--;
				break;
			}
		}
	}

	// Update obstacle
	for (int i = 0; i < SCENE_OBSTACLES_NUM; i++)
	{
		if (sceneObstacles[i] != nullptr)
		{
			sceneObstacles[i]->Update();
		}
	}

	return true;
}

bool SceneLevel1::PostUpdate()
{
	SDL_Rect rectUI = { 0,0,256,23 };

	// Draw Map
	App->render->DrawTexture(texMap, { 0, 16 }, nullptr);

	// Draw Obstacle
	for (int i = 0; i < SCENE_OBSTACLES_NUM; i++)
	{
		if (sceneObstacles[i] != nullptr)
		{
			sceneObstacles[i]->PostUpdate();

			
			
		}
	}
	bool isRender = false;
	/*for (int i = 0; i < 3; i++)
	{
		// Si hay obstaculo que ubica arriba de player o player esta en primera fila
		if (sceneObstacles[renderExceptionPos[i]]->getPosition().y >= bomberman->position.y) // Pendiente de optimizar
		{
			// Draw Bomberman
			if (!isRender) {
				bomberman->PostUpdate();
				isRender = true;
			}
		}

		sceneObstacles[renderExceptionPos[i]]->PostUpdate();

		if (sceneObstacles[renderExceptionPos[i]]->getPosition().y <= bomberman->position.y) // Pendiente de optimizar
		{
			// Draw Bomberman
			if (!isRender) {
				bomberman->PostUpdate();
				isRender = true;
			}
		}
	}*/

	for (int i = 0; i < 3; i++)	//TEMPORAL
	{
		if (sceneObstacles[renderExceptionPos[i]] != nullptr) 
		{
			sceneObstacles[renderExceptionPos[i]]->PostUpdate();
		}
	}

	if (bomberman != nullptr)
	{
		bomberman->PostUpdate();
	}

	for (int i = 0; i < 3; i++)
	{
		if (Powers[i] != nullptr)
		{
			Powers[i]->PostUpdate();
		}
	}

	// Draw FrontGround
	App->render->DrawTexture(texFG, { 0,20 }, nullptr);

	// Draw UI
	App->render->DrawTexture(texUI, 0, 0, &rectUI);

	//Draw UI text
	//App->scene->text->showText(App->render->renderer, 55, 18, "0 : 00", 30, App->scene->text->getColors((int) textColour::WHITE));  //Timer
	//text->showText(App->render->renderer, 360, 18, "SC\t\t\t\t\t\t\t\t\t\t\t\t\t" + std::to_string(test), text->getFonts(36), text->getColors((int)textColour::WHITE)); //Points
	//text->showText(App->render->renderer, 700, 18, "3", text->getFonts(36), text->getColors((int)textColour::WHITE)); //Lifes

	return true;
}

void SceneLevel1::OnCollision(Collider* c1, Collider* c2)
{

	if (bomberman != nullptr && bomberman->col == c1)
	{
		bomberman->OnCollision(c2);
	}

	for (int i = 0; i < 3; i++)
	{
		if (Powers[i] != nullptr && Powers[i]->getCollider() == c1)
		{
			Powers[i]->OnCollision(c2);
		}
	}


	//Obstacle Collision ----------------------
	for (uint i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		// cuando se choca algo
		if (sceneObstacles[i] != nullptr && sceneObstacles[i]->getCollider() == c1)
		{
			sceneObstacles[i]->OnCollision(c2);
		}
	}



}

void SceneLevel1::WillCollision(Collider* c1, Collider* c2)
{
	if (bomberman != nullptr && bomberman->col == c1)
	{
		bomberman->WillCollision(c2);
	}
}

bool SceneLevel1::CleanUp(bool finalCleanUp)
{
	LOG("Freeing all test");

	// Clean Scene if not close the game
	if (!finalCleanUp) {
		App->audio->CleanUpScene();
		App->collisions->CleanUpScene();
		App->textures->CleanUpScene();
		App->particle->CleanUpScene();
	}

	// Delete obstacles
	for (uint i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (sceneObstacles[i] != nullptr)
		{
			delete sceneObstacles[i];
			sceneObstacles[i] = nullptr;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (Powers[i] != nullptr)
		{
			delete Powers[i];
			Powers[i] = nullptr;
		}
	}

	tileMap.Reset();

	//Delete Vector
	emptySpaces.clear();
	emptySpaces.shrink_to_fit();

	#pragma region Delete Particles
	// Delete particles
	delete explosionCenter;
	explosionCenter = nullptr;
	delete explosionMiddle;
	explosionMiddle = nullptr;
	delete explosionEnd;
	explosionEnd = nullptr;
	delete powerUpDestroyed;
	powerUpDestroyed = nullptr;
	delete redFlowerDestroyed;
	redFlowerDestroyed = nullptr;
	#pragma endregion

	// Delete player
	delete bomberman;
	bomberman = nullptr;

	return true;
}

