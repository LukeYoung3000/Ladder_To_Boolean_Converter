// Ladder_To_Boolean_Converter.cpp : Defines the entry point for the application.
//

#include "Ladder_To_Boolean_Converter.h"
#include "LadderLogicObjects.h"
#include "LadderLogicConfig.h"
#include "TruthTableObjects.h"

using namespace std;

int main()
{

	// ----- Get Ladder Logic Data In Block Format -----



	// ----- Optimise Ladder Logic -----
	//
	// Remove all single column inputs (They are basically straight AND sections)
	// Remove all isolated parallel inputs (They are basically straight OR sections)
	// Create boolean statement for all removed inputs


	// ----- Convert Remaining Ladder Logic Into A Truth Table -----


	// ----- Convert Truth Table Into Boolean Statement -----
	//
	// Combine in optimised boolean statement from optimised section


	// ----- Run Tests On Boolean Statement Vs Ladder Logic -----
	//
	// Make sure all input combinations arrive at the same result



	LadderLogicConfig ll_config;
	ll_config.LoadConfig("test.xml");



/*		

			LadderLogicEquation test_equation

				 A         B         D       Output
			|---| |---|---|\|---*---| |---|---( )---|
					  |                   |
					  |    C              |
					  |---| |---*---------|

*/



	LadderLogicEquation test_equation;
	test_equation.blocks_.push_back(LadderLogicBlock("A", 0, 0, LadderLogicBlock::Type::NO, vector<uint16_t> {0, 1}));
	test_equation.blocks_.push_back(LadderLogicBlock("B", 0, 1, LadderLogicBlock::Type::NC, vector<uint16_t> {0}));
	test_equation.blocks_.push_back(LadderLogicBlock("D", 0, 2, LadderLogicBlock::Type::NO, vector<uint16_t> {0}));
	test_equation.blocks_.push_back(LadderLogicBlock("C", 1, 1, LadderLogicBlock::Type::NO, vector<uint16_t> {1}));
	test_equation.blocks_.push_back(LadderLogicBlock(" ", 1, 2, LadderLogicBlock::Type::SHORT, vector<uint16_t> {0}));
	test_equation.blocks_.push_back(LadderLogicBlock("Output", 0, 3, LadderLogicBlock::Type::COIL, vector<uint16_t> {}));
	test_equation.inputs_.push_back("A");
	test_equation.inputs_.push_back("B");
	test_equation.inputs_.push_back("C");
	test_equation.inputs_.push_back("D");




	/* Print Blocks
	* yo
	for (int i = 0; i < test_equation.blocks_.size(); i++)
	{
		cout << "----- Start -----" << endl;
		cout << test_equation.blocks_[i].name_ << endl;
		cout << test_equation.blocks_[i].row_ << endl;
		cout << test_equation.blocks_[i].col_ << endl;
		for (int j = 0; j < test_equation.blocks_[i].next_row_.size(); j++)
			cout << test_equation.blocks_[i].next_row_[j] << ",";
		cout << endl;
		cout << "----- End -----" << endl << endl;
	}
	*/


	
	LadderLogicTruthTableGenerator llttg;
	llttg.ladder_logic_equations_.push_back(test_equation);

	cout << "Generate Truth Tables: Start" << endl;
	llttg.GenerateTruthTables();

	for (int i = 0; i < llttg.truth_tables_[0].output_states_.size(); i++)
	{
		cout << llttg.truth_tables_[0].output_states_[i] << " <- ";
		cout << llttg.truth_tables_[0].input_states_[i] << endl;
	}

	cout << "Generate Truth Tables: End" << endl;



	cout << "Generate Boolean:" << endl;
	llttg.GenerateBooleanStatements();

	cout << "Boolean:" << endl;
	if (llttg.boolean_equations_.size() > 0)
		cout << llttg.boolean_equations_[0] << endl;








	return 0;
}
