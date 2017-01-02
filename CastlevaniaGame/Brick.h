#ifndef _BRICK_H_
#define _BRICK_H_

#include "ThamSo.h"
#include "Ground.h"

class Brick : public Ground
{
public:
	DropTable *dropTable;
	LPD3DXSPRITE spriteHandler;

	Brick(LPD3DXSPRITE _SpriteHandler, World *_manager, int _Type);
	~Brick();

	virtual void Init(int _X, int _Y, int _ItemType, int rubbish);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
};

#endif
