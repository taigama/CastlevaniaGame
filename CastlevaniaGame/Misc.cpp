#include "Misc.h"

// --- update K_1.3

// ======= DROP ITEM TABLE =============
DropTable::DropTable()
{
	numberItem = 0;
	luckyInt = 0;
}

DropTable::~DropTable() {}

// ----------------- update K_1.3
// hàm trả về loại item sẽ rơi ra
int DropTable::DropItem()
{
	/*if (numberItem)
	{
		luckyInt = rand() % numberItem;
		if (dropLine[this->luckyInt].percent > rand() % 100)
			return dropLine[luckyInt].itemType;
	}*/

	luckyInt = rand() % 100;

	for (int i = 0; i < numberItem; i++)
	{
		if (luckyInt <= (dropLine[i].percent))
		{
			return dropLine[i].itemType;
		}
		luckyInt -= (dropLine[i].percent);
	}
	return 0;
}
// rồi tạo item theo loại item

void DropTable::AddItem(int itemType, int percent)
{
	// nếu như có nhiều item quá rồi thì không nhận thêm nữa
	if (numberItem >= 5)
		return;

	dropLine[numberItem].itemType = itemType;
	dropLine[numberItem].percent = percent;
	numberItem++;
}







// ---------------------


// ============ COLLIDER ============


Collider::Collider()
{
	top = 0;
	bottom = 0;
	left = 0;
	right = 0;

	owner = NULL;
}

Collider::Collider(int objectType)
{
	switch (objectType)
	{
	case 1:
		top = 24;
		left = -14;
		right = 14;
		bottom = -32;
		break;
	case 5:
		top = 24;
		bottom = -32;
		left = -17;
		right = 17;
	}

}

void Collider::setCollider(int _top, int _bottom, int _left, int _right)
{
	top = _top;
	bottom = _bottom;
	left = _left;
	right = _right;
}

// có 1 con trỏ đến owner (GameObject)
Collider::~Collider() {}
// mà GameObject có sẵn Destructor rồi