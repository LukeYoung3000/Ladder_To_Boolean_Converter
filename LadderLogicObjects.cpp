#include "LadderLogicObjects.h"

#include <iostream>
#include <stack>
#include <map>

using namespace std;



// LadderLogicBlock ------------------------------------

LadderLogicBlock::LadderLogicBlock(std::string name, uint16_t row, uint16_t col, LadderLogicBlock::Type type, std::vector<uint16_t> next_row)
{
	name_ = name; row_ = row; col_ = col; type_ = type; next_row_ = next_row;
}

bool LadderLogicBlock::CalculatePath(bool state)
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






// LadderLogicEquation ------------------------------------

LadderLogicEquation::LadderLogicEquation()
{

}

bool LadderLogicEquation::ExecuteLogic(std::vector<bool>& input_states)
{

	if (input_states.size() != inputs_.size())
	{
		// Error
		cout << "Error 1 " << endl;
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
		else
			block->CalculatePath(false);
	}


	// Traverse The Blocks From Left To Right
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
		LadderLogicBlock* next_block = GetNextUncheckedBlock(process.top());

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

LadderLogicBlock* LadderLogicEquation::GetNextUncheckedBlock(LadderLogicBlock* current_block)
{
	// Loop Through All Next Connected Blocks In "next_row_"
	for (int i = 0; i < current_block->next_row_.size(); i++)
	{
		uint16_t next_col = current_block->col_ + 1;
		uint16_t next_row = current_block->next_row_[i];

		for (int j = 0; j < blocks_.size(); j++)
		{
			if (blocks_[j].col_ == next_col && \
				blocks_[j].row_ == next_row && \
				blocks_[j].is_checked_ahead == false)
			{
				return &blocks_[j];
			}
		}
	}

	return nullptr;
}