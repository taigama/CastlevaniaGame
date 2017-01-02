// ------ update K_1.5

#include "GateWay.h"
#include "Player.h"
#include "Sprite.h"


GateWay::GateWay(LPD3DXSPRITE _SpriteHandler, World *_manager) :Zone(_SpriteHandler, _manager)
{
	//manager = _manager;
	objectType = ZONE_TYPE;
	typeZone = ZONE_GATEWAY;
	collider = new Collider();

	sizeWidth = 64;
	sizeHeight = 64;
	//sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\blank.bmp", sizeWidth, sizeHeight, 1, 1);
}


GateWay::~GateWay()
{
}

void GateWay::Render()
{
	// dùng để test
	//sprite->Render(postX, postY);
}


// ------- update K_1.5
// virtual function
void GateWay::Init(int _X, int _Y, int _Width, int _Height,// rect
	int _triggerX, int _triggerY,	// đem player đi xa
	int _camXLeft, int _camXRight, int _camY)	// chuyển camera
{

	isActive = true;
	// convert form topleft coordinate to center coordinate
	Zone::Init(_X, _Y, _Width, _Height);
	// ----------

	triggerX = _triggerX;
	triggerY = _triggerY;
	camXLeft = _camXLeft;
	camXRight = _camXRight;
	camY = _camY;
}

// player đụng vào => phép màu xảy ra
void GateWay::Collision(Player *actor, const float &_DeltaTime)
{
	if (actor->onStair <= 0)
		return;

	actor->postX = triggerX;
	//actor->checkpointX = triggerX;
	actor->postY = triggerY;
	//actor->checkpointY = triggerY;

	//actor->savedOnStair = actor->onStair;
	//actor->savedIsClimbing = actor->isClimbing;
	//actor->savedStairType = actor->stairType;

	Sprite::cameraXLeft = camXLeft;
	Sprite::cameraXRight = camXRight;
	Sprite::cameraY = camY;
}