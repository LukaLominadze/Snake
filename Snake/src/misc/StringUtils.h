#pragma once

#include <Nigozi.h>

namespace StringUtils
{
	// From Walnut - https://github.com/StudioCherno/Walnut
	std::vector<std::string> SplitString(const std::string_view string, const std::string_view& delimiters);
	std::vector<std::string> SplitString(const std::string_view string, const char delimiter);
}

