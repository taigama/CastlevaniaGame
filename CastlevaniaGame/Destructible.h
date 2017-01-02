#ifndef _DESTRUCTIBLE_H_
#define _DESTRUCTIBLE_H_

#include "ThamSo.h"
#include "GameObject.h"

class Destructible :
	public GameObject

{
public:
	DropTable* dropTable;

	int destructibleType;
	int renderOffset;


	Destructible();
	Destructible(LPD3DXSPRITE _SpriteHandler, World *_Manager, int _Type);
	~Destructible();

	virtual void Init(int _X, int _Y);
	virtual void Init(int _X, int _Y, int _ItemType);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
};
#endif // !_Destructible_H_

