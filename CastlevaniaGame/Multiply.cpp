#include "Multiply.h"
#include "World.h"
#include "Game.h"

Multiply::Multiply() {}

Multiply::Multiply(LPD3DXSPRITE _SpriteHandler, World *_manager)
	:Item(_SpriteHandler, _manager)
{
	itemType = MULTIPLY;
}

Multiply :: ~Multiply()
{

}

void Multiply::Init(int _X, int _Y)
{
	Item::Init(_X, _Y);
	if (manager->Simon->weaponNumber < 2)
		sprite->Next(11, 11);
	else
		sprite->Next(12, 12);
}


void Multiply::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= 5.0f)
		isActive = false;
	
	if (isActive)
	{
		//Khi chạm nền thì dừng lại
		Item::CheckGroundCollision(manager, _DeltaTime);
		postY += velocityY * _DeltaTime;

		timerSprite += _DeltaTime;
		if (timerSprite >= 0.2f)
		{
			if (manager->Simon->weaponNumber < 2)
				sprite->Next(11, 11);
			else
				sprite->Next(12, 12);
			timerSprite = 0;
		}
		
	}


}

void Multiply::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Multiply::Destroy()
{
	isActive = false;
}

void Multiply::Collision(Player *player)
{
	isActive = false;
	Game::gameSound->playSound(EATWEAPON_CHICKEN);
	if (player->weaponNumber < 3)
		player->weaponNumber++;
}