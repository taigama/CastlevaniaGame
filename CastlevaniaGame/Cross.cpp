#include "Cross.h"
#include "World.h"
#include "Game.h"

Cross::Cross() {}

Cross::Cross(LPD3DXSPRITE _SpriteHandler, World *_manager)
	:Item(_SpriteHandler, _manager)
{
	itemType = CROSS;
}

Cross :: ~Cross()
{

}

void Cross::Init(int _X, int _Y)
{
	Item::Init(_X, _Y);
	sprite->Next(5, 5);
}


void Cross::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= 6.0f)
		isActive = false;
	if (isActive)
	{
		//Khi chạm nền thì dừng lại
		Item::CheckGroundCollision(manager, _DeltaTime);
		postY += velocityY * _DeltaTime;

		timerSprite += _DeltaTime;
		if (timerSprite >= 0.2f)
		{
			sprite->Next(5, 5);
			timerSprite = 0;
		}
		
	}

}

void Cross::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Cross::Destroy()
{
	isActive = false;
}

void Cross::Collision(Player *player)
{
	isActive = false;
	manager->isFlash = true;
	
	Game::gameSound->playSound(EATCROSS);
	//tieu diet tat ca enemy trong viewport, tru boss
	for (int i = 0; i < manager->groupEnemy->number; i++)
	{
		GameObject* temp = manager->groupEnemy->objects[i];
		if (temp->postX >= Sprite::cameraX && temp->postX <= Sprite::cameraX + 512 &&
			temp->postY >= Sprite::cameraY - 448 && temp->postY <= Sprite::cameraY &&
			temp->objectType != MEDUSA && temp->objectType != VAMBAT)
			temp->Destroy();
	}
}