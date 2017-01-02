#pragma once
#ifndef __TILEMAPS_H__
#define __TILEMAPS_H__

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <ddraw.h>
#include "Sprite.h"
using namespace std;

	// không dùng vì vấn đề hướng đối tượng
//#define TILE_SIZE   	64		//Mỗi title 64*64

	// đối với map1
//#define WORLD_SIZEX 	90  //Cả map gồm 90*14 titles
//#define WORLD_SIZEY 	14

class TileMaps
{
public:
	// ---- update K_1.6

	// truyền vào lúc khởi tạo
	int tileSize; 

	// thay đổi giá trị sau khi load matrix
	int worldSizeX;
	int worldSizeY;

	// ------

	Sprite* source;
	vector<vector<int>> map1Matrix;
	TileMaps(char* filename, LPD3DXSPRITE _SpriteHandler, int tileSize, int tileCount, int numWidth);

	~TileMaps();

	void ReadMatrixFromFile(char* filename, const string& splitchar);

	//void LoadTiledMap(map<int,int> tileIDs);
	void LoadTiledMap(int *tileIDs, int size);
};

#endif