#include "Potion.h"
#include "World.h"
#include "Game.h"

Potion::Potion() {}

Potion::Potion(LPD3DXSPRITE _SpriteHandler, World *_manager)
	:Item(_SpriteHandler, _manager)
{
	itemType = POTION;
}

Potion :: ~Potion()
{

}

void Potion::Init(int _X, int _Y)
{
	Item::Init(_X, _Y);
	sprite->Next(6, 6);
}


void Potion::Update(const float &_DeltaTime)
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
			sprite->Next(6, 6);
			timerSprite = 0;
		}
		
	}


}

void Potion::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Potion::Destroy()
{
	isActive = false;
}

void Potion::Collision(Player *player)
{
	isActive = false;
	Game::gameSound->playSound(POTIONIMMORTAL);
	player->timeImmortal = -4;
	player->isImmortal = true;
	player->atePotion = true;
}