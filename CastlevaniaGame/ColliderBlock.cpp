#include "ColliderBlock.h"

ColliderBlock::ColliderBlock(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	Ground::Ground(_SpriteHandler, _manager);
	objectType = GROUND_TYPE;
	typeGround = GROUND_BLOCK;

	////
	isBreakable = false;

	collider = new Collider();
}

ColliderBlock::~ColliderBlock() {};

void ColliderBlock::Init(int _X, int _Y, int _Width, int _Heigh)
{
	////
	isActive = true;
	postX = _X;
	postY = _Y;
	
	collider->top = (_Heigh / 2);
	collider->bottom = -(collider->top);

	collider->right = (_Width / 2);
	collider->left = -(collider->right);
}