#ifndef _BONE_H_
#define _BONE_H_

#include "Enemy.h"
#include "EnemyFire.h"

class Bone :
	public Enemy

{
public:

	//bien Ðo thoi gian de  tan cong
	float TimeToAttack;

	//khoang thoi gian can thiet de co the tan cong
	float timer;

	bool isRight;
	Bone();
	Bone(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Bone();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
	virtual void CheckActive();

	virtual void TakeDamage(int damage);
	void ActivateEnemyFire();

};
#endif // !_BONE_H_