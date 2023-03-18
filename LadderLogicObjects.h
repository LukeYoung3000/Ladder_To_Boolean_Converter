#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>


/*		Example:



			Ladder Logic Equation

				 A         B         D       Output
			|---| |---|---|\|---*---| |---|---( )---|
					  |                   |
					  |    C              |
					  |---| |---*---------|




			Truth Table Representation

			|----------------Example Table--------------|
			|-----------|----------Input Names----------|
			|	Ouput	|	A	|	B	|	C	|	D	|
		0	|	0		|	0	|	0	|	0	|	0	|
		1	|	0		|	0	|	0	|	0	|	1	|
		2	|	0		|	0	|	0	|	1	|	0	|
		3	|	0		|	0	|	0	|	1	|	1	|
		4	|	0		|	0	|	1	|	0	|	0	|
		5	|	0		|	0	|	1	|	0	|	1	|
		6	|	0		|	0	|	1	|	1	|	0	|
		7	|	0		|	0	|	1	|	1	|	1	|
		8	|	0		|	1	|	0	|	0	|	0	|
		9	|	1		|	1	|	0	|	0	|	1	|	->	A & !B & !C & D
		10	|	1		|	1	|	0	|	1	|	0	|	->	A & !B & C & !D
		11	|	1		|	1	|	0	|	1	|	1	|	->	A & !B & C & D
		12	|	0		|	1	|	1	|	0	|	0	|
		13	|	0		|	1	|	1	|	0	|	1	|
		14	|	1		|	1	|	1	|	1	|	0	|	->	A & B & C & !D
		15	|	1		|	1	|	1	|	1	|	1	|	->	A & B & C & D




		Boolean Equation

		Output = (A & !B & !C & D) | (A & !B & C & !D) | (A & !B & C & D) | (A & B & C & !D) | (A & B & C & D)

	*/





class LadderLogicConfig
{

};

class LadderLogicBlock
{
public:

	std::string name_;
	uint16_t row_;
	uint16_t col_;

	enum class Type
	{
		SHORT = 0,
		OPEN = 1,
		NO = 2,		// Normally Open
		NC = 3,		// Normally Closed
		COIL = 4
	};
	Type type_;

	std::vector<uint16_t> next_row_;	// Connected Blocks In "col_ + 1" 

	LadderLogicBlock(std::string name, uint16_t row, uint16_t col, Type type, std::vector<uint16_t> next_row)
	{
		name_ = name; row_ = row; col_ = col; type_ = type; next_row_ = next_row;
	}




	bool is_path_closed = false;
	bool CalculatePath(bool state)
	{
		if (type_ == Type::SHORT)
			is_path_closed = true;

		else if (type_ == Type::OPEN)
			is_path_closed = false;

		else if (type_ == Type::NO)
			is_path_closed = state;

		else if (type_ == Type::NC)
			is_path_closed = !state;

		else if (type_ == Type::COIL)
			is_path_closed = is_path_closed;

		else
		{
			// Error
		}

		return is_path_closed;

	}

	bool is_checked_ahead = false;

};

class LadderLogicEquation
{
public:

	// Configuration
	std::vector<LadderLogicBlock> blocks_;

	// Derived
	std::vector<std::string> inputs_;

	LadderLogicEquation()
	{

	}

