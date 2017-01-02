#include "BigHeart.h"
#include "World.h"
#include "Game.h"
BigHeart::BigHeart() {}

BigHeart::BigHeart(LPD3DXSPRITE _SpriteHandler, World *_manager)
	:Item(_SpriteHandler, _manager)
{
	itemType = BIGHEART;
}

BigHeart :: ~BigHeart()
{
	
}

void BigHeart::Init(int _X, int _Y)
{
	Item::Init(_X, _Y);
	sprite->Next(9, 9);
}


void BigHeart::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= 3.0f)
		Destroy();
	
	if (isActive)
	{
		//Khi chạm nền thì dừng lại
		Item::CheckGroundCollision(manager, _DeltaTime);

		postY += velocityY * _DeltaTime;
		timerSprite += _DeltaTime;
		if (timerSprite >= 0.2f)
		{
			sprite->Next(9, 9);
			timerSprite = 0;
		}
		
			
	}
	
		
}

void BigHeart::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void BigHeart::Destroy()
{
	isActive = false;
}

void BigHeart::Collision(Player *player)
{
	player->heart += 5;
	Game::gameSound->playSound(EATHEART);
	Destroy();
}