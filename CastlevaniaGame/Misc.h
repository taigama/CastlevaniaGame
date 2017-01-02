#ifndef _MISC_H_
#define _MISC_H_

#include "ThamSo.h"

// --- update K_1.2

// ======== DROP ITEM TABLE =========
struct DropLine
{
	int itemType;
	int percent;
};

class DropTable
{
	int numberItem;
	int luckyInt;
	DropLine dropLine[5];

	// ---- update K_1.7
public:
	int DropItem();
	void AddItem(int itemType, int percent);

	DropTable();
	~DropTable();
};


// ========= COLLIDER ===========
class Collider
{
public:
	// các biến
		// trục Y hướng lên
	float top;	// luôn > 0
	float bottom;	// luôn < 0
		
		// trục X hướng qua phải
	float left;	// luôn < 0
	float right;	// luôn > 0

	GameObject *owner;

	//Khởi tạo và huỷ
	Collider();
	Collider(int objectType);
	
	~Collider();

	void setCollider(int _top, int _bottom, int _left, int _right);
};

#endif // !_MISC_H_
