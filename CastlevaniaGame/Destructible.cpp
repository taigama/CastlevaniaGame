#include "Destructible.h"
#include "Misc.h"
#include "World.h"
#include "Item.h"
#include "GroupObject.h"
#include "Game.h"

Destructible::Destructible() {}

Destructible::Destructible(LPD3DXSPRITE _SpriteHandler, World *_Manager, int _Type)
{
	// init 1 số biến cố định
	manager = _Manager;
	// dùng cấp cho item
	spriteHandler = _SpriteHandler;
	objectType = DESTRUCTIBLE_TYPE;
	destructibleType = _Type;

	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\destructible.bmp", 64, 64, 8, 6);
	timerSprite = 0.0f;

	collider = new Collider();

	// cụ thể theo từng loại
	switch (destructibleType)
	{
		// torch
	case DESTRUCTIBLE_TORCH:
		// vị trí để render trong cục sprite
		renderOffset = 2;
		sprite->Next(2, 2);

		// chỉnh collider
		collider->setCollider(32, -32, -18, 18);
		break;

		// candle
	case DESTRUCTIBLE_CANDLE:
		// vị trí để render trong cục sprite
		renderOffset = 0;
		sprite->Next(0, 0);

		// chỉnh collider
		collider->setCollider(15, -15, -10, 10);
		break;
	default:
		break;
	}


	dropTable = new DropTable;
}

Destructible :: ~Destructible()
{

}

void Destructible::Init(int _X, int _Y)
{
	Init(_X, _Y, 0);
}

void Destructible::Init(int _X, int _Y, int _ItemType)
{
	postX = _X;
	postY = _Y;
	isActive = true;

	dropTable->AddItem(_ItemType, 100);
}

void Destructible::Update(const float &_DeltaTime)
{
	timerSprite += _DeltaTime;
	if (timerSprite >= ANIM_TIME)
	{
		timerSprite -= ANIM_TIME;
		sprite->Next(renderOffset, renderOffset + 1);
	}
}

void Destructible::Render()
{
	sprite->Render(postX, postY);
}

void Destructible::Destroy()
{
	this->isActive = false;
	Game::gameSound->playSound(HITSOFT);

	// làm hiệu ứng cháy
	Effect* newEffect = Effect::CreateEffect(3, this->postX, this->postY, 1, spriteHandler, manager);
	manager->groupEffect->AddObject(newEffect);


	int randomX = RandomOutside(8, 12);
	int randomY = RandomOutside(8, 12);

	Effect* hitEffect = Effect::CreateEffect(EFFECT_HIT, this->postX + randomX, this->postY + randomY, 1, spriteHandler, manager);
	manager->groupEffect->AddObject(hitEffect);

	int itemType = dropTable->DropItem();
	// nếu item = tim nhỏ, xem coi whip lvl của simon đã đủ chưa
	//, chưa đủ thì cho khả năng ngẫu nhiên rớt whip upgrade
	if ((itemType == 1) && (manager->whip->whipLevel < 2))
	{
		// mức ngẫu nhiên này là 50/50
		if ((rand() % 2) == 1)
			itemType = WHIPUPGRADE;
	}

	// tạo item mới theo con số & add vào world
	Item* newItem = Item::CreateItem(itemType, this->postX, this->postY, spriteHandler, manager);
	manager->groupItem->AddObject(newItem);

}

void Destructible::Collision()
{

}