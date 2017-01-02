#include "DeadZone.h"
#include "Player.h"
#include "World.h"


DeadZone::DeadZone(LPD3DXSPRITE _SpriteHandler, World *_manager, int _Type) :Zone(_SpriteHandler, _manager)
{
	manager = _manager;
	objectType = ZONE_TYPE;
	typeZone = _Type;
	//	ZONE_DEAD
	//	ZONE_GRINDER
	
	isActive = false;

	// đối với grinder, thêm sprite
}


DeadZone::~DeadZone()
{
}

// đối với grinder
void DeadZone::Update(const float &_DeltaTime)
{
	//if(typeZone == ZONE_GRINDER)
	// thuật toán kéo thả
}

// đối với grinder
void DeadZone::Render()
{
	//if(sprite != NULL)
	// render grinder
}


// virtual function
void DeadZone::Init(int _X, int _Y, int _Width, int _Height,// rect
	int _Stack, int rubbish1,
	int rubbish2, int rubbish3, int rubbish4)
{
	isActive = true;
	// coordinate & collider
	Zone::Init(_X, _Y, _Width, _Height);
	// ----------

	// đối với grinder
	//if
	//iStack = _Stack;
	//status = 0;
}

// player đụng vào => phép màu xảy ra
void DeadZone::Collision(Player *actor, const float &_DeltaTime)
{
	// chết ngay lập tức!
	actor->Destroy();
}