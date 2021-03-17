#pragma once

#include <windows.h>
#include <string>

#include "../memory/address.h"

struct pattern {

	address find( address module_base, std::string_view pattern );

};

inline pattern g_pattern;