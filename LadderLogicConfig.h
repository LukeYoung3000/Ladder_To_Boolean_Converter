#include <string>
#include <iostream>
#include <vector>

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
				block.name_ = blk.child("name").text().get();
				block.row_ = blk.child("row").text().as_int(-1);
				block.col_ = blk.child("col").text().as_int(-1);
				block.type_ = blk.child("type").text().get();
				for (pugi::xml_node next_row = blk.child("next_row"); next_row; next_row = next_row.next_sibling("next_row"))
					block.next_row_.push_back(next_row.text().as_int(-1));

				equation.blocks_.push_back(block);
			}
			equations.push_back(equation);
		}
			
		// std::cout << xml.child("yo").attribute("hey").value() << std::endl;
		//std::cout << "Block: " << "Name: " << blk.attribute("name").value() << " Row: " << blk.attribute("row").as_int() << std::endl;





		return true;
	}

};