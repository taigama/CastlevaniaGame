#ifndef _OLOADER_H_
#define _OLOADER_H_

#include "ThamSo.h"
#include <string>
#include <map>

class OLoader
{
private:
	World* manager;
	LPD3DXSPRITE spriteHandler;

	// giữ các object, dùng để dọn bộ nhớ sau khi dùng xong
	GameObject** GOHolders;
	int objectHolderPost;
	// thật ra thoát chương trình thì sẽ tự dọn hết bộ nhớ rồi
	// mình thích thì mình làm thôi

	// dùng cho việc load lvl
	int* initParam;

	GroupObject* groupEnemy;
	OTreeNode* rootGONode;

	// 2 cái mapping
	std::map<int, GameObject*>mappedObjects;
	std::map<int, OTreeNode*>mappedOTreeNodes;
public:
	OLoader(int _lvl, LPD3DXSPRITE _SpriteHandler, World *_manager);
	~OLoader();

	// cập nhật các thông tin đầu tiên của map
	void Reload();

	// đọc file GO
	void ReadObjectListFromFile(const char* filename);

	// đọc file QuadTree
	void ReadOQuadTreeFromFile(const char* filename);
	// bỏ các gameobject vào node từ phần chuỗi còn lại
	void MappingObject(GroupObject* theGroup, std::string &theLine);
	// ghép các node lại với nhau
	void LinkTheOTreeNodes();



	// chuyển chuỗi thành mảng số
	int* ParseFromString(std::string &line, int limit);

	// tạo object từ mảng số
	GameObject* CreateGameObject(int* parameters);

	// cụ thể hoá từng vấn đề tạo object
	Enemy* CreateEnemy(int* parameters);
	Destructible* CreateDestructible(int* parameters);
	Ground* CreateGround(int* parameters);
	Stair* CreateStair(int* parameters);
	Zone* CreateZone(int* parameters);

};

#endif