#include "CommandB.h"

bool CommandB::RunCommand([[maybe_unused]] const std::string_view& pInput, [[maybe_unused]] std::string& pOutput, [[maybe_unused]] const std::string_view& pSettings)
{	
	pOutput = "I just ran command B";
	return true;
}