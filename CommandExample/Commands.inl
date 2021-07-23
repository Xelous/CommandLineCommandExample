constexpr std::array<std::string_view, cMaxCommandIndex> CommandStrings =
{
	"commandalpha",		// By convention I'm lower-casing these here and I'll lower-case the input
	"commandbeta"
	// Add additional command strings here
};

// The help strings for each command - these can all be in an inl file out of sight
static constexpr std::array<std::string_view, cMaxCommandIndex> HelpStrings =
{
	// Sneaky use of pre-formatted strings here ;-)
R"(
CommandAlpha        Used to invoke command Alpha.
                    No Parameters.
                    No Input or output required.
)",

R"(
CommandBeta         Used to invoke command Beta.
                    Also No Parameters.
                    Also No Input or output required.
)"
// Add additional help strings here
};

// The command function signature here has to match the "RunCommand" funcion per class instance
using CommandFunctionSignature = std::function<bool(const std::string_view&, std::string&, const std::string_view&)>;

// Command macro define
#define CommandFunctionDeclaration(CommandClassType)																\
	[&](const std::string_view& pInput, std::string& pOutput, const std::string_view& pSettings)					\
	{																												\
		CommandClassType commandClass;																				\
		return commandClass.RunCommand(pInput, pOutput, pSettings);													\
	}

// Add additional Command Class includes here
#include "ImplementedCommands/CommandA.h"
#include "ImplementedCommands/CommandB.h"

static std::array<CommandFunctionSignature, cMaxCommandIndex> CommandFunctions =
{
	CommandFunctionDeclaration(CommandA),
	CommandFunctionDeclaration(CommandB)
	// Add a more command functions
};