#ifndef __TILE_SET_H__
#define __TILE_SET_H__

#include <vector>
#include <string>
#include <boost/array.hpp>

typedef boost::array<unsigned int, 4> int_array_3;

struct TileUnit
{
	std::string TerrainType;
	int IconIndex;
	int Move;
	int_array_3 Color;
};

typedef std::vector<TileUnit> TileSet;

enum EUnitType
{
	U_GROUND		=	0x00000001,	/* a unit can only have one of U_GROUND, U_SHIP */
	U_SHIP			=	0x00000002,	/* and U_AIR set; for amphibian units you must */
	U_AIR			=	0x00000004,	/* always set U_GROUND! */

	U_CONQUER		=	0x00000010,	/* unit can take over enemy buildings */
	U_SLOW			=	0x00000020,	/* can only fight OR move on one turn */
	U_TRANSPORT		=	0x00000040,	/* can carry other units, */
                                        /* note: transporters may NEVER have U_CONQUER set! */
	U_MINE			=	0x00000080,	/* can be cleared/reused by minesweepers */
	U_MEDIC			=	0x00000100,	/* can repair other units */
	U_MINESWEEPER	=	0x00000400,

	U_FLOATING		=	0x01000000,	/* for units which can move on both land and water */
									/* (i.e. U_SHIP|U_GROUND) this flag must be set */
									/* when the unit moves on water; always true for ships */
	//U_DUMMY		0x02000000	/* used for units generated for replays */
	//U_BUSY		0x04000000	/* used by computer player */
	//U_DONE		0x08000000
	//U_MOVED		0x10000000	/* unit moved this turn */
	//U_ATTACKED	0x20000000	/* unit initiated combat this turn */
	//U_SHELTERED	0x40000000	/* unit is currently inside a building/transporter */
	//U_DESTROYED	0x80000000
};

enum ETerrainType
{
	TT_ROAD				= 0x0001,
	TT_PLAINS			= 0x0002,
	TT_FOREST			= 0x0004,
	TT_SWAMP			= 0x0008,
	TT_MOUNTAINS		= 0x0010,
	TT_WATER_SHALLOW	= 0x0020,
	TT_WATER_DEEP		= 0x0040,
	TT_BARRICADES		= 0x0080,
	TT_RAILS			= 0x0100,
	TT_WATER			= 0x0200,
	TT_RESTRICTED       = 0x0400,  /* for the default set, this means Infantry and aircraft only */
	TT_TRENCHES         = 0x0800,
	TT_ENTRANCE			= 0x4000,  /* entrance to a building */
};

struct UnitInfo
{
	std::string name;
	int type;
	int icon;
	int terrain;
	int armour;
	int speed;
	int price;
	int weight;
	int power_ground;
	std::pair<int, int> power_ground_range;
	int power_ship;
	std::pair<int, int> power_ship_range;
	int power_air;
	std::pair<int, int> power_air_range;
	std::string portrait;
	int transslots;
	int transminweight;
	int transmaxweight;
};

struct UnitSet
{
	std::string name;
	std::string icons;

	std::vector<UnitInfo> unit;
};


TileSet InitTileUnitsFromIni(const char* filename);
UnitSet InitUnitSetFromUSRCFile(const char* filename);
#endif