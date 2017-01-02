#include "StandItem.h"
#include "Player.h"
#include "Item.h"
#include "World.h"
#include "Game.h"

StandItem::StandItem(LPD3DXSPRITE _SpriteHandler, World *_manager) :Zone(_SpriteHandler, _manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	objectType = ZONE_TYPE;
	typeZone = ZONE_STAND;
	itemType = 0;
	timeRequired = 0.0f;
	timePending = 0.0f;
	needCrouch = false;
}


StandItem::~StandItem()
{
}

void StandItem::Render()
{
}


// virtual function
void StandItem::Init(int _X, int _Y, int _Width, int _Height,// rect
	int _triggerX, int _triggerY,	// show item chỗ này
	int _itemType, int _time, int _needCrouch)	// item rớt & điều kiện
{
	isActive = true;
	// coordinate & collider
	Zone::Init(_X, _Y, _Width, _Height);
	// ----------

	triggerX = _triggerX;
	triggerY = _triggerY;

	itemType = _itemType;
	timeRequired = (float)(_time); // thời gian tính = giây

	if (_needCrouch)
	{
		needCrouch = true;
	}
}

// player đụng vào => phép màu xảy ra
void StandItem::Collision(Player *actor, const float &_DeltaTime)
{
	if (!needCrouch)
	{
		timePending += _DeltaTime;
		// thời gian đạt yêu cầu -> quăng ra item
		if (timePending > timeRequired)
		{
			this->isActive = false;

			Item* newItem = Item::CreateItem(itemType, triggerX, triggerY, spriteHandler, manager);
			manager->groupItem->AddObject(newItem);
			Game::gameSound->playSound(SHOWSECRETITEM);
		}
	}
	else
	{
		if (actor->isCrouch)
		{
			this->isActive = false;

			Item* newItem = Item::CreateItem(itemType, triggerX, triggerY, spriteHandler, manager);
			manager->groupItem->AddObject(newItem);
			Game::gameSound->playSound(SHOWSECRETITEM);
		}
	}
}