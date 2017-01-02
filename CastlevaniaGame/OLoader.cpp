#include "OLoader.h"

#include "GameObject.h"

#include "Enemy.h"
#include "Bone.h"
#include "Destructible.h"

//#include "Ground.h"
#include "ColliderBlock.h"
#include "Brick.h"
#include "Bar.h"

#include "Stair.h"

//#include "Zone.h"
#include "GateWay.h"
#include "StandItem.h"
#include "DeadZone.h"
#include "Spawner.h"
#include "BattleBoss.h"
#include "Grinder.h"
#include "Door.h"
#include "Gate.h"

#include "World.h"
#include "MainGame.h"
#include "GroupObject.h"
#include "OQuadTree.h"
#include <fstream>


// nhận lvl, đọc file tương ứng lvl
OLoader::OLoader(int _lvl, LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	// mặc định phải có để tạo object
	spriteHandler = _SpriteHandler;
	manager = _manager;

	// khởi tạo thằng Holder
	GOHolders = new GameObject*[500];
	objectHolderPost = 0;

	// khởi tạo tree và group enemy
	groupEnemy = new GroupObject(manager);
	rootGONode = NULL;

	// cái này để cho an toàn trong quá trình Init các object
	manager->groupEnemy = this->groupEnemy;



	// dùng string để load file
	std::string prefix = "Resources\\Maps\\map" + std::to_string(_lvl);
	std::string postfixGO = "_GO.txt";
	std::string postfixGOQT = "_GO_quadtree.txt";

	// đọc file
	ReadObjectListFromFile((prefix + postfixGO).c_str());
	ReadOQuadTreeFromFile((prefix + postfixGOQT).c_str());
	LinkTheOTreeNodes();

	manager->rootGONode = this->rootGONode;
}

OLoader::~OLoader()
{
	for (int i = 0; i < 100; i++)
	{
		delete GOHolders[i];
	}
	delete GOHolders;
}

// cập nhật lại các thông tin đầu tiên của map
void OLoader::Reload()
{
	// gán các thông số đầu game
	manager->Simon->postX = initParam[0];
	manager->Simon->postY = initParam[1];

	manager->Simon->checkpointX = initParam[0];
	manager->Simon->checkpointY = initParam[1];
	//manager->Simon->Destroy();
	manager->Simon->P++;
	manager->Simon->isClimbing = false;
	manager->Simon->isHitted = false;
	manager->Simon->isJump = false;

	Sprite::cameraXLeft = initParam[2];
	Sprite::cameraX = Sprite::cameraXLeft;
	Sprite::cameraXRight = initParam[3];
	Sprite::cameraY = initParam[4];

	// cập nhật các con trỏ groupEnemy & rootGONode
	manager->groupEnemy = this->groupEnemy;
	manager->rootGONode = this->rootGONode;

	auto it = mappedObjects.find(1000);
	if (it != mappedObjects.end())
	{
		//element found;
		manager->boss = ((Enemy*)mappedObjects[1000]);
	}

}

// ============= đọc file ==============
void OLoader::ReadObjectListFromFile(const char* filename)
{
	// dùng để đọc từng dòng trong file
	std::string lineStr;
	// dùng để nhận mảng số sau khi xử lý chuỗi
	int* parameters = NULL;


	// mở file
	std::fstream pFile;
	pFile.open(filename, std::fstream::in);

	// đọc dòng đầu tiên trong file
	if (pFile.good())
	{
		std::getline(pFile, lineStr);
		// nếu không tìm thấy "END" => tiếp tục
		if (lineStr.find("END") == std::string::npos)
		{
			// biến đổi chuỗi thành mảng số
			initParam = ParseFromString(lineStr, 12);
			// dùng trong Reload()
		}
	}

	while (pFile.good())
	{
		std::getline(pFile, lineStr);
		// nếu tìm thấy "END" => thôi
		if (lineStr.find("END") != std::string::npos)
		{
			// hết danh sách
			break;
		}

		// ----- update K_1.7.5
		// nếu tìm thấy "//" 
		if (lineStr.find("//") != std::string::npos)
		{
			// bỏ đi đoạn "//" về sau
			lineStr = lineStr.substr(0, lineStr.find("//"));
		}

		// nếu hàng này không có gì => skip
		if (lineStr == "")
		{
			continue;
		}//-------------------

		 // biến đổi chuỗi thành mảng số
		parameters = ParseFromString(lineStr, 12);

		// tạo object từ mảng số
		GOHolders[objectHolderPost] = CreateGameObject(parameters);

		// nếu như tạo object thành công thì map và tiếp tục (tạo object mới)
		if (GOHolders[objectHolderPost] != NULL)
		{
			// mapping object
			mappedObjects[parameters[0]] = GOHolders[objectHolderPost];

			// tăng cái này giống tăng i thôi
			objectHolderPost++;
		}
	}

	pFile.close();
}

