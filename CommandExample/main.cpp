#include <string_view>
#include <iostream>
#include <cstdint>
#include <string>
#include <array>
#include <functional>
#include <optional>
#include <cassert>
#include <algorithm>

#include "Commands.h"


// Note: using string_view whereever possible to avoid unnecessary string copying, but accept the thought
// overhead required to use this efficiency doesn't suit everyone.

constexpr std::string_view EmptyStringView{ "" };

template<std::size_t SegmentCount>
std::optional<std::array<std::string_view, SegmentCount>> SplitIntoSegments(const std::string_view pText, const char pDelimiter);

void ShowHelp(const std::string_view& pHelpText);


// All commands should have "input:settings" for my scheme. To simply make
// it simple to handle commands which don't have all three params, for instance
// a command with only settings would appear as "::value,value,value"...
int main(const int argc, const char** argv)
{
	// The default position is to help the user
	bool noValidCommand{ true };
	for (auto index{ 1 }; index < argc; ++index)
	{
		std::string cliString{ argv[index] };
		std::transform(cliString.begin(), cliString.end(), cliString.begin(), [](char c) -> char{ return static_cast<char>(::tolower(c)); });
		if (IsValidCommand(cliString) && index < argc)
		{
			noValidCommand = false;

			// The integer index from the string, via the enum
			const auto commandIndex = CommandIndex(cliString);
			
			// Move onto the next string
			++index;
			std::string_view nextString{ argv[index] };
			std::string outputString{ "" };

			const auto segments = SplitIntoSegments<2>(nextString, ':');	// Expected 2 pieces to our input CLI
			if (segments.has_value())
			{
				if (!CommandFunctions[commandIndex](segments.value()[0], outputString, segments.value()[1]))
				{
					ShowHelp(HelpStrings[commandIndex]);
				}
				else
				{
					// Do we want to do anything with the output?... Like pipe it, or network it, or whatever?
					std::cout << "ok:" << outputString;
				}
			}
		}		
	}

	if (noValidCommand)
	{
		std::cout << "Overall help here, possible commands, tell them the format of the \"<input>:<output>:<settings>\" strings we use?" << std::endl;
	}
}



// ----------- misc service functions - Abandon hope all yea who enter here
template<std::size_t SegmentCount>
static std::optional<std::array<std::string_view, SegmentCount>> SplitIntoSegments(const std::string_view pText, const char pDelimiter)
{
	std::optional<std::array<std::string_view, SegmentCount>> result;

	if (!pText.empty())
	{
		std::array<std::string_view, SegmentCount> pieces;

		bool allFound{ true };
		size_t start{ 0 };
		for (std::size_t index{ 0 }; index < SegmentCount; ++index)
		{
			// Last segment is just "to the end"
			if (index == SegmentCount - 1)
			{
				pieces[index] = { pText.data() + start, pText.size() - start };
			}
			else
			{
				const auto found{ pText.find_first_of(pDelimiter, start) };
				if (found != std::string_view::npos)
				{
					pieces[index] = { pText.data() + start, found - start };
					start = found + 1;
				}
				else
				{
					allFound = false;
					break;
				}
			}
		}

		if (allFound)
		{
			result.emplace(std::move(pieces));
		}
	}

	return result;
}

void ShowHelp(const std::string_view& pHelpText)
{
	std::cout << pHelpText << std::endl;
}