	bool ExecuteLogic(std::vector<bool> &input_states)
	{

		if (input_states.size() != inputs_.size())
		{
			// Error
		}

		// Create Input Name To State Mapping
		std::map<std::string, bool> input_states_;
		for (int i = 0; i < inputs_.size(); i++)
			input_states_[inputs_[i]] = input_states[i];

		// Reset No Path Found Check On All Blacks
		// Calculate If Block Path Is Closed Or Open
		for (auto block = blocks_.begin(); block != blocks_.end(); ++block)
		{
			block->is_checked_ahead = false;

			if (input_states_.count(block->name_))
				block->CalculatePath(input_states_[block->name_]);
		}
			

		// Traverse The Block From Left To Right
		// Checking All Paths Along The Way

		std::stack<LadderLogicBlock*> process;

		// Add all first column blocks to the stack
		for (auto block = blocks_.rbegin(); block != blocks_.rend(); ++block)
			if (block->col_ == 0)
				process.push(&(*block));


		bool result = false;
		while (!process.empty())
		{

			// Check if we are at the coil/output of the ladder equation
			if (process.top()->type_ == LadderLogicBlock::Type::COIL)
			{
				process.top()->is_path_closed = true;
				result = true;
				break;
			}

			// Can we jump to the next block?
			// i.e Is the path closed/permissive?
			if (process.top()->is_path_closed == false)
			{
				process.top()->is_checked_ahead = true;
				process.pop();
				continue;
			}

			// Look for the next block to jump to
			LadderLogicBlock* next_block = GetNextBlock(process.top());

			// No next block available
			if (next_block == nullptr)
			{
				process.top()->is_checked_ahead = true;
				process.pop();
				continue;
			}
			
			// Add next block to process stack
			process.push(next_block);
		}

		return result;
	}

	LadderLogicBlock* GetNextBlock(LadderLogicBlock* current_block)
	{
		// Complete this function

		return nullptr;
	}

};











class TruthTable
{

public:

	std::vector<std::string> input_names_;
	std::vector<uint32_t> input_states_;
	std::vector<bool> output_states_;

	bool GetStateForName(std::string name, uint32_t row_number)
	{
		uint32_t column_number = 0;
		for (uint32_t i = 0; i < input_names_.size(); i++)
		{
			if (name != input_names_[i])
				continue;

			column_number = i;
			break;
		}

		return bool((input_states_[row_number] >> column_number) & 0x1);
	}

};

class LadderLogicTruthTableGenerator
{

	std::vector<LadderLogicEquation> ladder_logic_equations_;
	std::vector<TruthTable> truth_tables_;
	std::vector<std::string> boolean_equations_;

	bool GenerateTruthTables()
	{

		for (auto itr = ladder_logic_equations_.begin(); itr != ladder_logic_equations_.end(); ++itr)
		{
			LadderLogicEquation lle = *itr;
			TruthTable tt;

			// Test All Input Combinations To LadderLogicEquation
			// Store Results In TruthTable
			tt.input_names_ = lle.inputs_;
			uint32_t num_input_combinations = 2 ^ tt.input_names_.size() - 1;
			for (uint32_t i = 0; i < num_input_combinations; i++)
			{
				// To Do: Add code to time how log it takes to execute all combinations of input states

				// Execute LadderLogicEquation For This Current Set Of Input States
				std::vector<bool> input_states;
				for (uint32_t j = 0; j < lle.inputs_.size(); j++)
					input_states.push_back((i >> j) & 0x1);
				bool lle_result = lle.ExecuteLogic(input_states);

				// Add Data To "TruthTable"
				tt.input_states_.push_back(i);
				tt.output_states_.push_back(lle_result);
			}

			truth_tables_.push_back(tt);
		}
	}


	bool GenerateBooleanStatements()
	{

		for (auto tt = truth_tables_.begin(); tt != truth_tables_.end(); ++tt)
		{

			std::string boolean_equation_string = "";
			for (uint32_t i = 0; tt->output_states_.size(); i++)
			{
				if (tt->output_states_[i] == false)
					continue;

				// Generate Partial Boolean Equation String
				std::string pbes = "(";
				for (auto in = tt->input_names_.begin(); in != tt->input_names_.end(); ++in)
				{
					if (tt->GetStateForName(*in, i) == false)
						pbes.append("!");
					pbes.append(*in + " & ");
				}

				pbes = pbes.substr(0, pbes.length() - 3); // Remove Last " & "
				pbes.append(")");

				boolean_equation_string.append(pbes + " | ");
			}

			boolean_equation_string = boolean_equation_string.substr(0, boolean_equation_string.length() - 3); // Remove Last " + "
			boolean_equations_.push_back(boolean_equation_string);
		}

		return true;
	}

};

