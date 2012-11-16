#pragma once

#include <vector>
#include <string>

struct MissionInfo
{
	int name;
	int mapwidth;
	int mapheight;
	int info;
	int players;
};

struct PlayerInfo
{
	int name;
	int briefing;
};


struct UnitInstance
{
	std::string type;
	int player;
	int id;
	int pos[2];
};

struct BuildingInfo
{
	int name;
	int player;
	int id;
	int pos[2];
	std::string type;
	int crystals;
};

struct EventInfo
{
	int id;
	std::string type;
	int player;
	int title;
	int message;
	int pos[2];
	std::string trigger;
	int ttime;
};

struct LevelInfo
{
	MissionInfo mission;

	std::vector<int> map_raw;

	std::vector<PlayerInfo> player;
	std::vector<UnitInstance> unit;
	std::vector<BuildingInfo> building;
	std::vector<EventInfo> event;
};

LevelInfo LoadLevelInfoFile(const char* filename);