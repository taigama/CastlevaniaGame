#include "Heart.h"
#include "World.h"
#include "GroupObject.h"
#include "Game.h"

Heart::Heart() {}

Heart::Heart(LPD3DXSPRITE _SpriteHandler, World *_manager)
	:Item(_SpriteHandler, _manager)
{
	itemType = HEART;
	velocityX = -20;
	velocityY = -50;
}

Heart :: ~Heart()
{

}

void Heart::Init(int _X, int _Y)
{
	Item::Init(_X, _Y);
	a = 10;
	sprite->Next(8, 8);
	Stop = false;
}


void Heart::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= 10.0f)
		Destroy();
	
	a++;
	//Khi chạm nền thì dừng lại
	Item::CheckGroundCollision(manager, _DeltaTime);
	if (Stop)
		return;
	postX += velocityX * _DeltaTime;
	postY += velocityY * _DeltaTime;
	timerSprite += _DeltaTime;

	if (timerSprite >= 0.2f)
	{
		velocityX = sin(a) * 40;
		sprite->Next(8, 8);
		timerSprite = 0;
	}
	
}

void Heart::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
	
}

void Heart::Destroy()
{
	isActive = false;
	
}

void Heart::Collision(Player *player)
{
	isActive = false;
	player->heart++;
	Game::gameSound->playSound(EATHEART);
}
