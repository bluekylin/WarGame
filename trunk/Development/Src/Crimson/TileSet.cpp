#include "TileSet.h"
#include <fstream>
#include <string>
using std::string;
using std::ifstream;

#include <boost/xpressive/xpressive.hpp>
using namespace boost::xpressive;

TileSet InitTileUnitsFromIni(const char* filename)
{
	TileSet InitedTileSet;
	TileUnit OneTileUnit;

	ifstream File(filename);
	string OneLine;

    sregex rex = (s1= +_w) >> *space >> '=' >> *space >> (s2= +~_s);
    smatch what;
	
	while (!File.eof())
	{
		getline(File, OneLine);
		if ( regex_match(OneLine, what, rex) )
		{
			if ( !what.str(1).compare("terrain") )
			{
				OneTileUnit.TerrainType = what[2];
			}
			else if ( !what.str(1).compare("icon") )
			{
				OneTileUnit.IconIndex = atoi(what.str(2).c_str());
			}
			else if ( !what.str(1).compare("move") )
			{
				OneTileUnit.Move = atoi(what.str(2).c_str());
			}
			else if ( !what.str(1).compare("color") )
			{
				InitedTileSet.emplace_back(OneTileUnit);
			}
		}
	}

	return InitedTileSet;
}

UnitSet InitUnitSetFromUSRCFile(const char* filename)
{
	UnitSet InitedUnitSet;
	UnitInfo* OneUnit = nullptr;

	ifstream File(filename);
	string OneLine;

    sregex titlerex = '[' >> *space >> (s1= +set[ _w | '-' ]) >> *space >> ']';
	sregex contentrex = (s1= +set[ _w | '-' | '(' | ')' ]) >> *space >> '=' >> *space >> (s2= +~_s);
	//power(air) = 30 (2-6)
	sregex powerpattern = "power(" >> (s1 = +_w ) >> ')' >> *space >> '=' >> *space >> (s2 = +_d ) >> *space >> !( '(' >> *space >> ( +_d ) >> *space >> '-' >> *space >> (+_d) >> *space >> ')' );
    smatch what;

	int state;
	while (!File.eof())
	{
		getline(File, OneLine);
		if ( regex_match(OneLine, what, titlerex) )
		{
			if ( !what.str(1).compare("unitset") )
			{
				state = 0;
			}
			else if ( !what.str(1).compare("unit") )
			{
				InitedUnitSet.unit.push_back(UnitInfo());
				OneUnit = &InitedUnitSet.unit[InitedUnitSet.unit.size()-1];
				state = 1;
			}
		}
		else if ( regex_match(OneLine, what, contentrex) )
		{
			switch (state)
			{
			case 0:
				{
					if ( !what.str(1).compare("name") )
					{
						InitedUnitSet.name = what.str(2);
					}
					else if ( !what.str(1).compare("icons") )
					{
						InitedUnitSet.icons = what.str(2);
					}
				}
				break;
			case 1:
				if ( OneUnit != nullptr )
				{
					if ( !what.str(1).compare("name(en)") )
					{
						OneUnit->name = what.str(2);
					}
					else if ( !what.str(1).compare("type") )
					{
						// to do!
					}
					else if ( !what.str(1).compare("icon") )
					{
						OneUnit->icon = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("terrain") )
					{
						//OneUnit->name = what.str(2);
					}
					else if ( !what.str(1).compare("armour") )
					{
						OneUnit->armour = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("speed") )
					{
						OneUnit->speed = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("price") )
					{
						OneUnit->price = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("weight") )
					{
						OneUnit->weight = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("portrait") )
					{
						OneUnit->portrait = what.str(2);
					}
					else if ( !what.str(1).compare("transslots") )
					{
						OneUnit->transslots = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("transminweight") )
					{
						OneUnit->transminweight = atoi(what.str(2).c_str());
					}
					else if ( !what.str(1).compare("transmaxweight") )
					{
						OneUnit->transmaxweight = atoi(what.str(2).c_str());
					}
				}
				else
				{
					assert(false);
				}
			default:
				break;
			}
		}
		else if ( regex_match(OneLine, what, powerpattern) )
		{
			if ( !what.str(1).compare("ground") )
			{
			}
			else if ( !what.str(1).compare("ship") )
			{
			}
			else if ( !what.str(1).compare("air") )
			{
			}
		}
	}

	return InitedUnitSet;
}

