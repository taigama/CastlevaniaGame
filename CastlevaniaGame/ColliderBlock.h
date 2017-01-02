#ifndef _COLLIDERBLOCK_H_
#define _COLLIDERBLOCK_H_

#include "ThamSo.h"
#include "Ground.h"

class ColliderBlock : public Ground
{
public:

	ColliderBlock(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~ColliderBlock();
	// update K_1.7
	virtual void Init(int _X, int _Y, int _Width, int _Heigh);
};

#endif
