#include <string>
#include <iostream>

//#include "LadderLogicObjects.h"
#include "libs/pugixml/src/pugixml.hpp"


struct Block
{
	std::string name_;
	uint16_t row_;
	uint16_t col_;
	std::string type_;

	std::vector<uint16_t> next_row_;	// Connected Blocks In "col_ + 1" 
};

struct Equation
{
	std::vector<Block> blocks_;
};





class LadderLogicConfig
{
public:

	std::vector<Equation> equations;

	bool LoadConfig(std::string config_path)
	{

		pugi::xml_document xml;
		pugi::xml_parse_result result = xml.load_file(config_path.c_str());

		for (pugi::xml_node eq = xml.child("equations").child("equation"); eq; eq = eq.next_sibling("equation"))
		{
			Equation equation;

			for (pugi::xml_node blk = eq.child("block"); blk; blk = blk.next_sibling("block"))
			{
				Block block;
				block.name_ = blk.attribute("name").value();
				block.row_ = blk.attribute("row").as_int();
				block.col_ = blk.attribute("col").as_int();
				block.type_ = blk.attribute("type").value();

				equation.blocks_.push_back(block);
			}
			equations.push_back(equation);
		}
			
		// std::cout << xml.child("yo").attribute("hey").value() << std::endl;
		//std::cout << "Block: " << "Name: " << blk.attribute("name").value() << " Row: " << blk.attribute("row").as_int() << std::endl;





		return true;
	}

};