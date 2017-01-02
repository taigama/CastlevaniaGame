#include "Item.h"
#include "World.h"
Item::Item() {}

Item::Item(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ITEM_TYPE;
	sizeWidth = 64;
	sizeHeight = 64;
	collider = new Collider();
	velocityY = -200;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", sizeWidth, sizeHeight, 22, 6);
}

Item :: ~Item()
{

}

void Item::Init(int _X, int _Y)
{
	isActive = true;
	timeSurvive = 0;
	postX = _X;
	postY = _Y;
	collider->setCollider(14, -14, -14, 14);
}

void Item::Init(int _X, int _Y, int _level)
{
	postX = _X;
	postY = _Y;
}


void Item::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= ITEM_TIME)
		isActive = false;
}

void Item::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Item::Destroy()
{
	isActive = false;
}

void Item::Collision(Player *player)
{
	isActive = false;

}

void Item::CheckGroundCollision(World * manager, const float _DeltaTime)
{
	float collisionScale = 0;
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		GameObject* tempObject = manager->groupQuadtreeCollision->objects[i];
		if (tempObject->objectType==GROUND_TYPE)
		{
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f )
			{
				if (normaly > 0.1f)
				{
					velocityY = 0;
					velocityX = 0;
					Stop = true;
				}
				SlideFromGround(tempObject, _DeltaTime, collisionScale);
			}
		}
	}
	
}

Item * Item::CreateItem(int itemType, int _X, int _Y, LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	Item* item = new Item();
	switch (itemType)
	{
	case HEART:
		item = new Heart(_SpriteHandler, _manager);
		item->Init(_X, _Y);
		break;
	case BIGHEART:
		item = new BigHeart(_SpriteHandler, _manager);
		item->Init(_X, _Y);
		break;
	case BAG100:
		item = new MoneyBag(_SpriteHandler, _manager);
		item->Init(_X, _Y, BAG100);
		break;
	case BAG400:
		item = new MoneyBag(_SpriteHandler, _manager);
		item->Init(_X, _Y, BAG400);
		break;
	case BAG700:
		item = new MoneyBag(_SpriteHandler, _manager);
		item->Init(_X, _Y, BAG700);
		break;
	case BAG1000:
		item = new Treasure(_SpriteHandler, _manager);
		item->Init(_X, _Y, BAG1000);
		break;
	case WHIPUPGRADE:
		item = new WhipUpgrade(_SpriteHandler, _manager);
		item->Init(_X, _Y);
		break;
	case GETKNIFE:
		item = new GetSubWeapon(_SpriteHandler, _manager);
		item->Init(_X, _Y, GETKNIFE);
		break;
	case GETAXE:
		item = new GetSubWeapon(_SpriteHandler, _manager);
		item->Init(_X, _Y, GETAXE);
		break;
	case GETWATER:
		item = new GetSubWeapon(_SpriteHandler, _manager);
		item->Init(_X, _Y, GETWATER);
		break;
	case GETWATCH:
		item = new GetSubWeapon(_SpriteHandler, _manager);
		item->Init(_X, _Y, GETWATCH);
		break;
	case GETBOOMERANG:
		item = new GetSubWeapon(_SpriteHandler, _manager);
		item->Init(_X, _Y, GETBOOMERANG);
		break;
	case CROSS:
		item = new Cross(_SpriteHandler, _manager);
		item->Init(_X, _Y);
		break;
	case POTION:
		item = new Potion(_SpriteHandler, _manager);
		item->Init(_X, _Y);
		break;
	case CHICKEN:
		item = new Chicken(_SpriteHandler, _manager);
		item->Init(_X, _Y);
		break;
	case MULTIPLY:
		item = new Multiply(_SpriteHandler, _manager);
		item->Init(_X, _Y);
		break;
	case TREASURE:
		item = new Treasure(_SpriteHandler, _manager);
		item->Init(_X, _Y, TREASURE);
		break;
	case CROWN:
		item = new Treasure(_SpriteHandler, _manager);
		item->Init(_X, _Y, CROWN);
		break;
	case CRYSTAL:
		item = new Crystal(_SpriteHandler, _manager);
		item->Init(_X, _Y);
		break;
	}
	return item;
}

void Item::GetMultiSprite(int itemType)
{
	timeUp += 0.1f;
	switch (itemType)
	{
		//-------SubWeapon-------
	case GETKNIFE:
		sprite->Next(0, 0);
		break;
	case GETAXE:
		sprite->Next(1, 1);
		break;
	case GETBOOMERANG:
		sprite->Next(2, 2);
		break;
	case GETWATER:
		sprite->Next(3, 3);
		break;
	case GETWATCH:
		sprite->Next(4, 4);
		break;
		//---------Money Bag
	case BAG100:
		sprite->Next(13, 13);
		break;
	case BAG400:
		sprite->Next(14, 14);
		break;
	case BAG700:
		sprite->Next(15, 15);
		break;
		//-------Big Money& Treasure
	case BAG1000:
		//itemType = BAG1000;
		//timeUp += 0.1f;
		if (timeUp >= 1.5f)
			sprite->Next(15, 17);
		else
			sprite->Next(0, 14);
		break;
	case TREASURE:
		//itemType = TREASURE;
		//timeUp += 0.1f;
		if (timeUp >= 1.1f)
			sprite->Next(47, 48);
		else
			sprite->Next(36, 46);
		break;
	case CROWN:
		//itemType = CROWN;
		//timeUp += 0.1f;
		if (timeUp >= 1.5f)
			sprite->Next(34, 35);
		else
			sprite->Next(18, 33);
		break;
	}
}
