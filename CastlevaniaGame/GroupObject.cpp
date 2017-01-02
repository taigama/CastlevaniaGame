// ------- update K_1.5

#include "GroupObject.h"
#include "OQuadTree.h"
#include "GameObject.h"
#include "World.h"

// init just set manager
GroupObject::GroupObject(World *manager)
{
	this->manager = manager;
	number = 0;
}

// clear: clear all pointers, no need to clear further
GroupObject::~GroupObject() {}

void GroupObject::AddObject(GameObject* theObject)
{
	// xem coi có đối tượng như vầy trong mảng chưa
	for (int i = 0; i < number; i++)
	{
		if (objects[i] == theObject)
			return;
	}	// hàm này không hay chút nào, sử dụng vector cũng vì lười

	this->objects.push_back(theObject);
	number++;
}

// lấy object từ group khác
void GroupObject::GetObjectFrom(GroupObject* theGroup)
{
	int theGroupNumber = theGroup->number;
	for (int i = 0; i < theGroupNumber; i++)
	{
		if (theGroup->objects[i]->isActive == true)	// phải đang active mới lấy
			this->AddObject(theGroup->objects[i]);
	}// làm kiểu này cũng không hay
	 // đúng ra phải tạo thêm hàm throw object at (i), nhưng không thích làm nhiều công đoạn
}

void GroupObject::Update(const float &_DeltaTime)
{
	for (int i = 0; i < number; i++)
	{
		objects[i]->Update(_DeltaTime); // gọi hàm virtual
	}
}

// giống update ở trên nhưng xét active mới được update
void GroupObject::UpdateActive(const float &_DeltaTime)
{
	for (int i = 0; i < number; i++)
	{
		if(objects[i]->isActive)
			objects[i]->Update(_DeltaTime); // gọi hàm virtual
	}
}

void GroupObject::Render()
{
	for (int i = 0; i < number; i++)
	{	
		// không có cái if này là tèo
		if (objects[i]->sprite != NULL)
			objects[i]->Render();	// gọi hàm virtual
	}
}

// giống render ở trên nhưng xét active mới được update
void GroupObject::RenderActive()
{
	for (int i = 0; i < number; i++)
	{
		// kiểm tra object
		if (objects[i]->isActive)
			if (objects[i]->sprite != NULL)
				objects[i]->Render();	// gọi hàm virtual
	}
}
// ------

void GroupObject::Clear()
{
	this->objects.clear();
	number = 0;
}


// --- lấy danh sách đối tượng special có thể va chạm
// --- Dùng world chạy hàm này, chỉ dành cho CollisionGroup
void GroupObject::GetCollisionSpecial()
{		// tên đầy đủ của hàm này phải là: Re-get Special "active-Object with Collision"

	this->objects.clear();
	number = 0;
	GetObjectFrom(manager->groupItem);
	GetObjectFrom(manager->groupEnemy);
	//GetObjectFrom(manager->groupProjectile);
	//GetObjectFrom(manager->groupEffect);
}

// --- lấy danh sách đối tượng trong quadtree có thể va chạm
// --- Dùng world chạy hàm này, chỉ dành cho CollisionGroup
void GroupObject::GetCollisionQuadtree()
{		// tên đầy đủ của hàm này phải là: Re-get Possible "active-Object with Collision" in Quadtree

	this->objects.clear();
	number = 0;
	manager->rootGONode->SendObjectTo(this);
}
