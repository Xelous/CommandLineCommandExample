#include "Commands.h"

#include <cassert>

bool IsValidCommand(const std::string_view pCommand)
{
	for (const auto& commandString : CommandStrings)
	{
		if (commandString.compare(pCommand) == 0)
		{
			return true;
		}
	}
	return false;
}

uint16_t CommandIndex(const std::string_view pCommand)
{
	assert(IsValidCommand(pCommand));
	for (uint16_t index{ 0 }; index < static_cast<uint16_t>(PossibleCommands::MaxCommandCount); ++index)
	{
		if (pCommand.compare(CommandStrings[index]) == 0)
		{
			return index;
		}
	}
	// Must return something, but we should only come into here with a validated string
	return UINT16_MAX;
}