//#include <boost/config/warning_disable.hpp>
//#include <boost/spirit/include/qi.hpp>
//#include <boost/spirit/include/phoenix_core.hpp>
//#include <boost/spirit/include/phoenix_operator.hpp>
//#include <boost/spirit/include/phoenix_fusion.hpp>
//#include <boost/spirit/include/phoenix_stl.hpp>
//#include <boost/spirit/include/phoenix_object.hpp>
//#include <boost/fusion/include/adapt_struct.hpp>
//#include <boost/variant/recursive_variant.hpp>
//#include <boost/foreach.hpp>
//
//namespace fusion = boost::fusion;
//namespace phoenix = boost::phoenix;
//namespace qi = boost::spirit::qi;
//namespace ascii = boost::spirit::ascii;
//
//BOOST_FUSION_ADAPT_STRUCT(
//	TileUnit,
//	(std::string, TerrainType)
//	(int, IconIndex)
//	(int, Move)
//	(int_array_3, Color) 
//)
//
//template <typename Iterator>
//struct mini_tileunit_grammar
//	: qi::grammar<Iterator, TileUnit(), qi::locals<std::string>, ascii::space_type>
//{
//	
//        mini_tileunit_grammar()
//          : mini_tileunit_grammar::base_type(tileunit, "tileunit")
//        {
//            using qi::lit;
//			using qi::int_;
//            using qi::lexeme;
//            using qi::on_error;
//            using qi::fail;
//            using ascii::char_;
//            using ascii::string;
//            using namespace qi::labels;
//
//            using phoenix::construct;
//            using phoenix::val;
//
//			start_tag = "[tile]";
//			text = lexeme[+(char_)];
//			terrain = 
//					"terrain" 
//				>>	lit('=') 
//				>>	text		[_val = _1]
//			;
//			icon = 
//					"icon" 
//				>>	lit('=') 
//				>>	int_		[_val = _1]
//			;
//			move = 
//					"move" 
//				>>	lit('=') 
//				>>	int_		[_val = _1]
//			;
//			color = 
//					"color" 
//				>> lit('=')
//				>> (int_ % ',')	[_val = _1]
//			;
//            
//			tileunit = 
//					start_tag
//				>> terrain
//				>> icon
//				>> move
//				>> color
//			;
//
//            start_tag.name("start_tag");
//            text.name("text");
//            terrain.name("terrain");
//            icon.name("icon");
//            move.name("move");
//			color.name("color");
//
//            on_error<fail>
//            (
//                tileunit
//              , std::cout
//                    << val("Error! Expecting ")
//                    << _4                               // what failed?
//                    << val(" here: \"")
//                    << construct<std::string>(_3, _2)   // iterators to error-pos, end
//                    << val("\"")
//                    << std::endl
//            );
//        }
//
//        qi::rule<Iterator, TileUnit(), qi::locals<std::string>, ascii::space_type> tileunit;
//        qi::rule<Iterator, std::string(), ascii::space_type> start_tag;
//		qi::rule<Iterator, std::string(), ascii::space_type> text;
//		qi::rule<Iterator, std::string(), ascii::space_type> terrain;
//        qi::rule<Iterator, int, ascii::space_type> icon;
//		qi::rule<Iterator, int, ascii::space_type> move;
//		qi::rule<Iterator, int_array_3, ascii::space_type> color;
//};
//
//#include <fstream>
//
//TileSet InitTileUnitsFromIni(const char* filename)
//{
//	TileSet InitedTileSet;
//
//	std::ifstream in(filename, std::ios_base::in);
//
//	if (!in)
//	{
//		std::cerr << "Error: Could not open input file: "
//			<< filename << std::endl;
//	}
//
//	std::string storage; // We will read the contents here.
//	in.unsetf(std::ios::skipws); // No white space skipping!
//	std::copy(
//		std::istream_iterator<char>(in),
//		std::istream_iterator<char>(),
//		std::back_inserter(storage));
//
//	typedef mini_tileunit_grammar<std::string::const_iterator> tileunit_grammar;
//	tileunit_grammar tileunit_; // Our grammar
//	TileUnit ast; // Our tree
//
//	using boost::spirit::ascii::space;
//	std::string::const_iterator iter = storage.begin();
//	std::string::const_iterator end = storage.end();
//	bool r = phrase_parse(iter, end, tileunit_, space, ast);
//
//	if (r && iter == end)
//	{
//		std::cout << "-------------------------\n";
//		std::cout << "Parsing succeeded\n";
//		std::cout << "-------------------------\n";
//	}
//	else
//	{
//		std::cout << "-------------------------\n";
//		std::cout << "Parsing failed\n";
//		std::cout << "-------------------------\n";
//	}
//
//
//	return InitedTileSet;
//}