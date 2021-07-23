#pragma once

#include <string_view>
#include <string>

// Whatever commands defined wherever, but we're using inheritance to let the compiler help
// affirm new commands are valid for use, even though this introduces a requirement to allocate
// rather than using a static function later (because the command class is empty, the compiler
// will not generate any code beyond the stub entry for the class, it becomes as though it is
// a static function - class elision under /O3+).

/// <summary>
/// Using a base API with virtuals just helps everyone implementing a command get it right.... and if we 
/// assume we're interested in chaining commands together, then a common interface, no matter what the
/// individual command does is a good start.
/// </summary>
class BaseAPI
{
public:
	virtual bool RunCommand(const std::string_view& pInput, std::string& pOutput, const std::string_view& pSettings) = 0;
};
