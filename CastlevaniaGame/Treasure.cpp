#include "Treasure.h"
#include "World.h"
#include "Game.h"

Treasure::Treasure() {}

Treasure::Treasure(LPD3DXSPRITE _SpriteHandler, World *_manager)
	:Item(_SpriteHandler, _manager)
{
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\hiddenitem.bmp", 32, 32, 49, 6);
}

Treasure :: ~Treasure()
{

}

void Treasure::Init(int _X, int _Y, int _type)
{
	Item::Init(_X, _Y);
	itemType = _type;
	timeUp = 0;
}


void Treasure::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= 6.0f)
		isActive = false;
	timerSprite += _DeltaTime;
	if (timerSprite >= 0.1f)
	{
		GetMultiSprite(itemType);
		timerSprite = 0;
	}

}

void Treasure::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Treasure::Destroy()
{
	isActive = false;
}

void Treasure::Collision(Player *player)
{
	Game::gameSound->playSound(EATMONEY);
	isActive = false;
	switch (itemType)
	{
	case BAG1000:
		player->score += 1000;
		break;
	case TREASURE:
	case CROWN:
		player->score += 2000;
		break;
	}
}