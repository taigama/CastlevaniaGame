#include "Door.h"
#include "World.h"
#include "Player.h"


Door::Door(LPD3DXSPRITE _SpriteHandler, World *_manager):Zone(_SpriteHandler, _manager)
{
	typeZone = ZONE_DOOR;
	spriteHandler = _SpriteHandler;
	isActive = false;
	isTagged = false;
	doorOpened = false;
	doorClocked = false;
}


Door::~Door()
{
}


void Door::Init(int _X, int _Y, int _Width, int _Height,// rect
	int rubbish1, int rubbish2,
	int camXLeft, int camXRight, int direct)
{
	doorOpened = false;
	doorClocked = false;
	isActive = true;
	Zone::Init(_X, _Y, _Width, _Height);

	postX = _X; postY = _Y;
	newLeft = camXLeft;
	newRight = camXRight;
	this->direct = direct;

	switch (direct)
	{
	case -1:
		sprite = new Sprite(spriteHandler, "Resources\\Sprites\\door2_alter.bmp", 48, 96, 3, 3);
		sprite->Next(0, 0);
		break;
	case 1:
		sprite = new Sprite(spriteHandler, "Resources\\Sprites\\door1.bmp", 48, 96, 3, 3);
		sprite->Next(0, 0);
		break;
	default:
		break;
	}

}
void Door::Update(const float &_DeltaTime)
{
	
	if (!isTagged)
		return;
	if (doorOpened)
	{
		timerSprite += _DeltaTime;
		if (timerSprite >= ANIM_TIME * 3)
		{
			if (sprite->_Index == 0)
			{
				manager->Simon->ChangingScene++;
				isTagged = false;
				doorOpened = false;
				doorClocked = true;
				return;
			}
			timerSprite -= ANIM_TIME * 3;
			sprite->Next(0, 2);
		}
		
	}
	else //cua chua mo
	{
		timerSprite += _DeltaTime;
		if (timerSprite >= ANIM_TIME * 3)
		{
			if (sprite->_Index == 2)
			{
				manager->Simon->ChangingScene++;
				isTagged = false;
				doorOpened = true;
				return;
			}
			timerSprite -= ANIM_TIME * 3;
			sprite->Next(0, 2);
		}
	}
	
}

void Door::Render()
{
	sprite->Render(postX, postY);
}

void Door::Collision(Player *actor, const float &_DeltaTime)
{
	manager->Simon->heart++;
}
