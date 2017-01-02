#include "Grinder.h"
#include "Player.h"
#include "World.h"

Grinder::Grinder(LPD3DXSPRITE _SpriteHandler, World *_manager) :Zone(_SpriteHandler,_manager)
{ 
	manager = _manager;
	typeZone = ZONE_GRINDER;
	sizeHeight = 16;
	sizeWidth = 64;
	collider = new Collider();
	collider->setCollider(5, -5, -29, 29);
	isActive = false;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\grinder.bmp", sizeWidth, sizeHeight, 1, 1);
	sprite->_Index = 0;
	sizeHeight = 16;
	sizeWidth = 16;
	spriteTop = new Sprite(_SpriteHandler, "Resources\\Sprites\\grinder_top.bmp", sizeWidth, sizeHeight, 1, 1);
	spriteTop->_Index = 0;
	pos = 300;
	isLifting = false;
	numberCount = 1;
}

Grinder :: ~Grinder()
{

}


void Grinder::Init(int _X, int _Y, int _Width, int _Height,// rect
	int _triggerX, int _triggerY,	// trigger tại vị trí này
	int param7, int param8, int _maxCount)
{
	isActive = true;
	postX = _X;
	anchorY = _Y;
	maxCount = 7;
	isLifting = false;
	numberCount = 1;
	maxCount = _maxCount;

	//postY = diem treo - chieu dai top*so luong top - 1/2 chieu dai grinder
	postY = anchorY - sizeHeight* numberCount - sizeHeight / 2;
}

void Grinder::Update(const float &_deltaTime)
{
	timerSprite += _deltaTime;
	if (isLifting)
	{
		if (timerSprite >= ANIM_TIME*3)
		{
			timerSprite -= ANIM_TIME*3;
			numberCount--;
			if (numberCount < 1)
			{
				isLifting = false;
				numberCount++;
			}

		}
	}
	else
	{
		if (timerSprite >= ANIM_TIME/2.0)
		{
			timerSprite -= ANIM_TIME/2.0;
			numberCount++;
			if (numberCount > maxCount)
			{
				isLifting = true;
				numberCount--;
			}

		}
	}
	postY = anchorY - sizeHeight* numberCount - sizeHeight / 2;
	
}

void Grinder::Render()
{
	if (!isActive)
		return;
	for (int i = 0; i < numberCount; i++)
		spriteTop->Render(postX, anchorY- sizeHeight*i - sizeHeight);
	sprite->Render(postX, postY);
	
}

void Grinder::Collision(Player *actor, const float &_DeltaTime)
{
	if (actor->isImmortal)
		return;

	actor->Destroy();
}
