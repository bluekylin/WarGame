#include "LevelInfo.h"

#include <fstream>
#include <string>
using std::string;
using std::ifstream;

#include <boost/xpressive/xpressive.hpp>
using namespace boost::xpressive;

LevelInfo LoadLevelInfoFile(const char* filename)
{
	LevelInfo InitedLevelInfo;

	ifstream File(filename);
	string OneLine;

	sregex titlerex = '[' >> *space >> (s1= +set[ _w | '-' ]) >> *space >> ']';
    sregex contentrex = (s1= +_w) >> *space >> '=' >> *space >> (s2= +~_s);
	sregex digit = +_d;
	sregex posrex = (+_d) >> '/' >> (+_d);
    smatch what;

	int state;
	
	while (!File.eof())
	{
		getline(File, OneLine);
		if ( regex_match(OneLine, what, titlerex) )
		{
			if ( !what.str(1).compare("mission") )
			{
				state = 0;
			}
			else if ( !what.str(1).compare("map-raw") )
			{
				state = 1;
			}
			else if ( !what.str(1).compare("player") )
			{
				state = 2;
				InitedLevelInfo.player.push_back(PlayerInfo());
			}
			else if ( !what.str(1).compare("unit") )
			{
				state = 3;
				InitedLevelInfo.unit.push_back(UnitInstance());
			}
			else if ( !what.str(1).compare("building") )
			{
				state = 4;
				InitedLevelInfo.building.push_back(BuildingInfo());
			}
			else if ( !what.str(1).compare("event") )
			{
				state = 5;
				InitedLevelInfo.event.push_back(EventInfo());
			}
		}
		else if ( regex_match(OneLine, what, contentrex) )
		{
			switch (state)
			{
			case 0:
				//mission:
				if ( !what.str(1).compare("name") )
				{
					InitedLevelInfo.mission.name = atoi(what.str(2).c_str());
				}
				else if ( !what.str(1).compare("mapwidth") )
				{
					InitedLevelInfo.mission.mapwidth = atoi(what.str(2).c_str());
				}
				else if ( !what.str(1).compare("mapheight") )
				{
					InitedLevelInfo.mission.mapheight = atoi(what.str(2).c_str());
				}
				else if ( !what.str(1).compare("info") )
				{
					InitedLevelInfo.mission.info = atoi(what.str(2).c_str());
				}
				else if ( !what.str(1).compare("players") )
				{
					InitedLevelInfo.mission.players = atoi(what.str(2).c_str());
				}
				break;
			case 2:
				{
					//player
					int index = InitedLevelInfo.player.size()-1;
					if ( !what.str(1).compare("name") )
					{
						InitedLevelInfo.player[index].name = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("briefing") )
					{
						InitedLevelInfo.player[index].briefing = atoi(what.str(2).c_str());
					}
				}
				break;
			case 3:
				{
					//unit
					int index = InitedLevelInfo.unit.size()-1;
					if ( !what.str(1).compare("type") )
					{
						InitedLevelInfo.unit[index].type = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("player") )
					{
						InitedLevelInfo.unit[index].player = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("id") )
					{
						InitedLevelInfo.unit[index].id = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("pos") )
					{
						smatch digitwhat;
						if ( regex_match(what.str(2), digitwhat, posrex) )
						{
							InitedLevelInfo.unit[index].pos[0] = atoi(digitwhat.str(1).c_str());
							InitedLevelInfo.unit[index].pos[1] = atoi(digitwhat.str(2).c_str());
						}					
					}
				}
				break;
			case 4:
				{
					//building
					int index = InitedLevelInfo.building.size()-1;
					if ( !what.str(1).compare("name") )
					{
						InitedLevelInfo.building[index].name = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("player") )
					{
						InitedLevelInfo.building[index].player = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("id") )
					{
						InitedLevelInfo.building[index].id = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("pos") )
					{
						smatch digitwhat;
						if ( regex_match(what.str(2), digitwhat, posrex) )
						{
							InitedLevelInfo.building[index].pos[0] = atoi(digitwhat.str(1).c_str());
							InitedLevelInfo.building[index].pos[1] = atoi(digitwhat.str(2).c_str());
						}					
					}
					else if ( !what.str(1).compare("type") )
					{
						InitedLevelInfo.building[index].type = what.str(2);
					}
					else if ( !what.str(1).compare("crystals") )
					{
						InitedLevelInfo.building[index].crystals = atoi(what.str(2).c_str());
					}
				}
				break;
			case 5:
				{
					//event
					int index = InitedLevelInfo.event.size()-1;
					if ( !what.str(1).compare("id") )
					{
						InitedLevelInfo.event[index].id = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("type") )
					{
						InitedLevelInfo.event[index].type = std::move(what.str(2));
					}
					else if ( !what.str(1).compare("player") )
					{
						InitedLevelInfo.event[index].player = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("message") )
					{
						InitedLevelInfo.event[index].message = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("pos") )
					{
						smatch digitwhat;
						if ( regex_match(what.str(2), digitwhat, posrex) )
						{
							InitedLevelInfo.event[index].pos[0] = atoi(digitwhat.str(1).c_str());
							InitedLevelInfo.event[index].pos[1] = atoi(digitwhat.str(2).c_str());
						}					
					}
					else if ( !what.str(1).compare("trigger") )
					{
						InitedLevelInfo.event[index].trigger = what.str(2);
					}
					else if ( !what.str(1).compare("ttime") )
					{
						InitedLevelInfo.event[index].ttime = atoi(what.str(2).c_str());
					}
				}
				break;

			default:
				break;
			}
		}
		else if ( state == 1 )
		{
			// map-raw
			sregex_token_iterator begin( OneLine.begin(), OneLine.end(), digit ), end;
			for ( ; begin != end; ++begin )
			{
				InitedLevelInfo.map_raw.push_back(atoi(begin->str().c_str()));
			}
		}
	}

	return InitedLevelInfo;
}
