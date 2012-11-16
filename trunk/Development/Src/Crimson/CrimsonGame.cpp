#include "CrimsonGame.h"

#include "CHexMap.h";

USING_NS_CC;

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

#include "TileSet.h"
#include "LevelInfo.h"
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	//CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
	//									"CloseNormal.png",
	//									"CloseSelected.png",
	//									this,
	//									menu_selector(HelloWorld::menuCloseCallback) );
	//pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

	// create menu, it's an autorelease object
	//CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
	//pMenu->setPosition( CCPointZero );
	//this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	TileSet tileSet = std::move(InitTileUnitsFromIni("..\\..\\..\\Engine\\Content\\crimson_data\\config\\default.tsrc"));
	UnitSet unitSet = std::move(InitUnitSetFromUSRCFile("..\\..\\..\\Engine\\Content\\crimson_data\\config\\default.usrc"));
	LevelInfo levelInfo = std::move(LoadLevelInfoFile("..\\..\\..\\Engine\\Content\\crimson_data\\levels\\Tutorial1.src"));
	CHexMapTilesetInfo testinfo;
	testinfo.m_sName = "test";
	testinfo.m_sSourceImage = "..\\..\\..\\Engine\\Content\\crimson_data\\terrain\\CFTiles.png";
	testinfo.m_tTileUnitSize = CCSizeMake(32, 28);
	testinfo.m_tImageSize = CCSizeMake(768, 448);
	testinfo.m_tTileSetSize = CCSizeMake(768/32, 448/28);


	CHexMap *child = CHexMap::CreateHexMap();
	addChild((CCNode*)child, 0, 0);

	unsigned int map_raw[] = 
	{
		203,181,30,139,135,31,117,117,117,117,76,117,117,118,30,30,177,177,77,30,
		30,176,30,136,55,232,117,75,117,75,117,118,120,119,121,30,74,30,181,30,
		30,176,146,30,32,225,74,117,117,117,120,119,121,37,117,117,30,30,180,181,
		145,188,77,178,224,37,117,120,118,121,117,38,31,30,117,117,30,30,55,179,
		30,190,196,78,36,33,76,117,119,120,118,121,34,117,117,117,30,30,182,56,
		79,176,82,82,78,77,31,311,338,117,119,118,117,117,76,80,30,30,180,181,
		81,180,81,84,83,85,315,38,31,35,120,119,121,82,80,78,30,30,30,176,
		82,83,177,223,86,311,312,38,38,76,117,117,81,82,81,79,30,30,30,176,
		84,86,85,311,304,223,30,31,34,30,117,117,82,81,81,30,77,80,30,179,
		82,315,311,30,30,31,203,181,30,30,117,120,118,121,82,77,30,178,178,30,
		82,309,30,30,30,32,36,202,31,30,30,117,119,118,82,79,182,78,30,30,
		80,309,30,30,30,30,37,176,30,30,74,117,120,119,121,77,176,30,30,30,
		77,312,30,98,104,90,30,180,38,34,34,35,117,117,117,38,176,5,26,28,
		311,30,30,88,30,71,90,99,177,177,38,30,117,117,117,178,185,177,29,30,
		30,30,30,96,70,73,72,87,30,30,177,183,184,183,207,146,145,30,177,177
	};
	//{
	//79,79,78,80,80,71,80,80,78,309,79,79,79,79,79,79,79,309,79,79,79,88,78,78,87,79,79,
	//79,78,78,80,70,73,72,80,78,303,79,79,79,79,79,79,79,309,79,80,79,96,78,78,87,79,79,
	//79,80,80,71,80,80,80,79,78,312,79,79,79,80,80,80,80,313,80,80,98,78,78,97,95,79,80,
	//78,80,70,73,72,80,79,79,315,80,80,80,79,70,71,72,80,80,314,80,88,78,78,87,79,315,311,
	//78,80,80,71,80,80,79,79,309,80,80,79,79,71,73,79,79,79,309,80,88,78,78,87,79,309,79,
	//79,80,70,73,72,80,79,79,303,80,80,79,70,73,72,70,71,72,309,80,94,89,78,95,79,309,79,
	//80,84,83,85,80,79,79,79,309,80,80,79,79,80,80,80,73,80,313,314,80,83,101,80,80,309,79,
	//80,80,86,71,80,80,79,79,313,314,80,79,79,70,71,72,80,80,80,303,84,86,85,80,80,312,79,
	//80,83,70,73,72,80,79,79,79,305,78,79,79,80,73,80,80,80,80,309,80,80,80,80,315,79,79,
	//84,86,85,80,80,79,79,80,79,309,79,80,79,71,80,84,83,85,80,305,80,80,80,302,312,80,79,
	//80,70,71,72,80,79,79,80,80,309,79,80,70,73,72,80,86,71,80,313,80,302,311,79,79,83,80,
	//80,80,73,80,80,79,79,80,80,305,78,79,80,80,80,71,70,73,72,80,319,79,79,80,84,86,85,
	//79,71,80,80,79,79,79,80,79,312,79,80,80,80,70,73,73,80,80,79,309,79,79,79,80,80,80,
	//70,73,72,80,79,79,79,80,315,79,80,70,71,72,80,80,80,71,80,80,313,301,79,79,79,79,79,
	//65,71,80,80,79,79,79,80,309,79,80,79,73,80,80,71,70,73,72,80,79,30,314,79,79,79,79,
	//70,73,72,83,80,80,79,80,309,79,79,79,80,80,70,73,72,80,80,80,80,80,309,79,79,79,79,
	//66,71,84,86,85,80,79,80,309,77,79,80,80,71,80,80,80,79,80,84,83,85,309,79,79,80,80,
	//70,73,72,80,80,79,79,80,303,78,79,30,70,73,72,71,80,77,80,80,86,80,309,78,80,84,83,
	//80,80,80,80,80,80,80,311,312,79,31,132,33,30,70,73,72,32,30,32,78,79,305,79,80,80,86,
	//80,84,83,85,80,80,315,80,80,132,30,36,32,30,36,31,30,31,132,37,32,79,313,314,79,79,80,
	//80,80,86,71,80,80,309,84,83,85,31,31,32,77,30,77,33,33,31,30,31,30,79,313,79,79,79,
	//79,80,70,73,72,80,309,80,86,78,77,71,80,78,80,80,78,70,71,72,30,78,79,79,314,79,80,
	//79,80,80,71,80,80,303,79,80,80,70,73,72,30,30,30,30,30,73,70,71,72,80,78,309,78,84,
	//79,80,70,73,72,80,309,80,80,71,80,80,78,30,30,18,30,30,30,80,73,80,80,78,305,79,80,
	//79,79,80,80,80,315,312,80,70,73,72,80,80,79,30,30,30,79,78,80,80,80,79,79,309,79,79
	//};

	
	child->addLayer(&testinfo, levelInfo.mission.mapwidth, levelInfo.mission.mapheight, levelInfo.map_raw, tileSet);
	return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
