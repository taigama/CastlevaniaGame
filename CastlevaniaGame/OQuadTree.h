// ------ update K_1.5

#ifndef _OQUADTREE_H_
#define _OQUADTREE_H_
// Quadtree Ojbects

#include "ThamSo.h"

class OTreeNode
{
public:
	int id;	// id của node
			// === !!! === NODE GỐC ID LÀ 1 === !!! ===
			// map editor C# thích thế


			// location & size
	int left;
	int bottom;

	int width;
	int height;

	// 4 subnodes
	OTreeNode** subNodes;

	// Group giữ các Object
	GroupObject* group;
	// Group này không có MANAGER, chỉ dùng để chứa object ------------ !!!
	// không được thao tác group với manager dưới mọi hình thức

	OTreeNode();
	OTreeNode(int _Id, int _XLeft, int _YBottom, int _Width, int _Height);
	~OTreeNode();

	// kiểm tra xem có giao với "Camera" không
	bool IsIntersectVP();

	// dựa vào id của con -> tính ra id của cha
	int GetParrentId();
	int GetOffsetId();

	// ném object trong phạm vi camera vào destination group
	void SendObjectTo(GroupObject *destinationGroup);
};

#endif