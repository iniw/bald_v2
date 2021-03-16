#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>
#include <fstream>

#include "../client_class.h"
#include "../data_map.h"

struct netvars {

	bool setup( );

	void store( std::string_view name, recv_table* table, size_t offset = 0 );

	size_t find_in_datamap( data_map* map, const size_t hash );

	std::unordered_map< size_t, size_t > m_offsets;

private:

	std::ofstream m_file;

};

inline netvars g_netvars;