void OLoader::ReadOQuadTreeFromFile(const char* filename)
{
	// dùng để đọc từng dòng trong file
	std::string lineStr;
	// dùng để nhận mảng số sau khi xử lý chuỗi
	int* parameters = NULL;


	// mở file
	std::fstream pFile;
	pFile.open(filename, std::fstream::in);

	while (pFile.good())
	{
		std::getline(pFile, lineStr);
		// nếu tìm thấy "END" => thôi
		if (lineStr.find("END") != std::string::npos)
		{
			// hết danh sách
			break;
		}

		// biến đổi chuỗi thành mảng số
		parameters = ParseFromString(lineStr, 5);

		mappedOTreeNodes[parameters[0]] = new OTreeNode(parameters[0], parameters[1], parameters[2], parameters[3], parameters[4]);
		MappingObject(mappedOTreeNodes[parameters[0]]->group, lineStr);
	}

	//	đọc dữ liệu sau END		// Enemy
	while (pFile.good())
	{

		std::getline(pFile, lineStr);
		// nếu tìm thấy "END" => thôi
		if (lineStr.find("END") != std::string::npos)
		{
			// hết danh sách
			break;
		}

		// đưa chỗ này vào group Enemy
		MappingObject(groupEnemy, lineStr);
	}

	pFile.close();

}

// bỏ các gameobject vào node từ phần chuỗi còn lại
void OLoader::MappingObject(GroupObject* theGroup, std::string &theLine)
{
	size_t postTab = 0;
	std::string subStr;	// cắt từng "số" ra rồi chuyển thành số
	int tempInt;

	map<int, GameObject*>::iterator it;

	while (1)
	{
		// bỏ đi phần đã được chuyển thành số rồi
		theLine = theLine.substr(postTab);
		// phần còn lại nếu là "\t" thôi thì không cần tiếp tục nữa
		if (theLine == "\t")
			break;

		// tìm kiếm vị trí "\t" vị trí >0 , trong phần chuỗi còn lại
		postTab = theLine.find("\t", 1);
		// copy đoạn chuỗi cho đến \t
		subStr = theLine.substr(0, postTab);
		// lấy đoạn chuỗi vừa có được đem chuyển thành số
		tempInt = stoi(subStr);

		// thêm object có id "tempInt" vào node

		it = mappedObjects.find(tempInt);
		if (it != mappedObjects.end())
		{
			//element found;
			theGroup->AddObject(mappedObjects[tempInt]);
		}
	}
}

// ----- 
// link các node lại với nhau

void OLoader::LinkTheOTreeNodes()
{
	// temporary
	int tempParrentId;
	int tempOffsetId;

	for (auto i = mappedOTreeNodes.begin(); i != mappedOTreeNodes.end(); i++)
	{
		// first tức là int, second tức là OTreeNode*
		if (i->first == 1)
		{
			rootGONode = i->second;
			continue;
		}
		// tính ra id của cha và offset của con
		tempParrentId = i->second->GetParrentId();
		tempOffsetId = i->second->GetOffsetId();

		// rồi lấy id cha trỏ vào
		mappedOTreeNodes[tempParrentId]->subNodes[tempOffsetId - 1] = i->second;
		// vậy là subNodes này sẽ không còn NULL nữa
	}
}




// biến chuỗi thành 1 mảng số
int* OLoader::ParseFromString(std::string &line, int limit)
{
	size_t postTab = 0;
	std::string subStr;	// cắt từng "số" ra rồi chuyển thành số
	int i = 0;
	int* parameters = new int[limit];


	while (1)
	{
		// bỏ đi phần đã được chuyển thành số rồi
		line = line.substr(postTab);
		// phần còn lại nếu là "\t" thôi thì không cần tiếp tục nữa
		if (line == "\t")
			break;

		// vượt qua giới hạn đọc số rồi thì không cần tiếp tục
		if (i >= limit)
		{
			break;
		}

		// tìm kiếm vị trí "\t" vị trí >0 , trong phần chuỗi còn lại
		postTab = line.find("\t", 1);
		// copy đoạn chuỗi cho đến \t
		subStr = line.substr(0, postTab);
		// lấy đoạn chuỗi vừa có được đem chuyển thành số
		parameters[i] = stoi(subStr);

		// tiếp tục
		i++;
	}

	// phòng ngừa hậu hoạ
	for (; i < limit; i++)
		parameters[i] = 0;

	return parameters;
}//

 // --------- tạo object dựa vào mảng số --------------
GameObject* OLoader::CreateGameObject(int* parameters)
{
	GameObject* gameObject = NULL;
	switch (parameters[1] / 100)
	{
	case ENEMY_TYPE:
		gameObject = CreateEnemy(parameters);
		break;
	case DESTRUCTIBLE_TYPE:
		gameObject = CreateDestructible(parameters);
		break;
	case GROUND_TYPE:
		gameObject = CreateGround(parameters);
		break;
	case STAIR_TYPE:
		gameObject = CreateStair(parameters);
		break;
	case ZONE_TYPE:
		gameObject = CreateZone(parameters);
		break;
	default:
		break;
	}

	return gameObject;
}

