#include "MoneyBag.h"
#include "World.h"
#include "Game.h"

MoneyBag::MoneyBag() {}

MoneyBag::MoneyBag(LPD3DXSPRITE _SpriteHandler, World *_manager)
	:Item(_SpriteHandler, _manager)
{
	
}

MoneyBag :: ~MoneyBag()
{
	
}
void MoneyBag::Init(int _X, int _Y)
{
	
}
void MoneyBag::Init(int _X, int _Y, int _type)
{
	Item::Init(_X, _Y);
	itemType = _type;
	GetMultiSprite(itemType);
}


void MoneyBag::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= 3.0f)
		isActive = false;
	
	if (isActive)
	{
		//Khi chạm nền thì dừng lại
		Item::CheckGroundCollision(manager, _DeltaTime);
		postY += velocityY * _DeltaTime;

		timerSprite += _DeltaTime;
		if (timerSprite >= 0.2f)
		{
			GetMultiSprite(itemType);
			timerSprite = 0;
		}
		
	}


}

void MoneyBag::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void MoneyBag::Destroy()
{
	isActive = false;
}

void MoneyBag::Collision(Player *player)
{
	isActive = false;
	switch (itemType)
	{
	case BAG100:
		player->score += 100;
		break;
	case BAG400:
		player->score += 400;
		break;
	case BAG700:
		player->score += 700;
		break;
	}
	Game::gameSound->playSound(EATMONEY);
}