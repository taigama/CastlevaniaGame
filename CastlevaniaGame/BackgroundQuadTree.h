#ifndef _BACKGROUNDQUADTREE_H_
#define _BACKGROUNDQUADTREE_H_


#include "ThamSo.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <list>

using namespace std;

class BackgroundQuadTree
{
public:
	
	BackgroundQuadTree *tl, *tr, *bl, *br;		//4 node con cua not hien tai
	int nodeID;
	RECT *rect;									//xac dinh hinh vuong bao quanh node
	//list <int> tileIDs;					//danh sach ID, do qua nang nen chuyen qua dung int*
	int *tile_IDs;								//danh sach cac ID cua tilemap
	int n;										//so luong phan tu cua danh sach cac ID

	BackgroundQuadTree();
	~BackgroundQuadTree();

	
	//ham set node hien tai lam node goc
	void setRootNode(map<int, BackgroundQuadTree*> &Nodes); 

	//ham tao mot node moi tu 1 chuoi
	BackgroundQuadTree *createNodeFromString(string line);

	//ham tao cay tu file
	void loadTreeFromFile(char* filename);

	//ham ket noi node hien tai voi not con cua no
	void ConnectToTheChildNodes(map<int, BackgroundQuadTree*> &Nodes);

	//ham xet node co va cham voi viewport hay khong
	bool IsIntersectVP();

	//ham de lay ra danh sach cac ID tilemap co va cham voi viewport
	void ListObjectInViewPort(int *ObjectIDs, int &size);


};
#endif // !_BACKGROUNDQUADTREE_H_

