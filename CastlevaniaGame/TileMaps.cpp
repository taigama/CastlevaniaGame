#include "TileMaps.h"
#include "MainGame.h"

TileMaps::TileMaps(char* filename, LPD3DXSPRITE _SpriteHandler, int tileSize, int tileCount, int numWidth)
{
	this->tileSize = tileSize;
	source = new Sprite(_SpriteHandler, filename, tileSize, tileSize, tileCount, numWidth);// 64,64,104,14
	map1Matrix.clear();
}

TileMaps::~TileMaps()
{
	if (source != NULL)
		delete source;
	map1Matrix.clear();
}

void TileMaps::ReadMatrixFromFile(char* filename,
	const string& splitchar)
{

	string      line;
	string      strnum;
	ifstream	in(filename);



	while (getline(in, line)) //tách từng dòng ra từ file in
	{
		map1Matrix.push_back(vector<int>()); // thêm 1 vector int vào cuối

		for (string::const_iterator i = line.begin(); i != line.end(); ++i) //iterator dùng để so sánh
		{
			// nếu i không phải kí tự cách, thì bỏ nó vào strnum
			if (splitchar.find(*i) == -1)
			{
				strnum += *i;
				if (i + 1 != line.end()) //Khác end thì vẫn tiếp tục
					continue;
			}

			// nếu strnum vẫn rỗng thì tiếp tục thêm vào (trường hợp 2 dấu cách liên tiếp)
			if (strnum.empty())
				continue;

			// nếu strnum không rỗng thì chuyển kí tự thành số
			int       number;
			istringstream(strnum) >> number;
			map1Matrix.back().push_back(number); //thêm số này vào cuối vector

			strnum.clear();
		}
	}
	worldSizeX = map1Matrix[0].size();
	worldSizeY = map1Matrix.size();
}

void TileMaps::LoadTiledMap(int *tileIDs, int size) 
{
	int h, w; //hang va cot trong ma tran map1Matrix

	//duyet tu dau den cuoi danh sach
	for (int i = 0; i < size; i++)
	{//--------- update K_1.6
		//tim vi tri cua tileID thu i trong map1matrix
		h = tileIDs[i] / worldSizeX;// +2;
		w = tileIDs[i] % worldSizeX;
		int id = map1Matrix[h][w];
		source->Next(id, id);
		source->Render(w * tileSize + 32 , /*896 - (h - 2)*/ (worldSizeY - h) * tileSize - 32) ; //896 là chiều cao cả world
	}//---------------
}

//void TileMaps::LoadTiledMap(map<int, int> tileIDs)
//{
//	int h, w; //hang va cot trong ma tran map1Matrix
//
//	//duyet tu dau den cuoi danh sach
//	for (map<int, int>::iterator i = tileIDs.begin(); i != tileIDs.end(); i++)
//	{
//		//tim vi tri cua tileID thu i trong map1matrix
//		h = tileIDs[i->first] / 90 + 2;
//		w = tileIDs[i->first] % 90;
//		int id = map1Matrix[h][w];
//		source->Next(id, id);
//		source->Render(w * TILE_SIZE , 896 - (h - 2) * TILE_SIZE - 32) ; //896 là chiều cao cả world
//	}
//}