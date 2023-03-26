
#include <vector>
#include <string>
#include <cmath>
#include <set>

using namespace std;

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

public:

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
			uint32_t num_input_combinations = pow(2, tt.input_names_.size());
			cout << "Num Combinations: " << num_input_combinations << endl;

			for (uint32_t i = 0; i < num_input_combinations; i++)
			{
				// To Do: Add code to time how log it takes to execute all combinations of input states

				// Execute LadderLogicEquation For This Current Set Of Input States
				std::vector<bool> input_states;
				for (uint32_t j = 0; j < lle.inputs_.size(); j++)
					input_states.push_back((bool)((i >> j) & (uint32_t)1));
				bool lle_result = lle.ExecuteLogic(input_states);

				// Add Data To "TruthTable"
				tt.input_states_.push_back(i);
				tt.output_states_.push_back(lle_result);
			}

			truth_tables_.push_back(tt);
		}

		return true;
	}


	bool GenerateBooleanStatements()
	{

		for (auto tt = truth_tables_.begin(); tt != truth_tables_.end(); ++tt)
		{

			std::string boolean_equation_string = "";
			for (uint32_t i = 0; i < tt->output_states_.size(); i++)
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
