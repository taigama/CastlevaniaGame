#include "Zone.h"

Zone::Zone(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ZONE_TYPE;
	typeZone = 0;	// for sub class
	collider = new Collider();
}

Zone :: ~Zone()
{

}

// ----- update K_1.9
void Zone::Init(int _X, int _Y, int _Width, int _Height)
{
	postX = _X;
	postY = _Y;

	collider->top = _Height / 2;
	collider->bottom = -collider->top;
	collider->right = _Width / 2;
	collider->left = -collider->right;
}

void Zone::Init(int _X, int _Y, int _Width, int _Height,// rect
	int _triggerX, int _triggerY,	// trigger tại vị trí này
	int param7, int param8, int param9) {}
// --------------

void Zone::Update(const float &_DeltaTime)
{
	// không có gì để update cả
}

void Zone::Render()
{
	// chẳng có gì để update luôn
}

void Zone::Destroy()
{

}

void Zone::Collision(Player *actor, const float &_DeltaTime)
{
	// virtual
}