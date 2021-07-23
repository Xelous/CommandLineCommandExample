#pragma once

#include "../CommandBase.h"

class CommandA final : public BaseAPI
{
public:
	bool RunCommand(const std::string_view& pInput, std::string& pOutput, const std::string_view& pSettings) override;
};
