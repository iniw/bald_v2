#pragma once

#include <windows.h>
#include <string>

#include "../memory/address.h"
#include "../utils/utils.h"

struct pattern {

	address find( address module_base, std::string_view pattern );

	address find( section_info section, std::string_view pattern );

	bool find( address module_base, std::string_view pattern, address result );

private:

	std::vector< size_t > pattern_to_byte( std::string_view pattern );

};

inline pattern g_pattern;