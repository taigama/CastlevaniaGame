#pragma once
#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <ddraw.h>
#include "Sprite.h"
using namespace std;

#define TILE_SIZE   	64		//Mỗi title 32*32
#define WORLD_SIZEX 	178  //Cả map gồm 178*28 titles
#define WORLD_SIZEY 	28

class TileMap
{
public:
	Sprite* source;
	TileMap() {}

	~TileMap() {}

	void ReadMatrixFromFile(char* filename,
		vector<vector<int>>* map1Matrix,
		const string& splitchar);

	void LoadTiledMap(vector<vector<int>> map1Matrix);
};

#endif