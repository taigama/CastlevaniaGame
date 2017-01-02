#include "GetSubWeapon.h"
#include "World.h"
#include "Game.h"

GetSubWeapon::GetSubWeapon() {}

GetSubWeapon::GetSubWeapon(LPD3DXSPRITE _SpriteHandler, World *_manager)
	:Item(_SpriteHandler,_manager)
{

}

GetSubWeapon :: ~GetSubWeapon()
{
	
}
void GetSubWeapon::Init(int _X, int _Y)
{
	
}
void GetSubWeapon::Init(int _X, int _Y, int _type)
{
	Item::Init(_X, _Y);
	itemType = _type;
	GetMultiSprite(_type);
}


void GetSubWeapon::Update(const float &_DeltaTime)
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

void GetSubWeapon::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void GetSubWeapon::Destroy()
{
	isActive = false;
}

void GetSubWeapon::Collision(Player *player)
{
	isActive = false;
	Game::gameSound->playSound(EATWEAPON_CHICKEN);
	switch (itemType)
	{
	case GETKNIFE:
		player->subWeapon = KNIFE;
		break;
	case GETAXE:
		player->subWeapon = AXE;
		break;
	case GETBOOMERANG:
		player->subWeapon = BOOMERANG;
		break;
	case GETWATER:
		player->subWeapon = HOLYWATER;
		break;
	case GETWATCH:
		player->subWeapon = WATCH;
		break;
	}
	
}


