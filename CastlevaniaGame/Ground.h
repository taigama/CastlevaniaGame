#ifndef _GROUND_H_
#define _GROUND_H_

#include "GameObject.h"




class Ground :
	public GameObject

{
public:

	int typeGround;
	bool isBreakable;
	//DropTable dropTable;

	Ground();
	Ground(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Ground();
	virtual void Init(int _X, int _Y, int param1, int param2);
	//
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
};
#endif // !_GROUND_H_

