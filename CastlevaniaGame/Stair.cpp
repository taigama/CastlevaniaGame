#include "Stair.h"

Stair::Stair(LPD3DXSPRITE _SpriteHandler, World *_manager, int _Type)
{
	manager = _manager;
	objectType = STAIR_TYPE;
	isBreakable = false;
	collider = new Collider();
	collider->setCollider(26, -32, -32, 32);
	stairType = _Type;
}

Stair::Stair(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = STAIR_TYPE;
	isBreakable = false;
	collider = new Collider();
	collider->setCollider(26, -32, -32, 32);

}

Stair :: ~Stair()
{

}

void Stair::Init(int _X, int _Y)
{
	postX = _X;
	postY = _Y;
	isActive = true;
}

void Stair::Update(const int &_deltaTime)
{
}

void Stair::Render()
{
	return;
}

void Stair::Destroy()
{

}

void Stair::Collision()
{

}