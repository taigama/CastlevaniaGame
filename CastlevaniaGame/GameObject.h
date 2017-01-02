//======= GAMEOBJECT ========
// cho kế thừa muôn nơi
// --------- update K_1.3

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <d3dx9.h>
#include "Sprite.h"
#include "Misc.h"

#include <cstdlib>
#include <ctime>

//#include <math.h>

#define PLAYER_TYPE 1
#define PROJECTILE_TYPE 2
#define EFFECT_TYPE 3
#define ITEM_TYPE 4
#define ENEMY_TYPE 5
#define DESTRUCTIBLE_TYPE 6
#define GROUND_TYPE 7
#define STAIR_TYPE 8
#define ZONE_TYPE 9

#define ANIM_TIME 0.15f
#define ITEM_TIME 2.0f
#define IMMORTAL_TIME 3.0f

#define PI 3.141592f
#define val PI/180


class GameObject
{
public:
	// các biến
	World *manager;
	LPD3DXSPRITE spriteHandler;
	bool isActive;
	int objectType;

	int sizeWidth;
	int sizeHeight;
		
	//LPD3DXSPRITE spriteHandler;
	Sprite *sprite;
	float timerSprite;

	Collider *collider;

	float postX;
	float postY;
	float velocityX;
	float velocityY;

	// ------ bo sung K_1.3 --- xét va chạm
	float normalx;	// "vector pháp tuyến" said thầy Dũng
	float normaly;

	
	Collider *BroadPhaseBox;
	float collisionTimeScale;
	// ----- đây là game đơn luồng => các hàm chạy tuần tự
	// ----------------------- => xài chung 1 biến là được rồi.

	// constructor và destructor
	GameObject();
	virtual ~GameObject();

	// ====== CÁC HÀM CHÍNH ======
	// ------ bo sung K_1.3
	// vị trí collistion (= vector0 nếu ko chạm)
	D3DXVECTOR3 VecCollide(GameObject *target); // hàm này có thể không dùng tới
	// xét coi có va chạm ko
	bool IsCollide(GameObject* target);
	bool IsInside(GameObject* target);
	//ham kiem tra doi tuong co nam trong camera hay khong
	bool IsInCamera();

	float SweptAABB(GameObject *target, const float &_DeltaTime);

	//void CollisionWorld(World *manager, const float &_DeltaTime);		// các hàm chia để trị
	//void CollisionGroup(GroupObject *theGroup, const float &_DeltaTime);
	//void CollisionTreeNode(TreeNode *treeNode, const float &_DeltaTime);

	// -------- bo sung K_1.3
	void ResponseFrom(GameObject *target, const float &_DeltaTime, const float &_CollisionTimeScale);
	void DeflectFrom(GameObject *target, const float &_DeltaTime, const float &_CollisionTimeScale);
	void PushFrom(GameObject *target, const float &_DeltaTime, const float &_CollisionTimeScale) {};
	void SlideFromGround(GameObject *target, const float &_DeltaTime, const float &_CollisionTimeScale);
	
	// ----------------

	// ====== các phương thức ảo =====
	virtual void Init(int _X, int _Y);		// reset object
	virtual void Update(const float &_DeltaTime);	// update per frame
	virtual void Render();							// render per frame
	virtual void Destroy();					// clear sub object, without delete this

	virtual void Collision();

	// bo sung K_1.1

	virtual void CollisionObject(GameObject *target, const float &_DeltaTime);	// xét có va chạm không, nếu có thì xử lý

	
	int RandomOutside(int radiusSmall, int radiusBig);
	
};



#endif