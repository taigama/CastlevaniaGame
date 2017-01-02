#include "Brick.h"
#include "Misc.h"
#include "World.h"
#include "Item.h"
#include "Effect.h"
#include "Game.h"

Brick::Brick(LPD3DXSPRITE _SpriteHandler, World *_manager, int _Type)
{
	Ground::Ground(_SpriteHandler, _manager);
	// ko hiểu sao bị NULL chỗ này
	manager = _manager;
	// dùng để cấp sprite handler cho item
	spriteHandler = _SpriteHandler;
	objectType = GROUND_TYPE;
	typeGround = _Type;

	// sẵn sàng rớt item
	dropTable = new DropTable;

	// sẵn sàng render
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\destructible.bmp", 64, 64, 8, 6);
	switch (_Type)
	{
	case GROUND_BRICK1:
		sprite->_Index = 4;
		break;
	case GROUND_BRICK2:
		sprite->_Index = 5;
		break;
	case GROUND_BRICK3:
		sprite->_Index = 6;
		break;
	case GROUND_BRICK4:
		sprite->_Index = 7;
		break;
	default:
		sprite->_Index = 8; // không có gì cả
		break;
	}

	// set giá trị collider
	collider = new Collider();
	collider->top = 16;
	collider->bottom = -16;

	collider->right = 16;
	collider->left = -16;
}

Brick::~Brick() {};

void Brick::Init(int _X, int _Y, int _ItemType, int rubbish)
{
	// không cần quan tâm tới rubbish làm gì
	//chẳng qua init của mấy cái ground cần 4 parameter thôi

	isActive = true;
	isBreakable = true;
	postX = _X;
	postY = _Y;

	dropTable->AddItem(_ItemType, 100);
}

void Brick::Render()
{
	sprite->Render(postX, postY);
}

// gọi đến hàm này khi whip đánh trúng
void Brick::Collision()
{

}

void Brick::Destroy()
{
	// làm cho đối tượng này biến mất
	this->isActive = false;

	// làm hiệu ứng bể
	Effect* newEffect = Effect::CreateEffect(2, this->postX, this->postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(newEffect);
	newEffect = Effect::CreateEffect(2, this->postX, this->postY, -2, spriteHandler, manager);
	manager->groupEffect->AddObject(newEffect);
	newEffect = Effect::CreateEffect(2, this->postX, this->postY, 1, spriteHandler, manager);
	manager->groupEffect->AddObject(newEffect);

	// làm rớt item
	int a = dropTable->DropItem();
	Item* theItem = Item::CreateItem(a, this->postX, this->postY + 2, spriteHandler, manager);
	// thêm item vào world
	manager->groupItem->AddObject(theItem);

	// âm thanh
	Game::gameSound->playSound(BRICKBREAK);
}