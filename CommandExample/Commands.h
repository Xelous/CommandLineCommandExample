#pragma once

// This header contans the global registration and types to support
// command registration.
//
// To add command simply add it to the "PossibleCommands" enum in this header.
//
// Then Add to the CommandStrings and HelpStrings in the Commands.inl
// file.
//
// Finally add the include for your command derived class and add it's invoke
// to the list of functions available in the mapping "CommandFunctions"

#include <cstdint>
#include <array>
#include <string_view>
#include <functional>
#include <string>

// -------------------- - The Enum
enum class PossibleCommands
{
	CommandA,
	CommandB,
	// Add additional commands here
	MaxCommandCount
};

// Constant to count commands
constexpr const uint16_t cMaxCommandIndex{ static_cast<uint16_t>(PossibleCommands::MaxCommandCount) };

bool IsValidCommand(const std::string_view pCommand);

uint16_t CommandIndex(const std::string_view pCommand);

#include "Commands.inl"