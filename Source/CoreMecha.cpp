#include "CoreMecha.h"

CoreMecha::CoreMecha()
{

}

CoreMecha::CoreMecha(iPoint pos, SDL_Texture* tex, SDL_Texture* texDie, Particle* destroyed, Tile* tile,int* coreMechaNum): Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::DESTRUCTABLE_WALL, App->scene), tex)
{
	// Flow tienen sprites en diferentes sprite sheet, por eso necesita una textura aparte para guardar la animacion de morir
	this->texDie = texDie;
	this->currentTileMap = tile;
	this->dieParticle = *destroyed;
	this->coreMechaNum = coreMechaNum;

	renderRect = { 0, 0, 16, 26 };

	coreMechaDestroyedSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Miscellaneous_Sounds/G_OrbsDestroyedSound.wav");
}

void CoreMecha::Die()
{
	pendingToDelete = true;
	getCollider()->pendingToDelete = true;

	// Offset dieParticle
	iPoint tempPos = getPosition();
	tempPos -= {5, 11};
	App->particle->AddParticle(dieParticle, tempPos, Type::NONE);

	App->scene->currentScene->score += 800;

	int tileX, tileY;
	tileX = currentTileMap->getTilePos(getPosition()).x;
	tileY = currentTileMap->getTilePos(getPosition()).y;
	currentTileMap->Level1TileMap[tileY - 1][tileX] = 0;

	(*coreMechaNum)--;
}

void CoreMecha::PostUpdate()
{
	iPoint temp = getPosition();
	temp.y -= 10;

	//App->render->DrawTexture(texture, temp, &renderRect);
	App->render->AddTextureRenderQueue(texture, temp, &renderRect, 1, getPosition().y);
}

void CoreMecha::OnCollision(Collider* col)
{
	if (col->type == Type::EXPLOSION)
	{
		App->audio->PlaySound(coreMechaDestroyedSFX, 0);
		Die();
	}
}
