#include "Crystal.h"
#include "World.h"
#include "MainGame.h"
Crystal::Crystal() {}

Crystal::Crystal(LPD3DXSPRITE _SpriteHandler, World *_manager)
	:Item(_SpriteHandler, _manager)
{
	itemType = CRYSTAL;
}

Crystal :: ~Crystal()
{

}

void Crystal::Init(int _X, int _Y)
{
	Item::Init(_X, _Y);
	sprite->Next(16, 17);
}


void Crystal::Update(const float &_DeltaTime)
{
	
	if (isActive)
	{
		//Khi chạm nền thì dừng lại
		Item::CheckGroundCollision(manager, _DeltaTime);
		postY += velocityY * _DeltaTime;
		timerSprite += _DeltaTime;
		if (timerSprite >= 0.1f)
		{
			sprite->Next(16, 17);
			timerSprite = 0;
		}
		
	}
}

void Crystal::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Crystal::Destroy()
{
	isActive = false;
}

void Crystal::Collision(Player *player)
{
	isActive = false;
	//xu ly qua man
	player->score += player->heart;
	player->health = 16;
	player->heart = 5;
	Game::gameSound->playSound(EATCRYSTAL);
	manager->castlevania->NextIntro();
}

