#include <string>
#include <vector>

/*		Example: Test



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

		Output =	(A & !B & !C & D) | (A & !B & C & !D) | (A & !B & C & D) | (A & B & C & !D) | (A & B & C & D)

					(A & !B & !C & D) | (A & !B & C & !D) | (A & !B & C & D) | (A & B & C & !D) | (A & B & C & D)
	*/






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

	LadderLogicBlock(std::string name, uint16_t row, uint16_t col, Type type, std::vector<uint16_t> next_row);
	bool CalculatePath(bool state);

	bool is_path_closed = false;

	bool is_checked_ahead = false;

};

class LadderLogicEquation
{
public:

	// Configuration
	std::vector<LadderLogicBlock> blocks_;

	// Derived
	std::vector<std::string> inputs_;

	LadderLogicEquation();
	bool ExecuteLogic(std::vector<bool>& input_states);
	LadderLogicBlock* GetNextUncheckedBlock(LadderLogicBlock* current_block);

};