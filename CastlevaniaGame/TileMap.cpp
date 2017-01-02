#include "TileMap.h"
#include "MainGame.h"
void TileMap::ReadMatrixFromFile(char* filename,
	vector<vector<int>>* map1Matrix,
	const string& splitchar)
{

	string      line;
	string      strnum;
	ifstream	in(filename);

	map1Matrix->clear(); //Đảm bảo ma trận rỗng

	while (getline(in, line)) //tách từng dòng ra từ file in
	{
		map1Matrix->push_back(vector<int>()); // thêm 1 vector int vào cuối

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
			map1Matrix->back().push_back(number); //thêm số này vào cuối vector

			strnum.clear();
		}
	}
}



void TileMap::LoadTiledMap(vector<vector<int>> map1Matrix)
{

	for (int h = 0; h <WORLD_SIZEY; h++)
	{
		for (int w = 0; w <WORLD_SIZEX; w++)
		{
			int id = map1Matrix[h][w];
			source->Next(id,id);
			source->Render(w * TILE_SIZE, 896 - h * TILE_SIZE); //896 là chiều cao cả world 
		}

	}
}