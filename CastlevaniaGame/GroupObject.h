// ----- update K_1.5

#ifndef _GROUPOBJECT_H_
#define _GROUPOBJECT_H_

#include "ThamSo.h"
#include <vector>

class GroupObject
{
public:
	// các biến 
	World* manager;
	std::vector<GameObject*> objects;
	int number;

	// constructor & destructor
	GroupObject(World *manager);
	~GroupObject();

	// ---- update K_1.5
	// thêm đối tượng & xoá danh sách
	void AddObject(GameObject* theObject);
	void GetObjectFrom(GroupObject* theGroup);

	void Update(const float &_DeltaTime);
	void UpdateActive(const float &_DeltaTime);
	void Render();
	void RenderActive();
	// ---------
	void Clear();


	// --- lấy danh sách đối tượng có thể va chạm
	void GetCollisionSpecial();
	void GetCollisionQuadtree();
	// --- Dùng world chạy hàm này, chỉ dành cho CollisionGroup
};



#endif