// tạo enemy dựa vào mảng số
Enemy* OLoader::CreateEnemy(int* parameters)
{
	Enemy* newEnemy = NULL;

	switch (parameters[1] % 100)
	{
		// map1 enemies
	case REDBAT:
		newEnemy = new RedBat(spriteHandler, manager);
		break;
	case GHOUL:
		newEnemy = new Ghoul(spriteHandler, manager);
		break;
	case FISH:
		newEnemy = new Fish(spriteHandler, manager);
		break;
	case PANTHER:
		newEnemy = new Panther(spriteHandler, manager);
		break;

		// boss enemies
	case VAMBAT:
		newEnemy = new VamBat(spriteHandler, manager);
		break;
	case MEDUSA:
		newEnemy = new Medusa(spriteHandler, manager);
		break;

		// map2 enemies
	case BLUEBAT:
		newEnemy = new BlueBat(spriteHandler, manager);
		break;
	case KNIGHT:
		newEnemy = new Knight(spriteHandler, manager);
		((Knight*)newEnemy)->Init(parameters[2], parameters[3], parameters[4], parameters[5]);
		break;
		/*case HEAD:
		newEnemy = new Head(spriteHandler, manager);
		break;
		case GHOST:
		newEnemy = new Ghost(spriteHandler, manager);
		break;*/
	case BONE:
		newEnemy = new Bone(spriteHandler, manager);
		break;
	default:
		return NULL;
		break;

	}

	// nếu vị trí == 0 thì enemy sẽ không active
	if ((parameters[2] == 0) && (parameters[3] == 0))
	{
		newEnemy->isActive = false;
	}
	else
	{
		newEnemy->Init(parameters[2], parameters[3]);
	}

	//// ----------------- test 
	//if (newEnemy->enemyType == VAMBAT)
	//	newEnemy->isActive = false;
	//if (newEnemy->enemyType == MEDUSA)
	//	newEnemy->isActive = false;
	//// --------------------

	return newEnemy;
}

Destructible* OLoader::CreateDestructible(int* parameters)
{
	Destructible* newDestructible = NULL;

	newDestructible = new Destructible(spriteHandler, manager, parameters[1] % 100);
	newDestructible->Init(parameters[2], parameters[3], parameters[4]);

	return newDestructible;
}

Ground* OLoader::CreateGround(int* parameters)
{
	Ground* newGround = NULL;

	switch (parameters[1] % 100)
	{
		// khối block bình thường, đứng lên dc, tuỳ chỉnh kích thước
	case GROUND_BLOCK:
		newGround = new ColliderBlock(spriteHandler, manager);
		break;
		// các cục gạch có thể bị đập bể & rớt item
	case GROUND_BRICK1:
	case GROUND_BRICK2:
	case GROUND_BRICK3:
	case GROUND_BRICK4:
		newGround = new Brick(spriteHandler, manager, parameters[1] % 100);
		break;
		// 1 thanh ground đi qua đi lại
	case GROUND_BAR:
		newGround = new Bar(spriteHandler, manager);
		break;
	default:
		break;
	}

	if (newGround != NULL)
		newGround->Init(parameters[2], parameters[3], parameters[4], parameters[5]);

	return newGround;
}

Stair* OLoader::CreateStair(int* parameters)
{
	Stair* newStair = NULL;

	newStair = new Stair(spriteHandler, manager, parameters[1] % 100);
	newStair->Init(parameters[2], parameters[3]);

	return newStair;
}

Zone* OLoader::CreateZone(int* parameters)
{
	Zone* newZone = NULL;

	switch (parameters[1] % 100)
	{
		// đụng vào đây là dịch chuyển
	case ZONE_GATEWAY:
		newZone = new GateWay(spriteHandler, manager);
		break;
		// chuyên thả item
	case ZONE_STAND:
	case ZONE_CROUCH:
		newZone = new StandItem(spriteHandler, manager);
		break;
	case ZONE_SPAWNER:
		newZone = new Spawner(spriteHandler, manager);
		break;
	case ZONE_DEAD:
		newZone = new DeadZone(spriteHandler, manager, parameters[1] % 100);
		break;
	case ZONE_GRINDER:
		newZone = new Grinder(spriteHandler, manager);
		break;
	case ZONE_BATTLEBOSS:
		newZone = new BattleBoss(spriteHandler, manager);
		break;
	case ZONE_DOOR:
		newZone = new Door(spriteHandler, manager);
		break;
	case ZONE_GATE:
		newZone = new Gate(spriteHandler, manager);
		break;
	default:
		break;
	}

	// tổng cộng Zone cần đến 11 paramaters
	if (newZone != NULL)
		newZone->Init(parameters[2], parameters[3], parameters[4], parameters[5]
			, parameters[6], parameters[7]
			, parameters[8], parameters[9], parameters[10]);


	return newZone;
}