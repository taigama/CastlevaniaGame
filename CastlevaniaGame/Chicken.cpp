#include "Chicken.h"
#include "World.h"
#include "Game.h"

Chicken::Chicken() {}

Chicken::Chicken(LPD3DXSPRITE _SpriteHandler, World *_manager)
	:Item(_SpriteHandler, _manager)
{
	itemType = CHICKEN;
}

Chicken :: ~Chicken()
{

}

void Chicken::Init(int _X, int _Y)
{
	Item::Init(_X, _Y);
	sprite->Next(10, 10);
}


void Chicken::Update(const float &_DeltaTime)
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
			sprite->Next(10, 10);
			timerSprite = 0;
		}
		
	}
}

void Chicken::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Chicken::Destroy()
{
	isActive = false;
}

void Chicken::Collision(Player *player)
{
	isActive = false;
	Game::gameSound->playSound(EATWEAPON_CHICKEN);
	if (player->health < 16)
		player->health = 16;
}

