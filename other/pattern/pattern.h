#pragma once

#include <windows.h>
#include <string>

#include "../memory/address.h"

struct pattern {

	address find( std::string_view module_name, std::string_view pattern );

};

inline pattern g_pattern;